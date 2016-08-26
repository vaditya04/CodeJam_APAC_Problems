/*input
4
7 3
.......
.......
.......
...R...
...BB..
..BRB..
.RRBR..
6 4
......
......
.R...R
.R..BB
.R.RBR
RB.BBB
4 4
R...
BR..
BR..
BR..
3 3
B..
RB.
RB.
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

using namespace std; 

int main(int argc, char const *argv[])
{	
	freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

	for (int i = 0; i < testCaseCount; ++i)
    {
    	int boardSize, target;
    	cin>>boardSize>>target;

    	bool flagB = false, flagR = false;

    	string R(target, 'R');
    	string B(target, 'B');

    	vector<string> board;
    	for (int j = 0; j < boardSize; ++j)
    	{
	    	string row;
	    	cin>>row;
	    	row.erase(remove(row.begin(), row.end(), '.'), row.end());
	    	string temp(boardSize - row.length(),'.');
	    	row = temp + row;
	    	if (row.find(R) != string::npos)
	    	{
	    		flagR = true;
	    	}
	    	if (row.find(B) != string::npos)
	    	{
	    		flagB = true;
	    	}
	    	board.push_back(row);
	    	// cout<<row<<endl;    	

    	}

    	for (int j = 0; j < boardSize; ++j)
    	{
    		string col = "";
    		for (int k = 0; k < boardSize; ++k)
    		{
    			col += board[k][j];
    		}	    	
    		string B(target, 'B');
	    	if (col.find(B) != string::npos)
	    	{
	    		flagB = true;
	    	}

    		string R(target, 'R');
	    	if (col.find(R) != string::npos)
	    	{
	    		flagR = true;
	    	}

    	}

    	for (int j = 0; j < boardSize-target+1; ++j)
    	{
    		string s1="", s2="", s3="", s4="";
    		for (int k = 0; k < boardSize; ++k)
    		{
    			if (j + k < boardSize)
	    			s1 += board[j + k ][k];
    			if (boardSize- 1 - j - (boardSize - k - 1) >= 0)
	    			s2 += board[boardSize- 1 - j - (boardSize - k - 1)][(boardSize - 1 - k)];
	    		if (boardSize- 1 - j - (boardSize - k - 1)>= 0)
	    		{
	    			s3 += board[boardSize- 1 - j - (boardSize - k - 1)][k];
	    		}
	    		if (j+k < boardSize)
	    		{
	    			s4 += board[j+k][boardSize-1-k];
	    		}


    		}
    		if (s1.find(R) != string::npos || s2.find(R) != string::npos || s3.find(R) != string::npos || s4.find(R) != string::npos)
    		{
    			flagR = true;
    		}
    		if (s1.find(B) != string::npos || s2.find(B) != string::npos || s3.find(B) != string::npos || s4.find(B) != string::npos)
    		{
    			flagB = true;
    		}

    	}


    	cout<<"Case #"<<i+1<<": ";
    	if (flagB && flagR)
    	{
    		cout<<"Both";
    	}
    	else if (flagB && !flagR)
    	{
    		cout<<"Blue";
    	}
    	else if (!flagB && flagR)
    	{
    		cout<<"Red";
    	}
    	else
    	{
    		cout<<"Neither";
    	}
    	cout<<endl;
    }

}