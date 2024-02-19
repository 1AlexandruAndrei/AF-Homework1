#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<int> result;
        vector<int> intra(numCourses,0);
        unordered_map<int,vector<int>> graf;

        int i;
        for (i=0; i<prerequisites.size(); i++)
        {
            int course=prerequisites[i][0];
            int necesar=prerequisites[i][1];
            graf[necesar].push_back(course);
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
                    int vecin = graf[course][i];
                    intra[vecin]--;///scad gradful intern al vecinilor, dar nu il elimin din reprezentare
                    if (intra[vecin]==0)
                        q.push(vecin);///adaug in coada vecinii al caror grad intern devine 0
                }

            }
        }

        if (result.size()!=numCourses)
            return {}; ///ciclu

        for (i=0; i<numCourses; i++)
            if (intra[i]>0)
                return {};

        return result;
    }
};

int main()
{
    Solution sol;
    int numCourses=4;
    int i;
    vector<vector<int>> prerequisites = {{1,0}, {2, 0}, {3,1}, {3,2}};

    vector<int> rez = sol.findOrder(numCourses, prerequisites);
    for (i=0; i<rez.size(); i++)
        cout<<rez[i] << " ";



    return 0;
}
