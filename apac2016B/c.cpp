/*input
9
2
3
4
6
8
9
30
36300
1000000000000000
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

using namespace std;

#define ACCURACY 100

map <long long, bool> winningNumber;
set <int> prime;
vector<bool> sieve(31622777, true);

void sieveOfEratosthenes()
{
    sieve[0] = false;
    sieve[1] = false;

    for (int i = 0; i < sieve.size(); ++i)
    {
        if (sieve[i] == false)
        {
            continue;
        }
        else
        {
            prime.insert(i);
            for (int j = 2; j <= sieve.size()/i; ++j)
            {
                sieve[i*j] = false;
            }
        }
    }
}

long long power(long long x, long long y, long long p)
{
    long long res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}
 
bool millerTest(long long d, long long n)
{
    long long a = 2 + rand() % (n - 4);
 
    // Compute a^d % n
    long long x = power(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;

    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)      return false;
        if (x == n-1)    return true;
    }
 
    // Return composite
    return false;
}
 
bool isPrime2(long long n)
{
    long long k = ACCURACY;
    // Corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
 
    // Find r such that n = 2^d * r + 1 for some r >= 1
    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;
 
    // Iterate given nber of 'k' times
    for (long long i = 0; i < k; i++)
         if (millerTest(d, n) == false)
              return false;
 
    return true;
}

bool isPrime(int n)
{
    return prime.find(n) != prime.end(); 
}

long long computeDigitSum(long long n)
{
    long long sum=0;
    while (n != 0)
    {
        sum += n%10;
        n = n/10;
    }
    return sum;
}

void getPrimeFactors(long long n, vector<long long> &primeFactors)
{
    for (long long i = 2; i <= sqrt(n); ++i)
    {
        if (n%i == 0)
        {
            primeFactors.push_back(i);
            while (n%i == 0)
            {
                n = n/i;
            }
        }       
    }

    if (n != 1)
    {
        primeFactors.push_back(n);
    }
}

bool getWinner(long long n, bool playerFlag)
{
    // cout<<n<<" "<<endl;
    if (winningNumber.find(n) != winningNumber.end())
    {
        if (winningNumber[n])
        {
            return playerFlag;
        }
        else
        {
            return !playerFlag;
        }
    }
    long long digitSum = computeDigitSum(n);
    if (digitSum == 1 || isPrime(digitSum))
    {
        winningNumber[n] = false;
        return !playerFlag;
    }

    vector<long long> primeFactors;
    getPrimeFactors(n, primeFactors);

    for (int i = 0; i < primeFactors.size(); ++i)
    {
        long long newN = n, primeFactor = primeFactors[i];
        while(newN%primeFactor == 0)
        {
            newN /= primeFactor;
        }    
        if (getWinner(newN, !playerFlag) == playerFlag)
        {
            winningNumber[n] = true;
            return playerFlag;
        }
    }

    if (primeFactors.size() == 0)
    {
        winningNumber[n] = true;
        return playerFlag;
    }
    winningNumber[n] = false;
    return !playerFlag;

}

int main(int argc, char const *argv[])
{	
	freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    sieveOfEratosthenes();

    int testCaseCount;

    cin>>testCaseCount;

    srand(time(NULL));
 
    for (int i = 0; i < testCaseCount; ++i)
    {

        cout<<"Case #"<<i+1<<": ";
        long long n;
        cin>>n;
        // cout<<n<<" "<<computeDigitSum(n)<<endl;
        bool winnerFlag = getWinner(n, false);
        if (winnerFlag)
        {
            cout<<"Seymour";
        }
        else
        {
            cout<<"Laurence";
        }
        cout<<endl;
    }
}