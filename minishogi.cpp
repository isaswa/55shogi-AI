#include "minishogi.h"

char minishogi::GetChess(int x0, int y0)
{
	return table[x0][y0];
}

void minishogi::PutChess(int x0, int y0, char type)
{
    //printf("\n   %x   \n",type);
	table[x0][y0] = char(type);
}

void minishogi::initial()
{
	for (int i = 0;i<5;i++)
		for (int j = 0;j<5;j++)
			table[i][j] = '\0';

	table[4][0] = 'K';
	table[3][0] = 'G';
	table[2][0] = 'S';
	table[1][0] = 'C';
	table[0][0] = 'F';
	table[4][1] = 'W';

	table[0][4] = 'k';
	table[1][4] = 'g';
	table[2][4] = 's';
	table[3][4] = 'c';
	table[4][4] = 'f';
	table[0][3] = 'w';

	for (int i = 0;i<6;i++) A[i] = 0;
	for (int i = 0;i<6;i++) B[i] = 0;

}

void minishogi::PrintTable()
{
	printf("*  0 1 2 3 4\n");

	for (int i = 0;i<5;i++)
	{
		for (int j = 0;j<5;j++)
		{
			if (j == 0) printf("%d |", i);
			printf("%c|", table[j][i]);
		}

		if (i == 0)
		{
			printf("   hold B: ");
			for (int k = 0;k<6;k++)
				if (B[k]) printf("%c ", hold[k]);
		}

		if (i == 4)
		{
			printf("   hold A: ");
			for (int k = 0;k<6;k++)
				if (A[k]) printf("%c ", hold[k]);
		}

		printf("\n  -----------\n");
	}
	printf("%x   ",table[1][1]);
}

bool minishogi::IsEnemy(int x,int y,bool who)
{
    if(table[x][y]==0) return 0;

    if(who){
        if(table[x][y] > 97) return 1;
    }
    else
    {   if(table[x][y] < 97) return 1; }

    return 0;
}

bool minishogi::IsFriend(int x,int y,bool who)
{
    if(table[x][y]==0) return 0;

    if(who){
        if(table[x][y] < 97) return 1;
    }
    else
    {   if(table[x][y] > 97) return 1; }

    return 0;
}

double minishogi::Tablescore(bool who)
{
    double R=0;

    if( who && A[0] || !who && B[0] ) return R=INF;
    if( who && B[0] || !who && A[0] ) return R=-INF;

    for(int i=0;i<25;i++)
    {
        switch(table[i/5][i%5])
        {
        case 'G' : R+=(who ? minions[1] : -minions[1]); break;
        case 'S' : R+=(who ? minions[2] : -minions[2]); break;
        case 'C' : R+=(who ? minions[3] : -minions[3]); break;
        case 'F' : R+=(who ? minions[4] : -minions[4]); break;
        case 'W' : R+=(who ? minions[5] : -minions[5]); break;
        case 'T' : R+=(who ? minions[6] : -minions[6]); break;
        case 'X' : R+=(who ? minions[7] : -minions[7]); break;
        case 'U' : R+=(who ? minions[8] : -minions[8]); break;
        case 'H' : R+=(who ? minions[9] : -minions[9]); break;

        case 'g' : R+=(!who ? minions[1] : -minions[1]); break;
        case 's' : R+=(!who ? minions[2] : -minions[2]); break;
        case 'c' : R+=(!who ? minions[3] : -minions[3]); break;
        case 'f' : R+=(!who ? minions[4] : -minions[4]); break;
        case 'w' : R+=(!who ? minions[5] : -minions[5]); break;
        case 't' : R+=(!who ? minions[6] : -minions[6]); break;
        case 'x' : R+=(!who ? minions[7] : -minions[7]); break;
        case 'u' : R+=(!who ? minions[8] : -minions[8]); break;
        case 'h' : R+=(!who ? minions[9] : -minions[9]); break;

        default: break;
        }

    }

    return R;
}

bool minishogi::Move_K( int x1, int y1, int x2, int y2, bool who)
{
	if (table[x2][y2] == '\0');
	else if (who == 0 && (table[x2][y2] - 'a')>0) return false;
	else if (who == 1 && (table[x2][y2] - 'a')<0) return false;

	if ((abs(x1 - x2) <= 1) && (abs(y1 - y2) <= 1)) return true;
	return false;
}

