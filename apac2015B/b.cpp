/*input
7
1 2 1
1 1 1
2 1 1
20 1 1
1 3 1
2 3 1
10 4 10
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
#include <bitset>

using namespace std; 

int main(int argc, char const *argv[])
{	
	// freopen("B-small-practice.in","r",stdin);
    // freopen("output.out","w",stdout);
    cout<<fixed<<setprecision(8);
    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int bottles, level, num;

        cin>>bottles>>level>>num;

        double answer = 0;
        cout<<"Case #"<<i+1<<": ";
        cout<<answer;
        cout<<endl;
    }
}