/*input
4
1 0
1 1
3 2
30000 20000
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

int main(int argc, char const *argv[])
{	
    // freopen("A-small-attempt0.in","r",stdin);
    // freopen("output.out","w",stdout);

    // cout<<fixed<<setprecision(10);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int L, R;
        cin>>L>>R;

        long long minLR = min(L, R);

        long long answer = 0;

        answer = minLR*(minLR+1)/2;

        /*for (int j = 0; j < minLR; ++j)
        {
            answer += (minLR-j);
        }*/

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}