#include<bits/stdc++.h>
using namespace std;
#define pp pair<int,int>
class graph{
    int v;
    list<pp > *garray;
public:
    graph(int n){
     v = n;
     garray = new list<pp >[v+1];
    }
    void addEdge(int u, int v, int w)
    {
        garray[u].push_back(pp(v,w));
        garray[v].push_back(pp(u,w));
    }
    void print()
    {
        for(int i = 1;i<=v;i++)
        {
            cout<<i<<" ";
            for(list<pp >::iterator it = garray[i].begin();it!=garray[i].end();it++)
            {
                cout<<it->first<<" ";
            }
            cout<<endl;
        }
    }
    void prim(int src)
    {
        graph primTree(v);
        int* key = new int[v+1];
        int* pi = new int[v+1];
        bool* visited = new bool[v+1];
        for(int i = 1;i<=v;i++)
        {
            key[i] = INT_MAX;
            pi[i] = 0;
            visited[i] = false;
        }
        key[src] = 0;
        set<pp > Q;
        for(int i = 1;i<=v;i++)
        {
            Q.insert(pp(key[i],i));
        }
        while(Q.size())
        {
            set<pp >::iterator U = Q.begin();
            int u = U->second;
            for(list<pp >::iterator it = garray[u].begin();it!=garray[u].end();it++)
            {
                int v = it->first;
                int weight = it->second;
                if(Q.find(pp(key[v],v)) != Q.end() && weight < key[v])
                {
                    pi[v] = u;
                    Q.erase(Q.find(pp(key[v],v)));
                    key[v] = weight;
                    Q.insert(pp(key[v],v));
                }
            }
            Q.erase(Q.find(pp(key[u],u)));
        }
        for(int i = 1;i<=v;i++)
        {
            primTree.addEdge(pi[i],i,key[i]);
        }
        primTree.print();
    }
};
int main()
{
    graph G(9);
    G.addEdge(1,2,4); G.addEdge(1,8,8);
    G.addEdge(2,3,8); G.addEdge(2,8,11);
    G.addEdge(3,9,2); G.addEdge(3,6,4); G.addEdge(3,4,7);
    G.addEdge(4,5,9); G.addEdge(4,6,14);
    G.addEdge(5,6,10);
    G.addEdge(6,7,2);
    G.addEdge(7,8,1); G.addEdge(7,9,6);
    G.addEdge(8,9,7);
    G.print();
    cout<<"MST using Prim is "<<endl;
    G.prim(1);
    return 0;
}