bool minishogi::Move_G(int x1, int y1, int x2, int y2, bool who)
{
	if (table[x2][y2] == '\0');
	else if (who == 0 && (table[x2][y2] - 'a')>0) return false;
	else if (who == 1 && (table[x2][y2] - 'a')<0) return false;

	if (abs(x1 - x2)>1 && abs(y1 - y2)>1) return false;
	if (y2 == y1 + 1 - who * 2 && (x1 - x2) != 0) return false;
	return true;
}

bool minishogi::Move_S(int x1, int y1, int x2, int y2, bool who)
{
	if (table[x2][y2] == '\0');
	else if (who == 0 && (table[x2][y2] - 'a')>0) return false;
	else if (who == 1 && (table[x2][y2] - 'a')<0) return false;

	if (abs(x1 - x2)>1 && abs(y1 - y2)>1) return false;
	if (y2 == y1 - 1 + who * 2) if ((x1 - x2) == 0) return true;
	//if forward judge if it didnt move side
	if (abs(x1 - x2) != abs(y1 - y2)) return false;
	return true;
}

bool minishogi::Move_C(int x1, int y1, int x2, int y2, bool who)
{
	if (table[x2][y2] == '\0');
	else if (who == 0 && (table[x2][y2] - 'a')>0) return false;
	else if (who == 1 && (table[x2][y2] - 'a')<0) return false;

	if (abs(x1 - x2) != abs(y1 - y2)) return false;

	for (int i = x1 + (x2 - x1) / abs(x2 - x1), j = y1 + (y2 - y1) / abs(y2 - y1); i != x2; )
	{
		if (table[i][j] != 0) return false;
		i += (x2 - x1) / abs(x2 - x1);
		j += (y2 - y1) / abs(y2 - y1);
	}

	return true;
}

bool minishogi::Move_F(int x1, int y1, int x2, int y2, bool who)
{
	if (table[x2][y2] == '\0');
	else if (who == 0 && (table[x2][y2] - 'a')>0) return false;
	else if (who == 1 && (table[x2][y2] - 'a')<0) return false;

	if ((x1 - x2)*(y1 - y2)) return false;
	if (!(y2 - y1)) //row
		for (int i = x1 + (x2 - x1) / abs(x2 - x1); i != x2; i += ((x2 - x1) / abs(x2 - x1)))
            if (table[i][y1] != 0) return false;

	if (!(x2 - x1)) //col
		for (int i = y1 + (y2 - y1) / abs(y2 - y1); i != y2; i += ((y2 - y1) / abs(y2 - y1)))
            if (table[x1][i] != 0) return false;

	return true;
}

bool minishogi::Move_W(int x1, int y1, int x2, int y2, bool who)
{
	if (table[x2][y2] == '\0');
	else if (who == 0 && (table[x2][y2] - 'a')>0) return false;
	else if (who == 1 && (table[x2][y2] - 'a')<0) return false;

	if (((y1 - y2) + who * 2) == 1 && (x1 - x2) == 0) return true;
	else return false;
}

bool minishogi::movement(int x1, int y1, int x2, int y2, bool who)
{
	if (x2>4 || x2<0) return 0;
	else if (y2>4 || y2<0) return 0;
	else if (x1 == x2 && y1 == y2) return 0;

	if (table[x1][y1] == 'k' || table[x1][y1] == 'K') return Move_K(x1, y1, x2, y2, who);
	else if (table[x1][y1] == 'g' || table[x1][y1] == 'G') return Move_G( x1, y1, x2, y2, who);
	else if (table[x1][y1] == 's' || table[x1][y1] == 'S') return Move_S( x1, y1, x2, y2, who);
	else if (table[x1][y1] == 'c' || table[x1][y1] == 'C') return Move_C( x1, y1, x2, y2, who);
	else if (table[x1][y1] == 'f' || table[x1][y1] == 'F') return Move_F( x1, y1, x2, y2, who);
	else if (table[x1][y1] == 'w' || table[x1][y1] == 'W') return Move_W( x1, y1, x2, y2, who);
	else if (table[x1][y1] == 't' || table[x1][y1] == 'T') return Move_G( x1, y1, x2, y2, who);
	else if (table[x1][y1] == 'x' || table[x1][y1] == 'X') return Move_G( x1, y1, x2, y2, who);
	else if (table[x1][y1] == 'u' || table[x1][y1] == 'U')
		return Move_K(x1, y1, x2, y2, who) || Move_F( x1, y1, x2, y2, who);
	else if (table[x1][y1] == 'h' || table[x1][y1] == 'H')
		return Move_K( x1, y1, x2, y2, who) || Move_C( x1, y1, x2, y2, who);
	else return 0;
}

