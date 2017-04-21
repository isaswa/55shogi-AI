#include "minishogi.h"

#ifndef AI_H
#define AI_H

#define learningRATE 0.0025

class AI
{
protected:

    minishogi S;
    stack<minishogi> TDbuffer;

public:

    void AssignTable(minishogi &);

    //ABsearch
	vector<minishogi> NextMoves(minishogi & ,bool);
	double AlphaCut(minishogi & ,int ,int ,int ,bool);
	double BetaCut(minishogi & ,int ,int ,int ,bool);
	minishogi ABSearch(minishogi & ,int ,int ,int ,bool);

	//TD-learning
	void TD1(stack<minishogi> ,bool ,bool);

};

#endif
