#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Solution
{
public:
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
            parent[x]=y;///fac radacinile identice ca sa fie in acelasi set
        }

        for(i=0; i<diferite.size(); i++)
        {
            int pos=diferite[i];
            char a=equations[pos][0];
            char b=equations[pos][3];
            if (getParent(a,parent) == getParent(b, parent))
                return false;///daca sunt in acelasi disjoint set inseamna ca nu pot fii ecuatii egale deci fals

        }
        return true;
    }

    char getParent(char x, map<char, char> top)
    {
        if(x==top[x])
            return x;
        top[x]=getParent(top[x],top);
        return top[x];
    }


};

int main()
{
    vector<string> v1={"a==b", "b==a"};
    Solution sol;
    if (sol.equationsPossible(v1))
        cout<<"true";
    else
        cout<<"false";
    return 0;
}
