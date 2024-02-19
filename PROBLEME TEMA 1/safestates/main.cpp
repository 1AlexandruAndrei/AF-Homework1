#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {
        int n=graph.size();

        vector<int> safe;
        vector<int> check(n,0);
        vector<int> muchieviz(n, 0);
        vector<int> nodviz(n, 0);

        int i;
        for(i=0; i<n; i++)
            if(nodviz[i]==0)
                dfs(i,graph,nodviz,check, muchieviz);///dfs din nod nevizitat
        for(i=0;i<n;i++)
            if(check[i]==1)
                safe.push_back(i);///e bun

        return safe;
    }

    bool dfs(int nod, vector<vector<int>>& graph, vector<int>& nodviz, vector<int>& check, vector<int>& muchieviz)
    {
        nodviz[nod]=1;
        muchieviz[nod]=1;
        check[nod]=0;
        for(int j=0;j<graph[nod].size();j++)
        {
            int vecin=graph[nod][j];
            if(nodviz[vecin]==0)///daca vecinul nu a fost vizitat
            {
                if(dfs(vecin, graph, nodviz, check, muchieviz)!=0)
                {
                    check[nod]=0;///nu e bun
                    return true;
                }
            }
            else if(muchieviz[vecin]==1)///avem ciclu
            {
                check[nod]=0;
                return true;
            }
        }
        check[nod]=1;///e bun
        muchieviz[nod]=0;
        return false;
    }

};

int main()
{
    vector<vector<int>> graph={{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4},{}};
    Solution sol;
    vector<int> safe=sol.eventualSafeNodes(graph);
    for (int i=0;i<safe.size();i++)
        cout<<safe[i]<<" ";
    return 0;
}
