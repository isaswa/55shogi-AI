#include <cstdlib>
#include <cstdio>
#include "Game.h"
#include <math.h>
using namespace std;

//boolean id we=A=0 enemy=B=1
//K=king=0 G=kin=1 S=silver=2
//C=croS=3 F=fly=4 W=warrior=5
//T=silver(up)=6 X=warrior(up)=7 U=ryuou=8 H=horse=9
//A side:small, B side:big

void aigame()
{
	minishoghi S;
	int x1, x2, y1, y2, act;
	bool id = 0, End = 0;
	S.initial();
	while (true)
	{
		End = 0;

		while (!End)
		{
			S.PrintTable();
			if (id == 0)
			{
				//AI
			}
			//turns
			if (id == 1)
			{
				printf("turn : B\n");
				printf("0 for move, 1 for hit :");
				scanf("%d", &act);

				//move
				if (!act)
				{
					//ask location
					printf("from( , ): ");
					scanf("%d%d", &x1, &y1);
					printf("  to( , ): ");
					scanf("%d%d", &x2, &y2);

					//illegal movement
					if (S.movement(x1, y1, x2, y2, id) == 0)
						printf("motion illegal.\n");

					//legal movement
					else if (S.movement(x1, y1, x2, y2, id) != 0)
					{
						//taking up
						if (S.eat(x2, y2, id) != 0)
						{
							int loc = -1;

							//find the char location in hold array
							for (int i = 0;i<6;i++)
								if (S.GetChess(x2, y2) == S.hold[i] || S.GetChess(x2, y2) - ('a' - 'A') == S.hold[i])
								{
									loc = i;
									break;
								}

							//find the upgraded type
							if (loc == -1 && (S.GetChess(x2, y2) == 't' || S.GetChess(x2, y2) == 'T')) loc = 2;
							else if (S.GetChess(x2, y2) == 'H' || S.GetChess(x2, y2) == 'h') loc = 3;
							else if (S.GetChess(x2, y2) == 'U' || S.GetChess(x2, y2) == 'u') loc = 4;
							else if (S.GetChess(x2, y2) == 'x' || S.GetChess(x2, y2) == 'X') loc = 5;

							//eating
							if (S.GetChess(x2, y2) - 'a' > 0) S.B[loc] = 1;
							else { S.A[loc] = 1; }
						}

						//moving
						S.PutChess(x2, y2, S.GetChess(x1, y1));
						S.PutChess(x1, y1, '\0');

						//upgrading
						int ug = S.IFupgrade(S.GetChess(x2, y2) + id*('a' - 'A'), y1, y2, id);
						if (ug)
						{
							int flag;
							printf("upgrade ? (1/0) : ");
							scanf("%d", &flag);

							if (flag == 1)
							{
								if (ug == 2) S.PutChess(x2, y2, 't' - id*('a' - 'A'));
								else if (ug == 3) S.PutChess(x2, y2, 'h' - id*('a' - 'A'));
								else if (ug == 4) S.PutChess(x2, y2, 'u' - id*('a' - 'A'));
								else if (ug == 5) S.PutChess(x2, y2, 'x' - id*('a' - 'A'));
							}
						}

						End = 1;
					}
				}

				//hit
				else
				{
					char type;

					//ask type & direction
					printf("hit type: ");
					getchar();
					scanf("%c", &type);
					printf("  to( , ): ");
					scanf("%d%d", &x1, &y1);

					//location in hold array
					int loc = S.hit(type, x1, y1, id);

					//illegal hit
					if (loc == 0) printf("motion illegal.\n");

					//legal hit
					else
					{
						//hiting
						S.PutChess(x1, y1, type - ('a' - 'A')*id);

						//taking out
						if (!id) S.A[loc] = 0;
						else { S.B[loc] = 0; }
						printf("hit location=%d\n", loc);

						End = 1;
					}
				}
			}

		}

		//change turn
		id = !id;
		printf("\n");

		//judging
		if (S.win())
		{
			S.PrintTable();
			break;
		}

		//for(int i=0;i<6;i++) printf("A[%d]=%d ",i,S.A[i]==1 ? 1 : 0);
		//printf("\n");

	}
}

