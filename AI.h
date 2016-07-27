#include "minishogi.h"

#ifndef AI_H
#define AI_H

class AI
{
protected:

    minishogi S;

public:

	void NextMoves(vector<minishogi> & ,bool);
	int Tablescore(minishogi & ,bool);
	int AlphaCut(minishogi & ,int ,int ,int ,bool);
	int BetaCut(minishogi & ,int ,int ,int ,bool);
	minishogi ABSearch(minishogi & ,int ,int ,int ,bool);

};

#endif
