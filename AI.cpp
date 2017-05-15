#include "AI.h"


void AI::AssignTable(minishogi &S0)
{
    S=S0;
}

//tons of bug
vector<minishogi> AI::NextMoves(minishogi &S0,bool who)
{
    minishogi S1=S0;
    minishogi S2;
    vector<minishogi> V;

    int x,y;

    //move
    for(x=0; x<5; x++)
    {
    for(y=0; y<5; y++)
    {
        //choose my chess
        if(S1.IsFriend(x,y,who))
        {
            S1.initialMovable();
            S1.GetMovable(x,y);

            //move search
            for(int Aim=0; Aim<25; Aim++)
            {
                S2=S1;

                //legal move
                if(S2.movable[Aim%5][Aim/5])
                {
                    //capture judge
                    if(S2.IsEnemy(Aim%5,Aim/5,who))
                        S2.Take(Aim%5,Aim/5,who);

                    //pure move
                    S2.PutChess(Aim%5,Aim/5,S1.GetChess(x,y));
                    S2.PutChess(x,y,0);

                    V.push_back(S2);


                    //promote judge
                    if( y==(who ? 4 : 0 ) || (Aim/5)==(who ? 4 : 0 ) )
                    {
                        char ThisChess=S2.GetChess(Aim%5,Aim/5)+who*32;

                        switch(ThisChess)
                        {
                        case 's':
                            S2.PutChess(Aim%5,Aim/5,('t'-who*32));
                            V.push_back(S2);
                            break;

                        case 'c':
                            S2.PutChess(Aim%5,Aim/5,('h'-who*32));
                            V.push_back(S2);
                            break;

                        case 'f':
                            S2.PutChess(Aim%5,Aim/5,('u'-who*32));
                            V.push_back(S2);
                            break;

                        case 'w':
                            S2.PutChess(Aim%5,Aim/5,('x'-who*32));
                            V.push_back(S2);
                            break;

                        default:
                            break;
                        }
                    }

                }

            }
        }
    }
    }

    //for safe
    S1=S0;

    //hit
    for(int index=1; index<6; index++)
    {
        if( (!who && S1.A[index]) || (who && S1.B[index]) )
        {
            for(x=0; x<5; x++)
            {
            for(y=0; y<5; y++)
            {

                //illegal judge
                bool IsLegal=1;

                //2 pawn
                if(index==5)
                {
                    for(int Y=0; Y<5; Y++)
                        if( S1.GetChess(x,Y)==('w'-who*32) )
                            IsLegal=0;

                    //pawn drop last line
                    if( y==(who*4) ) IsLegal=0;
                }

                if(!IsLegal) break;


                //empty judge
                if(S1.GetChess(x,y)==0)
                {
                    S2=S1;
                    S2.hit(index,x,y,who);
                    V.push_back(S2);
                }
            }
            }
        }
    }


    return V;
}

double AI::AlphaCut(minishogi &S0,double Alpha,double Beta,int depth,bool who)
{
    if(depth==0) return S0.TableScore(who);

    double a=Alpha;

    vector<minishogi> V=NextMoves(S0,who);

    for(int i=0; i<V.size(); i++)
    {
        double R=BetaCut(V[i],a,Beta,depth-1,who);

        if(R>a) a=R;
        if(a>=Beta) return a;
    }

    return a;
}

double AI::BetaCut(minishogi &S0,double Alpha,double Beta,int depth,bool who)
{
    if(depth==0) return S0.TableScore(who);

    double b=Beta;

    vector<minishogi> V=NextMoves(S0,!who);

    for(int i=0; i<V.size(); i++)
    {
        double R=AlphaCut(V[i],Alpha,b,depth-1,who);

        if(R<b) b=R;
        if(b<=Alpha) return b;
    }

    return b;
}

minishogi AI::ABSearch(minishogi &S0,double Alpha,double Beta,int depth,bool who)
{

    double a=Alpha;

    minishogi Sg;

    vector<minishogi> V=NextMoves(S0,who);

    for(int i=0; i<V.size(); i++)
    {
        double R=BetaCut(V[i],a,Beta,depth-1,who);

        if(R>a)
        {
            a=R;
            Sg=V[i];
        }
        if(a>=Beta) return Sg;
    }

    return Sg;
}

/**********TD*********/

double AI::AdjustScalar(minishogi S,bool id)
{
    int len;

    for(int i=1; i<10; i++)
        len+=S.Minions[i]*S.Minions[i];

    for(int i=1; i<6; i++)
    len+=(id ? S.B[i]*S.B[i] : S.A[i]*S.A[i] );

    for(int i=0; i<2; i++)
    {
        len+=S.BigChessForce[i]*S.BigChessForce[i];
        len+=S.SpecialForm[i]*S.SpecialForm[i];
    }

    return (learningRATE/sqrt((double)len));
}

