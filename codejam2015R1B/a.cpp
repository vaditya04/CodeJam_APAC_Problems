/*input
3
1
19
23
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
#include <stack>

using namespace std;

map <long long, long long> memoize;

long long getMinMoves(long long n)
{
    if (n == 1)
    {
        return 1;
    }
    // cout<<n<<endl;
    if (memoize.find(n) != memoize.end())
    {
        return memoize[n];
    }

    long long reverse = 0;
    long long temp = n;
  
    while (temp != 0)
    {
        reverse = reverse*10 + (temp%10);
        temp /= 10;
    }
    // cout<<reverse<<" "<<n<<endl;
    if (reverse >= n)
    {
        memoize[n] = getMinMoves(n-1) + 1;
    }
    else
    {
        memoize[n] = min(getMinMoves(n-1) + 1, getMinMoves(reverse) + 1);    
    }

    // cout<<n<<" "<<memoize[n]<<endl;
    return memoize[n];
}

int main(int argc, char const *argv[])
{	
    // freopen("A-small-practice.in","r",stdin);
    // freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        long long n;
        cin>>n;

        long long answer = getMinMoves(n);

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}