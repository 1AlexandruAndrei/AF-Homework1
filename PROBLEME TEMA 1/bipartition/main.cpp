#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {

        vector<vector<int>> graf(n+1);
        vector<int> parte(n+1,-1);

        int i;
        for(i=0; i<dislikes.size(); i++) ///parcurg lista de muchii din dislike si formez graful
        {
            int x=dislikes[i][0];
            int y=dislikes[i][1];
            graf[x].push_back(y);
            graf[y].push_back(x);
        }

        for(i=1; i<=n; i++)
        {
            if(parte[i]==-1 && dfs(i,0,graf,parte)==0)///daca n am reusit sa il bagam in grup
                return false;
        }
        return true;
    }

    bool dfs(int nod, int gr, vector<vector<int>>& graf, vector<int>& parte)
    {
        int i;
        if(parte[nod]!=-1)///daca face parte dintr un grup deja
        {
            if (parte[nod]==gr)
                return true;

            return false;///daca i am dat alt grup
        }

        parte[nod]=gr;
        for(i=0;i<graf[nod].size();i++)
        {
            int vecin=graf[nod][i];
            if(dfs(vecin, 1-gr, graf, parte)==0)///1-gr pentru a alterna grupurile intre vecini
                return false;
        }
        return true;
    }



};

int main()
{
    Solution sol;
    int n1=3;
    vector<vector<int>> vec= {{1, 2}, {1, 3}, {2,3}};
    bool result1 = sol.possibleBipartition(n1, vec);
    if (result1==0)
        cout<<"false";
    else
        cout<<"true";

    return 0;
}
