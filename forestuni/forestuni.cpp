/*input
2
2
0 1
CJ
4
CJ C D JC
3
0 1 0
BAA
3
AA AAB ABA
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

using namespace std; 

#define MAX 101


int main(int argc, char const *argv[])
{	
	freopen("B-small-practice.in","r",stdin);
    freopen("output.out","w",stdout);

	long long testCaseCount;
	srand(time(NULL));
	cin>>testCaseCount;

	cout<<fixed;
	cout<<setprecision(2);

	for (long long i = 0; i < testCaseCount; ++i)
	{
		long long courseCount;
		cin>>courseCount;

		vector<int> courseReq;
		vector<vector<int> > adjList(courseCount, vector<int>(0));

		vector<int> inDegree(courseCount, 0);
		vector<int> outDegree(courseCount, 0);

		for (int j = 0; j < courseCount; ++j)
		{
			int reqNumber;
			cin>>reqNumber;

			if (reqNumber)
			{
				reqNumber--;
				courseReq.push_back(reqNumber);	
				adjList[reqNumber].push_back(j);
				inDegree[j]++;
				outDegree[reqNumber]++;
			}
		}

		vector<char> letterList;

		for (int j = 0; j < courseCount; ++j)
		{
			char letter;
			cin>>letter;
			letterList.push_back(letter);
		}

		vector<int> sizeOfTree(courseCount, 0);

		int doneCount = 0;
		int index = 0;
		while(doneCount<courseCount)
		{
			if (outDegree[index] == 0)
			{
				for (int k = 0; k < courseCount; ++k)
				{
					if (find(adjList[k].begin(), adjList[k].end(), index) != adjList[k].end())
					{
						sizeOfTree[k] += sizeOfTree[index] + 1;
						outDegree[k]--;
					}
				}
				outDegree[index]--;
				doneCount++;
			}

			index = (index+1)%courseCount;
		}

		vector<int> initialCourses;

		for (int j = 0; j < courseCount; ++j)
		{
			if (inDegree[j] == 0)
			{
				initialCourses.push_back(j);
			}
		}

		vector<string> wordSamples;

		for (int j = 0; j < 3000; ++j)
		{
			vector<int> courseRoots(initialCourses);
			string word = "";
			while(word.length() < courseCount)
			{
				vector<int> probDist;
				for (int k = 0; k < courseRoots.size(); ++k)
				{
					vector<int> temp(sizeOfTree[courseRoots[k]]+1, courseRoots[k]);
					probDist.insert(probDist.end(), temp.begin(), temp.end());
				}

				int randNum = rand()%probDist.size();
				int courseTaken = probDist[randNum];
				word += letterList[courseTaken];

				for (int k = 0; k < courseRoots.size(); ++k)
				{
					if (courseRoots[k] == courseTaken)
					{
						// courseRoots[k] = -1;
						courseRoots.erase(courseRoots.begin() + k);
						break;
					}
				}

				for (int k = 0; k < adjList[courseTaken].size(); ++k)
				{
					courseRoots.push_back(adjList[courseTaken][k]);
				}

			}

			wordSamples.push_back(word);
		}

		int wordCount;
		cin>>wordCount;

		cout<<"Case #"<<i+1<<": ";


		for (int j = 0; j < wordCount; ++j)
		{
			double fraction = 0;

			string word;
			cin>>word;

			for (int k = 0; k < wordSamples.size(); ++k)
			{
				if (wordSamples[k].find(word) != string::npos)
				{
					fraction++;
				}
			}

			fraction = (double)fraction/(double)wordSamples.size();
			cout<<fraction<<" ";

		}

		cout<<endl;
	}

	return 0;
}