/*input
3
1 1 1 1 1 1 1 1
3 2 5 1 2 3 4 10
4 3 4 3 3 8 10 10
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
#include <stack>

using namespace std;

#define PAIRINT pair<int, int>
#define INF INT_MAX

int N;

class Compare
{
public:
    bool operator() (PAIRINT a, PAIRINT b)
    {
        if (a.first != b.first)
        {
            return a.first < b.first;
        }
        else if (a.second < 0 && b.second > 0)
        {
            if (abs(a.second) == b.second)
                return false;
            return true;
        }
        else if (a.second > 0 && b.second < 0)
        {
            if (a.second == abs(b.second))
                return true;
            return false;
        }
        else if (a.second > 0 && b.second > 0)
        {
            return a.second < b.second;
        }
        else
        {
            return abs(a.second) > abs(b.second);
        }
    }
};


int getMinCoveredArea(vector<PAIRINT> &LR, vector<PAIRINT> &ranges)
{
    stack <int> S;
    vector<int> sizes(N, 0);

    int totalSize = 0;
    int lowestTop, currentEnd;

    int endCount = 0;

    for (int i = 0; i < LR.size(); ++i)
    {
        if (LR[i].second > 0)
        {
            if (!S.empty())
            {
                if (S.size() == endCount + 1)
                {
                    int activeInterval = S.top();
                    sizes[LR[activeInterval].second - 1] += LR[i].first - LR[i-1].first;
                    // cout<<i<<" "<<S.size()<<" "<<LR[i].first<<" "<<LR[i].second<<" "<<LR[i-1].first<<" "<<LR[i-1].second<<endl;

                    if (LR[i-1].second < 0 || (i-1 > 0 && LR[i-1].first == LR[i-2].first))
                    {
                        sizes[LR[activeInterval].second-1]--;
                    }
                }
            }
            else
            {
                lowestTop = i;
            }
            S.push(i);
        }
        if (LR[i].second < 0)
        {
            currentEnd = i;
            if (S.empty() && LR[i].first == LR[i-1].first)
            {
                continue;
            }
            int activeInterval = S.top();

            if (LR[activeInterval].second == abs(LR[i].second))
            {
                S.pop();
                    cout<<endCount<<" "<<S.size()<<endl;
                if (S.size() == endCount)
                {
                    endCount = 0;
                    sizes[LR[activeInterval].second-1] += LR[i].first - LR[i-1].first;
                    cout<<LR[i].first<<" "<<LR[i].second<<" "<<LR[i-1].first<<" "<<LR[i-1].second<<endl;
                    if (i < LR.size()-1 && LR[i].first == LR[i+1].first)
                    {
                        sizes[LR[activeInterval].second-1]--;
                    }

                    if (i-1 == activeInterval)
                    {
                        if ((i-1 > 0 && LR[i-2].first != LR[i-1].first )|| i-2 < 0)
                        {
                            sizes[LR[activeInterval].second-1]++;  
                        }
                    }   
                    while (!S.empty())
                    {
                        S.pop();
                    }
                }
                else
                {
                    endCount--;
                }

                if (S.empty())
                {
                    totalSize += LR[currentEnd].first - LR[lowestTop].first + 1;
                }
            }
            else
            {
                endCount++;
                continue;
            }
        }
    }
    int maxSize = 0;
    for (int i = 0; i < sizes.size(); ++i)
    {
        // cout<<sizes[i]<<endl;
        maxSize = max(maxSize, sizes[i]);
    }
    // cout<<"TOTAL "<<totalSize<<endl;
    return totalSize-maxSize;
}

int main(int argc, char const *argv[])
{	
    // freopen("C-small-practice.in","r",stdin);
    // freopen("output.out","w",stdout);

    // cout<<fixed<<setprecision(10);
    // cout<<INT_MAX<<endl;
    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int L1, R1, A, B, C1, C2, M;
        cin>>N>>L1>>R1>>A>>B>>C1>>C2>>M;

        vector<PAIRINT> ranges;
        int prevx = L1, prevy = R1;
        ranges.push_back(make_pair(prevx, prevy));
        // rangesR.push_back(make_pair(prevy, prevx));
        for (int j = 1; j < N; ++j)
        {
            int x1, y1;
            x1 = (A*prevx + B*prevy + C1)%M;
            y1 = (A*prevy + B*prevx + C2)%M;
            ranges.push_back(make_pair(min(x1, y1), max(x1,y1)));
            // rangesR.push_back(make_pair( max(x1,y1), min(x1, y1)));
            
            prevx = x1;
            prevy = y1;
        }        

        vector <PAIRINT> LR; 

        for (int j = 0; j < ranges.size(); ++j)
        {
            // cout<<ranges[j].first<<" "<<ranges[j].second<<endl;
            LR.push_back(make_pair( ranges[j].first, j+1));
            LR.push_back(make_pair(ranges[j].second, -j-1));
        }

        sort(LR.begin(), LR.end(), Compare());

        for (int j = 0; j < LR.size(); ++j)
        {
            // cout<<LR[j].first<<" "<<LR[j].second<<endl;
        }

        int answer = getMinCoveredArea(LR, ranges);

        // long long answer = INF;

        // for (int j = 0; j < N; ++j)
        // {

        // answer = min(answer, computeArea(rangesL, rangesR, j));
        // }

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}