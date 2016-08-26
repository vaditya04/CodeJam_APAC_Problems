/*input
3
1 1
1 1 1
2
2 2
1 1 1
2
3 1 1
4
3 3
1 2 2
3 4
2 2 2
5 6
7 1 1
8
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

#define INF LLONG_MAX
#define NEGINF LLONG_MIN

#define PERMUTECOUNT 100000 //increase for even better odds, up to 10^7

using namespace std;

vector< vector<int> > problems;
vector<pair<int, int> > problemElves;
vector< vector<int> > permutations;

int contestSize, problemElfCount, elfCount;

long long factorial (int n)
{
	long long answer = 1;
	for (int i = 1; i <= n; ++i)
	{
		answer *= i;
	}
	return answer;
}

void generatePermutations(int levelsLeft, vector<int> currentPermute)
{
	if (levelsLeft == 0)
	{
		permutations.push_back(currentPermute);
		return;
	}
	for (int i = 0; i < elfCount; ++i)
	{
		if (find(currentPermute.begin(), currentPermute.end(), i+1) == currentPermute.end())
		{

			currentPermute.push_back(i+1);
			generatePermutations(levelsLeft-1, currentPermute);
			currentPermute.erase(currentPermute.begin() + currentPermute.size()-1);
		}
	}

}

void generatePermutations2(int length)
{
	vector<int> numbers;
	for (int i = 0; i < length; ++i)
	{
		numbers.push_back(i+1);
	}
	for (long long i = 0; i < PERMUTECOUNT; ++i)
	{
		vector<int> numbersLeft = numbers;
		vector<int> permute;
		while (numbersLeft.size())
		{
			int randIndex = rand()%numbersLeft.size();
			permute.push_back(numbersLeft[randIndex]);
			numbersLeft.erase(numbersLeft.begin() + randIndex);
		}
		permutations.push_back(permute);
	}
}

bool isPossible()
{
	for (long long i = 0; i < permutations.size(); ++i)
	{
		vector<int> permute = permutations[i];
		bool possible = true;

		
		for (int j = 0; j < problemElfCount; ++j)
		{
			int problemElf = problemElves[j].first;
			int problemLevel = problemElves[j].second;
			int elfPos;
			for (elfPos = 0; elfPos < permute.size(); ++elfPos)
			{
				if (permute[elfPos] == problemElf)
					break;
			}
			// cout<<problemElf<<" "<<problemLevel<<" "<<elfPos<<endl;

			int problemRangeLower = elfPos/pow(2, problemLevel);
			problemRangeLower *= pow(2, problemLevel);
			int problemRangeUpper = problemRangeLower + pow(2, problemLevel);

			// cout<<problemRangeLower<<" "<<problemRangeUpper<<endl;
			for (int k = problemRangeLower; k < problemRangeUpper; ++k)
			{
				if (find(problems[j].begin(), problems[j].end(), permute[k]) != problems[j].end())
				{
					possible = false;
					break;
				}
			}
			if (possible == false)
				break;
		}
		if (possible == true)
		{
/*		for (int k = 0; k < permute.size(); ++k)
		{
			cout<<permute[k];
		}
		cout<<endl;*/

			return true;
		}

	}

	return false;
}

int main(int argc, char const *argv[])
{	
    freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    srand(time(NULL));
    generatePermutations2(16);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
    	cin>>contestSize>>problemElfCount;
    	elfCount = pow(2, contestSize);

    	// permutations.clear();
    	problems.clear();
    	problemElves.clear();

    	problems.resize(problemElfCount,  vector<int> (0));

    	// permutations.resize(factorial(elfCount), vector<int>(elfCount));

    	for (int j = 0; j < problemElfCount; ++j)
    	{
    		int elfId, elfLevel, problemCount;
    		cin>>elfId>>elfLevel>>problemCount;
			problemElves.push_back(make_pair(elfId, elfLevel));
			// cout<<elfId<<" "<<elfLevel<<endl;
    		for (int k = 0; k < problemCount; ++k)
    		{
    			int problemId;
    			cin>>problemId;

    			problems[j].push_back(problemId);
    		}			    		
    	}

    	// generatePermutations(elfCount, vector<int>(0));
    	bool answer = isPossible();

        cout<<"Case #"<<i+1<<": ";

        if (answer)
        {
        	cout<<"YES";
        }
        else
        {
        	cout<<"NO";
        }

        cout<<endl;
    }
}