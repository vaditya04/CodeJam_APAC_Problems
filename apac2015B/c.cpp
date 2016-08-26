/*input
2
6 0
4 4 3 3 3 4
5 1
3 1 2 3 4
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

int diff;
vector<int> numArr;
vector<vector<int> > answerStore;

int computeRemainingCards(int start, int end)
{
    if (answerStore[start][end] != -1)
    {
        return answerStore[start][end];
    }
    else if (end-start+1 < 3)
    {
        answerStore[start][end] = end-start+1;
    }
    else if (end<start)
    {
        answerStore[start][end] = 0;
    }
    else
    {
        int answer1 = 1 + computeRemainingCards(start+1, end);
        int answer2 = INF;

        int next1 = numArr[start] + diff, next2 = numArr[start] + 2*diff;
        int newEnd=start, newStart=end;

        for (int i = start+1; i < end; ++i)
        {
            if (numArr[i] == next1)
            {
                newEnd = i;
                for (int j = i+1; j <= end; ++j)
                {
                    if (numArr[j] == next2)
                    {
                        newStart = j;
                        if (computeRemainingCards(start+1, newEnd-1) == 0 && computeRemainingCards(newEnd+1, newStart-1) == 0)
                        {
                            answer2 = min(answer2, computeRemainingCards(newStart+1, end));
                        }
                    }
                }
            }
        }
        answerStore[start][end] = min(answer1, answer2);
    }

    return answerStore[start][end];
}

int main(int argc, char const *argv[])
{   
    freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int cardCount;
        cin>>cardCount>>diff;

        numArr.clear();
        numArr.resize(cardCount);

        for (int j = 0; j < cardCount; ++j)
        {
            cin>>numArr[j];
        }

        answerStore.clear();
        answerStore.resize(cardCount+2, vector<int> (cardCount+2, -1));

        int answer = computeRemainingCards(0, cardCount-1);

        cout<<"Case #"<<i+1<<": ";
        
        cout<<answer;

        cout<<endl;
    }
}
