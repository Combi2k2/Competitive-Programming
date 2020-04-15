#include<bits/stdc++.h>

using namespace std;

#define pb  push_back

const int   N   = 1e5 + 1;

typedef vector<int> vi;
typedef vector<vi>  vii;

int tot = 0;

struct Edge {
	int v;
	int nxt;
	Edge(int v = 0,int nxt = 0) : v(v), nxt(nxt)    {}
}   E[N << 2];
int t[N << 2];
int h[N], d[N];

void addEdge(int u,int v)   {
	E[tot] = Edge(v,h[u]);  h[u] = tot++; d[u]++;
	E[tot] = Edge(u,h[v]);  h[v] = tot++; d[v]++;
}
vii res;
void work(int S)    {
	if (h[S] < 0)   return;
	vector<int> path;
	stack<int>  st; st.push(h[S] ^ 1);
	while (st.size())   {
		int i = st.top();
		int u = E[i].v;
		for(; h[u] >= 0 && t[h[u]] ; h[u] = E[h[u]].nxt);
		if (h[u] >= 0)  {
			st.push(h[u]);
			t[h[u]] = 1;    h[u] ^= 1;
			t[h[u]] = 1;    h[u] ^= 1;
			continue;
		}
		path.pb(st.top());  st.pop();
	}
	for(int i : path)   cout << E[i].v << " ";
}

int main()  {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, m;   cin >> n >> m;
	
	memset(h,-1,sizeof h);
	
	while (m--) {
		int x, y;
		cin >> x >> y;
		addEdge(x,y);
	}
	
	work(1);
}
