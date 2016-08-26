/*3
3 7
0 0 0 0 0 0
1 2 2 0 0 0
1 1 1 0 0 0
5 10
0 0 0 0 0 0
35 0 0 -1 0 0
1 54 0 0 -2 0
2 -150 0 0 10 0
4 0 0 -1 0 0
3 1
-10 2 0 1 0 0
0 0 10 0 0 -1
-10 -2 0 1 0 0
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

#define DISTANCE(pos1, vel1, pos2, vel2, t) sqrt(pow(pos1[0]-pos2[0] + (vel1[0]-vel2[0])*t,2) + pow(pos1[1]-pos2[1] + (vel1[1]-vel2[1])*t,2) + pow(pos1[2]-pos2[2] + (vel1[2]-vel2[2])*t,2))


#define X 0
#define Y 1
#define Z 2

#define INF DBL_MAX
#define NEGINF DBL_MIN

#define PAIRDINT pair<double, pair<double, int> >

double timer;
double timeLimit;

vector<vector<int> > asteroidPos;
vector<vector<int> > asteroidVel;
vector<vector<double> > distances;
int asteroidCount;

double currentBestDistance;

class Compare
{
public:
    bool operator() (PAIRDINT a, PAIRDINT b)
    {
    	return a.first > b.first;
    }
};
priority_queue< PAIRDINT, vector< PAIRDINT >, Compare > distqueue; 

int findMinMax(int currentIndex, vector<bool> &visited, double pathMax)
{
	if (visited[currentIndex])
	{
		return -1;
	}
	else
	{
		visited[currentIndex] = true;
	}
	// cout<<currentIndex<<endl;
	for (int i = 0; i < asteroidCount; ++i)
	{
		// int minIndex = -1;
		// double min = INF;

		// cout<<"1"<<endl;
		if (!visited[i])
		{

		// cout<<"2"<<endl;
			distances[currentIndex][i] = DISTANCE(asteroidPos[currentIndex], asteroidVel[currentIndex], asteroidPos[i], asteroidVel[i], timer);
			distqueue.push(make_pair(distances[currentIndex][i], make_pair(max(pathMax,distances[currentIndex][i]), i)));
			// cout<<distqueue.top().first<<" "<<distqueue.top().second<<endl;
		}		
	}

	int lastIndex = -1;
	while(!distqueue.empty())
	{
		// cout<<"3"<<endl;
// cout<<"A" <<distqueue.empty()<<endl;
			
		if (distqueue.top().second.second == 1)
		{
			pathMax = max(pathMax, distqueue.top().first);
			// cout<<pathMax<<endl;
			currentBestDistance = pathMax;
			distqueue = priority_queue< PAIRDINT, vector< PAIRDINT >, Compare > ();
			// cout<<"B"<<distqueue.empty()<<endl;
			return 1;
		}
		else
		{
			pathMax = max(pathMax, distqueue.top().first);
			// cout<<pathMax<<endl;
			lastIndex = distqueue.top().second.second;
			double newPathMax = distqueue.top().second.first;
			distqueue.pop();
			findMinMax(lastIndex, visited, newPathMax);
		}
	}
	return lastIndex;
}
int main(int argc, char const *argv[])
{	
	freopen("C-small-practice.in","r",stdin);
    freopen("output.out","w",stdout);
	cout<<fixed;
	cout<<setprecision(7);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
    	cin>>asteroidCount;
    	cin>>timeLimit;
    	asteroidPos.resize(asteroidCount, vector<int> (3, 0));
    	asteroidVel.resize(asteroidCount, vector<int> (3, 0));
    	
    	distances.resize(asteroidCount, vector<double> (asteroidCount, INF));

    	for (int j = 0; j < asteroidCount; ++j)
    	{
    		cin>>asteroidPos[j][X]>>asteroidPos[j][Y]>>asteroidPos[j][Z];
    		cin>>asteroidVel[j][X]>>asteroidVel[j][Y]>>asteroidVel[j][Z];
    	}

    	timer = 0;
    	currentBestDistance = INF;

    	vector<bool> visited(asteroidCount, false);
    	distqueue = priority_queue< PAIRDINT, vector< PAIRDINT >, Compare > ();
    	double distance = findMinMax(0, visited, NEGINF);

		cout<<"Case #"<<i+1<<": "<<currentBestDistance<<endl;
		
		/*if (i == 1)
			break;*/
    	asteroidPos.clear();
    	asteroidVel.clear();
    	distances.clear();
    }

	return 0;
}