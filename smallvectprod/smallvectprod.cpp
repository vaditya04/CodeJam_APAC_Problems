/*input
2
3
1 3 -5
-2 4 1
5
1 2 3 4 5
1 0 1 0 1
*/

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std; 

int main(int argc, char const *argv[])
{
	freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

	long long testCaseCount;

	cin>>testCaseCount;

	for (long long i = 0; i < testCaseCount; ++i)
	{
		long long vectorSize;
		cin>>vectorSize;
		vector<long long> v1;
		vector<long long> v2;

		for (long long j = 0; j < vectorSize; ++j)
		{
			long long a;
			cin>>a;
			v1.push_back(a);
		}

		sort(v1.begin(),v1.end());
		for (long long j = 0; j < vectorSize; ++j)
		{
			long long a;
			cin>>a;
			v2.push_back(a);
		}

		sort(v2.begin(), v2.end(), greater<long long>());

		long long answer = 0;

		for (long long j = 0; j < vectorSize; ++j)
		{
			answer += v1[j]*v2[j];
		}

		cout<<"Case #"<<i+1<<": "<<answer<<endl;

	}

	return 0;
}