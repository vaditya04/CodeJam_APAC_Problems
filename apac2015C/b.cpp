/*input
2
2
5 3
3 5 7 3
4 2
1 1 1
1
1 2 2 2 1
1
1 1 2 4
2
5 3
3 5 7 3
4 2
1 1 1
2
1 2 2 2 1
2 4 1 4 1
1
1 1 1 5
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
#define PAIRDINT pair<int, pair<int, bool> >
#define PAIRINT pair<int,  int >

using namespace std; 

/*class Compare
{
public:
    bool operator() (PAIRINT a, PAIRINT b)
    {
        return a.first > b.first;
    }

    bool operator() (PAIRINT a, int b)
    {
        return a.second < b;
    }

    bool operator() (int a, PAIRINT b)

    {
        return a < b.second;
    }
};*/

/*

bool inBounds(int i, int j, int min, int max)
{
    if (i<min || i>= max || j < min || j >= max)
    {
        return false;
    }
    return true;
}

*/
int findShortestPath(int source, int destin, vector<vector<PAIRINT> > graph, vector<int> &mapping, vector<int> &waitTime)
{
    priority_queue< PAIRDINT, vector<PAIRDINT>, greater<PAIRDINT> > minheap;

    vector<int> dist(1001, INF);
    vector<int> distT(1001, INF);

    // vector<bool> visited(1001, false);

    minheap.push(make_pair(0, make_pair(source, true)));
    dist[source] = 0;
    distT[source] = 0;

    while(!minheap.empty())
    {       
        int index = minheap.top().second.first;
        bool tunnelFlag = minheap.top().second.second;
        minheap.pop();

        bool endFlag = false;
        
        int i;
        for (i = 0; i < mapping.size(); ++i)
        {
            if (mapping[i] == index)
            {
                endFlag = true;
                i++;
                break;
            }
            else if (mapping[i] == index + 1)
            {
                endFlag = true;
                break;
            }
            else if (mapping[i]>index)
            {
                break;
            }
        }

        if (tunnelFlag == true)
        {
        
            graph[index][0].first += waitTime[i-1];

            if (!endFlag)
            {
                graph[index][1].first += waitTime[i-1];
            }
        }
/*
        if (visited[index])
        {
            continue;
        }
        else
        {
            visited[index] = true;
        }*/
        for (int j = 0; j < graph[index].size(); ++j)
        {
            int edge = graph[index][j].first;
            int target = graph[index][j].second;
            
            if ((!endFlag && j > 1) || (endFlag && j>0))
            {
                if (tunnelFlag)
                {
                    if (distT[target] > distT[index] + edge)
                    {
                        distT[target] = distT[index] + edge;
                        minheap.push(make_pair(distT[target], make_pair(target, true)));
                    }

                }
                else
                {
                    if (distT[target] > dist[index] + edge)
                    {
                        distT[target] = dist[index] + edge;
                        minheap.push(make_pair(dist[target], make_pair(target, true)));   

                    }
                }
            }
            else
            {
                if (tunnelFlag)
                {
                    if (dist[target] > distT[index] + edge)
                    {
                        dist[target] = distT[index] + edge;
                        minheap.push(make_pair(dist[target], make_pair(target, false)));                
                    }
                }
                else
                {
                    if (dist[target] > dist[index] + edge)
                    {
                        dist[target] = dist[index] + edge;
                        minheap.push(make_pair(dist[target], make_pair(target, false)));  
                    }
                }
            }
        }

        if (tunnelFlag == true)
        {
        
            graph[index][0].first -= waitTime[i-1];

            if (!endFlag)
            {
                graph[index][1].first -= waitTime[i-1];
            }
        }

    }

    return min(dist[destin], distT[destin]);
}


int main(int argc, char const *argv[])
{	
	freopen("B-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

    int testCaseCount;

    cin>>testCaseCount;


    for (int i = 0; i < testCaseCount; ++i)
    {
        int lineCount;
        cin>>lineCount;
    
        vector<vector<PAIRINT> > graph;

        vector<int> mapping(lineCount+1, 0);
        vector<int> waitTime(lineCount, 0);
        for (int j = 0; j < lineCount; ++j)
        {
            int travelTime;
            int stationCount;
            cin>>stationCount>>waitTime[j];
            mapping[j+1] = stationCount + mapping[j];
            vector<int> station;

            for (int k = 0; k < stationCount; ++k)
            {
                if (k!= 0)
                {
                    graph.push_back(vector<PAIRINT>(1,make_pair(travelTime, mapping[j] + k-1)));
                }
                else
                {
                    graph.push_back(vector<PAIRINT>(0));
                }
                if (k == stationCount-1)
                    break;
                cin>>travelTime;
                graph[graph.size()-1].push_back(make_pair(travelTime, mapping[j] + k+1));                
                
            }
        }

        int tunnelCount;
        cin>>tunnelCount;

        for (int j = 0; j < tunnelCount; ++j)
        {
            int l1, s1, l2, s2, walkTime;
            cin>>l1>>s1>>l2>>s2>>walkTime;

            int index1 = mapping[l1-1] + s1 - 1;
            int index2 = mapping[l2-1] + s2 - 1;
            graph[index1].push_back(make_pair(walkTime, index2));
            graph[index2].push_back(make_pair(walkTime, index1));
        }

        int queryCount;
        cin>>queryCount;

        cout<<"Case #"<<i+1<<": "<<endl;

        for (int j = 0; j < queryCount; ++j)
        {
            int s1, l1, s2, l2;
            cin>>l1>>s1>>l2>>s2;

            int source = mapping[l1-1] + s1-1;
            int destin = mapping[l2-1] + s2-1;

            int time = findShortestPath(source, destin, graph, mapping, waitTime);
            

            if (time == INF)
                cout<<"-1"<<endl;
            else
            {
                cout<<time<<endl;
            }
        }
    }



}