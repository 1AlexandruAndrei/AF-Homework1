/// ALEXANDRU ANDREI - GRUPA 232
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <fstream>
using namespace std;

ifstream f("padure.in");
ofstream g("padure.out");
const int nmaxi=1e3;///dim maxima a matricei
int a[nmaxi+1][nmaxi+1];
int d[nmaxi+1][nmaxi+1];
int dx[]= {1,-1,0,0};
int dy[]= {0,0,-1,1};


class Graf
{
private:
    int n;
    vector<vector<int>> graf;
    vector<vector<int>> graf2;
    vector<vector<int>> muchie;
    vector<int> parte;
    vector<char> ec;

    bool dfsbasic(int nod, int gr)
    {
        if (parte[nod]!=-1)
        {
            if (parte[nod]==gr)
                return true;
            else
                return false;
        }

        parte[nod]=gr;
        for (int i = 0; i < graf[nod].size(); i++)
        {
            int vecin=graf[nod][i];
            if (dfsbasic(vecin, 1-gr)==0)
                return false;
        }
        return true;
    }




public:
    ///constructori
    Graf(int n, vector<vector<int>>& muchie)
    {
        this->n=n;
        this->muchie=muchie;

    }

    Graf(vector<string>& ecuatii)
    {
        this->ec=ec;
    }

    Graf(vector<vector<int>>& graf2)
    {
        this->graf2=graf2;
    }


    Graf(const Graf& obj)
    {

        this->n=obj.n;
        this->graf=obj.graf;
        this->parte=obj.parte;
    }

    Graf& operator =(const Graf& obj)
    {
        this->n=obj.n;
        this->graf=obj.graf;
        this->parte=obj.parte;
    }


    ///----------------------------------------------------------------------------------------------------------------
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



    ///----------------------------------------------------------------------------------------------------------------


    vector<int> topologicalsort(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<int> result;
        vector<int> intra(numCourses,0);
        unordered_map<int,vector<int>> graf;

        int i;
        for (i=0; i<prerequisites.size(); i++)
        {
            int course=prerequisites[i][0];
            int prerequisite=prerequisites[i][1];
            graf[prerequisite].push_back(course);
            intra[course]++;
        }

        queue<int> q;

        for (i=0; i<numCourses; i++)
            if (intra[i]==0)
                q.push(i);///ce nu are precendenti

        ///sortarea topologica
        while (q.size()>0)
        {
            int course=q.front();
            q.pop();
            result.push_back(course);
            if (graf.find(course)!=graf.end())
            {
                for (i=0; i<graf[course].size(); i++)
                {
                    int vecin=graf[course][i];
                    intra[vecin]--;///scad gradful intern al vecinilor, dar nu il elimin din reprezentare
                    if (intra[vecin]==0)
                        q.push(vecin);///adaug in coada vecinii al caror grad intern devine 0
                }

            }
        }

        if (result.size()!=numCourses)
            return {};

        for (i=0; i<numCourses; i++)
            if (intra[i]>0)
                return {};

        return result;
    }


    ///----------------------------------------------------------------------------------------------------------------


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


        vector<int> nivel(n,-1);
        vector<int> niv_min(n,-1);
        vector<int> viz(n, 0);
        vector<vector<int>> result;

        for (int i=0; i<n; i++)
            if (viz[i]==0)
                df(i, -1, 0, vecin, nivel, niv_min, viz, result);

