/*input
2
3
ADAM
BOB
JOHNSON
2
A AB C
DEF
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

class Compare
{
public:
    bool operator() (string a, string b)
    {
        for (int i = 0; i < min(a.length(), b.length()); ++i)
        {
            if (a[i] == ' ' && b[i] != ' ')
            {
                return true;
            }
            else if (a[i] != ' ' && b[i] == ' ')
            {
                return false;
            }
            else if (a[i] != ' ' && b[i] != ' ')
            {
                if (a[i] != b[i])
                {
                    return a[i] < b[i];
                }   
            }
        }
        return a.length() < b.length();
    }
};



int main(int argc, char const *argv[])
{	
    freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int nameCount;
        cin>>nameCount;

        int maxDiff = 0;

        vector<string> possibleAnswers;
        cin.ignore();
        for (int j = 0; j < nameCount; ++j)
        {
            vector<bool> alph(26, false);
            string name;
            getline(cin, name);
            // cout<<name<<endl;
            int diffCount = 0;
            for (int k = 0; k < name.length(); ++k)
            {
                // cout<<name[k];
                if (name[k] == ' ')
                {
                    continue;
                }
                else if (alph[(int)(name[k]-'A')] == false)
                {
                    alph[(int)(name[k]-'A')] = true;
                    diffCount++;
                    // cout<<name[k]<<" "<<diffCount<<endl;
                }
            }

            if (diffCount > maxDiff)
            {
                possibleAnswers = vector<string>(0);
                possibleAnswers.push_back(name);
                maxDiff = diffCount;
            }
            else if (diffCount == maxDiff)
            {
                possibleAnswers.push_back(name);
            }
        }

        sort(possibleAnswers.begin(), possibleAnswers.end(), Compare());
/*
        for (int j = 0; j < possibleAnswers.size(); ++j)
        {
            cout<<possibleAnswers[j]<<endl;
        }
*/
        cout<<"Case #"<<i+1<<": ";

        cout<<possibleAnswers[0];

        cout<<endl;
    }
}