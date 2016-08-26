/*input
4
ag
aa
abcde
x
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

long long computeWordCount(string word)
{
	long long answer = 1;

	if (word.length() == 1)
	{
		return answer;
	}
	char a, b, c;


	a = word[0];
	b = word[1];

	if (a == b)
	{
		answer *= 1;
	}
	else
	{
		answer *= 2;
	}

	for (int i = 1; i < word.length()-1; ++i)
	{
		a = word[i-1];
		b = word[i];
		c = word[i+1];
		if (a != b && b != c && a != c)
		{
			answer *= 3;
		}
		else if (a == b && b == c)
		{
			answer *= 1;
		}
		else if ((a == b && b != c )|| (a == c && b != c )|| (b == c && a != c))
		{
			answer *= 2;
		}
		answer %= MOD;
	}

	a = word[word.length() - 2];
	b = word[word.length() - 1];

	if (a == b)
	{
		answer *= 1;
	}
	else
	{
		answer *= 2;
		answer %= MOD;
	}

	return answer;
}

int main(int argc, char const *argv[])
{	
    freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
    	string word;
    	cin>>word;
        cout<<"Case #"<<i+1<<": ";

        long long answer = computeWordCount(word);
        cout<<answer<<endl;
    }
}