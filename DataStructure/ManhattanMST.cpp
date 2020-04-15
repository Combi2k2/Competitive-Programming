#include<bits/stdc++.h>

using namespace std;

#define int     long long
#define X       first
#define Y       second
#define ed      tuple<int,int,int>
#define mt      make_tuple

const int   inf = 1e18;
const int   N   = 1e5 + 1;

namespace   DSU {
    int p[N];
    int s[N];
    int init(int n) {
        iota(p,p + n,0);
        fill(s,s + n,1);
    }
    int lead(int x) {
        return p[x] == x ? x : p[x] = lead(p[x]);
    }
    int join(int x,int y)   {
        x = lead(x);
        y = lead(y);
        if (x == y) return  0;
        if (s[x] < s[y])
            swap(x,y);
        p[y] = x;
        s[x] += s[y];
        return  1;
    }
};

typedef pair<int,int>   ii;

struct  Poi {
    int x, y;
    int t, d;
    int idx;
    int nxt;
}   P[N];
bool compareX(Poi a,Poi b)  {   return  ii(a.x,a.y) < ii(b.x,b.y);  }
bool compareY(Poi a,Poi b)  {   return  ii(a.y,a.x) < ii(b.y,b.x);  }
bool compareSum(Poi a,Poi b)    {   return  ii(a.x + a.y,a.y) < ii(b.x + b.y,b.y);  }
bool compareDif(Poi a,Poi b)    {   return  ii(a.x - a.y,a.y) < ii(b.x - b.y,b.y);  }

int x[N], y[N];

void swp(int l,int r,int T) {
    if (P[l].y >= P[r].y)   {
        for(int i = l + 1 ; i <= r ; ++i)
            P[i].d   = P[i - 1].x + P[i - 1].y * (T + T - 1),
            P[i].nxt = P[i - 1].idx;
        return;
    }
    int k = (P[l].y + P[r].y) / 2;
    int m = l;
    for(; m <= r ; ++m) if (P[m].y > k) {
        swp(m,r,T); --m;
        swp(l,m,T); break;
    }
    for(int i = m ; i >= l ; --i)   P[i].t = T;
    for(int i = r ; i >  m ; --i)   P[i].t = 1 - T;

    if (T)  sort(P + l,P + 1 + r,compareDif);
    else    sort(P + l,P + 1 + r,compareSum);

    int cur = -inf;
    int idx = -1;

    for(int i = l ; i <= r ; ++i)   {
        if (P[i].d < cur && P[i].t == 0)
            P[i].d = cur,
            P[i].nxt = idx;
        if (cur < P[i].x + P[i].y * (T + T - 1) && P[i].t == 1)
            cur = P[i].x + P[i].y * (T + T - 1),
            idx = P[i].idx;
    }
}

signed main()   {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("Combi.inp","r",stdin);
    freopen("out1.out","w",stdout);

    int n;  cin >> n;

    for(int i = 1 ; i <= n ; ++i)   {
        cin >> x[i];    P[i].x = x[i];
        cin >> y[i];    P[i].y = y[i];
        P[i].idx = i;
    }

    priority_queue<ed>  pq;

    for(int t = 0 ; t < 4 ; ++t)    {
        for(int i = 1 ; i <= n ; ++i)   P[i].y *= -1,   swap(P[i].x,P[i].y);
        for(int k = 0 ; k <  2 ; ++k)   {
            for(int i = 1 ; i <= n ; ++i)   {
                P[i].d   = -inf;
                P[i].nxt = -1;
            }
            sort(P + 1,P + 1 + n,compareY); swp(1,n,k);

            for(int i = 1 ; i <= n ; ++i)   if (P[i].nxt > 0)   {
                int u = P[i].idx;
                int v = P[i].nxt;
                pq.push(mt(-abs(x[u] - x[v]) - abs(y[u] - y[v]),u,v));
            }
        }
    }

    int ans = 0;
    DSU::init(n);

    while (pq.size())   {
        int u, v, w;
        tie(w, u, v) = pq.top();

        if (DSU::join(u,v))
            ans -= w;

        pq.pop();
    }

    cout << ans << "\n";
}
