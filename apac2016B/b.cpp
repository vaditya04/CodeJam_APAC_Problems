/*input
1
1 2 3
5
4 6
3 5 7
2
1 1
5 2
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

#define PAIRINT pair<int, int>

class Compare
{
    public:
    bool operator () (PAIRINT a, PAIRINT b)
    {
        return a.first < b.first;
    }
    bool operator () (PAIRINT &a, int b)
    {
        return a.first < b;
    }
    bool operator () (int a, PAIRINT &b)
    {
        return a < b.first;
    }
};


int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void generatePairs(vector<int> &a, vector<int> &extraGears, vector<PAIRINT> &c)
{
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < extraGears.size(); ++j)
        {
            c[extraGears.size()*i+j].first = a[i]*extraGears[j];
            c[extraGears.size()*i+j].second = j; 
        }
    }

    sort(c.begin(), c.end(), Compare());
}

int main(int argc, char const *argv[])
{	
	freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);
    int testCaseCount;

    cin>>testCaseCount;


    for (int i = 0; i < testCaseCount; ++i)
    {

        int pedalCount, extraCount, tireCount;
        cin>>pedalCount>>extraCount>>tireCount;

        vector<int> pedalGears(pedalCount), extraGears(extraCount), tireGears(tireCount);

        for (int j = 0; j < pedalCount; ++j)
        {
            cin>>pedalGears[j];
        }

        for (int j = 0; j < extraCount; ++j)
        {
            cin>>extraGears[j];
        }

        for (int j = 0; j < tireCount; ++j)
        {
            cin>>tireGears[j];
        }

        vector<PAIRINT> pedalExtraProd(pedalCount*extraCount);
        generatePairs(pedalGears, extraGears, pedalExtraProd);

        vector<PAIRINT> extraTireProd(extraCount*tireCount);
        generatePairs(tireGears, extraGears, extraTireProd);

        int queryCount;
        cin>>queryCount;
        
        cout<<"Case #"<<i+1<<": "<<endl;

        for (int j = 0; j < queryCount; ++j)
        {
            int P, Q;    
            cin>>P>>Q;
            int gcdPQ = gcd(P,Q);
            P /= gcdPQ;
            Q /= gcdPQ;

            bool foundFlag = false;

            for (int k = 1; k <= 100000000/max(P,Q) + 1 && !foundFlag; ++k)
            {
                int PSearch = k*P;
                int QSearch = k*Q;
                // cout<<PSearch<<" "<<QSearch<<" "<<P<<" "<<Q<<" "<<k<<endl;
                if (PSearch > pedalExtraProd[pedalExtraProd.size()-1].first || QSearch > extraTireProd[extraTireProd.size()-1].first)
                {
                    break;
                }

                pair<vector<PAIRINT>::iterator, vector<PAIRINT>::iterator> rangePE, rangeET;
                rangePE = equal_range(pedalExtraProd.begin(), pedalExtraProd.end(), PSearch, Compare());
                rangeET = equal_range(extraTireProd.begin(), extraTireProd.end(), QSearch, Compare());

                if (rangePE.first == rangePE.second || rangeET.first == rangeET.second)
                {
                    continue;
                }

                for (; rangePE.first != rangePE.second && !foundFlag; ++rangePE.first)
                {
                    for (; rangeET.first != rangeET.second; ++rangeET.first)
                    {
                            // cout<<(*rangePE.first).first<<" "<<(*rangeET.first).first<<endl;
                        if ((*rangePE.first).second != (*rangeET.first).second)
                        {
                            foundFlag = true;
                            break;
                        }
                    }
                }

            }

            if (foundFlag)
            {
                cout<<"Yes"<<endl;
            }
            else
            {
                cout<<"No"<<endl;
            }
        }        

        
        // cout<<endl;
    }
}