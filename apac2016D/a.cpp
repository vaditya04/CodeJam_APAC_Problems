/*input
1
4 4
0101
0010
0100
1111
7
Q
M 0 2 1
Q
M 2 2 0
Q
M 2 1 0
Q
*/

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>
#include <map>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <climits>
#include <cfloat>
#include <queue>
#include <set>

using namespace std;

vector<vector<int> > board;
int rows, cols, connectedCount;

void checkNeighbours(int i, int j)
{
	if (board[max(i-1, 0)][j] == 1)
	{
		board[max(i-1, 0)][j] = 2;
		checkNeighbours(max(i-1,0), j);	
	}
	if (board[i][max(j-1, 0)] == 1)
	{
		board[i][max(j-1, 0)] = 2;
		checkNeighbours(i, max(j-1, 0));	
	}
	if (board[min(i+1, rows-1)][j] == 1)
	{
		board[min(i+1, rows-1)][j] = 2;
		checkNeighbours(min(i+1, rows-1), j);	
	}
	if (board[i][min(j+1, cols-1)] == 1)
	{
		board[i][min(j+1, cols-1)] = 2;
		checkNeighbours(i, min(j+1, cols-1));	
	}
}

int initCount()
{
	int initCount = 0;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (board[i][j] == 1)
			{
				initCount++;
				board[i][j] = 2;
				checkNeighbours(i, j);
			}
			else
			{
				continue;
			}
		}
	}

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (board[i][j] == 2)
			{
				board[i][j] = 1;
			}
		}
	}

	return initCount;
}

void markCell(int x, int y, int newVal)
{
	board[x][y] = newVal;
	// initCount();
}

int main(int argc, char const *argv[])
{	
    freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
    	cin>>rows>>cols;

    	board = vector<vector<int> > (rows, vector<int> (cols));

    	for (int j = 0; j < rows; ++j)
    	{
    		for (int k = 0; k < cols; ++k)
    		{
    			char cell;
    			cin>>cell;
    			if (cell == '0')
    			{
    				board[j][k] = 0;
    			}
    			else
    			{
    				board[j][k] = 1;
    			}
    		}
    	}
    	connectedCount = initCount();

    	int opCount;
    	cin>>opCount;

        cout<<"Case #"<<i+1<<": "<<endl;
    	for (int j = 0; j < opCount; ++j)
    	{
    		char move;
    		cin>>move;
    		if (move == 'M')
    		{
				int x, y, newVal;
				cin>>x>>y>>newVal;
				markCell(x, y, newVal);    			
    		}
    		else
    		{
    			cout<<initCount()<<endl;
    		}
    	}
    }
}