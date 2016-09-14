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

long long getUp, work, home, bed, X, secondsInDay, lastFed;
long long day;
long long tempDay;


vector<pair<int, int> > patternDetect;

int convertTime(string time)
{
	return atoi(time.substr(0,2).c_str())*60*60 + atoi(time.substr(3,2).c_str())*60 + atoi(time.substr(6,2).c_str()); 
}

long long computeFeedCount()
{
	long long count = 0;
	while (1)
	{
		if (lastFed != 0)
		{
			patternDetect.push_back(make_pair(lastFed%secondsInDay, lastFed));
		}

		long long nextFeedTime = lastFed + X;
		if (nextFeedTime >= tempDay*secondsInDay)
		{
			return count;
		}

		long long currentDay = lastFed/secondsInDay;
		long long newDay = nextFeedTime/secondsInDay;
		long long feedTimeInDay = nextFeedTime%secondsInDay;
		bool inWorkHours = feedTimeInDay >= work && feedTimeInDay < home;
		bool inSleepHours = feedTimeInDay >= bed || feedTimeInDay < getUp;
		if (!inWorkHours && !inSleepHours)
		{
			count++;
			lastFed = nextFeedTime;
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
					long long days = newDay;
					lastFed = newDay*secondsInDay + work-1;
				}
				else if (feedTimeInDay >= bed || feedTimeInDay < getUp)
				{
					lastFed = currentDay*secondsInDay + bed-1;
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
    freopen("D-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;
    cin>>testCaseCount;
 	for (int i = 0; i < testCaseCount; ++i)
    {
    	lastFed = 0;
    	patternDetect.clear();

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

    	tempDay = day;
    	long long answer = 0;
    	if (tempDay <= 1000)
    	{
    		answer = computeFeedCount();
    	}
    	else
    	{
    		tempDay = 1000;
	    	if (computeFeedCount() == -1)
	    	{
				answer = -1;	    		
	    	}
	    	else
	    	{
		    	int start = -1, end = -1;
		    	for (int j = 0; j < patternDetect.size()-1; ++j)
		    	{
			    	for (int k = j+1; k < patternDetect.size(); ++k)
			    	{
			    		if (patternDetect[k].first == patternDetect[j].first)
			    		{
			    			end = k;
			    			start = j;
			    			break;
			    		}
			    	}
			    	if (end != -1)
			    		break;
		    	}
		    	if (end == -1)
		    	{
		    		cout<<"COULDN'T FIND PATTERN"<<endl;
		    		return -1;
		    	}

		    	int patternFeed = end-start;
		    	int timeLapse = patternDetect[end].second - patternDetect[start].second;
		    	answer = (day*secondsInDay - patternDetect[start].second)/timeLapse; 		
		    	lastFed = patternDetect[end-1].second + (answer-1)*timeLapse;

		    	answer *= patternFeed;
		    	answer += start;

		    	tempDay = day;
		    	answer += computeFeedCount();
	    	}

    	}

        cout<<"Case #"<<i+1<<": ";
        cout<<answer;
        cout<<endl;
	}

}