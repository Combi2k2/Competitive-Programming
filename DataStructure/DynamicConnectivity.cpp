//Problem: 100551A
//This is just basic implementation of this type

#include<bits/stdc++.h>

using namespace std;

#define pb      push_back
#define X       first
#define Y       second
#define lch     i << 1
#define rch     i << 1 | 1

const int   N   = 3e5 + 1;

typedef pair<int,int>   ii;

namespace   DCP {   //Dynamic Connectivity Problem
    struct  PSU {   //Persistent DSU
        int u, hu;
        int v, hv;
    };
    struct  Que {
        int u, v;
        int United;
        Que(int _u,int _v) : u(_u), v(_v), United(0) {}
    };
    int p[N], h[N];
    int cntComp;
    stack<PSU> ops;

    int init(int n) {
        iota(p + 1,p + 1 + n,1);
        cntComp = n;
    }
    int lead(int x) {
        for(; x != p[x] ; x = p[x]);
        return  x;
    }
    int join(int x,int y)   {
        x = lead(x);
        y = lead(y);
        if (x == y)
            return  0;
        if (h[x] < h[y])
            swap(x,y);
        ops.push({x,h[x],y,h[y]});
        cntComp--;
        p[y] = x;
        if (h[x] == h[y])
            h[x]++;
        return  1;
    }
    void rollback() {
        if (ops.empty()) return;
        h[ops.top().u] = ops.top().hu;
        p[ops.top().v] = ops.top().v;
        cntComp++;
        ops.pop();
    }

    vector<Que> Q[N << 2];
    vector<int> ans;

    void add(int i,int l,int r,int L,int R,Que x)   {
        if (l > R)  return;
        if (L > r)  return;
        if (L <= l && r <= R)   {
            Q[i].pb(x);
            return;
        }
        int m = (l + r) / 2;
        add(lch,l,m,L,R,x); ++m;
        add(rch,m,r,L,R,x);
    }
    void cal(int i,int l,int r) {
        for(Que &t : Q[i])
            t.United = join(t.u,t.v);
        if (l == r) ans.pb(cntComp);
        else    {
            int m = (l + r) / 2;
            cal(lch,l,m);   ++m;
            cal(rch,m,r);
        }

        reverse(Q[i].begin(),Q[i].end());
        for(Que &t : Q[i])  if (t.United)
            rollback();
    }
};
using DCP::ans;
using DCP::add;

bool ask[N];

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("connect.in","r",stdin);
    freopen("connect.out","w",stdout);

    int n;  cin >> n;
    int q;  cin >> q;

    if (q == 0) return  0;

    map<ii,int> Open;

    for(int i = 1 ; i <= q ; ++i)   {
        char c; cin >> c;
        if (c == '?')   {
            ask[i] = 1;
            continue;
        }
        ii  e;  cin >> e.X >> e.Y;

        if (e.X > e.Y)
            swap(e.X,e.Y);

        if (c == '+')   Open[e] = i;
        if (c == '-')   {
            add(1,1,q,Open[e],i,DCP::Que(e.X,e.Y));
            Open.erase(e);
        }
    }
    for(auto it : Open) {
        int x = it.X.X;
        int y = it.X.Y;
        int l = it.Y;
        add(1,1,q,l,q,DCP::Que(x,y));
    }

    DCP::init(n);
    DCP::cal(1,1,q);

    for(int i = 1 ; i <= q ; ++i)   if (ask[i])
        cout << ans[i - 1] << "\n";
}
