#include "AI.h"

void AI::NextMoves(vector<minishogi> &V,bool who)
{
    minishogi S2;

    for(int i=0;i<25;i++)
    {
        //hit
        if(S.GetChess(i/5,i%5)==0)
        {
            if(!who)
            {
                for(int j=0;j<6;j++)
                {
                    if(S.A[j])
                    {
                        S2=S;
                        S2.hit(j,i/5,i%5,0);
                        V.push_back(S2);
                    }
                }
            }
            else
            {
                for(int j=0;j<6;j++)
                {
                    if(S.B[j])
                    {
                        S2=S;
                        S2.hit(j,i/5,i%5,1);
                        V.push_back(S2);
                    }
                }
            }
        }

        //move
        else if( ((S.GetChess(i/5,i%5)>97) && (!who) ) ||
                 ((S.GetChess(i/5,i%5)<97) &&   who  )   )
        {
            S.initialMovable();
            S.GetMovable(i/5,i%5);

            for(int j=0;j<25;j++)
            {
                if(S.movable[j/5][j%5])
                {
                    S2=S;
                    if(S.GetChess(j/5,j%5)!=0) S.Take(j/5,j%5,who);
                    S2.PutChess(j/5 , j%5 , S2.GetChess(i/5,i%5) );
                    S2.PutChess(i/5 , i%5 , 0);

                    V.push_back(S2);
                }
            }
        }
    }
}

int AI::Tablescore(minishogi &S,bool who)
{

}

int AI::AlphaCut(minishogi &S,int Alpha,int Beta,int depth,bool who)
{
    if(depth==0) return Tablescore(S,who);

    int a=Alpha;

    vector<minishogi> V;
    NextMoves(V,who);

    for(int i=0; i<V.size(); i++)
    {
        int R=BetaCut(V[i],a,Beta,depth-1,who);

        if(R>a) a=R;
        if(a>=Beta) return a;
    }

    return a;
}

int AI::BetaCut(minishogi &S,int Alpha,int Beta,int depth,bool who)
{
    if(depth==0) return Tablescore(S,who);

    int b=Beta;

    vector<minishogi> V;
    NextMoves(V,!who);

    for(int i=0; i<V.size(); i++)
    {
        int R=AlphaCut(V[i],Alpha,b,depth-1,who);

        if(R<b) b=R;
        if(b<=Alpha) return b;
    }

    return b;
}

minishogi AI::ABSearch(minishogi &S,int Alpha,int Beta,int depth,bool who)
{

    int a=Alpha;

    vector<minishogi> V;
    NextMoves(V,who);

    for(int i=0; i<V.size(); i++)
    {
        int R=BetaCut(V[i],a,Beta,depth-1,who);

        if(R>a) a=R;
        if(a>=Beta) return V[i];
    }

    return V[V.size()-1];
}