//take out the chess on (x,y)
bool minishogi::Take(int x, int y, bool who)
{
	if (table[x][y]==0) return 0;
	if(!who)
    {
        switch(table[x][y])
        {
        case 'K':
            A[0]++; break;
        case 'G':
            A[1]++; break;
        case 'S':
        case 'T':
            A[2]++; break;
        case 'C':
        case 'H':
            A[3]++; break;
        case 'F':
        case 'U':
            A[4]++; break;
        case 'W':
        case 'X':
            A[5]++; break;
        }
    }
    else
    {
        switch(table[x][y])
        {
        case 'k':
            B[0]++; break;
        case 'g':
            B[1]++; break;
        case 's':
        case 't':
            B[2]++; break;
        case 'c':
        case 'h':
            B[3]++; break;
        case 'f':
        case 'u':
            B[4]++; break;
        case 'w':
        case 'x':
            B[5]++; break;
        }
    }
}

//return type index in hold array or 0
int minishogi::HitIndex(char type, int x1, int y1, bool who)
{
	if (x1>4 || x1<0 || y1>4 || y1<0) return 0;
	if (table[x1][y1] != '\0') return 0;

	if (!who)
	{
		//illegal
		if (type == 'w' && y1 == 0) return 0;

		int loc = 0;

		for (int i = 0;i<6;i++)
			if (hold[i] == type-32 ) loc=i;

		//not exist
		if (!loc) return 0;
		else if (A[loc]==0) return 0;

		return loc;
	}

	else
	{
		int loc = 0;

		//illegal
		if (type == 'w' && y1 == 4) return 0;

		for (int i = 0;i<6;i++)
			if (hold[i] == type-32) loc=i;

		//not exist
		if (!loc) return 0;
		if (B[loc]==0) return 0;

		return loc;
	}
}

void minishogi::hit(int index,int x,int y,bool who)
{
    if(!who)
    {
        PutChess(x,y,(hold[index]+32) );
        A[index]--;
    }
    else{
        PutChess(x,y,(hold[index]) );
        B[index]--;
    }
}

//return upgrading type or 0
int minishogi::IFupgrade(char type, int y1, int y2, int who)
{
	if (type == 'k' || type == 'K' || type == 'g' || type == 'G') return 0;

	if (y1 == who * 4 || y2 == who * 4)
	{
		if (type == 's' || type == 'S') return 2;
		if (type == 'c' || type == 'C') return 3;
		if (type == 'f' || type == 'F') return 4;
		if (type == 'w' || type == 'W') return 5;
	}
	return 0;
}

bool minishogi::win()
{
	if (A[0] != 0)
	{
		printf("A win!!\n");
		return 1;
	}
	if (B[0] != 0)
	{
		printf("B win!!\n");
		return 1;
	}
	return 0;
}

//initial controlA&B
void minishogi::initialControl()
{
	for(int i=0;i<5;i++)
		for (int j = 0;j < 5;j++)
		{
			controlA[i][j] = 0;
			controlB[i][j] = 0;
		}

}

void minishogi::PrintControlA()
{
	printf("*  0 1 2 3 4\n");

	for (int i = 0;i<5;i++)
	{
		for (int j = 0;j<5;j++)
		{
			if (j == 0) printf("%d |", i);
			printf("%d|", controlA[j][i]);
		}

		printf("\n  -----------\n");
	}

}

