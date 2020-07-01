#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 5e3 + 5;

struct Edge {
    int u, v;
    int cost;

    Edge(int _u,int _v,int _C) : u(_u), v(_v), cost(_C) {}
};
vector<Edge> E;

int in[N], fa[N];
int id[N], vv[N];

int Directed_MST(int R,int n)   {
    int ans = 0;

    while (1)   {
        fill(in + 1,in + 1 + n,2e9);
        fill(fa + 1,fa + 1 + n,2e9);

        for(Edge e : E)
            if (in[e.v] > e.cost && e.u != e.v) {
                in[e.v] = e.cost;
                fa[e.v] = e.u;
            }
        for(int i = 1 ; i <= n ; ++i)   {
            if (i == R) continue;
            if (in[i] == 2e9)
                return  -1;
        }
        in[R] = 0;
        ans += accumulate(in + 1,in + 1 + n,0);

        fill(id + 1,id + 1 + n,0);
        fill(vv + 1,vv + 1 + n,0);

        int node = 0;

        for(int i = 1 ; i <= n ; ++i)   {
            int x = i;
            while (vv[x] != i && !id[x] && (x != R))    {
                vv[x] = i;
                x = fa[x];
            }
            if (x == R) continue;
            if (id[x])  continue;

            id[x] = ++node;

            for(int u = fa[x] ; u != x ; u = fa[u])
                id[u] = node;
        }
        if(!node)   break;

        for(int i = 1 ; i <= n ; ++i)
            if (id[i] == 0)
                id[i] = ++node;
        
        for(Edge&e : E) {
            int u = e.u;    e.u = id[u];
            int v = e.v;    e.v = id[v];

            if (u != v)
                e.cost -= in[v];
        }
        n = node;
        R = id[R];
    }
    return  ans;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n;  cin >> n;
    int m;  cin >> m;
    
    for(int i = 1 ; i <= m ; ++i)   {
        int x;  cin >> x;
        int y;  cin >> y;
        int w;  cin >> w;
        
        E.pb(x,y,w);
    }
    for(int i = 1 ; i <= n ; ++i)
        E.pb(n + 1,i,1e9);
    
    cout << Directed_MST(n + 1,n + 1) - 1e9 << endl;
}
