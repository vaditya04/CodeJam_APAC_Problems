/*input
3
0 1 1 0 0 1 0 0 0 0
60
1 0 1 0 1 1 1 1 1 1
20
0 1 0 1 0 1 0 1 0 1
128
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

#define INF INT_MAX

using namespace std; 

vector<int> generateNums(vector<bool> digitAvail, int target)
{
    vector<int> nums;
    for (int i = 2; i < target+1; ++i)
    {
        int j = i;
        bool contained = true;
        while (j>9)
        {
            // cout<<"j"<<digitAvail[j%10]<<endl;
            if (digitAvail[j%10])
            {
                j = j/10;
            }
            else
            {
                contained = false;
                break;
            }
        }
        if (digitAvail[j%10] && contained)
        {
            // cout<<i<<endl;
            nums.push_back(i);
        }
    }
    return nums;
}

int digitCount(int num)
{
    int count = 0;

    while (num = num/10)
    {
        count++;
    }

    return count+1;
}

int findMinClicks(vector<int> &nums, int target, vector<int> &computed)
{
    if (computed[target] != -1)
    {
        return computed[target];
    }
    if (target == 1)
    {
        computed[target] = 1;
        return computed[target];
    }

    int minClick = INF;
    for (int i = nums.size()-1; i >= 0; --i)
    {
        // cout<<nums[i]<<endl;
        if (nums[i] > target)
        {
            continue;
        }
        else if (nums[i] == target)
        {
            computed[target] = digitCount(target);
            return computed[target];
        }
        else if (target%nums[i] == 0)
        {

            int subCount = findMinClicks(nums, target/nums[i], computed);
            if (subCount != INF)
            {
                subCount += 1 + digitCount(nums[i]);
            }
            if (minClick > subCount)
            {
                minClick = subCount;
            }
        }
    }

    computed[target] = minClick;
    return computed[target];
}

int main(int argc, char const *argv[])
{	
	freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;


    for (int i = 0; i < testCaseCount; ++i)
    {
        vector<bool> digitAvail;
        for (int j = 0; j < 10; ++j)
        {
            int on;
            cin>>on;
            if (on)
            {
                digitAvail.push_back(true);
            }
            else
            {
                digitAvail.push_back(false);
            }
        }

        int target;
        cin>>target;

        // cout<<target<<endl;
        vector<int> nums;
        nums = generateNums(digitAvail, target);

        cout<<"Case #"<<i+1<<": ";
        
        vector<int> computed(target+1, -1);
        int answer = findMinClicks(nums, target, computed);

        if (answer != INF)
        {
            cout<<answer+1;        
        }
        else
        {
            cout<<"Impossible";
        }

        cout<<endl;


    }



}