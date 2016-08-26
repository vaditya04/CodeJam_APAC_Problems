/*input
2
2 3 
0 0
2 0
0 0
0 1
2 0
1 10
1 10
1 10
1 10
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


int main(int argc, char const *argv[])
{	
    freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
    	int N, trendyNumber;
    	cin>>N>>trendyNumber;

    	vector<int> A, B, C, D;

    	map<long long, long long> prod1, prod2;


    	for (int j = 0; j < N; ++j)
    	{
    		int num;
    		cin>>num;
    		A.push_back(num);
    	}

    	for (int j = 0; j < N; ++j)
    	{
    		int num;
    		cin>>num;
    		B.push_back(num);
    	}

    	for (int j = 0; j < N; ++j)
    	{
    		int num;
    		cin>>num;
    		C.push_back(num);
    	}

    	for (int j = 0; j < N; ++j)
    	{
    		int num;
    		cin>>num;
    		D.push_back(num);
    	}

    	for (int j = 0; j < N; ++j)
    	{
    		for (int k = 0; k < N; ++k)
    		{
    			if (prod1.find(A[j]^B[k]) != prod1.end())
    			{
    				prod1[A[j]^B[k]]++;
    			}
    			else
    			{
    				prod1[A[j]^B[k]] = 1;
    			}

    			if (prod2.find(C[j]^D[k]^trendyNumber) != prod2.end())
    			{
    				prod2[C[j]^D[k]^trendyNumber]++;
    			}
    			else
    			{
    				prod2[C[j]^D[k]^trendyNumber] = 1;
    			}
    		}
    	}

    	long long answer = 0;

    	for (map<long long, long long>::iterator j = prod1.begin(); j != prod1.end(); ++j)
    	{
    		if (prod2.find(j->first) != prod2.end())
    		{
    			answer += j->second * prod2[j->first];
    		}
    	}

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}