/*input
2
3 3
0 1 10
1 2 3
2 0 3
3 3
0 1 10
1 2 3
2 1 3
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

#define INF LLONG_MAX
#define PAIRINT pair<int, int>

using namespace std; 

int main(int argc, char const *argv[])
{   
    freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
        int officeCount, roadCount;
        cin>>officeCount>>roadCount;

        vector<vector<long long> > network(officeCount, vector<long long>(officeCount, INF));


        map<PAIRINT, int> roadMap;
        vector<PAIRINT> samePairs;
        for (int j = 0; j < roadCount; ++j)
        {
            int u, v, time;

            cin>>u>>v>>time;

            if (u == v)
            {

            }
            else if (roadMap.find(make_pair(u,v)) != roadMap.end())
            {
                if (network[u][v] > time)
                {
                    network[u][v] = time;
                    network[v][u] = time;
                    roadMap[make_pair(u,v)] = j;
                    roadMap[make_pair(v,u)] = j;
                }                
                else if (network[u][v] == time)
                {
                    samePairs.push_back(make_pair(roadMap[make_pair(u,v)], j));
                }
            }
            else
            {
                network[u][v] = time;
                network[v][u] = time;       
                roadMap[make_pair(u,v)] = j;
                roadMap[make_pair(v,u)] = j;
            }
        }
        vector<vector<int> > predecessor(officeCount, vector<int>(officeCount, -1));

        for (int j = 0; j < officeCount; ++j)
        {
            for (int k = 0; k < officeCount; ++k)
            {
                if (network[k][j] != INF)
                {
                    predecessor[k][j] = k;
                }
            }
        }

        vector<vector<long long> > dist(network);

        for (int j = 0; j < officeCount; ++j)
        {
            for (int k = 0; k < officeCount; ++k)
            {
                for (int r = 0; r < officeCount; ++r)
                {
                    if (dist[k][j] != INF && dist[j][r] != INF && dist[k][j] + dist[j][r] < dist[k][r])
                    {
                        dist[k][r] = dist[k][j] + dist[j][r];
                        predecessor[k][r] = predecessor[j][r];
                    }
                }
            }
        }

        vector<bool> answer(roadCount, false);

        for (int j = 0; j < officeCount; ++j)
        {
            for (int k = 0; k < officeCount; ++k)
            {
                // cout<<j<<" "<<k<<" "<<predecessor[j][k]<<endl;
                if (j != k && predecessor[j][k] != -1)
                {
                    // cout<<"ANS"<<j<<" "<<k<<" "<<predecessor[j][k]<<" "<<roadMap[make_pair(k, predecessor[j][k])]<<endl;
                    if (roadMap.find(make_pair(k, predecessor[j][k])) != roadMap.end())
                        answer[roadMap[make_pair(k, predecessor[j][k])]] = true;
                }
            }
        }

        for (int j = 0; j < samePairs.size(); ++j)
        {
            answer[samePairs[j].second] = answer[samePairs[j].first];
        }

        cout<<"Case #"<<i+1<<": "<<endl;;

        for (int j = 0; j < roadCount; ++j)
        {
            if (!answer[j])
            {
                cout<<j<<endl;
            }
        }
        
        // cout<<endl;
    }
}