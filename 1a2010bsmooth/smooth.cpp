/*input
2
6 6 2 3
1 7 5
100 1 5 3
1 50 7
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

#define INF INT_MAX
#define PAIRINT pair<int, int>

using namespace std; 

int delCost, insCost, minDiff, pixelCount;
vector<int> pixels;
// map<PAIRINT, int> minCostStore;
vector< vector<int> >minCostStore;

int optimalCost(int N, int currentValue)
{
    /*
    PAIRINT key = make_pair(N, currentValue);
    if (minCostStore.find(key) != minCostStore.end())
    {
        return minCostStore[key];
    }
    */
    if (minCostStore[N][currentValue] != -1)
    {
        return minCostStore[N][currentValue];
    }
    if (N == 0)
    {
        return 0;
    }
    // cout<<N<<" "<<currentValue<<" "<<pixels[N-1]<<endl;

    int noOpCost = INF;
    if (abs(currentValue - pixels[N-1]) <= minDiff)
    {
        noOpCost = optimalCost(N-1, pixels[N-1]);
    }

    int netDelCost = delCost + optimalCost(N-1, currentValue);

    int changeCost = INF;
    for (int i = 0; i <= 255; ++i)
    {
        if (abs(currentValue - i) <= minDiff )
        {
            int newChangeCost = abs(pixels[N-1] - i) + optimalCost(N-1, i);
            // cout<<newChangeCost<<endl;
            changeCost = min(changeCost, newChangeCost);
        }
        else if (minDiff != 0)
        {
            int insCount = (abs(currentValue-i) - 1)/minDiff;
            int newChangeInsCost = abs(pixels[N-1] - i ) + insCost*insCount + optimalCost(N-1, i);
            changeCost = min(changeCost, newChangeInsCost);
        }
    }
    // cout<<netInsCost<<" "<<netDelCost<<" "<<changeCost<<" "<<currentValue<<" "<<pixels[N-1]<<endl;

    int minCost = min(min(noOpCost, netDelCost), changeCost);
    // minCostStore[key] = minCost;
    minCostStore[N][currentValue] = minCost;
    // cout<<minCost<<endl;
    return minCost;
}

int main(int argc, char const *argv[])
{   
    freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        cin>>delCost>>insCost>>minDiff>>pixelCount;
        pixels = vector<int>(pixelCount);

        for (int j = 0; j < pixelCount; ++j)
        {
            cin>>pixels[j];
        }

        // minCostStore = map<PAIRINT, int> ();
    	minCostStore.clear();
        minCostStore.resize(pixelCount, vector<int>(256, -1));
        cout<<"Case #"<<i+1<<": ";

        int minCost = INF;
        for (int j = 0; j <= 255; ++j)
        {
            minCost = min(minCost, optimalCost(pixelCount-1, j) + abs(pixels[pixelCount-1] - j));
            // cout<<minCost<<" "<<i<<" "<<pixels[pixelCount-1]<<endl;
        }
        for (int j = 1; j <= pixelCount; ++j)
        {
            minCost = min(minCost, optimalCost(pixelCount-j, pixels[pixelCount-j]) + (j-1)*delCost);
        }

        cout<<minCost;

    	cout<<endl;
    }

}