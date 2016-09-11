/*input
3
1 1 5 3
1 2 4 5
1 1 2 2
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

#define MOD 1000000007

long long N;

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

void getModCandidates(map<int, vector<int> > &A, int divisor, int exponent)
{
    for (long long i = 1; i <= divisor && i <= N; ++i)
    {
        long long newVal = power(i, exponent, divisor);
        // cout<<newVal<<endl;
        if (A.find(newVal) == A.end())
        {
            A[newVal] = vector<int>(0);
        }
        A[newVal].push_back(i);
/*        if (A.find(newVal) == A.end())
        {
            A[newVal] = 1;
        }*/
    }

}

long long getDivisors(long long N, long long start, long long divisor)
{
    long long temp1 = (N - start)/divisor;
    // cout<<temp1<<endl;
    temp1++;
    temp1 %= MOD;
    return temp1;
}

int main(int argc, char const *argv[])
{   
    freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    // cout<<fixed<<setprecision(10);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        long long A, B, divisor;

        cin>>A>>B>>N>>divisor;

        map<int, vector<int> > AVals;
        getModCandidates(AVals, divisor, A);

        map<int, vector<int> > BVals;
        getModCandidates(BVals, divisor, B);

        vector<pair<vector<int>, vector<int> > > modPairs;

        for (map<int, vector<int> >::iterator j = AVals.begin(); j != AVals.end(); ++j)
        {
            if (BVals.find(divisor - j->first) != BVals.end())
            {
                // cout<<j->first<<" "<<divisor-j->first<<" "<<j->second[0]<<" "<<BVals[divisor-j->first][0]<<" "<<endl;
                modPairs.push_back(make_pair(AVals[j->first], BVals[divisor - j->first]));

            }
            if (BVals.find(2*divisor - j->first) != BVals.end())
            {
                // cout<<j->first<<" "<<divisor-j->first<<" "<<j->second[0]<<" "<<BVals[divisor-j->first][0]<<" "<<endl;
                modPairs.push_back(make_pair(AVals[j->first], BVals[2*divisor - j->first]));
            }
            if (j->first == 0)
            {
                if (BVals.find(0) != BVals.end())
                {
                    modPairs.push_back(make_pair(AVals[0], BVals[0]));
                }                
            }
        }

        long long answer = 0;

        for (int j = 0; j < modPairs.size(); ++j)
        {
            // cout<<N<<" "<<setA[0]<<endl;
            vector<int> setA = modPairs[j].first;
            vector<int> setB = modPairs[j].second;

            for (int k = 0; k < setA.size(); ++k)
            {
                for (int r = 0; r < setB.size(); ++r)
                {
                    if (setA[k] != setB[r])
                    {
                        // cout<<setA[k]<<" "<<setB[r]<<endl;
                        long long count1 = getDivisors(N, setA[k], divisor);
                        long long count2 = getDivisors(N, setB[r], divisor);

                        // cout<<count1<<" asd "<<count2<<" "<<setA[k]<<" "<<setB[r]<<" "<<divisor<<" "<<N<<endl;
                        answer += (count1*count2)%MOD;
                        answer %= MOD;
                    }
                    else
                    {
                        long long count1 = getDivisors(N, setA[k], divisor);

                        long long count2 = (count1-1)%MOD;
                        // cout<<count1<<" "<<count2<<endl;
                        count2 = (count2%MOD + MOD)%MOD;

                        answer += (count1*count2)%MOD;
                        answer %= MOD;
                    }
                }
            }

        }

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}