        return result;
    }
    void df(int u, int parent, int nivelcurent, vector<vector<int>>& vecin, vector<int>& nivel, vector<int>& niv_min, vector<int>& viz, vector<vector<int>>& result)
    {
        viz[u]=1;
        nivel[u]=nivelcurent;
        niv_min[u]=nivelcurent;

        for (int j=0; j<vecin[u].size(); j++)
        {
            int v=vecin[u][j];
            if (v==parent)
                continue;

            if (viz[v]==0)/// ij muchie de avansare
            {
                df(v, u, nivelcurent + 1, vecin, nivel, niv_min, viz, result);
                /// actualizare niv_min[u] cu formula B
                niv_min[u]=min(niv_min[u], niv_min[v]);
                /// testez ij daca este muchie critica cu formula 1
                if (niv_min[v]>nivel[u])
                    result.push_back({u, v});
            }
            else
                niv_min[u] = min(niv_min[u], nivel[v]); /// inseamna ca e muchie de intoarcere

        }

    }


    ///----------------------------------------------------------------------------------------------------------------

    bool equationsPossible(vector<string>& equations)
    {
        vector <int> egale;
        vector <int> diferite;
        map <char,char> parent;
        int n=equations.size();
        int i;
        for(i=0;i<n;i++)
        {
            parent[equations[i][0]]=equations[i][0];
            parent[equations[i][3]]=equations[i][3];

            if(equations[i][1]=='=')
                egale.push_back(i);
            else if(equations[i][1]=='!')
                diferite.push_back(i);
        }
        for(i=0; i<egale.size(); i++)
        {
            int pos=egale[i];
            char a=equations[pos][0];
            char b=equations[pos][3];

            char x=getParent(a, parent);
            char y=getParent(b, parent);
            parent[x]=y;///sa fie in acelasi set
        }

        for(i=0; i<diferite.size(); i++)
        {
            int pos=diferite[i];
            char a=equations[pos][0];
            char b=equations[pos][3];
            if (getParent(a,parent) == getParent(b, parent))
                return false;///daca sunt in acelasi disjoint set inseamna ca nu pot fi ecuatii egale deci fals

        }
        return true;
    }

    ///find ul
    char getParent(char x, map<char, char> top)
    {
        if(x==top[x])
            return x;
        top[x]=getParent(top[x],top);
        return top[x];
    }

    ///----------------------------------------------------------------------------------------------------------------


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

    ///----------------------------------------------------------------------------------------------------------------

    int shortestBridge(vector<vector<int>>& grid)
    {
        int n=grid.size();
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        insula1(grid, visited);
        return bfsinsula(grid, visited);
    }
    void insula1(vector<vector<int>>& grid, vector<vector<bool>>& visited)
    {
        int n=grid.size();
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                if (grid[i][j]==1 && visited[i][j]==0)
                {
                    dfsinsula(grid, visited,i,j);
                    return;
                }


    }

    void dfsinsula(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y)
    {
        if (x>=grid.size() || y>=grid[0].size() || visited[x][y] || grid[x][y] == 0 || y<0 || x<0) ///NU e insula
            return;

        visited[x][y]=true; ///daca nu e in afara sau vizitat
        dfsinsula(grid, visited, x, y-1);
        dfsinsula(grid, visited, x, y+1);
        dfsinsula(grid, visited, x+1, y);
        dfsinsula(grid, visited, x-1, y);
    }

    int bfsinsula(vector<vector<int>>& grid, vector<vector<bool>>& visited)
    {
        int n=grid.size();
        queue<pair<int, int>> coada;
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                if (visited[i][j])
                    coada.push({i,j});

        int parcurgere[4][2]= {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int nrpasi=0;
        while (coada.size()>0)
        {
            int kk=coada.size();
            for (int i=0; i<kk; i++)
            {
                int pr=coada.front().first;
                int dl=coada.front().second; ///coordonatele unui nod caruia ii dam deque
                coada.pop();

                for (int k=0; k<4; k++)
                {
                    int newX=pr+parcurgere[k][0];
                    int newY=dl+parcurgere[k][1];

                    if (newX<n && newY<n && newX >= 0 && newY>=0)
                        if (visited[newX][newY]==0)
                        {
                            if (grid[newX][newY]==1)///am gst
                                return nrpasi;

                            coada.push({newX, newY});
                            visited[newX][newY]=true;
                        }

                }
            }
            nrpasi++;
        }

        return -1;
    }

};

class Solution
{
public:

    /// POSSIBLE BIPARTITION
    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {
        Graf graf(n, dislikes);
        return graf.possibleBipartition(n,dislikes);
    }

    ///COURSE SCHEDULE
    vector<int> topologicalsortvec(int numCourses, vector<vector<int>>& prerequisites)
    {
        Graf graf(numCourses, prerequisites);
        vector<int> res=graf.topologicalsort(numCourses, prerequisites);
        return res;
    }