//check current table controlA&B
void minishogi::GetControl(bool who)
{
	bool old;
	if (who)
	{
		for (int i = 0; i < 25; i++)
		{

			switch (table[i / 5][i % 5]){
			case 'K':
				old = controlB[i / 5][i % 5];
				for (int t = -1;t < 2;t++)
				{
					if ((i / 5 + t) > 4 || (i/5 + t) < 0) continue;
					for (int g = -1;g < 2;g++)
					{
						if ((i % 5 + g) > 4 || (i % 5 + g) < 0) continue;
						controlB[i / 5 + t][i % 5 + g] = true;
					}
				}
				controlB[i / 5][i % 5] = old;
				break;
			case 'G':
			case 'T':
			case 'X':
				old = controlB[i / 5][i % 5];
				for (int t = -1;t<2;t++)
				{
					if (i / 5 + t> 4 || i / 5 + t<0) continue;
					for (int g = -1;g<2;g++)
					{
						if (i % 5 + g> 4 || i % 5 + g<0) continue;
						controlB[i / 5 + t][i % 5 + g] = true;
					}
				}
				controlB[i / 5 + 1][i % 5 - 1] = false;
				controlB[i / 5 - 1][i % 5 - 1] = false;
				controlB[i / 5][i % 5] = old;
				break;
			case 'S':
				old = controlB[i / 5][i % 5];
				for (int t = -1;t<2;t += 2)
				{
					if (i / 5 + t> 4 || i / 5 + t<0) continue;
					for (int g = -1;g<2;g += 2)
					{
						if (i % 5 + g> 4 || i % 5 + g<0) continue;
						controlB[i / 5 + t][i % 5 + g] = true;
					}
				}
				controlB[i / 5][i % 5 + 1] = true;
				controlB[i / 5][i % 5] = old;
				break;
			case 'C':
				old = controlB[i / 5][i % 5];
				for (int t = -4;t<4;t++)
				{
					if (i / 5 + t> 4 || i / 5 + t<0) continue;
					if (i % 5 + t> 4 || i % 5 + t<0) continue;
					controlB[i / 5 + t][i % 5 + t] = true;

				}
				for (int t = -4;t < 4;t++)
				{
					int g = -t;
					if (i / 5 + t> 4 || i / 5 + t<0) continue;
					if (i % 5 + g> 4 || i % 5 + g<0) continue;
					controlB[i / 5 + t][i % 5 + g] = true;
				}
				controlB[i / 5][i % 5] = old;
				break;
			case 'F':
				old = controlB[i / 5][i % 5];
				for (int t = -4;t<4;t ++)
				{
					if (i / 5 + t> 4 || i / 5 + t<0) continue;
					controlB[i / 5 + t][i % 5] = true;
				}
				for (int g = -4;g<4;g ++)
				{
					if (i % 5 + g> 4 || i % 5 + g<0) continue;
					controlB[i / 5][i % 5 + g] = true;
				}
				controlB[i / 5][i % 5] = old;
				break;
			case 'W':
				old = controlB[i / 5][i % 5];
				if ((i % 5) <= 4 || (i % 5) > 0) controlB[i / 5][i % 5 + 1] = true;
				controlB[i / 5][i % 5] = old;
				break;
			case 'U':
				old = controlB[i / 5][i % 5];
				for (int t = -4;t<4;t++)
				{
					if (i / 5 + t> 4 || i / 5 + t<0) continue;
					controlB[i / 5 + t][i % 5] = true;
				}
				for (int g = -4;g<4;g++)
				{
					if (i % 5 + g> 4 || i % 5 + g<0) continue;
					controlB[i / 5][i % 5 + g] = true;
				}
				for (int t = -1;t<2;t++)
				{
					if ((i / 5) + t > 4 || (i / 5) + t < 0) continue;
					for (int g = -1;g<2;g++)
					{
						if (((i % 5) + g)> 4 || ((i % 5) + g)<0) continue;
						controlB[i / 5 + t][i % 5 + g] = true;
					}
				}
				controlB[i / 5][i % 5] = old;
				break;
			case 'H':
				old = controlB[i / 5][i % 5];
				for (int t = -4;t<4;t++)
				{
					if (i / 5 + t> 4 || i / 5 + t<0) continue;
					if ((i % 5) + t> 4 || (i % 5) + t<0) continue;
					controlB[i / 5 + t][i % 5 + t] = true;

				}
				for (int t = -4;t < 4;t++)
				{
					int g = -t;
					if (i / 5 + t> 4 || i / 5 + t<0) continue;
					if ((i % 5) + g> 4 || (i % 5) + g<0) continue;
					controlB[i / 5 + t][i % 5 + g] = true;
				}
				for (int t = -1;t<2;t++)
				{
					if ((i / 5 + t)> 4 || (i / 5 + t)<0) continue;
					for (int g = -1;g<2;g++)
					{
						if ((i % 5) + g> 4 || (i % 5) + g<0) continue;
						controlB[i / 5 + t][i % 5 + g] = true;
					}
				}
				controlB[i / 5][i % 5] = old;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < 25; i++)
			{
				switch (table[i / 5][i % 5]) {
				case 'k':
					old = controlA[i / 5][i % 5];
					for (int t = -1;t < 2;t++)
					{
						if (((i / 5) + t) > 4 || ((i / 5) + t) < 0) continue;
						for (int g = -1;g < 2;g++)
						{
							if ((i % 5 + g) > 4 || (i % 5 + g) < 0) continue;
							controlA[i / 5 + t][i % 5 + g]= true;
						}
					}
					controlA[i / 5][i % 5] = old;
					break;
				case 'g':
				case 't':
				case 'x':
					old = controlA[i / 5][i % 5];
					for (int t = -1;t < 2;t++)
					{
						if (i / 5 + t > 4 || i / 5 + t < 0) continue;
						for (int g = -1;g < 2;g++)
						{
							if (i % 5 + g > 4 || i % 5 + g < 0) continue;
							controlA[i / 5 + t][i % 5 + g]= true;
						}
					}
					controlA[i / 5 + 1][i % 5 + 1]= false;
					controlA[i / 5 - 1][i % 5 + 1]= false;
					controlA[i / 5][i % 5] = old;
					break;
				case 's':
					old = controlA[i / 5][i % 5];
					for (int t = -1;t<2;t += 2)
					{
						if (i / 5 + t> 4 || i / 5 + t<0) continue;
						for (int g = -1;g<2;g += 2)
						{
							if (i % 5 + g> 4 || i % 5 + g<0) continue;
							controlA[i / 5 + t][i % 5 + g]= true;
						}
					}
					controlA[i / 5][i % 5 - 1]= true;
					controlA[i / 5][i % 5] = old;
					break;
				case 'c':
					old = controlA[i / 5][i % 5];
					for (int t = -4;t<4;t++)
					{
						if (i / 5 + t> 4 || i / 5 + t<0) continue;
						if (i % 5 + t> 4 || i % 5 + t<0) continue;
						controlA[i / 5 + t][i % 5 + t]= true;

					}
					for (int t = -4;t < 4;t++)
					{
						int g = -t;
						if (i / 5 + t> 4 || i / 5 + t<0) continue;
						if (i % 5 + g> 4 || i % 5 + g<0) continue;
						controlA[i / 5 + t][i % 5 + g]= true;
					}
					controlA[i / 5][i % 5] = old;
					break;
				case 'f':
					old = controlA[i / 5][i % 5];
					for (int t = -4;t<4;t++)
					{
						if (i / 5 + t> 4 || i / 5 + t<0) continue;
						controlA[i / 5 + t][i % 5]= true;
					}
					for (int g = -4;g<4;g++)
					{
						if (i % 5 + g> 4 || i % 5 + g<0) continue;
						controlA[i / 5][i % 5 + g]= true;
					}
					controlA[i / 5][i % 5] = old;
					break;
				case 'w':
					old = controlA[i / 5][i % 5];
					if ((i % 5) <= 4 || (i % 5) > 0) controlA[i / 5][i % 5 - 1]= true;
					controlA[i / 5][i % 5] = old;
					break;
				case 'u':
					old = controlA[i / 5][i % 5];
					for (int t = -4;t<4;t++)
					{
						if (i / 5 + t> 4 || i / 5 + t<0) continue;
						controlA[i / 5 + t][i % 5]= true;
					}
					for (int g = -4;g<4;g++)
					{
						if (i % 5 + g> 4 || i % 5 + g<0) continue;
						controlA[i / 5][i % 5 + g]= true;
					}
					for (int t = -1;t<2;t++)
					{
						if ((i / 5) + t > 4 || (i / 5) + t < 0) continue;
						for (int g = -1;g<2;g++)
						{
							if (((i % 5) + g)> 4 || ((i % 5) + g)<0) continue;
							controlA[i / 5 + t][i % 5 + g]= true;
						}
					}
					controlA[i / 5][i % 5] = old;
					break;
				case 'h':
					old = controlA[i / 5][i % 5];
					for (int t = -4;t<4;t++)
					{
						if (i / 5 + t> 4 || i / 5 + t<0) continue;
						if ((i % 5) + t> 4 || (i % 5) + t<0) continue;
						controlA[i / 5 + t][i % 5 + t]= true;

					}
					for (int t = -4;t < 4;t++)
					{
						int g = -t;
						if (i / 5 + t> 4 || i / 5 + t<0) continue;
						if ((i % 5) + g> 4 || (i % 5) + g<0) continue;
						controlA[i / 5 + t][i % 5 + g]= true;
					}
					for (int t = -1;t<2;t++)
					{
						if ((i / 5 + t)> 4 || (i / 5 + t)<0) continue;
						for (int g = -1;g<2;g++)
						{
							if ((i % 5) + g> 4 || (i % 5) + g<0) continue;
							controlA[i / 5 + t][i % 5 + g]= true;
						}
					}
					controlA[i / 5][i % 5] = old;
					break;
				default:
					break;
				}
			}


	}
}

void minishogi::initialMovable()
{
    for(int i=0;i<25;i++)
        movable[i/5][i%5]=0;
}

void minishogi::Movable_K(int x0,int y0,bool who)
{
    for(int i=x0-1;i<x0+2;i++)
        for(int j=y0-1;j<y0+2;j++)
        {
            if(i>4 || i<0 || j>4 || j<0) continue;
            if(i==x0 && j==y0) continue;
            if(IsFriend(i,j,who)) continue;
            movable[i][j]=1;
        }
}

void minishogi::Movable_G(int x0,int y0,bool who)
{
    for(int i=x0-1;i<x0+2;i++)
        for(int j=y0-1;j<y0+2;j++)
        {
            if(i>4 || i<0 || j>4 || j<0) continue;
            if(i==x0 && j==y0) continue;
            if(IsFriend(i,j,who)) continue;
            movable[i][j]=1;
        }

    if(x0-1<=4 && x0-1>=0 && y0+1-who*2 <= 4 && y0+1-who*2 >= 0)
        if(!IsFriend(x0-1,y0+1-who*2,who)) movable[x0-1][y0+1-who*2]=0;

    if(x0+1<=4 && x0+1>=0 && y0+1-who*2 <= 4 && y0+1-who*2 >= 0)
        if(!IsFriend(x0+1,y0+1-who*2,who)) movable[x0+1][y0+1-who*2]=0;
}

void minishogi::Movable_S(int x0,int y0,bool who)
{
    for(int i=x0-1;i<x0+2;i+=2)
        for(int j=y0-1;j<y0+2;j+=2)
        {
            if(i>4 || i<0 || j>4 || j<0) continue;
            if(IsFriend(i,j,who)) continue;
            movable[i][j]=1;
        }

    if( y0-1+who*2 <= 4 && y0-1+who*2 >= 0 )
        if(!IsFriend(x0,y0-1+who*2,who)) movable[x0][y0-1+who*2]=1;
}

void minishogi::Movable_C(int x0,int y0,bool who)
{
    for(int i=1; x0-i>-1 && x0-i<5 && y0-i>-1 && y0-i<5 ;i++)
    {
        if(IsFriend(x0-i,y0-i,who)) break;
        movable[x0-i][y0-i]=1;
        if(IsEnemy(x0-i,y0-i,who)) break;
    }

    for(int i=1; x0+i>-1 && x0+i<5 && y0-i>-1 && y0-i<5 ;i++)
    {
        if(IsFriend(x0+i,y0-i,who)) break;
        movable[x0+i][y0-i]=1;
        if(IsEnemy(x0+i,y0-i,who)) break;
    }

    for(int i=1; x0-i>-1 && x0-i<5 && y0+i>-1 && y0+i<5 ;i++)
    {
        if(IsFriend(x0-i,y0+i,who)) break;
        movable[x0-i][y0+i]=1;
        if(IsEnemy(x0-i,y0+i,who)) break;
    }

    for(int i=1; x0+i>-1 && x0+i<5 && y0+i>-1 && y0+i<5 ;i++)
    {
        if(IsFriend(x0+i,y0+i,who)) break;
        movable[x0+i][y0+i]=1;
        if(IsEnemy(x0+i,y0+i,who)) break;
    }
}

void minishogi::Movable_H(int x0,int y0,bool who)
{
    Movable_C(x0,y0,who);

    for(int j=-1;j<2;j+=2)
    {
        if(x0+j <= 4 && x0+j >= 0)
            if(!IsFriend(x0+j,y0,who)) movable[x0+j][y0]=1;
    }

    for(int j=-1;j<2;j+=2)
    {
        if(y0+j <= 4 && y0+j >= 0)
            if(!IsFriend(x0,y0+j,who)) movable[x0][y0+j]=1;
    }
}

void minishogi::Movable_F(int x0,int y0,bool who)
{
    for(int i=1; x0+i<=4 ;i++)
    {
        if(IsFriend(x0+i,y0,who)) break;
        movable[x0+i][y0]=1;
        if(IsEnemy(x0+i,y0,who)) break;
    }

    for(int i=-1; x0+i>=0 ;i--)
    {
        if(IsFriend(x0+i,y0,who)) break;
        movable[x0+i][y0]=1;
        if(IsEnemy(x0+i,y0,who)) break;
    }

    for(int j=1; y0+j<=4 ;j++)
    {
        if(IsFriend(x0,y0+j,who)) break;
        movable[x0][y0+j]=1;
        if(IsEnemy(x0,y0+j,who)) break;
    }

    for(int j=-1; y0+j>=0 ;j--)
    {
        if(IsFriend(x0,y0+j,who)) break;
        movable[x0][y0+j]=1;
        if(IsEnemy(x0,y0+j,who)) break;
    }
}

void minishogi::Movable_U(int x0,int y0,bool who)
{
    Movable_F(x0,y0,who);

    for(int j=-1;j<2;j+=2)
    {
        if(x0+j <= 4 && x0+j >= 0 && y0+j <= 4 && y0+j >= 0)
            if(!IsFriend(x0+j,y0+j,who)) movable[x0+j][y0+j]=1;
    }

    for(int j=-1;j<2;j+=2)
    {
        if(x0+j <= 4 && x0+j >= 0 && y0-j <= 4 && y0+j >= 0)
            if(!IsFriend(x0+j,y0-j,who)) movable[x0+j][y0-j]=1;
    }
}

void minishogi::Movable_W(int x0,int y0,bool who)
{
    if(y0-1+who*2 <= 4 && y0-1+who*2 >= 0)
        if(!IsFriend(x0,y0-1+who*2,who)) movable[x0][y0-1+who*2]=1;
}

//mask movable area of the chess on (x0,y0)
void minishogi::GetMovable(int x0,int y0)
{
    switch(table[x0][y0])
    {
    case 'k': Movable_K(x0,y0,0); break;
    case 'g':
    case 't':
    case 'x': Movable_G(x0,y0,0); break;
    case 's': Movable_S(x0,y0,0); break;
    case 'c': Movable_C(x0,y0,0); break;
    case 'h': Movable_H(x0,y0,0); break;
    case 'f': Movable_F(x0,y0,0); break;
    case 'u': Movable_U(x0,y0,0); break;
    case 'w': Movable_W(x0,y0,0); break;

    case 'K': Movable_K(x0,y0,1); break;
    case 'G':
    case 'T':
    case 'X': Movable_G(x0,y0,1); break;
    case 'S': Movable_S(x0,y0,1); break;
    case 'C': Movable_C(x0,y0,1); break;
    case 'H': Movable_H(x0,y0,1); break;
    case 'F': Movable_F(x0,y0,1); break;
    case 'U': Movable_U(x0,y0,1); break;
    case 'W': Movable_W(x0,y0,1); break;

    default:
        break;
    }
}

void minishogi::PrintMovable()
{
	printf("*  0 1 2 3 4\n");

	for (int i = 0;i<5;i++)
	{
		for (int j = 0;j<5;j++)
		{
			if (j == 0) printf("%d |", i);
			printf("%d|", movable[j][i]);
		}

		printf("\n  -----------\n");
	}
}
