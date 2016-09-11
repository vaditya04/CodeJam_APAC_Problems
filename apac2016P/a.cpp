/*input
2
1
Dead_Bowie Fake_Thomas_Jefferson
3
Dead_Bowie Fake_Thomas_Jefferson
Fake_Thomas_Jefferson Fury_Leika
Fury_Leika Dead_Bowie
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

map<string, vector<string> > adjList;
map<string, bool> color;
bool isBipartite;

void BFS(string startNode)
{
    queue<string> BFSQueue;

    color[startNode] = true;
    BFSQueue.push(startNode);  

    while (!BFSQueue.empty())
    {
        string currentNode = BFSQueue.front();
        BFSQueue.pop();

        bool currentColor = color[currentNode];
        for (auto i: adjList[currentNode])
        {
            if (color.find(i) != color.end())
            {
                if (color[i] == !currentColor)
                {
                    continue;
                }    
                else
                {
                    isBipartite = false;
                    break;
                }
            }
            else
            {
                color[i] = !currentColor;
                BFSQueue.push(i);
            }
        }
    }    
}

bool bipartiteCheck()
{
    for (auto i : adjList)
    {
        if (color.find(i.first) == color.end())
        {
            BFS(i.first);
        }
    }
}

int main(int argc, char const *argv[])
{   
    freopen("A-small-practice-2.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;
    cin>>testCaseCount;

    // cout<<fixed<<setprecision(10);

    for (int i = 0; i < testCaseCount; ++i)
    {
        adjList.clear();
        color.clear();
        isBipartite = true;

        int m;
        cin>>m;

        string startName;

        for (int j = 0; j < m; ++j)
        {
            string name1, name2;
            cin>>name1>>name2;

            adjList[name1].push_back(name2);
            adjList[name2].push_back(name1);
            startName = name1;
        }

        bipartiteCheck();

        string answer;
        if (isBipartite)
        {
            answer = "Yes";
        }
        else
        {
            answer = "No";
        }

        cout<<"Case #"<<i+1<<": ";

        cout<<answer;

        cout<<endl;
    }
}