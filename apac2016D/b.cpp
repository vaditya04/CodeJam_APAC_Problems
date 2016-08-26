/*input
2
2 4 1
2 1 -2 -1
3 3
-2 1
1 3 1
1 -1 -2
-2 2
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

using namespace std;

#define INF INT_MAX
#define PAIRINT pair<int, int>

vector<int> velocities;
vector<PAIRINT> balloonPos;
vector<int> currentBalloonHeight;

priority_queue<PAIRINT, vector<PAIRINT> > balloonTime;

int balloonCount, maxHeight, availableEnergy;

int findTime(int horizontal, int vertical)
{
	if (horizontal*velocities[vertical] > 0 || horizontal != 0 && velocities[vertical] == 0)
	{
		return INF;
	}
	else if (horizontal == 0)
	{
		return 0;
	}
	else
	{
		// cout<<horizontal<<" "<<velocities[vertical]<<" "<<(horizontal/velocities[vertical])?-(horizontal/velocities[vertical]):1;
		// cout<<endl;
		int vel = abs(velocities[vertical]), pos = abs(horizontal);

		return (pos + vel-1)/vel;

	}
}

int findMaxTime()
{
	while (1)
	{
		int maxTime = balloonTime.top().first;
		int currentBalloon = balloonTime.top().second;
		
		// cout<<maxTime<<" "<<availableEnergy<<endl;
		if (availableEnergy == 0)
		{
			return maxTime;
		}

		balloonTime.pop();

		int currentVertical = currentBalloonHeight[currentBalloon];
		int horizontal = balloonPos[currentBalloon].first;
		int originalVertical = balloonPos[currentBalloon].second;

		int diff = abs(currentVertical - originalVertical);
		int startPointDown = originalVertical - diff-1;
		int startPointUp = originalVertical + diff+1;

		int optionUp, upTime = INF;
		for (optionUp = startPointUp; optionUp < maxHeight; ++optionUp)
		{
			upTime = findTime(horizontal, optionUp);
			if ( upTime < maxTime)
			{
				break;
			}
		}
		
		int optionDown, downTime = INF;
		for (optionDown = startPointDown; optionDown >= 0; --optionDown)
		{
			downTime = findTime(horizontal, optionDown);
			if ( downTime < maxTime)
			{
				break;
			}
		}

		// cout<<downTime<<" "<<abs(originalVertical-optionDown)<<" "<<upTime<<" "<<abs(originalVertical-optionUp)<<endl;

		int nextHeight, nextTime;

		if (upTime >= maxTime || optionUp >= maxHeight)
		{
			nextHeight = optionDown;
			nextTime = downTime;
		}
		else if (downTime >= maxTime || optionDown < 0)
		{
			nextHeight = optionUp;
			nextTime = upTime;			
		}
		else if (abs(originalVertical-optionUp) < abs(originalVertical-optionDown))
		{
			nextHeight = optionUp;
			nextTime = upTime;
		}
		else if (abs(originalVertical-optionUp) > abs(originalVertical-optionDown))
		{
			nextHeight = optionDown;
			nextTime = downTime;
		}
		else
		{
			if (upTime >= downTime)
			{
				nextHeight = optionDown;
				nextTime = downTime;
			}
			else
			{
				nextHeight = optionUp;
				nextTime = upTime;
			}
		}

		if (nextTime >= maxTime || nextHeight >= maxHeight || nextHeight < 0)
		{
			return maxTime;
		}

		int cost = abs(originalVertical - nextHeight) - abs(originalVertical - currentVertical);

		if (availableEnergy >= cost)
		{
			availableEnergy -= cost;
			currentBalloonHeight[currentBalloon] = nextHeight;
			balloonTime.push(make_pair(nextTime, currentBalloon));
			// cout<<nextTime<<" "<<maxTime<<endl;
		}
		else
		{
			return maxTime;
		}
	}
}

int main(int argc, char const *argv[])
{	
    freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
 		cin>>balloonCount>>maxHeight>>availableEnergy;

 		velocities = vector<int>(maxHeight);

 		for (int j = 0; j < maxHeight; ++j)
 		{
 			cin>>velocities[j];
 			// cout<<velocities[j]<<endl;
 		}

 		balloonPos = vector<PAIRINT> (balloonCount);
 		currentBalloonHeight = vector<int> (balloonCount);
		balloonTime = priority_queue<PAIRINT, vector<PAIRINT> >();

 		for (int j = 0; j < balloonCount; ++j)
 		{
 			int horizontal, vertical;
 			cin>>horizontal>>vertical;

 			currentBalloonHeight[j] = vertical;
 			balloonPos[j] = make_pair(horizontal, vertical);
 			balloonTime.push(make_pair(findTime(horizontal, vertical), j));
 		}

 		int answer = findMaxTime();

        cout<<"Case #"<<i+1<<": ";

        if (answer == INF)
        {
        	cout<<"IMPOSSIBLE";
        }
        else
        {
	        cout<<answer;
        }

        cout<<endl;
    }
}