/*input
2
4
15 25 30 35 45 50 10 20
2
15
25
10
10 15 5 12 40 55 1 10 25 35 45 50 20 28 27 35 15 40 4 5
3
5
10
27
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

int main(int argc, char const *argv[])
{	
	freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);
    int testCaseCount;

    cin>>testCaseCount;
	for (int i = 0; i < testCaseCount; ++i)
    {
        int busCount;
        cin>>busCount;

        vector<int> cityCount(99999, 0);
        
        for (int j = 0; j < busCount; ++j)
        {
            int a, b;
            cin>>a>>b;

            for (int k = a; k <= b; ++k)
            {
                cityCount[k]++;
            }
        }

    	cout<<"Case #"<<i+1<<": ";

        int cityNumbers;
        cin>>cityNumbers;
        for (int j = 0; j < cityNumbers; ++j)
        {
            int cityNum;
            cin>>cityNum;
            cout<<cityCount[cityNum]<<" ";
        }

    	cout<<endl;
    }



}