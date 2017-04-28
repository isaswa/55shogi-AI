#include "AI.h"


void AI::AssignTable(minishogi &S0)
{
    S=S0;
}

vector<minishogi> AI::NextMoves(minishogi &S0,bool who)
{
    minishogi S2;
    vector<minishogi> V;

    for(int i=0;i<25;i++)
    {
        //hit
        if(S0.GetChess(i/5,i%5)==0)
        {
            if(!who)
            {
                for(int j=0;j<6;j++)
                {
                    if(S0.A[j])
                    {
                        S2=S0;
                        S2.hit(j,i/5,i%5,0);
                        V.push_back(S2);
                    }
                }
            }
            else
            {
                for(int j=0;j<6;j++)
                {
                    if(S0.B[j])
                    {
                        S2=S0;
                        S2.hit(j,i/5,i%5,1);
                        V.push_back(S2);
                    }
                }
            }
        }

        //move
        else if( ((S0.GetChess(i/5,i%5)>97) && (!who) ) ||
                 ((S0.GetChess(i/5,i%5)<97) &&   who  )   )
        {
            S0.initialMovable();
            S0.GetMovable(i/5,i%5);

            for(int j=0;j<25;j++)
            {
                if(S0.movable[j/5][j%5])
                {
                    S2=S0;
                    if(S2.GetChess(j/5,j%5)!=0) S2.Take(j/5,j%5,who);
                    S2.PutChess(j/5 , j%5 , S2.GetChess(i/5,i%5) );
                    S2.PutChess(i/5 , i%5 , 0);

                    V.push_back(S2);
                }
            }
        }
    }

    return V;
}

double AI::AlphaCut(minishogi &S0,double Alpha,double Beta,int depth,bool who)
{
    if(depth==0) return S0.Tablescore(who);

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
    if(depth==0) return S0.Tablescore(who);

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

void AI::TD1(stack<minishogi> state,bool ifWIN,bool id)
{
    minishogi ST=state.top();
    state.pop();
    double VT=ST.Tablescore(id);

    minishogi St;
    double Vt;

    while(!state.empty() && ifWIN)
    {
        St=state.top();
        state.pop();
        Vt=St.Tablescore(id);

        for(int i=1;i<10;i++)
        {
            //judge if minions[i] is exist
            S.MinionsWeight[i]+=learningRATE*(VT-Vt);
        }
    }

}
