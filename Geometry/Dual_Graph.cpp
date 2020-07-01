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

typedef pair<int,int>   Poi;

Poi operator + (const Poi&a,const Poi&b)    {   return  Poi(a.X + b.X,a.Y + b.Y);   }
Poi operator - (const Poi&a,const Poi&b)    {   return  Poi(a.X - b.X,a.Y - b.Y);   }

Poi P[N];
int n, m;
int tot = 0;

namespace Geometry  {
    struct Data {
        Data *another;
        int to;
        int cost;
        int face;
        ld  alpha;
        Data(int v,int c,ld  A) : another(0), to(v), cost(c), face(0), alpha(A) {}
    };
    bool cmp(Data *a,Data *b)   {
        return  a -> alpha < b -> alpha;
    }
    vector<Data*>   g[N];

    void add(int x,int y,int C1,int C2) {
        Poi E = P[y] - P[x];

        Data *node1 = new Data(y,C1,atan2( E.Y, E.X));
        Data *node2 = new Data(x,C2,atan2(-E.Y,-E.X));

        node1 -> another = node2;
        node2 -> another = node1;

        g[x].pb(node1);
        g[y].pb(node2);
    }
    void dfs(Data* e,int S,int F)   {
        int  u  = e -> to;  e -> face = F;  if (u == S) return;
        auto it = upper_bound(all(g[u]),e -> another,cmp);

        if (it == g[u].end())
            it  = g[u].begin();

        dfs(*it,S,F);
    }
    void build()    {
        for(int i = 1 ; i <= n ; ++i)   sort(all(g[i]),cmp);
        for(int i = 1 ; i <= n ; ++i)
        for(Data *e : g[i]) if(!e -> face)
            dfs(e,i,++tot);

        for(int i = 1 ; i <= n ; ++i)
        for(Data *e : g[i]) if (e -> cost)
            E.pb(e -> another -> face,e -> face,e -> cost);
    }
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
        cin >> P[i].X,
        cin >> P[i].Y;

    for(int i = 1 ; i <= m ; ++i)   {
        int x,  y;  cin >> x  >> y;
        int V1, V2; cin >> V1 >> V2;

        Geometry::add(x,y,V1,V2);
    }
    Geometry::build();
}
