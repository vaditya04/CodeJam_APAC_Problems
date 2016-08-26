/*input
3
1 1 1 5
1
1
2 1 5 11
1 2
3 4
3 2 3 109
6 4 3
2 1 5
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

#define PAIRDINT pair<int, pair<int, int> >

using namespace std;

vector<int> A, B;
int matSize, subMatSize, offset, mod;

#define VAL(i, j) ((i+1)*A[i] + (j+1)*B[j] + offset)%mod

void checkErase(map<int, int> &subMatMap, int value)
{
    // cout<<value<<" deleted "<<endl;
    subMatMap[value]--;
    if (subMatMap[value] == 0)
    {
        subMatMap.erase(value);
    }
}

void checkInsert(map<int, int> &subMatMap, int newValue)
{
    // cout<<newValue<<" inserted "<<endl;
    if (subMatMap.find(newValue) != subMatMap.end())
    {
        subMatMap[newValue]++;
    }
    else
    {
        subMatMap[newValue] = 1;
    }
}

void updateSum(map<int, int> &subMatMap, long long &answer)
{
    map <int, int>::iterator currentMax;
    currentMax = max_element(subMatMap.begin(), subMatMap.end());
    answer += currentMax->first;
    // cout<<currentMax->first<<" added "<<endl;
}

long long getSumMax()
{   
    long long answer = 0;

    map <int, int> subMatMap;

    for (int i = 0; i < subMatSize; ++i)
    {
        for (int j = 0; j < subMatSize; ++j)
        {
            int value = VAL(i, j);
            checkInsert(subMatMap, value);
        }
        // cout<<currentMax->first<<endl;
    }
        updateSum(subMatMap, answer);

    bool startToEnd = true;
    for (int i = 0; i < matSize-subMatSize+1; ++i)
    {
        if (startToEnd)
        {
            for (int j = 1; j < matSize-subMatSize+1 ; ++j)
            {
                for (int k = 0; k < subMatSize; ++k)
                {
                    int value = VAL(i+k, j-1);
                    checkErase(subMatMap, value);

                    int newValue = VAL(i+k, j+subMatSize-1);
                    checkInsert(subMatMap, newValue);
                }
                updateSum(subMatMap, answer);
            }            
        }
        else
        {
            for (int j = matSize-2; j >= subMatSize - 1 ; --j)
            {
                for (int k = 0; k < subMatSize; ++k)
                {
                    int value = VAL(i+k, j+1);
                    checkErase(subMatMap, value);

                    int newValue = VAL(i+k, j+1-subMatSize);
                    checkInsert(subMatMap, newValue);
                }
                updateSum(subMatMap, answer);
            }          
        }

        if (i != matSize-subMatSize)
        {
            int base = 0;
            if (startToEnd)
            {
                base = matSize-subMatSize;
            }
            for (int j = base; j < base + subMatSize; ++j)
            {
                int value = VAL(i, j);
                checkErase(subMatMap, value);
                    // cout<<i<<" "<<j<<endl;

        
                int newValue = VAL(i+subMatSize, j);
                checkInsert(subMatMap, newValue);
                    // cout<<i+subMatSize<<" "<<j<<endl;
            }   

            updateSum(subMatMap, answer);
        }

        startToEnd = !startToEnd;
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
        cin>>matSize>>subMatSize>>offset>>mod;

        A.clear();
        B.clear();
        A.resize(matSize); 
        B.resize(matSize);

        for (int j = 0; j < matSize; ++j)
        {
            cin>>A[j];
            // cout<<A[j]<<" ";
        }
        // cout<<endl;

        for (int j = 0; j < matSize; ++j)
        {
            cin>>B[j];
            // cout<<B[j]<<" ";
        }
        // cout<<endl;

        long long answer = getSumMax();

        cout<<"Case #"<<i+1<<": ";
        cout<<answer;
        cout<<endl;
    }
}

/*    priority_queue <PAIRDINT , vector<PAIRDINT> > maxHeap;

    for (int i = 0; i < matSize; ++i)
    {
        for (int j = 0; j < matSize; ++j)
        {
            maxHeap.push(make_pair(VAL(i,j), make_pair(i, j)));
        }
    }
    int doneCount = pow((matSize-subMatSize+1),2);
    vector<vector<bool> > doneSubMat(matSize-subMatSize+1, vector<bool>(matSize-subMatSize+1, false));

    while (doneCount)
    {
        int val = maxHeap.top().first;
        int posx = maxHeap.top().second.first;
        int posy = maxHeap.top().second.second;
        maxHeap.pop();
        // cout<<doneCount<<endl;
        int lowerBoundx, upperBoundx, lowerBoundy, upperBoundy;

        lowerBoundx = max(posx-subMatSize+1, 0);
        upperBoundx = min(posx, matSize-subMatSize);
        lowerBoundy = max(posy-subMatSize+1, 0);
        upperBoundy = min(posy, matSize-subMatSize);

        for (int i = lowerBoundx; i <= upperBoundx ; ++i)
        {
            for (int j = lowerBoundy; j <= upperBoundy; ++j)
            {
                if (!doneSubMat[i][j])
                {
                    doneCount--;
                    answer += val;
                    doneSubMat[i][j] = true;
                }
                if (doneCount == 0)
                {
                    break;
                }
            }
        }
    }
*/