void game( bool who)
{
	minishoghi S;
	int x1, x2, y1, y2, act;
	bool id=0, End=0;
	S.initial();

	while (true)
	{
		End=0;

		while (!End)
		{
			S.PrintTable();
			printf("\n");
			S.initialControl();
			S.GetControl(0);
			S.PrintControlA();

			//turns
			if (id == 0) printf("turn : A\n");
			else if (id == 1) printf("turn : B\n");

			printf("0 for move, 1 for hit :");
			scanf("%d", &act);

			//move
			if (!act)
			{
			    //ask location
				printf("from( , ): ");
				scanf("%d%d", &x1, &y1);
				printf("  to( , ): ");
				scanf("%d%d", &x2, &y2);

                //illegal movement
				if (S.movement(x1, y1, x2, y2, id) == 0)
                    printf("motion illegal.\n");

                //legal movement
				else if (S.movement( x1, y1, x2, y2, id) != 0)
				{
					//taking up
					if (S.eat(x2, y2, id) != 0)
					{
						int loc = -1;

                        //find the char location in hold array
						for (int i = 0;i<6;i++)
							if (S.GetChess(x2,y2) == S.hold[i] || S.GetChess(x2,y2) - ('a' - 'A') == S.hold[i])
							{
								loc = i;
								break;
							}

						//find the upgraded type
						if (loc == -1 && (S.GetChess(x2, y2) == 't' || S.GetChess(x2, y2) == 'T')) loc = 2;
						else if (S.GetChess(x2, y2) == 'H' || S.GetChess(x2, y2) == 'h') loc = 3;
						else if (S.GetChess(x2, y2) == 'U' || S.GetChess(x2, y2) == 'u') loc = 4;
						else if (S.GetChess(x2, y2) == 'x' || S.GetChess(x2, y2) == 'X') loc = 5;

						//eating
						if (S.GetChess(x2, y2) - 'a' > 0) S.B[loc] = 1;
						else { S.A[loc] = 1; }
					}

					//moving
					S.PutChess(x2, y2, S.GetChess(x1, y1));
					S.PutChess(x1, y1, '\0');

					//upgrading
					int ug = S.IFupgrade(S.GetChess(x2, y2) + id*('a' - 'A'), y1, y2, id);
					if (ug)
					{
						int flag;
						printf("upgrade ? (1/0) : ");
						scanf("%d", &flag);

						if (flag == 1)
						{
							if (ug == 2) S.PutChess(x2, y2, 't' - id*('a' - 'A'));
							else if (ug == 3) S.PutChess(x2, y2, 'h' - id*('a' - 'A'));
							else if (ug == 4) S.PutChess(x2, y2, 'u' - id*('a' - 'A'));
							else if (ug == 5) S.PutChess(x2, y2, 'x' - id*('a' - 'A'));
						}
					}

					End = 1;
				}
			}

			//hit
			else
			{
				char type;

				//ask type & direction
				printf("hit type: ");
				getchar();
				scanf("%c", &type);
				printf("  to( , ): ");
				scanf("%d%d", &x1, &y1);

				//location in hold array
				int loc = S.hit(type, x1, y1, id);

				//illegal hit
				if (loc == 0) printf("motion illegal.\n");

                //legal hit
				else
				{
					//hiting
					S.PutChess(x1, y1, type - ('a' - 'A')*id);

					//taking out
					if (!id) S.A[loc] = 0;
					else { S.B[loc] = 0; }
					printf("hit location=%d\n", loc);

					End = 1;
				}
			}
		}

		//change turn
		id = !id;
		printf("\n");

		//judging
		if (S.win())
		{
			S.PrintTable();
			break;
		}

		//for(int i=0;i<6;i++) printf("A[%d]=%d ",i,S.A[i]==1 ? 1 : 0);
		//printf("\n");

	}
}

void test();

int main()
{
	game(0);
	//aigame();
	//test();
	return 0;
}

//test
void test()
{
	minishoghi S;
	S.initial();
	//S.canmove_croS(2,2,0);
	int a; scanf("%d", &a);
	//print_shogi(x);
	//printf("is (1,4) can be eaten : %d\n",eat(x,1,4,0));
	//printf("is (0,4)='k': %d\n",x.x[0][4]=='k' ? 1 : 0);
	//printf("move_king (0,4)->(1,3) : %d\n",move_king(x,0,4,1,3,0));
	//printf("movement (0,4)->(1,3) : %d",movement(x,0,4,1,3,0));
	//for(int i=0;i<6;i++) printf("A[%d]=%d ",i,x.hold[i]==1 ? 1 : 0);
}
