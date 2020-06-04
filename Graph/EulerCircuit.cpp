#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 1 << 20;

typedef pair<int,int>   ii;

vector<int> path;   //path contains the index of used edges in resulting order and the direction as the parity of the value
vector<int> g[N];
vector<ii>  E;

void addEdge(int u,int v)   {
    g[u].pb(sz(E)); E.pb(v,0);
    g[v].pb(sz(E)); E.pb(u,0);
}
void work(int S)    {
    if (g[S].empty())
        return;
    
    stack<int>  st;
    st.push(g[S].back() ^ 1);

    while (st.size())   {
        int i = st.top();
        int u = E[i].X;

        for(; g[u].size() && E[g[u].back()].Y ; g[u].pop_back());

        if (g[u].size())    {
            int j = g[u].back();
            st.push(j);
            E[j].Y = 1; j ^= 1;
            E[j].Y = 1; continue;
        }
        path.pb(i); st.pop();
    }
    path.pop_back();
}
int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
