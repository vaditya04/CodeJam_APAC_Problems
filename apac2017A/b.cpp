/*input
3
3 3
3 5 5
5 4 5
5 5 5
4 4
5 5 5 1
5 1 1 5
5 1 5 5
5 2 5 8
4 3
2 2 2
2 1 2
2 1 2
2 1 2
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
#include <bitset>

using namespace std;

#define INF INT_MAX

int R, C;

int getConnectedAreas(int, int, vector<vector<int> > &, set<pair<int, int> > &);

int conditional(int i, int j,  int p, int q, vector<vector<int> > &newIsland, set<pair<int, int> > &connectedAreas)
{
    int val;
    if (newIsland[i][j] <= newIsland[p][q] )
    {
        if (connectedAreas.find(make_pair(i, j)) == connectedAreas.end())
        {
            connectedAreas.insert(make_pair(i, j));
            // sort(connectedAreas.begin(), connectedAreas.end());
            val = getConnectedAreas(i, j, newIsland, connectedAreas);            
        }
        else
        {
            val = INF;
        }
    }
    else
    {
        val = newIsland[i][j];
    }
    return val;

}

int getConnectedAreas(int i, int j, vector<vector<int> > &newIsland, set<pair<int, int> > &connectedAreas)
{
    if (i == 0 || j == 0 || i == R-1 || j == C-1)
    {
        return 0;
    }
    int val1, val2, val3, val4;

    val1 = conditional(i+1, j,i, j, newIsland, connectedAreas);
    val2 = conditional(i-1, j,i, j, newIsland, connectedAreas);
    val3 = conditional(i, j-1,i, j, newIsland, connectedAreas);
    val4 = conditional(i, j+1, i, j, newIsland, connectedAreas);

    // cout<<val1<<" "<<val2<<" "<<val3<<" "<<val4<<endl;
    // if (val1 && val2 && val3 && val4)
    // {
        return min(min(val1, val2), min(val3, val4));
    // }

    // return 0;

}


int main(int argc, char const *argv[])
{	
    freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        cin>>R>>C;

        vector<vector<int> > island(R, vector<int>(C, 0));
        // vector<vector<bool> > visited(R, vector<bool>(C,false));
        priority_queue<pair<int, pair<int, int> > > lowAreas; 

        for (int j = 0; j < R; ++j)
        {
            for (int k = 0; k < C; ++k)
            {
                cin>>island[j][k];
                if (j != 0 && j != R-1 && k != 0 && k != C-1)
                {
                    lowAreas.push(make_pair(island[j][k], make_pair(j, k)));
                }
            }
        }

        vector<vector<int> > newIsland = island;

        while (!lowAreas.empty())
        {
            int j = lowAreas.top().second.first;
            int k = lowAreas.top().second.second;
            lowAreas.pop();

            // int currentVal = newIsland[j][k];

            set<pair<int, int> > connectedAreas;
            connectedAreas.insert(make_pair(j, k));
            int updateValue = getConnectedAreas(j, k, newIsland, connectedAreas);
            // cout<<j<<" "<<k<<" "<<updateValue<<endl;
            if (updateValue != 0 && updateValue != INF)
            {
                for (set<pair<int, int> >::iterator r = connectedAreas.begin(); r != connectedAreas.end(); ++r)
                {
                    pair<int, int> element = *r;
                    int p = element.first;
                    int q = element.second;
                    if (newIsland[p][q] < updateValue)
                    {
                        newIsland[p][q] = updateValue;
                    }
                }                
            }
        }


        int answer = 0;

        for (int j = 0; j < R; ++j)
        {
            for (int k = 0; k < C; ++k)
            {
                answer += newIsland[j][k] - island[j][k];
            }
        }

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}