/*input
2
2 2
1 4
0 0
0 1
3 2
1 2 3
0 1
1 2
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

#define INF INT_MAX

using namespace std; 

int main(int argc, char const *argv[])
{   
    freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;

    cout<<fixed<<setprecision(9);

    for (int i = 0; i < testCaseCount; ++i)
    {
        int dimensionCount, queryCount;
        
        cin>>dimensionCount>>queryCount;

        vector<double> lengths(dimensionCount);

        for (int j = 0; j < dimensionCount; ++j)
        {
            cin>>lengths[j];
        }

        cout<<"Case #"<<i+1<<": "<<endl;
        for (int j = 0; j < queryCount; ++j)
        {
            int left, right;
            cin>>left>>right;

            double answer = 1;
            double newDimensionCount = right - left + 1;
            // cout<<" "<<newDimensionCount<<endl;
            for (int k = left; k <= right; ++k)
            {
                answer *= pow(lengths[k], 1/newDimensionCount);
            }            
            cout<<answer<<endl;
        }
        // cout<<endl;
    }
}