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
    double AlphaCut(minishogi & ,double ,double ,int ,bool);
    double BetaCut(minishogi & ,double ,double ,int ,bool);
	minishogi ABSearch(minishogi & ,double ,double ,int ,bool);

	//TD-learning
	void TD1(stack<minishogi> ,bool ,bool);

	//mcts
    node* Selection(node*);
    void Update(node* ,bool);
    void PlayOneSequence(node* ,bool);
    bool Simulation(node* ,bool);
    minishogi MCTS(minishogi & ,int ,bool);

};

#endif
