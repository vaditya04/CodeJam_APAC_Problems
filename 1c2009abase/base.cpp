/*input
3
11001001
cats
zig
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

int getIndex(char c)
{
    if (c <= '9' && c >= '0')
        return c - '0';
    else
        return (c - 'a' + 10);
}

int main(int argc, char const *argv[])
{	
	freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;
	for (int i = 0; i < testCaseCount; ++i)
    {
   
        string num;

        cin>>num;

        vector<int> alph(36, 0);

        int baseCount = 0;
        for (int j = 0; j < num.length(); ++j)
        {
            // cout<<num[j]<<" "<<getIndex(num[j])<<endl;
            if (alph[getIndex(num[j])] == 0)
            {
                baseCount++;
                alph[getIndex(num[j])]++;
            }
        }

        vector<int> mapping(36,-1);

        mapping[getIndex(num[0])] = 1;
        if (baseCount == 1)
        {
            baseCount++;
        }

        vector<int> finalNumber(num.length());
        finalNumber[0] = 1;
        int mapInt = 0;
        for (int j = 1; j < num.length(); ++j)
        {
            if (mapping[getIndex(num[j])] == -1)
            {
                mapping[getIndex(num[j])] = mapInt;
                mapInt++;
                if (mapInt == 1)
                    mapInt++;
            }
            finalNumber[j] = mapping[getIndex(num[j])];
            // cout<<finalNumber[j]<<" ";
        }
        // cout<<endl<<mapInt<<" "<<baseCount<<endl;

        vector<int> decimalNumber;
        long long answer = 0;
        for (int j = finalNumber.size()-1; j >= 0; --j)
        {
            answer+= (finalNumber[j]*pow(baseCount, finalNumber.size()-1-j));
        }

    	cout<<"Case #"<<i+1<<": ";        


        cout<<answer;
    	cout<<endl;
    }

}