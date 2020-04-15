#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 2e5 + 5;

typedef pair<int,int>   ii;

struct Edge {
    int v, c;
    Edge(int _v,int _c) : v(_v), c(_c)  {}
};

vector<Edge> E;
vector<int>  g[N];

int addEdge(int u,int v,int c)  {
    g[u].pb(sz(E)); E.pb(v,c);
    g[v].pb(sz(E)); E.pb(u,0);

    return  sz(E) - 1;
}

int S, T;
int d[N];
int p[N];

bool bfs()  {
    for(int i = 0 ; i <= T ; ++i)
        d[i] = -1,
        p[i] = 0;

    queue<int>  q;
    q.push(S);  d[S] = 0;

    while (q.size())    {
        int u = q.front();  q.pop();
        for(int i : g[u])   {
            int v = E[i].v;
            if (E[i].c == 0)    continue;
            if (d[v] < 0)   {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    return  d[T] >= 0;
}

int dfs(int u,int F)    {
    if (u == T || F == 0)   return  F;
    for(int &i = p[u] ; i < sz(g[u]) ; ++i)  {
        int j = g[u][i];
        int v = E[j].v;
        if (E[j].c == 0 || d[v] != d[u] + 1)
            continue;
        int res = dfs(v,min(E[j].c,F));
        if (res)    {
            E[j].c -= res;  j ^= 1;
            E[j].c += res;  return  res;
        }
    }
    return  0;
}

int MaxFlow()   {
    while (bfs())
    while (dfs(S,N));

    int ans = 0;

    for(int i : g[T])
        ans += E[i].c;

    return  ans;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