void AI::TD1(bool ifWIN,bool id)
{
    minishogi ST=TDbuffer.top();
    TDbuffer.pop();

    ST.LoadHeuristic();

    double VT=ST.TableScore(id);

    minishogi St;
    double Vt;

    while(!TDbuffer.empty() && ifWIN)
    {
        St=TDbuffer.top();
        TDbuffer.pop();
        Vt=St.TableScore(id);

        double Scalar=AdjustScalar(St,id)*((double)ifWIN-Vt);
        St.GetAllStates(id);

        //adjust
        for(int i=1; i<10; i++)
            ST.MinionsWeight[i]+=Scalar*(double)St.Minions[i];

        for(int i=1; i<6; i++)
            ST.HoldWeight[i]+=Scalar*(double)(id ? St.B[i] : St.A[i]);

        for(int i=0; i<2; i++)
        {
            ST.BigChessForceWeight[i]+=Scalar*(double)St.BigChessForce[i];
            ST.SpecialFormWeight[i]+=Scalar*(double)St.SpecialForm[i];
        }
    }

    ST.SaveHeuristic();
}

/*********mcts********/

void AI::Expand(node* leaf)
{
    minishogi S=leaf->GetTable();
    vector<minishogi> next=NextMoves(S,leaf->GetID());

    for(int i=0; i<next.size(); i++)
    {
        node* child=new node;
        child->SetTable(next[i]);
        child->SetID(!leaf->GetID());
        child->FatherNode=leaf;
        leaf->ChildNode.push_back(child);
    }
}

node* AI::Selection(node* root)
{
    if(root->ChildNode.empty())
        Expand(root);

    vector<double> UCT;
    for(int i=0; i<root->ChildNode.size(); i++)
    {
        if( root->ChildNode[i]->TryTimes==0 )
        {
            UCT.push_back(INF);
            break;
        }
        else
        {
            UCT.push_back( (double)root->ChildNode[i]->WinTimes/(double)root->ChildNode[i]->TryTimes
                          +sqrt( 2.0*log( (double)root->TryTimes )/(double)root->ChildNode[i]->TryTimes ) );
        }
    }

    int index=0;
    for(int i=0; i<UCT.size(); i++)
        if(UCT[i]>UCT[index]) index=i;

    return root->ChildNode[index];
}

void AI::Update(node* leaf,bool ifWin)
{
    for(node* i=leaf; i!=NULL; i=i->FatherNode)
    {
        i->TryTimes+=1;
        i->WinTimes+=ifWin;
        ifWin=!ifWin;
    }
}

bool AI::Simulation(node* ThisNode)
{
    srand(time(NULL));

    bool turn=ThisNode->GetID();
    minishogi S=ThisNode->GetTable();
    vector<minishogi> next;

    while(S.win()!=1)
    {
        next=NextMoves(S,turn);
        S=next[rand() % next.size()];
        turn=!turn;
    }

    if( (ThisNode->GetID()&&S.B[0]) || ((!ThisNode->GetID())&&S.A[0]) ) return 1;
    return 0;
}

void AI::PlayOneSequence(node* root)
{
    node* CurrentNode=root;
    bool turn=root->GetID();

    do
    {
        CurrentNode=Selection(CurrentNode);
        turn=!turn;
    }
    while( CurrentNode->ChildNode.size()!=0 );


    bool ifWin=Simulation(CurrentNode);

    Update(CurrentNode,ifWin);
}

minishogi AI::MCTS(minishogi &S0,int Times,bool id)
{
    node* Root=new node;
    Root->SetTable(S0);
    Root->SetID(id);

    int n=Times;
    while(n--) PlayOneSequence(Root);

    int index=0,MaxNi=0;
    for(int i=0; i<Root->ChildNode.size(); i++)
        if( Root->ChildNode[i]->TryTimes > MaxNi )
        {
            index=i;
            MaxNi=Root->ChildNode[i]->TryTimes;
        }

    minishogi S1=Root->ChildNode[index]->GetTable();

    //test
    /*
    printf("root's children:%d\n",Root->ChildNode.size());
    for(int i=0; i<Root->ChildNode.size(); i++)
        printf("child[%d] TryTimes:%d\n",i,Root->ChildNode[i]->TryTimes);
    */

    Root->FreeTree(Root);

    return S1;

}
