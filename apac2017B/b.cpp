
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

#define MOD 1000000007


long long power(long long x, long long y, long long p)
{
    long long res = 1;      
    x = x % p;  
    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;

        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

int main(int argc, char const *argv[])
{	
    freopen("B-small-attempt0.in","r",stdin);
    freopen("output.out","w",stdout);

    // cout<<fixed<<setprecision(10);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        long long A, B, N, divisor;

        cin>>A>>B>>N>>divisor;

        long long answer = 0;

        for (int j = 1; j <= N; ++j)
        {
            for (int k = 1; k <= N; ++k)
            {
                if (j == k)
                {
                    continue;
                }
                if ((power(j, A, divisor) + power(k, B, divisor))%divisor == 0)
                {
                    answer++;
                    answer %= MOD;
                }

            }
        }

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}