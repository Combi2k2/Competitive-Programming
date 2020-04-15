/**
*   Original problem:
*   https://vn.spoj.com/problems/VOMARIO/
**/

#include<bits/stdc++.h>

using namespace std;

#define ll  long long

#define lch     i << 1
#define rch     i << 1 | 1

const int   N   = 1e5 + 1;
const ll    inf = 1e18;

struct Line {
    ll  a, b;
    ll  get(int x)  {
        return  a * x + b;
    }
    Line(ll _a = 0,ll _b = 0) : a(_a), b(_b)    {}
};
struct LiChao_Tree  {
    #define get(x)  get(comp[x])

    vector<int>  comp;
    vector<Line> tree;

    LiChao_Tree() : comp({}), tree({})  {}

    void initialize()   {
        sort(comp.begin(),comp.end());
        comp.erase(unique(comp.begin(),comp.end()),comp.end());

        int n = comp.size();
        tree.resize(n << 2);

        for(Line &d : tree)
            d.a = 0,
            d.b = -inf;

        tree[1].b = 0;
    }
    void upd(int i,int l,int r,int L,int R,Line d)    {
        if (l > R)  return;
        if (L > r)  return;

        int m = (l + r) / 2;

        if (L <= l && r <= R)   {
            if (tree[i].get(l) >= d.get(l) && tree[i].get(r) >= d.get(r))
                return;
            if (tree[i].get(l) <= d.get(l) && tree[i].get(r) <= d.get(r))   {
                tree[i] = d;
                return;
            }
            if (tree[i].get(l) >= d.get(l) && tree[i].get(m) >= d.get(m))   {
                upd(rch,m + 1,r,L,R,d);
                return;
            }
            if (tree[i].get(l) <= d.get(l) && tree[i].get(m) <= d.get(m))   {
                upd(rch,m + 1,r,L,R,tree[i]);
                tree[i] = d;
                return;
            }   ++m;
            if (tree[i].get(m) >= d.get(m) && tree[i].get(r) >= d.get(r))   {
                upd(lch,l,m - 1,L,R,d);
                return;
            }
            if (tree[i].get(m) <= d.get(m) && tree[i].get(r) <= d.get(r))   {
                upd(lch,l,m - 1,L,R,tree[i]);
                tree[i] = d;
                return;
            }
            return;
        }

        upd(lch,l,m,L,R,d); ++m;
        upd(rch,m,r,L,R,d);
    }
    ll  ask(int i,int l,int r,int p)    {
        if (l > p)  return  -inf;
        if (r < p)  return  -inf;

        ll  res = tree[i].get(p);

        if (l == r) return  res;

        int m = (l + r) / 2;

        res = max(res,ask(lch,l,m,p));  ++m;
        res = max(res,ask(rch,m,r,p));

        return  res;
    }
}   T;

int x[N], w[N];
ll  c[N];

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;  cin >> n;

    for(int i = 1 ; i <= n ; ++i)   {
        cin >> x[i];
        cin >> w[i];
        cin >> c[i];

        T.comp.push_back(x[i]);
    }

    T.initialize();

    int S = T.comp.size() - 1;

    ll  ans = 0;

    for(int i = 1 ; i <= n ; ++i)   {
        int j = lower_bound(T.comp.begin(),T.comp.end(),x[i]) - T.comp.begin();

        ll  F = T.ask(1,0,S,j) + c[i];

        if (w[i] == 0)  T.upd(1,0,S,0,S,Line(0,F));
        else    {
            ll  R = F / w[i];
            int l = lower_bound(T.comp.begin(),T.comp.end(),x[i] - R) - T.comp.begin();
            int r = upper_bound(T.comp.begin(),T.comp.end(),x[i] + R) - T.comp.begin() - 1;

            T.upd(1,0,S,l,j,Line( w[i],F - 1ll * w[i] * x[i]));
            T.upd(1,0,S,j,r,Line(-w[i],F + 1ll * w[i] * x[i]));
        }

        ans = max(ans,F);
    }
    cout << ans << endl;
}
