/*input
2
1
SFO
DFW
4
MIA
ORD
DFW
JFK
SFO
DFW
JFK
MIA
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

class Compare
{
public:
    bool operator() (vector<string> a, vector<string> b)
    {
        return a[0] < b[0];
    }
    bool operator() (string a, vector<string> b)
    {
        return a < b[0];
    }
    bool operator() (vector<string> a, string b)
    {
        return a[0] < b;
    }
};

int main(int argc, char const *argv[])
{	
	freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;
	for (int i = 0; i < testCaseCount; ++i)
    {
        int flightCount;
        cin>>flightCount;

        vector<vector<string> > sourceArr(flightCount, vector<string>(2)), destinArr(flightCount, vector<string>(2));

        for (int j = 0; j < flightCount; ++j)
        {
            string source, destin;
            cin>>source>>destin;
            sourceArr[j][0] = source;
            sourceArr[j][1] = destin;

            destinArr[j][0] = destin;
            destinArr[j][1] = source;
        }

        sort(sourceArr.begin(),sourceArr.end(), Compare());
        sort(destinArr.begin(),destinArr.end(), Compare());

        string currentFlight;

    	cout<<"Case #"<<i+1<<": ";
        for (int j = 0; j < flightCount; ++j)
        {
            // vector<vector<string> >::iterator loc = lower_bound(destinArr.begin(), destinArr.end(), sourceArr[j][0], Compare());
            if (!binary_search(destinArr.begin(), destinArr.end(), sourceArr[j][0], Compare()))
            {
                cout<<sourceArr[j][0]<<"-"<<sourceArr[j][1]<<" ";
                currentFlight = sourceArr[j][1];
                break;
            }
        }

        // vector<vector<string> >::iterator loc;
        while (binary_search(sourceArr.begin(), sourceArr.end(), currentFlight, Compare()))
        {
            vector<vector<string> >::iterator loc = lower_bound(sourceArr.begin(), sourceArr.end(), currentFlight, Compare());
            cout<<(*loc)[0]<<"-"<<(*loc)[1]<<" ";
            currentFlight = (*loc)[1];
        }


    	cout<<endl;
    }



}