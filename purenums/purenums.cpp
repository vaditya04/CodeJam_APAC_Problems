/*input
5
2
3
4
5
6
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

using namespace std; 

long long answerStore[501][501];

long long answers[501];

long long C[503][503];

int main(int argc, char const *argv[])
{	
	freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);
    long int modVal = 100003;

	long long testCaseCount;

	for (int i = 0; i < 501; ++i)
	{
		C[i][0] = 1;
		C[i][1] = i;
		C[i][i-1] = i;
		C[i][i] = 1;
	}

	for (int i = 1; i < 502; ++i)
	{
		for (int j = 1; j < i-1; ++j)
		{
			C[i][j] = (C[i-1][j] + C[i-1][j-1])%modVal;
		}
	}

	for (int i = 0; i < 501; ++i)
	{
		answerStore[i][1] = 1;		
	}

	for (int i = 2; i < 501; ++i)
	{
		answers[i] = 0;
		for (int j = 2; j < i; ++j)
		{
			for (int k = 1; k < j; ++k)
			{
				answerStore[i][j] += answerStore[j][k]*C[i-j-1][j-k-1];
				answerStore[i][j] %=modVal;
			}	
			answers[i] += answerStore[i][j];
			answers[i] %= modVal;
			
		}
		answers[i] += answerStore[i][1];
		answers[i] %= modVal;
	}


	cin>>testCaseCount;

	for (int i = 0; i < testCaseCount; ++i)
	{
		int n;
		cin>>n;
		cout<<"Case #"<<i+1<<": "<<answers[n]<<endl;
	}

	return 0;
}