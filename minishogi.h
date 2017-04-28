#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>

using namespace std;

#ifndef MINISHOGI_H
#define MINISHOGI_H

#define INF 100000000

class minishogi
{
private:

	char table[5][5];

public:

    //table elements
	char hold[6] = { 'K','G','S','C','F','W' };
	short A[6];
	short B[6];
	bool controlA[5][5];
	bool controlB[5][5];
	bool movable[5][5];

	//states & features
	bool Minions[10];
	double MinionsWeight[10];

	//table function
	char GetChess(int, int);
	void PutChess(int, int, char);
	void initial();
	void PrintTable();
	bool IsEnemy(int,int,bool);
	bool IsFriend(int,int,bool);
	bool IsEmpty();
	double TableScore(bool);

	//movement function
	bool movement(int, int, int, int, bool);
	bool Move_K(int, int, int, int , bool);
	bool Move_G(int, int, int, int, bool);
	bool Move_S(int, int, int, int, bool);
	bool Move_C(int, int, int, int, bool);
	bool Move_F(int, int, int, int, bool);
	bool Move_W(int, int, int, int, bool);

	//game body operation function
	bool Take(int, int, bool);
	int HitIndex(char, int, int, bool);
	void hit(int, int, int, bool);
	int IFupgrade(char, int, int, int);
	bool win();

	//control table function
	void initialControl();
	void GetControl(bool);
	void PrintControlA();

	//movable table function
	void initialMovable();
	void GetMovable(int,int);
	void Movable_K(int,int,bool);
	void Movable_G(int,int,bool);
	void Movable_S(int,int,bool);
	void Movable_C(int,int,bool);
	void Movable_H(int,int,bool);
	void Movable_F(int,int,bool);
	void Movable_U(int,int,bool);
	void Movable_W(int,int,bool);
	void PrintMovable();
};

#endif
