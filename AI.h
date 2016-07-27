#include "minishogi.h"
#define INF 100000000

#ifndef AI_H
#define AI_H

class AI
{
protected:

    minishogi S;

public:

    void AssignTable(minishogi &);

    //ABsearch
	vector<minishogi> NextMoves(minishogi & ,bool);
	int Tablescore(minishogi & ,bool);
	int AlphaCut(minishogi & ,int ,int ,int ,bool);
	int BetaCut(minishogi & ,int ,int ,int ,bool);
	minishogi ABSearch(minishogi & ,int ,int ,int ,bool);

};

#endif
