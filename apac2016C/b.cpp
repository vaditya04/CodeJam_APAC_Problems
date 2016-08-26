/*input
3
2
20 1
100 5
10
25 241
27 262
43 407
44 413
57 536
64 601
67 637
84 789
95 893
96 903
10
0 0
8 2
8 2
17 4
30 7
39 9
69 16
73 17
82 19
91 21
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

#define INF LLONG_MAX
#define NEGINF LLONG_MIN
using namespace std;

int main(int argc, char const *argv[])
{	
    freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int statusCount;
        cin>>statusCount;

        long long finalLowerBound = NEGINF, finalUpperBound = INF;
        for (int j = 0; j < statusCount; ++j)
        {
            int percentage;
            long long fileNum;
            cin>>percentage>>fileNum;
            // cout<<percentage<<" "<<fileNum<<endl;

            long long lowerBound, upperBound;

            if (percentage == 0)
            {
                upperBound = INF;
            }
            else
            {
                upperBound = (100.0*fileNum)/(double)(percentage);
            }
            if (percentage == 100)
            {
                lowerBound = upperBound-1;
            }
            else
            {
                lowerBound = (100.0*fileNum)/(double)(percentage+1);            
            }
            // cout<<lowerBound<<" "<<upperBound<<endl;
            finalLowerBound = max(finalLowerBound, lowerBound);
            finalUpperBound = min(finalUpperBound, upperBound);
        }

        cout<<"Case #"<<i+1<<": ";

        if (finalUpperBound - finalLowerBound != 1/* || finalUpperBound - finalLowerBound <= 0*/)
        {
            cout<<"-1";
        }
        else
        {
            cout<<finalUpperBound;
        }

        cout<<endl;
    }
}