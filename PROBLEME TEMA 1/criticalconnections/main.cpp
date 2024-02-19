#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections)
    {
        vector<vector<int>> vecin(n);
        for (int i=0; i<connections.size(); i++)
        {
            int u=connections[i][0];
            int v=connections[i][1];
            vecin[u].push_back(v);
            vecin[v].push_back(u);
        }


        vector<int> nivel(n, -1);///nivelul la fiecare nod
        vector<int> niv_min(n, -1);///nivelul minim la care se inchide un ciclu elementar care contine varful i
        vector<int> viz(n, 0);
        vector<vector<int>> result;

        for (int i=0; i<n; i++)
            if (viz[i]==0)
                df(i, -1, 0, vecin, nivel, niv_min, viz, result);

        return result;
    }
    void df(int u, int parent, int depth, const vector<vector<int>>& vecin,
             vector<int>& nivel, vector<int>& niv_min, vector<int>& viz, vector<vector<int>>& result)
    {
        viz[u]=1;
        nivel[u]=depth;
        niv_min[u]=depth;

        for (int j=0; j<vecin[u].size(); j++)
        {
            int v=vecin[u][j];
            if (v == parent)
                continue;

            if (viz[v]==0)
            {
                df(v, u, depth + 1, vecin, nivel, niv_min, viz, result);

                /// actualizare niv_min[u] cu formula B
                niv_min[u] = min(niv_min[u], niv_min[v]);

                /// testez ij daca este muchie critica cu formula
                if (niv_min[v] > nivel[u])
                    result.push_back({u, v});///muchie critica
            }
            else
                niv_min[u]=min(niv_min[u], nivel[v]); /// inseamna ca e muchie de intoarcere

        }

    }
};

int main()
{
    Solution sol;
    int n=4,i;
    vector<vector<int>> graf= {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    vector<vector<int>> critical=sol.criticalConnections(n,graf);
    for (i=0; i<critical.size(); i++)
        cout<<critical[i][0]<<" "<<critical[i][1]<<endl;

    return 0;
}

