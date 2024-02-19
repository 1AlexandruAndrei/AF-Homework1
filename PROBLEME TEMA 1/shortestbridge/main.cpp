#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Solution
{
public:
    int shortestBridge(vector<vector<int>>& grid)
    {
        int n=grid.size();
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        findIsland(grid, visited);
        return bfs(grid, visited);
    }
    void findIsland(vector<vector<int>>& grid, vector<vector<bool>>& visited) ///dfs pe primul nod pe car eil gasesc ca sa vad il 1
    {
        int n = grid.size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 1 && !visited[i][j])
                {
                    dfs(grid, visited, i, j);
                    return;

                }
    }

    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y)
    {
        if (x<0 || x>=grid.size() || y < 0 || y >= grid[0].size() || visited[x][y] || grid[x][y] == 0)
            return;

        visited[x][y]=true; ///e bun
        dfs(grid, visited, x, y-1);
        dfs(grid, visited, x, y+1);
        dfs(grid, visited, x+1, y);
        dfs(grid, visited, x-1, y);
    }

    int bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited)
    {
        int n=grid.size();
        queue<pair<int, int>> coada;
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                if (visited[i][j])
                    coada.push({i,j});///iau coordonatele de la insula

        int directions[4][2]= {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
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
                    int newX=pr+directions[k][0];
                    int newY=dl+directions[k][1];

                    if (newX<n && newY<n && newX >= 0 && newY>=0)
                        if (!visited[newX][newY])
                        {
                            if (grid[newX][newY]==1)
                                return nrpasi;

                            coada.push({newX, newY});
                            visited[newX][newY]=true;///marchez ca vizitat
                        }

                }
            }
            nrpasi++;
        }

        return -1;
    }
};

int main()
{
    vector<vector<int>> grid = {{0,1,0}, {0,0,0}, {0,0,1}};
    Solution sol;
    cout <<sol.shortestBridge(grid);
    return 0;
}
