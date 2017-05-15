#include "minishogi.h"

#ifndef AI_H
#define AI_H

#define learningRATE 0.0025

class AI
{
protected:

    minishogi S;

public:

    stack<minishogi> TDbuffer;

    void AssignTable(minishogi &);

    //ABsearch
	vector<minishogi> NextMoves(minishogi & ,bool);
    double AlphaCut(minishogi & ,double ,double ,int ,bool);
    double BetaCut(minishogi & ,double ,double ,int ,bool);
	minishogi ABSearch(minishogi & ,double ,double ,int ,bool);

	//TD-learning
	double AdjustScalar(minishogi ,bool);
	void TD1(bool ,bool);

	//mcts
	void Expand(node*);
    node* Selection(node*);
    void Update(node* ,bool);
    bool Simulation(node*);
    void PlayOneSequence(node*);
    minishogi MCTS(minishogi & ,int ,bool);

};

#endif
