#include "minishogi.h"

#ifndef AI_H
#define AI_H

class AI
{
protected:

    minishogi S;

public:

	void NextMoves(vector<minishogi> &, bool);

};

#endif
