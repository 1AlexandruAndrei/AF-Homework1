#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include <deque>
using namespace std;
ifstream f("padure.in");
ofstream g("padure.out");

const int nmaxi=1e3;
int a[nmaxi+1][nmaxi+1];
int d[nmaxi+1][nmaxi+1];
int dx[]= {1,-1,0,0};
int dy[]= {0,0,-1,1};

int main()
{


    int n,m,xs,ys,xf,yf,i,j;
    f>>n>>m>>xs>>ys>>xf>>yf;

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
            int ny=p.second+dy[i];///noile coordonate

            if (a[p.first][p.second]==a[nx][ny])///acelasi tip de copac cu vecinu
            {
                if (d[nx][ny]>d[p.first][p.second])///daca distanta  poate fi mai mica
                {
                    d[nx][ny]=d[p.first][p.second];
                    dq.push_front({nx,ny}); ///pun la inceput ca sa o explorez
                }
            }
            else
            {
                if (d[nx][ny]>d[p.first][p.second]+1)
                {
                    d[nx][ny]=d[p.first][p.second]+1;///schimba copacul
                    dq.push_back({nx, ny});///PB pt ca inainte explorez vecinii din aceeasi regiune si dupa ceilalti
                }
            }

        }
    }

    g<<d[xf][yf]<<endl;
    f.close();
    g.close();
    return 0;
}
