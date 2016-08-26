/*input
2
2
A1-K
A8-Q
3
B2-K
A1-P
H8-Q
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

int index(char a)
{
    if (a <= 'H' && a >= 'A')
    {
        return (a-'A');
    }
    else
    {
        return (a - '1');
    }
}

using namespace std; 
/*
class Compare
{
public:
    bool operator() (vector<string> a, vector<string> b)
    {
        return a[0] < b[0];
    }
    bool operator() (string a, vector<string> b)
    {
        return a < b[0];
    }
    bool operator() (vector<string> a, string b)
    {
        return a[0] < b;
    }
};

*/

int analyzePosition(vector<vector<char> > &board, int i, int j, char piece)
{
    int count = 0;
    if (piece == 'E')
    {
        return 0;
    }
    else if (piece == 'K')
    {
        for (int p = max(i-1,0); p < min(8, i+2); ++p)
        {
            for (int q = max(j-1,0); q < min(8,j+2); ++q)
            {
                if (p != i || q != j)
                {
                    if (board[p][q] != 'E')
                        count++;
                }
            }
        }
        return count;
    }
    else if (piece == 'R')
    {
        for (int p = i+1; p < 8; ++p)
        {
            if (board[p][j] != 'E')
            {
                count++;
                break;
            }
        }
        for (int p = i-1; p >= 0; --p)
        {
            if (board[p][j] != 'E')
            {
                count++;
                break;
            }
        }
        for (int p = j+1; p < 8; ++p)
        {
            if (board[i][p] != 'E')
            {
                count++;
                break;
            }
        }
        for (int p = j-1; p >= 0; --p)
        {
            if (board[i][p] != 'E')
            {
                count++;
                break;
            }
        }
        // cout<<"RO"<<count<<endl;

        return count;
    }
    else if (piece == 'B')
    {
        for (int p = 1; p < 8; ++p)
        {
            if (i+p > 7 || j+p > 7)
            {
                break;
            }
            if (board[i+p][j+p] != 'E')
            {
                count++;
                break;
            }
        }
        for (int p = 1; p < 8; ++p)
        {
            if (i-p < 0 || j-p < 0)
            {
                break;
            }
            if (board[i-p][j-p] != 'E')
            {
                count++;
                break;
            }
        }
        for (int p = 1; p < 8; ++p)
        {
            if (i-p < 0 || j+p > 7)
            {
                break;
            }
            if (board[i-p][j+p] != 'E')
            {
                count++;
                break;
            }
        }
        for (int p = 1; p < 8; ++p)
        {
            if (i+p > 7 || j-p < 0)
            {
                break;
            }
            if (board[i+p][j-p] != 'E')
            {
                count++;
                break;
            }
        }
        // cout<<"BIS"<<count<<endl;
        return count;
    }
    else if (piece == 'Q')
    {
        count = analyzePosition(board, i, j, 'B') + analyzePosition(board, i, j, 'R');
        // cout<<"QUE"<<i<<j<<count<<endl;
        return count;
    }
    else if (piece == 'P')
    {
        if (i<7)
        {
            if (j <7)
            {
                if (board[i+1][j+1] != 'E')
                {
                    count++;
                }
            }
            if (j > 0)
            {
                if (board[i+1][j-1] != 'E')
                {
                    count++;
                }
            }
        }
        // cout<<"PAW"<<count<<endl;
        return count;
    }
    else if (piece == 'N')
    {
        if (i<6)
        {
            if (j<7)
            {
                if (board[i+2][j+1] != 'E')
                {
                    count++;
                }
            }
            if (j>0)
            {
                if (board[i+2][j-1] != 'E')
                {
                    count++;
                }
            }
        }
        if (i>1)
        {
            if (j<7)
            {
                if (board[i-2][j+1] != 'E')
                {
                    count++;
                }
            }
            if (j>0)
            {
                if (board[i-2][j-1] != 'E')
                {
                    count++;
                }
            }

        }

        if (j<6)
        {
            if (i<7)
            {
                if (board[i+1][j+2] != 'E')
                {
                    count++;
                }
            }
            if (i>0)
            {
                if (board[i-1][j+2] != 'E')
                {
                    count++;
                }
            }
        }
        if (j>1)
        {
            if (i<7)
            {
                if (board[i+1][j-2] != 'E')
                {
                    count++;
                }
            }
            if (i>0)
            {
                if (board[i-1][j-2] != 'E')
                {
                    count++;
                }
            }

        }
        return count;
    }

}

int main(int argc, char const *argv[])
{	
	freopen("D-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;


    for (int i = 0; i < testCaseCount; ++i)
    {
        int pieceCount;
        cin>>pieceCount;
        vector<vector<char> > board(8, vector<char>(8, 'E'));

        for (int j = 0; j < pieceCount; ++j)
        {
            string piece;
            cin>>piece;
            board[index(piece[0])][index(piece[1])] = piece[3];
        }

        int kills = 0;

        for (int j = 0; j < 8; ++j)
        {
            for (int k = 0; k < 8; ++k)
            {            
                kills += analyzePosition(board, j, k, board[j][k]);
            }
        }

        cout<<"Case #"<<i+1<<": ";
        cout<<kills;
    	cout<<endl;
    }



}