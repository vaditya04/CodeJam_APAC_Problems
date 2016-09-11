/*input
2
20 8
3 1
1 10 100
1 2
3 1
1 10 100
1 3
3 1
1 10 100
1 4
3 1
1 10 100
1 5
3 1
1 10 100
1 6
3 1
1 10 100
1 7
3 1
1 10 100
1 8
3 1
1 10 100
1 9
30 10
4 1
1 10 100 200
1 2 3
3 1
1 10 100
2 4
3 1
1 10 100
3 6
4 2
1 10 100 200
4 8 16
3 1
1 10 100
5 10
3 1
1 10 100
6 12
3 1
1 10 100
7 14
3 1
1 10 100
8 16
3 1
1 10 100
9 18
3 1
1 10 100
10 20
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

#define MAXCARDS 8

vector<vector<int> > cardAttacks;
vector<vector<int> > cardCosts;

vector<int> currentLevels;
int coins, cardCount;

map<pair<int, pair<int, int> >, long long> memoizeSolution;

long long getBestAttack(int currentCard, int coinsLeft, int cardsLeft)
{
    pair<int, pair<int, int> > key = make_pair(currentCard, make_pair(coinsLeft, cardsLeft));
    if (memoizeSolution.find(key) != memoizeSolution.end())
    {
        return memoizeSolution[key];
    }

    if (cardsLeft == 0)
    {
        return 0;
    }

    long long attackPower = 0;
    int currentCardLevel = currentLevels[currentCard];
    long long cost = 0;

    if (cardsLeft < (MAXCARDS - currentCard))
    {
        attackPower = getBestAttack(currentCard+1, coinsLeft, cardsLeft);
    }

    for (int j = currentCardLevel; j < cardAttacks[currentCard].size(); ++j)
    {
        if (cost > coinsLeft)
        {
            break;
        }
        attackPower = max(attackPower, (long long)getBestAttack(currentCard+1, coinsLeft - cost, cardsLeft - 1) + (long long)cardAttacks[currentCard][j]);
        if (j != cardAttacks[currentCard].size()-1)
        {
            cost += cardCosts[currentCard][j];
        }    
    }

    memoizeSolution[key] = attackPower;
    return attackPower;
}

int main(int argc, char const *argv[])
{	
    freopen("D-small-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;
    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        cardAttacks.clear();
        cardCosts.clear();
        currentLevels.clear();

        memoizeSolution = map <pair<int, pair<int, int> >, long long> ();

        cin>>coins>>cardCount;

        for (int j = 0; j < cardCount; ++j)
        {
            int maxLevel, currentLevel;
            cin>>maxLevel>>currentLevel;
            currentLevels.push_back(currentLevel-1);

            vector<int> cardAttack(maxLevel);
            for (int k = 0; k < maxLevel; ++k)
            {
                cin>>cardAttack[k];
            }

            vector<int> cardCost(maxLevel);
            for (int k = 0; k < maxLevel-1; ++k)
            {
                cin>>cardCost[k];
            }
            cardAttacks.push_back(cardAttack);
            cardCosts.push_back(cardCost);
        }

        long long answer = getBestAttack(0, coins, MAXCARDS);

        cout<<"Case #"<<i+1<<": ";
        cout<<answer;
        cout<<endl;
    }
}