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

#define INF ULLONG_MAX

bool isValid(bitset<128> binaryK, int parLength)
{
    // cout<<binaryK.to_string()<<endl;
    int lCount = 0, rCount = 0;
    for (int i = 0; i < 2*parLength; ++i)
    {
        if (lCount > rCount)
        {
            return false;
        }

        if (binaryK[i])
        {
            rCount++;
        }
        else
        {
            lCount++;
        }
    }

    if (lCount == rCount)
    {
        return true;
    }
    return false;
}
int main(int argc, char const *argv[])
{	
	freopen("D-small-practice.in","r",stdin);
    freopen("output.out","w",stdout);
    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        unsigned long long K;
        int parLength;
        cin>>parLength>>K;

        // unsigned long long startPoint = K*parLength*2;
        unsigned long long startPoint = 0;
        bitset<128> binaryK(startPoint);
        bool possible = true;
        // cout<<binaryK.to_string()<<endl;
        for (int j = binaryK.size()-1; j >= 0; --j)
        {
            if (binaryK[j])
            {
                // cout<<j<<" "<<binaryK.size() - j<<" "<<2*parLength<<endl;
                if (j+1 > 2*parLength)
                {
                    possible = false;
                    break;
                }
            }
        }
        string answer;
        
        if (possible)
        {
            while (K--)
            {
                while (!isValid(binaryK, parLength))
                {
                    binaryK = bitset<128>(++startPoint);
                }
                if (K)
                {
                    binaryK = bitset<128>(++startPoint);
                }     
            }
            if (!isValid(binaryK, parLength))
            {
                possible = false;
            }
            for (int j = binaryK.size()-1; j >= 0; --j)
            {
                if (binaryK[j])
                {
                    // cout<<j<<" "<<binaryK.size() - j<<" "<<2*parLength<<endl;
                    if (j+1 > 2*parLength)
                    {
                        possible = false;
                        break;
                    }
                }
            }
            if (possible)
            {
                answer = binaryK.to_string();                    

                for (int j = answer.length() - 2*parLength; j < answer.length(); ++j)
                {
                    if (answer[j] == '0')
                    {
                        answer[j] = '(';
                    }
                    else
                    {
                        answer[j] = ')';
                    }
                }

                int answerLength = answer.length();
                for (int j = 0; j < answerLength - 2*parLength; ++j)
                {
                    answer.erase(answer.begin() + 0);
                }      

            }
            else
            {
                answer = "Doesn't Exist!";
            }      
        }
        else
        {
            answer = "Doesn't Exist!";
        }

        cout<<"Case #"<<i+1<<": ";
        cout<<answer;
        cout<<endl;
    }
}