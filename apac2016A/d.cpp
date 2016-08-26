/*input
2
3 3 3
1 R
2 L
3 R
5 3 3
2 R
4 R
6 R
7 R
8 R
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

#define PAIRINT pair<int, int>
#define PAIRBINT pair<bool, int>

using namespace std; 

int direction;
long long length;
long long rowCount, colCount;
long long low;

bool checkFood(int r, int c, map<PAIRINT, bool> &hasFood)
{
    if ((c+r)%2 == 0)
    {
        return false;
    }
    else if (hasFood.find(make_pair(r, c)) != hasFood.end())
    {
        return hasFood[make_pair(r,c)];
    }
    else
    {
        return true;
    }
}

void getCoords(int r, int c, int &newR, int &newC)
{
    newR = r-1;
    newC = c-1;

    // cout<<direction<<" "<<r<<" "<<c<<" ";
    if (direction == 0)
    {
        newC = (newC+1)%(colCount);
    }
    else if (direction == 1)
    {
        newR = (newR+1)%(rowCount);
    }
    else if (direction == 2)
    {
        newC = (newC+(colCount-1))%(colCount);
    }
    else if (direction == 3)
    {
        newR = (newR+(rowCount-1))%(rowCount);
    }
    newR++;newC++;
    // cout<<r<<" "<<c<<" "<<newR<<" "<<newC<<" "<<direction<<endl;
    // cout<<newR<<" "<<newC<<" "<<endl;
}

bool occupancyCheck(int newR, int newC,map<PAIRINT, bool> &occupied)
{
    if (occupied.find(make_pair(newR, newC)) == occupied.end())
    {
        // occupied[make_pair(newR,newC)] = false;    
        return false;
    }
    else
    {
        return occupied[make_pair(newR, newC)];
    }
}

bool runOne(map<int, PAIRINT> &snakePos, map<PAIRINT, bool> &hasFood, map<PAIRINT, bool> &occupied)
{
    int newR, newC;

    int r = snakePos[length].first;
    int c = snakePos[length].second;
    getCoords(r, c, newR, newC);
    // cout<<newR<<" "<<newC<<" "<<direction<<" "<<length<<endl;  
    // cout<<snakePos[length].first<<" "<<snakePos[length].second<<"fALSD"<<endl;
/*    if (occupancyCheck(newR, newC, occupied))
    {
        cout<<newR<<" "<<newC<<" "<<"FAIL"<<endl;
        return true;
    }
*/
    if (checkFood(newR, newC, hasFood))
    {

        hasFood[make_pair(newR, newC)] = false;

        length++;

        snakePos[length] = make_pair(newR, newC);

        occupied[snakePos[length]] = true;
        // cout<<snakePos[1].first<<" "<<snakePos[1].second<<" "<<snakePos[2].first<<" "<<snakePos[2].second<<"trud"<<endl;

    }
    else
    {
        occupied[snakePos[low]] = false;
        if (occupancyCheck(newR, newC, occupied))
        {
            // cout<<newR<<" "<<newC<<" "<<"FAIL"<<endl;
            return true;
        }

        length++;

        snakePos[length] = make_pair(newR, newC);
        low++;
        occupied[snakePos[length]] = true; 
        // cout<<snakePos[1].first<<" "<<snakePos[1].second<<"trud"<<endl;

    }
    return false;
}

bool executeMove(map<int, PAIRINT> &snakePos, map<PAIRINT, bool> &hasFood, map<PAIRINT, bool> &occupied, char move, bool actionFlag)
{
    // cout<<snakePos[1].first<<" "<<snakePos[1].second<<" "<<length<<" "<<move<<endl;
    if (runOne(snakePos, hasFood, occupied))
    {
        return true;
    }

    if (move == 'L')
    {
        direction += 3;
        direction = direction%4;
    }
    if (move == 'R')
    {
        direction += 1;
        direction = direction%4;
        // cout<<"L"<<endl;
    }
    if (move == 'N' && actionFlag == true)
    {
        // return false;
        for (int i = 0; i < max(2*rowCount+1, 2*colCount+1) + (length-low+1); ++i)
        {
            // cout<<"FINOFF"<<i<<" "<<max(2*rowCount+1, 2*colCount+1) + length<<" "<<length<<endl;
            if (runOne(snakePos, hasFood, occupied))
            {
                return true;
            }
        }
        return true;
    }
    return false;
}


int main(int argc, char const *argv[])
{   
    freopen("D-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int actionCount;
        cin>>actionCount>>rowCount>>colCount;

        long long timeLimit = 1000000000;

        map<PAIRINT, bool> hasFood;
        map<PAIRINT, bool> occupied;
        map<int, PAIRINT> snakePos;

        direction = 0;
        snakePos[1] = make_pair(1, 1);
        length = 1;
        low = 1;
        occupied[make_pair(1,1)] = true;
        long long answer; 
        bool doneFlag = false;
        bool nextMove = true;
        long long time = -1;
        char move;
        for (long long j = 0; j < timeLimit; ++j)
        {
            if ((nextMove || doneFlag ) && actionCount > 0)
            {
                cin>>time>>move;  
                nextMove = false;     
                actionCount--;         
            }
            // cout<<j<<" "<<actionCount<<" "<<time<<endl;

            if (!doneFlag)
            {
                if (j+1 == time)
                {
                    doneFlag = executeMove(snakePos, hasFood, occupied, move, false);
                    nextMove = true;   
                    if (actionCount == 0)
                    {
                        actionCount--;                                              
                    }
                    // cout<<actionCount<<endl;
                }
                else
                {
                    if (actionCount != -1)
                    {
                        doneFlag = executeMove(snakePos, hasFood, occupied, 'N', false);
                    }
                    else
                    {
                        // cout<<"BINGO"<<endl;
                        doneFlag = executeMove(snakePos, hasFood, occupied, 'N', true);
                        break;
                        // actionCount = 1;
                    }
                }

            }
            else
            {
                if (actionCount <= 0)
                {
                    break;
                }
                // break;
            }
        }

        cout<<"Case #"<<i+1<<": ";

        cout<<length-low+1;

        cout<<endl;
    }
}