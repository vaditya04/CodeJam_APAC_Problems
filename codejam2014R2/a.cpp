/*input
3
3 100
10 20 70
4 100
30 40 60 70
5 100
10 20 30 40 60
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

int main(int argc, char const *argv[])
{   
    freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    // cout<<fixed<<setprecision(10);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int fileCount, diskCapacity;
        cin>>fileCount>>diskCapacity;

        vector<int> files(fileCount);

        for (int j = 0; j < fileCount; ++j)
        {
            cin>>files[j];
        }

        sort(files.begin(), files.end());

        int diskCount = 0;
        int endPointer = fileCount-1;
        for (int j = 0; j < fileCount; ++j)
        {
            if (endPointer == j)
            {
                diskCount++;
                break;
            }
            else if (endPointer < j)
            {
                break;
            }

            if (files[j] + files[endPointer] <= diskCapacity)
            {
                endPointer--;
                diskCount++;
            }
            else
            {
                while (files[j] + files[endPointer] > diskCapacity && endPointer > j)
                {
                    endPointer--;
                    diskCount++;
                }
                if (endPointer > j)
                {
                    endPointer--;
                    diskCount++;
                }
                else
                {
                    diskCount++;
                    break;
                }
            }
        }

        cout<<"Case #"<<i+1<<": ";

        cout<<diskCount;

        cout<<endl;
    }
}