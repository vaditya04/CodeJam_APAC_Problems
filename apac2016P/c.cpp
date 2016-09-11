/*input
2
2
Oksana Baiul
Michelle Kwan
3
Elvis Stojko
Evgeni Plushenko
Kristi Yamaguchi
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
    freopen("C-small-practice-2.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    // cout<<fixed<<setprecision(10);

    for (int i = 0; i < testCaseCount; ++i)
    {
        int n;
        cin>>n;
        // cout<<n<<" "<<endl;
        vector<string> cards;
        string card;
        getline(cin, card);    
        for (int j = 0; j < n; ++j)
        {
            getline(cin, card);
            cards.push_back(card);
        }

        int count = 0;
        for (int j = 1; j < n; ++j)
        {
                // cout<<cards[j]<<" "<<cards[j-1]<<endl;

            if (cards[j].compare(cards[j-1]) < 0)
            {
                // cout<<cards[j]<<" "<<cards[j-1]<<endl;
                count++;
                string temp = cards[j];
                int k = j-1;
                while (k >= 0)
                {
                    if (temp >= cards[k])
                    {
                        break;
                    }
                    cards[k+1] = cards[k];
                    k--;
                    // cout<<"STUCK"<<endl;
                }
                cards[k+1] = temp;
            }
        }

        for (int j = 0; j < n; ++j)
        {
            // cout<<j<<" "<<cards[j]<<endl;
        }

        cout<<"Case #"<<i+1<<": ";

        cout<<count;

        cout<<endl;
    }
}