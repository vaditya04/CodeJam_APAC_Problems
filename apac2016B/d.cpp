/*input
5
abcd
aaaabcd
aaaabbccd
abcdabcdaabccd
b
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

#define MOD 1000000007

using namespace std;

string sequence;

map <pair<string, string> , int> subSeqDP;
vector<string> alboStrings;
// vector<vector<int> > alboDP;
map <string, int> alboDP;
// vector<int> alboNDP;
map <string, int> alboNDP;
int countSubsequences(int startPos, int endPos, string searchString)
{
    // pair<string, pair<int, int> > mapping = make_pair(searchString, make_pair(startPos, endPos));
    pair<string, string> mapping = make_pair(searchString, sequence.substr(startPos, endPos-startPos+1));

    if (subSeqDP.find(mapping) != subSeqDP.end())
    {
        return subSeqDP[mapping];
    }

    long long answer = 0;

    for (int i = endPos; i >= startPos; --i)
    {
        if (sequence[i] == searchString[searchString.length()-1])
        {
            searchString.erase(searchString.length()-1);
            // cout<<searchString<<endl;
            if (searchString.length() == 0)
            {
                answer++;                
            }
            else
            {
                answer += countSubsequences(startPos, i-1, searchString);
                answer %= MOD;        
            }
            searchString += sequence[i];
        }
    }
    // cout<<answer<<" "<<searchString<<" "<<sequence.substr(startPos, endPos-startPos+1)<<endl;
    subSeqDP[mapping] = answer;
    return answer;
}

int countAlboEndingIn(int startPos, int endPos)
{
    if (endPos - startPos + 1 < 4)
    {
        return 0;
    }
/*
    if (alboDP[startPos][endPos] != -1)
    {
        return alboDP[startPos][endPos];
    }*/
    string key = sequence.substr(startPos, endPos - startPos + 1);
    if (alboDP.find(key) != alboDP.end())
    {
        return alboDP[key];
    }
    long long answer = 0;

    for (int j = 0; j < alboStrings.size(); ++j)
    {
        string currentString = alboStrings[j];
        int length = alboStrings[j].length();
        if (currentString[length - 1] == sequence[endPos])
        {
            // cout<<currentString<<" "<<sequence.substr(startPos, endPos-startPos+1)<<" ";

            currentString.erase(currentString.length() - 1);
            // cout<<currentString<<endl;
            if (currentString.length() == 0)
            {
                answer++;
            }
            else
            {
                answer += countSubsequences(startPos, endPos-1, currentString);
            }
            answer %= MOD;
        }

    }

    alboDP[key] = answer;
    // alboDP[startPos][endPos] = answer;
    return answer;

}

int countSubSeqEndingAt(int endPos)
{
/*    if (alboNDP[endPos] != -1)
    {
        return alboNDP[endPos];
    }*/
    string key = sequence.substr(0, endPos+1);
    // cout<<key<<endl;
    if (alboNDP.find(key) != alboNDP.end())
    {
        return alboNDP[key];
    }
    if (endPos == -1)
    {
        return 0;
    }

    long long answer = 0;
    for (int i = -1; i < endPos; ++i)
    {
        long long subSeqEndingAtI = countSubSeqEndingAt(i);
        long long AlboEndingIn = countAlboEndingIn(i+1, endPos);
        // cout<<AlboEndingIn<<" "<<endl;
        if (i == -1)
        {
            answer += AlboEndingIn;
        }
        else
        {
            answer += subSeqEndingAtI*AlboEndingIn%MOD;
        }
        answer %= MOD;
    }

    alboNDP[key] = answer;
    return answer;
}


int countSubSeqAlboN()
{
    long long answer = 0;
    for (int i = 0; i < sequence.length(); ++i)
    {
        answer = (answer + countSubSeqEndingAt(i))%MOD;
    }
    return answer;
}

void populateAlboStrings(int n)
{
    for (int aCount = 1; aCount < n/4 + 1; ++aCount)
    {
        for (int bCount = 1; bCount < n/4 + 1; ++bCount)
        {
            string s = "";
            string tempC = "", tempD = "";
            for (int i = 0; i < aCount; ++i)
            {
                s += 'a';
                tempC += 'c';
            }
            for (int i = 0; i < bCount; ++i)
            {
                s+= 'b';
                tempD += 'd';
            }
            s = s+ tempC + tempD;
            if (s.length() <= n)
            {
                alboStrings.push_back(s);
            }
            // cout<<s<<endl;
        }
    }

}

int main(int argc, char const *argv[])
{	
	freopen("D-large-practice.in","r",stdin);
    // freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        cin>>sequence;

        alboStrings.clear();
        
        // subSeqDP.clear();
        // alboDP.clear();
        // alboNDP.clear();
        // alboDP.resize(sequence.length(), vector<int>(sequence.length(), -1));
        // alboNDP.resize(sequence.length(), -1);

        populateAlboStrings(sequence.length());
        // cout<<alboStrings.size()<<endl;
        int answer = countSubSeqAlboN();

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}