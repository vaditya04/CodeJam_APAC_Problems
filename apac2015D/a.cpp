/*input
2
2
3 4
1 2 
3
1 2 9 
5 3 8 
4 6 7 
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
        int mazeSize;
        cin>>mazeSize;
        // cout<<mazeSize<<endl;
        vector<vector<int> > maze(mazeSize, vector<int> (mazeSize) );
        vector<vector<int> > mazeLoc (pow(mazeSize,2), vector<int> (2));
        vector<int> pathCount (pow(mazeSize,2), 0);
        
        for (int j = 0; j < mazeSize; ++j)
        {
            for (int k = 0; k < mazeSize; ++k)
            {
                cin>>maze[j][k];
                maze[j][k]--;
                // cout<<maze[j][k]<<endl;
                mazeLoc[maze[j][k]][0] = j;
                mazeLoc[maze[j][k]][1] = k;
            }
        }
        for (int j = pow(mazeSize,2)-1; j >= 0; --j)
        {
            int p, q;
            p = mazeLoc[j][0];
            q = mazeLoc[j][1];
            // cout<<p<<" "<<q<<" "<<j+1<<endl;
            int thisPath = pathCount[maze[p][q]];
            if (p>0)
            {
                if (maze[p-1][q] == j-1)
                {
                    pathCount[maze[p-1][q]] = max(thisPath+1, pathCount[maze[p-1][q]]);
                }
            }
            if (q>0)
            {
                if (maze[p][q-1] == j-1)
                {
                    pathCount[maze[p][q-1]] = max(thisPath+1, pathCount[maze[p][q-1]]);
                }
            }

            if (p<mazeSize-1)
            {
                if (maze[p+1][q] == j -1)
                {
                    pathCount[maze[p+1][q]] = max(thisPath+1, pathCount[maze[p+1][q]]);
                }
            }

            if (q<mazeSize-1)
            {
                if (maze[p][q+1] == j-1)
                {
                    pathCount[maze[p][q+1]] = max(thisPath+1, pathCount[maze[p][q+1]]);
                }
            }
        }

    	cout<<"Case #"<<i+1<<": ";

        int maxPath = INT_MIN;
        int maxIndex = -1;

        for (int j = 0; j < pow(mazeSize,2); ++j)
        {
            if (maxPath < pathCount[j])
            {
                maxPath = pathCount[j];
                maxIndex = j;
            }
        }
        cout<<maxIndex+1<<" "<<maxPath+1;
    	cout<<endl;
    }



}