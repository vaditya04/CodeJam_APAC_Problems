/*input
3
5 3 10 5
0 2 5 6 7
1 1 1 1 4
5 3 10 5
0 2 3 5 7
2 1 1 1 4
5 3 10 5
0 2 3 4 7
2 1 1 1 4
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

using namespace std; 

int main(int argc, char const *argv[])
{
	freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


	long long testCaseCount;

	cin>>testCaseCount;

	for (long long i = 0; i < testCaseCount; ++i)
	{
		long long numChickens, numRequired, distance, time;
		cin>>numChickens>>numRequired>>distance>>time;
		vector<long long> positions;
		vector<long long> velocities; 

		for (long long j = 0; j < numChickens; ++j)
		{
			long long temp; 
			cin>>temp;
			positions.push_back(temp);
		}
		for (long long j = 0; j < numChickens; ++j)
		{
			long long temp; 
			cin>>temp;
			velocities.push_back(temp);
		}

		long long reachingCount = 0;
		long long lowerLimit = -1;
		for (long long j = numChickens-1; j >= 0; --j)
		{
			if ((double)((double)distance - (double)positions[j])/(double)velocities[j] <= (double)time)
			{
				// cout<<"TIME "<<(double)((double)distance - (double)positions[j])/(double)velocities[j]<<" "<<positions[j]<<" "<<velocities[j]<<endl;
				reachingCount++;
				if (reachingCount >= numRequired)
				{
					lowerLimit = j;
					break;
				}
			}
		}
		if (lowerLimit >= numChickens - numRequired || numRequired == 0)
		{
			cout<<"Case #"<<i+1<<": "<<"0"<<endl;
		}
		else if (lowerLimit == -1)
		{
			cout<<"Case #"<<i+1<<": "<<"IMPOSSIBLE"<<endl;
		}
		else
		{
			// long long negative = 0, positive = 0;
			long long swaps = 0;
			for (long long j = lowerLimit; j < numChickens; ++j)
			{
				if ((double)((double)distance - (double)positions[j])/(double)velocities[j] > (double)time)
				{
					swaps += j - lowerLimit;
					lowerLimit++;
				}

			}
			cout<<"Case #"<<i+1<<": "<<swaps<<endl;
		}

	}
	return 0;
}