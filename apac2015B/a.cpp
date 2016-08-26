/*input
4
1 1
3 4
5 5
15 15
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

#define MOD 1000000007

vector<vector<long long> > passwordStore;
vector<vector<long long> > factorialStore;

long long computePower(long long m , long long n)
{
    long long answer = 1;
    for (int i = 0; i < n; ++i)
    {
        answer *= m;
        answer %= MOD; 
    }
    return answer;
}

long long computeFactorial(long long n, long long i)
{
    if (factorialStore[n][i] != -1)
    {
        return factorialStore[n][i];
    }
    else if ( i == n || i == 0)
    {
        factorialStore[n][i] = 1;
    }
    else if (i == n-1 || i == 1)
    {
        factorialStore[n][i] = n%MOD;
    }
    else
    {
        factorialStore[n][i] = (factorialStore[n-1][i-1] + factorialStore[n-1][i])%MOD;

    }

    return factorialStore[n][i];
}

long long computePasswords(long long charCount, long long stringLength)
{
    if (passwordStore[stringLength][charCount] != -1)
    {
        return passwordStore[stringLength][charCount];
    }
    else if (stringLength < charCount)
    {
        passwordStore[stringLength][charCount] = 0;
    }
    else if (charCount == 1)
    {
        passwordStore[stringLength][charCount] = 1;
    }
    else if (charCount == 0)
    {
        passwordStore[stringLength][charCount] = 0;
    }
    else
    {
        long long answer = computePower(charCount, stringLength);
        for (int i = charCount-1; i > 0; --i)
        {
            answer -= computePasswords(i, stringLength)*computeFactorial(charCount, charCount-i);
            answer %= MOD;
        }

        passwordStore[stringLength][charCount] = answer;
    }
    return passwordStore[stringLength][charCount];

}

long long positiveMod(long long input)
{
    while (input<0)
    {
        input = (input%MOD + MOD)%MOD;
    }
    return input;
}

int main(int argc, char const *argv[])
{	
	freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;

    passwordStore.resize(101, vector<long long>(101, -1));
    factorialStore.resize(101, vector<long long>(101, -1));

    for (int i = 0; i < testCaseCount; ++i)
    {
        int charCount, stringLength;

        cin>>charCount>>stringLength;

        long long answer = computePasswords(charCount, stringLength);

        cout<<"Case #"<<i+1<<": ";
        
        cout<<positiveMod(answer);
        cout<<endl;
    }
}