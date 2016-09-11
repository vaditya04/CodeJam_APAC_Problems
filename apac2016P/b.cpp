/*input
3
98 980
98 490
299 1234
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

#define G 9.8
#define PI (4.0*atan(1))

#define PRECISION 0.00000001

using namespace std;

int main(int argc, char const *argv[])
{	
    freopen("B-small-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    cout<<fixed<<setprecision(10);

    for (int i = 0; i < testCaseCount; ++i)
    {
        double V, D;
        cin>>V>>D;
        // cout<<asin(G*D/pow(V,2))<<" "<<sin(asin(G*D/pow(V,2)))<<" "<<G*D/pow(V,2)<<endl;
        double sinVal = G*D/pow(V,2.0);
        double answer;
        if (abs(sinVal-1) < PRECISION)
        {
            answer = 45;
        }
        else
        {
            answer = (asin(sinVal)/2.0)*180.0/PI;
        }
        // double sinHalfVal = 
        // double tanVal = 

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}