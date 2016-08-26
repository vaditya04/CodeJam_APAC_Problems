/*input
5
CCJJ
CJCJ
CJJC
CJJJ
CCCCCC
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

int main(int argc, char const *argv[])
{	
	freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

	long long testCaseCount;

	cin>>testCaseCount;

	for (long long i = 0; i < testCaseCount; ++i)
	{
		string S;
		cin>>S;
		long long maxScore = 0;

		long long length = S.length();

		vector<char> stack;

		long long pushCount = 0;

		for (long long j = 0; j < length; ++j)
		{
			if (pushCount == length/2)
			{
				if (stack.back() == S[j])
				{
					stack.pop_back();
					maxScore += 10;
				}
				else
				{
					stack.pop_back();
					maxScore += 5;
				}
				continue;
			}

			if (stack.size() == 0 || stack.back() != S[j])
			{
				stack.push_back(S[j]);
				pushCount++;
			}
			else if (stack.back() == S[j])
			{
				stack.pop_back();
				maxScore += 10;
			}
			
		}

		cout<<"Case #"<<i+1<<": "<<maxScore<<endl;
	}

	return 0;
}