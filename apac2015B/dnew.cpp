/*input
3
2 2
3 4
3 6
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

#define LIMIT 1000000000000000007ULL

#define PAIRINT pair<int, int>

map<PAIRINT, unsigned long long> parCount; 

unsigned long long printKth(int leftPar, int rightPar, unsigned long long K, bool printFlag)
{
    if (!printFlag && parCount.find(make_pair(leftPar, rightPar)) != parCount.end())
    {
        return parCount[make_pair(leftPar, rightPar)];
    }
    unsigned long long count1 = 0, count2 = 0;

    if (leftPar == 1 && rightPar == 1)
    {
        count1 = 1;
        count2 = 0;
    }
    else if (leftPar == 0)
    {
        count1 = 0;
        if (rightPar)
            count2 = 1;
    }
    else
    {
        if (leftPar>0)
        {
            count1 = printKth(leftPar-1, rightPar, K, false);
            // cout<<count1<<endl;
        }
        if (rightPar > leftPar)
        {
            count2 = printKth(leftPar, rightPar-1, K, false);
            // cout<<count2<<endl;
        }   
    }


    if (printFlag && (leftPar || rightPar))
    {
        // cout<<K<<" "<<count1<<" "<<count2<<endl;        
        if (K <= count1)
        {
            cout<<'(';
            printKth(leftPar-1, rightPar, K, true);
        }
        else if (K <= count1 + count2)
        {
            cout<<')';
            printKth(leftPar,rightPar-1, K-count1, true);
        }
        else
        {
            cout<<"Doesn't Exist!";
            return -1;
        }
    }
    // cout<<leftPar<<" "<<rightPar<<" "<<count1<<" "<<count2<<" "<<endl;
    if (count1 > LIMIT || count2 > LIMIT)
    {
        parCount[make_pair(leftPar, rightPar)] = LIMIT;
        return LIMIT;
    }

    parCount[make_pair(leftPar, rightPar)] = count1 + count2;
    return count1+count2;
}

int main(int argc, char const *argv[])
{	
	freopen("D-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    // cout<<fixed<<setprecision(0);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        unsigned long long K;
        int parLength;
        cin>>parLength>>K;

        cout<<"Case #"<<i+1<<": ";
        
        printKth(parLength, parLength, K, true);
        
        cout<<endl;
    }
}