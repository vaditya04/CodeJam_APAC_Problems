/*input
3
2
200 100 100
3
10000 3000 4000 5000
5
3000 100 100 100 100 100
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

#define PRECISION 0.000000000001

vector<double> monthlyIncome;
double initialCost;
int monthCount;

double compute(double r)
{

    // cout<<pow(1.0+r, monthCount)<<" "<<pow(1.0+r, monthCount/2.0)<<" "<<pow(1.0+r, monthCount/10.0)<<endl;
    double val = 0 - (initialCost)*pow(1.0+r, monthCount);

    for (int i = 0; i < monthCount; ++i)
    {
        val += (monthlyIncome[i])*pow(1.0+r, (double)(monthCount - i - 1));
    }
    // cout<<val<<endl;
    return val;
}

int main(int argc, char const *argv[])
{	
    freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    cout<<fixed<<setprecision(11);

    // cout<<DBL_MAX<<endl;

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        cin>>monthCount;

        cin>>initialCost;

        monthlyIncome = vector<double> (monthCount);

        for (int j = 0; j < monthCount; ++j)
        {
            cin>>monthlyIncome[j];
        }

        double upper = 1.0;
        double lower = -1.0;
        double mid;

        while (lower<upper)
        {
            mid = (lower + upper)/2.0; 
            if ((upper-lower) < PRECISION)
            {
                break;
            }

            double val = compute(mid);

            if (val<0.0)
            {
                upper = mid;
            }
            else if (val > 0.0)
            {
                lower = mid;
            }
            else
            {
                break;
            }
        }

        double answer = (lower + upper)/2.0;
        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}