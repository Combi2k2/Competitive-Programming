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
    int cost;

    Edge(int _v,int _c,int _cost) : v(_v), c(_c), cost(_cost)   {}
};

vector<int>  g[N];
vector<Edge> E;

void addEdge(int u,int v,int c,int cost)    {
    g[u].pb(sz(E));     E.pb(v,c, cost);
    g[v].pb(sz(E));     E.pb(u,0,-cost);
}

int S, T;
int d[N];
int p[N];

bool inc()  {
    for(int i = 0 ; i <= T ; ++i)
        d[i] = inf,
        p[i] = -1;

    d[S] = 0;
    p[S] = inf;

    priority_queue<ii,vector<ii>,greater<ii> >  pq;

    pq.push(ii(0,S));

    while (pq.size())   {
        int du = pq.top().X;
        int u  = pq.top().Y;

        pq.pop();

        if (du != d[u])
            continue;

        for(int i : g[u])   {
            int v = E[i].v;
            int C = E[i].cost;

            if (d[v] > du + C && E[i].c > 0)    {
                d[v] = du + C;
                p[v] = i;
                pq.push(ii(d[v],v));
            }
        }
    }
    return  p[T] >= 0;
}
int MCMF()  {
    static int Flow = 0;
    static int Cost = 0;

    while (inc())   {
        int F = inf;
        for(int u = T ; u != S ;)   {
            int i = p[u];
            F = min(E[i].c,F);
            u = E[i ^ 1].v;
        }
        for(int u = T ; u != S ;)   {
            int i = p[u];
            E[i].c -= F;    i ^= 1;
            E[i].c += F;    u = E[i].v;
        }

        Flow += F;
        Cost += F * d[T];
    }
    return  Cost;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
