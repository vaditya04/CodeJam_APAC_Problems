/*input
3
1 5 5 10 50 40
2 5 5 10 50 40
10 15 21 70 20 10
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

#define PAIRD pair<int, double>

#define DIVMOD 1000000000
#define LIMIT 10000000000.0

int main(int argc, char const *argv[])
{	
    freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    cout<<fixed<<setprecision(10);

    for (int i = 0; i < testCaseCount; ++i)
    {
        int rngLength, input, fixedNum, A, B, C;
        cin>>rngLength>>input>>fixedNum>>A>>B>>C;

        map<int, double> generatedNumbers;

        generatedNumbers[input&fixedNum] = ((double)A)/*/100.0*/;
        if (generatedNumbers.find(input|fixedNum) != generatedNumbers.end())
        {
            generatedNumbers[input|fixedNum] += ((double)B)/*/100.0*/;        
        }
        else
        {
           generatedNumbers[input|fixedNum] = ((double)B)/*/100.0*/; 
        }

        if (generatedNumbers.find(input^fixedNum) != generatedNumbers.end())
        {
            generatedNumbers[input^fixedNum] += ((double)C)/*/100.0*/;        
        }
        else
        {
           generatedNumbers[input^fixedNum] = ((double)C)/*/100.0*/; 
        }
        
        for (int j = 1; j < rngLength; ++j)
        {
            vector<int> remove;
            vector<PAIRD> add;
            bool limitFlag = false;
            for (map<int, double>::iterator k = generatedNumbers.begin(); k != generatedNumbers.end(); k++)
            {
                int number = k->first;
                double count = k->second;
                // cout<<count<<endl;
                remove.push_back(number);

                // cout<<(number&fixedNum)<<" "<<(number|fixedNum)<<" "<<(number^fixedNum)<<endl;
/*                if (max(count*A, max(count*C, count*B)) > LIMIT)
                {
                    add.push_back(make_pair(number&fixedNum, count*A/(max(count*A, max(count*B, count*C)))));
                    add.push_back(make_pair(number|fixedNum, count*B/(max(count*A, max(count*B, count*C)))));
                    add.push_back(make_pair(number^fixedNum, count*C/(max(count*A, max(count*B, count*C)))));                    
                }*/
                add.push_back(make_pair(number&fixedNum, count*A));
                add.push_back(make_pair(number|fixedNum, count*B));
                add.push_back(make_pair(number^fixedNum, count*C));    
                if (count*A > LIMIT || count*B > LIMIT || count*C > LIMIT)
                {
                    limitFlag = true;
                }                                    
            }

            for (int k = 0; k < remove.size(); ++k)
            {
                generatedNumbers.erase(remove[k]);
            }

            for (int k = 0; k < add.size(); ++k)
            {
                int newNum = add[k].first;
                double numCount = add[k].second;
                if (limitFlag == true)
                {
                    if (numCount <= 0.0000001)
                        continue;
                    numCount /= LIMIT;
                }
                if (generatedNumbers.find(newNum) != generatedNumbers.end())
                {
                    generatedNumbers[newNum] += numCount;
                }
                else
                {
                    generatedNumbers[newNum] = numCount;
                }
            }
            limitFlag = false;
        }

        double answer = 0;
        double total = 0;

        for (map<int, double>::iterator j = generatedNumbers.begin(); j != generatedNumbers.end(); j++)
        {
            // cout<<j->first<<" "<<j->second<<endl;
            answer += (double)(j->first)*((double)j->second/10000.0);
            total += (double)j->second/10000.0;
        }

        answer = answer/total;
        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}