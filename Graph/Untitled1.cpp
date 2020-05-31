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

vector<int> g[N];
vector<int> a[N];

int dfn[N], low[N];
int tot = 0;
int ver = 0;

stack<int>  st;

void addEdge(int u,int v)   {
    a[u].pb(v);
    a[v].pb(u);
}
void rebuild(int u,int p)   {
    tot++;
    dfn[u] = tot;
    low[u] = tot;   st.push(u);

    for(int v : g[u])   if (v != p) {
        if (dfn[v]) {
            low[u] = min(low[u],dfn[v]);
            continue;
        }
        rebuild(v,u);
        low[u] = min(low[u],low[v]);
        
        if (low[v] >= dfn[u])   {
            int z = 0;
            addEdge(u,++ver);

            while (z != v)  {
                z = st.top();   st.pop();
                addEdge(z,ver);
            }
        }
    }
}
int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;  cin >> n;
    int m;  cin >> m;

    for(int i = 0 ; i < m ; ++i)    {
        int x;  cin >> x;
        int y;  cin >> y;

        g[x].pb(y);
        g[y].pb(x);
    }
    rebuild(1,0);
}