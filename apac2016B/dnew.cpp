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

#define PAIRINT pair<int, int>

using namespace std;

string sequence;

long long computeAlboNSubSeq()
{

    long long answer = 0;

    map<int, int> lastA;
    map<PAIRINT, int> lastB;
    map<PAIRINT, int> lastC;
    map<int, int> lastD;

    lastA[0] = 1;

    for (int i = 0; i < sequence.length(); ++i)
    {
        if (sequence[i] == 'a')
        {
            vector<PAIRINT> temp;
            for (map<int, int>::iterator j = lastA.begin(); j != lastA.end(); ++j)
            {
                temp.push_back(make_pair(j->first+1, j->second));
            }

            for (int j = 0; j < temp.size(); ++j)
            {
                int Anum = temp[j].first;
                int count = temp[j].second;
                if (lastA.find(Anum) != lastA.end())
                {
                    lastA[Anum] += count;
                }
                else
                {
                    lastA[Anum] = count;
                }
                lastA[Anum] %= MOD;
                
                if (lastB.find(make_pair(Anum, 0)) != lastB.end())
                {
                    lastB[make_pair(Anum, 0)] += count;
                }
                else
                {
                    lastB[make_pair(Anum, 0)] = count;
                }

                lastB[make_pair(Anum, 0)] %= MOD;

            }
        }
        if (sequence[i] == 'b')
        {
            vector<pair<PAIRINT, int> > temp;

            for (map<PAIRINT, int>::iterator j = lastB.begin(); j != lastB.end(); ++j)
            {
                temp.push_back(make_pair(make_pair(j->first.first, j->first.second+1), j->second));
            }

            for (int j = 0; j < temp.size(); ++j)
            {
                int Anum = temp[j].first.first;
                int Bnum = temp[j].first.second;
                int count = temp[j].second;
                if (lastB.find(make_pair(Anum, Bnum)) != lastB.end())
                {
                    lastB[make_pair(Anum, Bnum)] += count;
                }
                else
                {
                    lastB[make_pair(Anum, Bnum)] = count;
                }

                lastB[make_pair(Anum, Bnum)] %= MOD;

                if (lastC.find(make_pair(Bnum, Anum)) != lastC.end())
                {
                    lastC[make_pair(Bnum, Anum)] += count;
                }
                else
                {
                    lastC[make_pair(Bnum, Anum)] = count;
                }
                lastC[make_pair(Bnum, Anum)] %= MOD;

            }

        }

        if (sequence[i] == 'c')
        {
            vector<pair<PAIRINT, int> > temp;

            for (map<PAIRINT, int>::iterator j = lastC.begin(); j != lastC.end(); ++j)
            {
                if (j->first.second != 0)
                {
                    temp.push_back(make_pair(make_pair(j->first.first, j->first.second-1), j->second));                
                }
            }

            for (int j = 0; j < temp.size(); ++j)
            {
                int Cleft = temp[j].first.second;
                int Bnum = temp[j].first.first;
                int count = temp[j].second;
                if (Cleft == 0)
                {
                    if (lastD.find(Bnum) != lastD.end())
                    {
                        lastD[Bnum] += count;
                    }
                    else
                    {
                        lastD[Bnum] = count;                        
                    }
                    lastD[Bnum] %= MOD;
                }
                else
                {
                    if (lastC.find(make_pair(Bnum, Cleft)) != lastC.end())
                    {
                        lastC[make_pair(Bnum, Cleft)] += count;
                    }
                    else
                    {
                        lastC[make_pair(Bnum, Cleft)] = count;                        
                    }

                    lastC[make_pair(Bnum, Cleft)] %= MOD;
                }
            }
        }
        if (sequence[i] == 'd')
        {
            vector<PAIRINT> temp;
            for (map<int, int>::iterator j = lastD.begin(); j != lastD.end(); ++j)
            {
                temp.push_back(make_pair(j->first-1, j->second));
            }

            for (int j = 0; j < temp.size(); ++j)
            {
                int Dleft = temp[j].first;
                int count = temp[j].second;
                if (Dleft == 0)
                {
                    if (lastA.find(0) != lastA.end())
                    {
                        lastA[0] += count;
                    }
                    else
                    {
                        lastA[0] = count;
                    }
                    lastA[0] %= MOD;
                    answer += count;
                    answer %= MOD;
                }
                else
                {
                    if (lastD.find(Dleft) != lastD.end())
                    {
                        lastD[Dleft] += count;
                    }
                    else
                    {
                        lastD[Dleft] = count;
                    }
                    lastD[Dleft] %= MOD;
                }
            }

        }
    }
    return answer;
}


int main(int argc, char const *argv[])
{	
	freopen("D-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        cin>>sequence;

        long long answer = computeAlboNSubSeq();
        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}