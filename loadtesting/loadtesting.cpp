/*input
4
50 700 2
19 57 3
1 1000 2
24 97 2
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
	
	freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


	long long testCaseCount;

	cin>>testCaseCount;

	for (long long i = 0; i < testCaseCount; ++i)
	{
		long long lowerBound, upperBound, factor;
		cin>>lowerBound>>upperBound>>factor;
		long long testsNeeded = 0;

			while (!((double)upperBound/(double)lowerBound <= (double)factor))
			{

				long long tempBound1 = sqrt(upperBound*lowerBound);
				long long tempBound2 = tempBound1 + 1;

				double val1 = max((double)tempBound1/(double)lowerBound, (double)upperBound/(double)tempBound1);
				double val2 = max((double)tempBound2/(double)lowerBound, (double)upperBound/(double)tempBound2);

				long long tempBound;

				if (val1>val2)
				{
					tempBound = tempBound2;
				}	
				else
				{
					tempBound = tempBound1;
				}

				if ((double)tempBound/(double)lowerBound > (double)upperBound/(double)tempBound)
				{
					upperBound = tempBound;
				}
				else
				{
					lowerBound = tempBound;
				}
				testsNeeded++;
			}

		cout<<"Case #"<<i+1<<": "<<testsNeeded<<endl;
	}
	return 0;
}