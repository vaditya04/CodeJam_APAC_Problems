/*input
2
3
..*
..*
**.
5
..*..
..*..
.*..*
.*...
.*...
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

#define PAIRINT pair<int, int>

using namespace std; 

class Compare
{
public:
    bool operator() (PAIRINT a, PAIRINT b)
    {
        return a.first < b.first;
    }
/*    bool operator() (string a, vector<string> b)
    {
        return a < b[0];
    }
    bool operator() (vector<string> a, string b)
    {
        return a[0] < b;
    }*/
};



bool inBounds(int i, int j, int min, int max)
{
    if (i<min || i>= max || j < min || j >= max)
    {
        return false;
    }
    return true;
}

int countNeighbours(vector<vector<int> > &grid, int i, int j)
{
    if (grid[i][j] == -1)
        return -1;
    else if (grid[i][j] != 0)
    {
        return grid[i][j];
    }
    else
    {
        for (int p = i-1; p < i+2; ++p)
        {
            for (int q = j-1; q < j+2; ++q)
            {
                if (inBounds(p, q, 0, grid.size()))
                {
                    if (p!=i || q!=j)
                    {
                        if (grid[p][q] == -1)
                        {
                            grid[i][j]++;
                        }
                    }
                }
            }
        }
        return grid[i][j];
    }

}

void recurseReveal(vector<vector<int> > &grid, int i, int j)
{
    grid[i][j] = -2;
    for (int p = i-1; p < i+2; ++p)
    {
        for (int q = j-1; q < j+2; ++q)
        {
            if (inBounds(p, q, 0, grid.size()))
            {
                if (p!=i || q!=j)
                {
                    if (grid[p][q] == 0)
                    {
                        recurseReveal(grid, p, q);
                    }
                    else
                    {
                        grid[p][q] = -2;
                    }
                }
            }
        }
    }

}

int main(int argc, char const *argv[])
{	
	freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;


    for (int i = 0; i < testCaseCount; ++i)
    {
        int gridSize;
        cin>>gridSize;

        vector<vector<int> > grid(gridSize, vector<int>(gridSize));        

        for (int j = 0; j < gridSize; ++j)
        {
            string row;
            cin>>row;

            for (int k = 0; k < gridSize; ++k)
            {
                if (row[k] == '.')
                {
                    grid[j][k] = 0;
                }                  
                else
                {
                    grid[j][k] = -1;
                }         
            }            
        }

        vector<PAIRINT> listMins;

        for (int j = 0; j < gridSize; ++j)
        {
            for (int k = 0; k < gridSize; ++k)
            {
                int neighbourCount = 0;
                if ((neighbourCount = countNeighbours(grid, j, k)) != -1)
                {
                    listMins.push_back(make_pair(neighbourCount, j+k*gridSize));
                }
            }            
        }        
        sort(listMins.begin(), listMins.end(), Compare());

        int revealCount = 0;
        for (int j = 0; j < listMins.size(); ++j)
        {
            int p = listMins[j].second%gridSize;
            int q = (listMins[j].second - p)/gridSize;
            if (grid[p][q] != -2)
            {
                if (grid[p][q] == 0)
                {
                    recurseReveal(grid, p, q);
                    revealCount++;
                }
                else
                {
                    grid[p][q] = -2;
                    revealCount++;
                }
            }
        }

        cout<<"Case #"<<i+1<<": ";
        cout<<revealCount;
    	cout<<endl;
    }



}