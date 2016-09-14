/*input
3
08:00:00
09:00:00
18:00:00
22:00:00
12:00:00
100
08:00:00
09:00:00
18:00:00
22:00:00
01:00:00
1
00:00:00
12:00:00
12:00:01
23:59:59
00:00:02
2
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

int getUp, work, home, bed, X, secondsInDay, currentTime, lastFed;
long long day; 

int convertTime(string time)
{
	return atoi(time.substr(0,2).c_str())*60*60 + atoi(time.substr(3,2).c_str())*60 + atoi(time.substr(6,2).c_str()); 
}

long long computeFeedCount()
{
	long long count = 0;
	int i = 0;
	while (1)
	{
		int nextFeedTime = lastFed + X;
		if (nextFeedTime >= day*secondsInDay)
		{
			return count;
		}

		int currentDay = lastFed/secondsInDay;
		int newDay = nextFeedTime/secondsInDay;
		int feedTimeInDay = nextFeedTime%secondsInDay;
		bool inWorkHours = feedTimeInDay >= work && feedTimeInDay < home;
		bool inSleepHours = feedTimeInDay >= bed || feedTimeInDay < getUp;
		if (!inWorkHours && !inSleepHours)
		{
			count++;
			lastFed = i = nextFeedTime;
		}
		else
		{
			if (((lastFed%secondsInDay == work-1 && inWorkHours) || (lastFed%secondsInDay == bed-1 && inSleepHours)) && (currentDay == newDay || feedTimeInDay < getUp))
			{
				return -1;
			}
			else
			{
				count++;
				if (feedTimeInDay >= work && feedTimeInDay < home)
				{
					int days = newDay;
					lastFed = i = newDay*secondsInDay + work-1;
				}
				else if (feedTimeInDay >= bed || feedTimeInDay < getUp)
				{
					lastFed = i = currentDay*secondsInDay + bed-1;
				}
				else
				{
					return -2;
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{	
    freopen("D-small-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;
    cin>>testCaseCount;
 	for (int i = 0; i < testCaseCount; ++i)
    {
    	currentTime = 0;
    	lastFed = 0;

    	secondsInDay = convertTime("24:00:00");
    	string time;
    	cin>>time;
    	getUp = convertTime(time);
    	cin>>time;
    	work = convertTime(time);
    	cin>>time;
    	home = convertTime(time);
    	cin>>time;
    	bed = convertTime(time);
    	cin>>time;
    	X = convertTime(time);
    	cin>>day;

    	long long answer = computeFeedCount();

        cout<<"Case #"<<i+1<<": ";
        cout<<answer;
        cout<<endl;
	}

}