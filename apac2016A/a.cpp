/*input
4
1
2
3
10
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


int computeBit(long long pos, long long length)
{
    if (pos == length/2 + 1)
    {
        return 0;
    }
    else if (pos == 1)
    {
        return 0;
    }
    else if (pos == length)
    {
        return 1;
    }
    else
    {
        long long newPos = length - pos+1;
        long long newLength = length + 1;
        while (newLength > newPos)
        {
            newLength /= 2;
        }
        newLength *= 2;
        newLength--;
        // cout<<newPos<<" "<<newLength<<endl;
        return !computeBit(newPos, newLength);
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
        long long K;
        cin>>K;


        long long lengthCurrent = 2;
        for (long long j = 0; j < K; ++j)
        {
            if (lengthCurrent-1>= K)
            {
                lengthCurrent--;
                break;
            }
            lengthCurrent*=2;            
        }

        // cout<<lengthCurrent<<endl;
        int answer = computeBit(K, lengthCurrent);

        cout<<"Case #"<<i+1<<": ";
        
        cout<<answer;

        cout<<endl;
    }
}