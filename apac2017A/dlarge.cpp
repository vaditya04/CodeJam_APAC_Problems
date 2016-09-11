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
int cardsA;

class Compare
{
public:
    bool operator() (pair<int, long long> &a, int b)
    {
        return a.first < b;
    }
    bool operator() (int a, pair<int, long long> &b)
    {
        return a < b.first;
    }
};

void generateCombos(map <int, vector< pair<int, long long> > > &combos, int index, int cardsNeeded, int cardsTaken, int coinsLeft, long long attackPower)
{
    if (cardsNeeded == 0 && (index == cardsA  || index == cardCount) )
    {
        return;
    }

    int cardsLeft = ((index>=cardsA)?(cardCount-index):(cardsA-index));
    if (cardsNeeded < cardsLeft)
    {
        generateCombos(combos, index + 1, cardsNeeded, cardsTaken, coinsLeft, attackPower);
    }

    int cost = 0;
    for (int i = currentLevels[index]; i < cardAttacks[index].size(); ++i)
    {
        cost += cardCosts[index][i];
        if (cost > coinsLeft)
        {
            break;
        }

        if (cardsNeeded == 1 || cardsNeeded == 0)
        {
            combos[cardsTaken+1].push_back(make_pair(coins - (coinsLeft-cost), attackPower + cardAttacks[index][i]));  
        }
        generateCombos(combos, index + 1, (cardsNeeded-1)<0?0:(cardsNeeded-1), cardsTaken+1, coinsLeft-cost, attackPower + cardAttacks[index][i]);
    }
}

void eraseUseless(map <int, vector< pair<int, long long> > > &combos)
{
    for (auto& i : combos)
    {
        auto& currentVector = i.second;
        vector< pair<int, long long> > newVector;
        sort(currentVector.begin(), currentVector.end());

        long long prev = 0;
        for (int j = 0; j < currentVector.size(); ++j)
        {
            if (prev < currentVector[j].second)
            {
                newVector.push_back(currentVector[j]);
                prev = currentVector[j].second;
            }
        }
        currentVector = newVector;
    }
}

long long getBestAttack()
{
    cardsA = cardCount/2;

    int min1 = MAXCARDS - (cardCount-cardsA);
    int min2 = MAXCARDS - cardsA;

    map <int, vector<pair<int, long long> > > map1, map2;
    
    generateCombos(map1, 0, min1, 0, coins, 0);
    generateCombos(map2, cardsA, min2, 0, coins, 0);

    eraseUseless(map1);
    eraseUseless(map2);
 
    long long answer = 0;
    for (auto i : map1)
    {
        if (map2.find(MAXCARDS - i.first) != map2.end())
        {
            auto currentVector = i.second;
            auto searchVector = map2[MAXCARDS-i.first];

            for (auto j: currentVector)
            {
                auto ans = upper_bound(searchVector.begin(), searchVector.end(), coins-j.first, Compare());
                if (ans == searchVector.begin())
                {
                    continue;
                }

                ans--;
                if ((*ans).first + j.first <= coins)
                {
                    answer = max((*ans).second + j.second, answer);
                }
            }
        }
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
        cardAttacks.clear();
        cardCosts.clear();
        currentLevels.clear();

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
            for (int k = 1; k < maxLevel; ++k)
            {
                cin>>cardCost[k];
            }
            cardCost[currentLevel-1] = 0;
            cardAttacks.push_back(cardAttack);
            cardCosts.push_back(cardCost);
        }

        long long answer = getBestAttack();

        cout<<"Case #"<<i+1<<": ";
        cout<<answer;
        cout<<endl;
    }
}