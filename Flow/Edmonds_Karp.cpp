#include<bits/stdc++.h>

using namespace std;

const int   N   = 2e3 + 1;

#define sz(x)   x.size()
#define all(x)  x.begin(),x.end()
#define pb      push_back

namespace Edmonds_Karp  {
    int n, S, T, p[N];

    #define inf 1e9 + 7

    struct Edge {
        int u, v, c, f;
        Edge(int u,int v,int c) : u(u), v(v), c(c), f(0)    {}
    };

    vector<int>  g[N];
    vector<Edge> E;

    void init(int _n,int _S,int _T) {
        n = _n;
        S = _S;
        T = _T;
        for(int i = 0 ; i <= n ; ++i)
            g[i].clear();
        E.clear();
    }

    void addEdge(int u,int v,int c) {
        g[u].pb(sz(E)); E.pb({u,v,c});
        g[v].pb(sz(E)); E.pb({v,u,0});
    }

    bool bfs()  {
        queue<int>  q;
        for(int i = 0 ; i <= n ; ++i)
            p[i] = -1;
        p[S] = inf; q.push(S);
        while(q.size()) {
            int u = q.front();  q.pop();
            for(int i : g[u])   {
                int v = E[i].v;
                if (p[v] < 0 && E[i].c > E[i].f)    {
                    p[v] = i;
                    q.push(v);
                }
            }
        }
        return p[T] >= 0;
    }

    int trace() {
        int res = inf, u = T;
        while(u != S)   {
            int i = p[u];   u = E[i].u;
            res = min(res,E[i].c - E[i].f);
        }
        u = T;
        while(u != S)   {
            int i = p[u];   u = E[i].u;
            E[i].f += res;  E[i ^ 1].f -= res;
        }
        return res;
    }

    int calc()  {
        int ans = 0;
        while(bfs())
            ans += trace();
        return ans;
    }
};

using Edmonds_Karp::init;
using Edmonds_Karp::addEdge;
using Edmonds_Karp::calc;
using Edmonds_Karp::E;

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
