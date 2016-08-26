/*input
4
1 1 1 0
1 2 0 0
2 1 1 2
2 2 0 2
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

void makeGame( char player, string &answer, int pos)
{
	if (player == 'R')
	{
		answer.insert(pos, "RS");	
	
	}
	else if (player == 'S')
	{
		answer.insert(pos, "PS");
	}
	else
	{
		answer.insert(pos, "PR");
	}

}

void alphabetize(string &s)
{
	int n = s.length();

	for (int i = 1; i <= n/2; i*=2)
	{
		for (int j = 0; j <= n-i; j+=2*i)
		{
			if (s.substr(j, i) > s.substr(j+i, i))
			{
				for (int k = j; k < j+i; ++k)
				{
					char temp = s[k+i];
					s[k+i] = s[k];
					s[k] = temp;
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{	
	freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);
    int testCaseCount;

    cin>>testCaseCount;
	for (int i = 0; i < testCaseCount; ++i)
    {
    	int n, rock, paper, scissors;
    	cin>>n>>rock>>paper>>scissors;

    	string answerA = "R";
    	string answerB = "S";
    	string answerC = "P";

    	for (int j = 0; j < n; ++j)
    	{
    		int length = answerA.length();
    		int pos = 0;
    		for (int k = 0; k<length; ++k)
    		{
    			char playerA = answerA[pos];
    			char playerB = answerB[pos];
    			char playerC = answerC[pos];
   				
   				answerA.erase(answerA.begin() + pos);
   				answerB.erase(answerB.begin() + pos);
   				answerC.erase(answerC.begin() + pos);

   				makeGame(playerA, answerA, pos);
   				makeGame(playerB, answerB, pos);
   				makeGame(playerC, answerC, pos);
   				pos += 2;
	   		}
    	}

    	int rCountA = 0, sCountA = 0, rCountB = 0, sCountB = 0, rCountC = 0, sCountC = 0;
    	rCountA = count(answerA.begin(), answerA.end(), 'R');
    	sCountA = count(answerA.begin(), answerA.end(), 'S');

    	rCountB = count(answerB.begin(), answerB.end(), 'R');
    	sCountB = count(answerB.begin(), answerB.end(), 'S');


    	rCountC = count(answerC.begin(), answerC.end(), 'R');
    	sCountC = count(answerC.begin(), answerC.end(), 'S');

    	cout<<"Case #"<<i+1<<": ";

    	if (rock + paper + scissors != pow(2, n))
    	{
    		cout<<"IMPOSSIBLE";
    	}
		else if (rCountA == rock && sCountA == scissors)
    	{
    		alphabetize(answerA);
    		cout<<answerA;
    	}
    	else if (rCountB == rock && sCountB == scissors)
    	{
    		alphabetize(answerB);
    		cout<<answerB;
    	}
    	else if (rCountC == rock && sCountC == scissors)
    	{
    		alphabetize(answerC);
    		cout<<answerC;
    	}
    	else
    	{
    		cout<<"IMPOSSIBLE";
    	}

    	cout<<endl;

    }



}