    ///CRITICAL CONNECTIONS
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections)
    {
        Graf graf(n, connections);
        return graf.criticalConnections(n, connections);
    }

    ///SAFE STATES
    vector<int> eventualSafeNodesvec(vector<vector<int>>& graph2) {
        Graf graf(graph2);
        return graf.eventualSafeNodes(graph2);
    }

    ///EQUAL EQUATIONS
    bool equationsPossible(vector<string>& equations)
    {
        Graf graf(equations);
        return graf.equationsPossible(equations);
    }

    ///SHORTEST BRIDGE
    int shortestbridge(vector<vector<int>>& grid)
    {
        Graf graf(grid);
        return graf.shortestBridge(grid);
    }

};

int main()
{
    Solution sol;

    /// POSSIBLE BIPARTITION
    int n1=4;
    vector<vector<int>> dislikes= {{1,2},{1,3},{2,4}};
    bool result1 = sol.possibleBipartition(n1, dislikes);
    if (result1==0)
        cout<<"false"<<endl;
    else
        cout<<"true"<<endl;

    /// COURSE SCHEDULE
    int numCourses=4;
    int i;
    vector<vector<int>> prerequisites={{1,0},{2,0},{3,1},{3,2}};
    vector<int> courseOrder=sol.topologicalsortvec(numCourses, prerequisites);
    for (i=0; i<courseOrder.size(); i++)
        cout<<courseOrder[i]<<" ";
    cout<<endl;

    ///CRITICAL CONNECTIONS
    int n=4;
    vector<vector<int>> connections= {{0,1},{1,2}, {2, 0},{1,3}};
    vector<vector<int>> critical=sol.criticalConnections(n,connections);
    for (i=0; i<critical.size(); i++)
        cout<<critical[i][0]<<" "<<critical[i][1];
    cout<<endl;

    ///EQUAL EQUATIONS
    vector<string> v1= {"a==b", "b!=a"};
    bool posibil=sol.equationsPossible(v1);
    if(posibil==0)
        cout<<"false";
    else
        cout<<"true";
    cout<<endl;

    ///SAFE STATES
    vector<vector<int>> graph1={{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    vector<int> safe=sol.eventualSafeNodesvec(graph1);
    for (i=0; i<safe.size(); i++)
        cout<<safe[i]<<" ";
    cout<<endl;

    ///SHORTEST BRIDGE
    vector<vector<int>> grid={{0,1,0}, {0,0,0}, {0,0,1}};
    int drum=sol.shortestbridge(grid);
        cout<<drum;
    cout<<endl;



    /// INFO ARENA - PADURE

    ///int n,m,xs,ys,xf,yf,i,j;
    /*f>>n>>m>>xs>>ys>>xf>>yf;

    for (i=1; i<=n; i++)
        for (j=1; j<=m; j++)
        {
            f>>a[i][j];
            d[i][j]=1e3;
        }

    deque<pair<int,int>> dq;
    dq.push_back({xs,ys});
    d[xs][ys]=0;

    while(dq.size()>0)
    {
        pair<int,int> p=dq.front();
        dq.pop_front();
        for (i=0; i<4; i++)
        {
            int nx=p.first+dx[i];
            int ny=p.second+dy[i];

            if (a[p.first][p.second]==a[nx][ny])
            {
                if (d[nx][ny]>d[p.first][p.second])
                {
                    d[nx][ny]=d[p.first][p.second];///daca poater sa mearga pe directia aia si disstanta e mai mica, actualizez
                    dq.push_front({nx,ny}); ///si o pun in coada ca sa o explorez ulterior
                }
            }
            else
            {
                if (d[nx][ny]>d[p.first][p.second]+1)
                {
                    d[nx][ny]=d[p.first][p.second]+1;///schimba copacul
                    dq.push_back({nx, ny});
                }
            }

        }
    }

    g<<d[xf][yf]<<endl;
    f.close();
    g.close();
    */
    return 0;
}
