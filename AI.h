#include "minishogi.h"
#define INF 100000000

#ifndef AI_H
#define AI_H

class AI
{
protected:

    minishogi S;
    stack<minishogi> TDbuffer;

public:

    void AssignTable(minishogi &);

    //ABsearch
	vector<minishogi> NextMoves(minishogi & ,bool);
    double AlphaCut(minishogi & ,double ,double ,int ,bool);
    double BetaCut(minishogi & ,double ,double ,int ,bool);
	minishogi ABSearch(minishogi & ,double ,double ,int ,bool);

	//TD-learning
	void TD1(stack<minishogi> ,bool ,bool);

};

#endif
