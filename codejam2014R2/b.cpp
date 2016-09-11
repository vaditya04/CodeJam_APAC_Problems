/*input
2
3
1 2 3
5
1 8 10 3 7
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

int main(int argc, char const *argv[])
{   
    freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    // cout<<fixed<<setprecision(10);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int n;
        cin>>n;

        vector<int> arr(n);
        
        for (int j = 0; j < n; ++j)
        {
            cin>>arr[j];
        }

        int swapCount = 0;

        for (int j = 0; j < n; ++j)
        {
            int minPos = -1, minVal = INF;
            for (int k = 0; k < arr.size(); ++k)
            {
                if (minVal > arr[k])
                {
                    minVal = arr[k];
                    minPos = k;
                }
            }

            swapCount += min(minPos, (int)(arr.size()-minPos-1));
            arr.erase(arr.begin() + minPos);
        }
        
        cout<<"Case #"<<i+1<<": ";

        cout<<swapCount;
        
        cout<<endl;
    }
}