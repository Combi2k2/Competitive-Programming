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

#define lch     i << 1
#define rch     i << 1 | 1

struct Node {
    ll  Min;
    ll  Max;
}   tr[N << 2];
ll  lz[N << 2];

Node operator + (const Node&a,const Node&b) {
    Node c;
    c.Min = min(a.Min,b.Min);
    c.Max = max(a.Max,b.Max);

    return  c;
}

void pus(int i,int l,int r) {
    tr[i].Min += lz[i];
    tr[i].Max += lz[i];

    if (l < r)  {
        lz[lch] += lz[i];
        lz[rch] += lz[i];

        if (tr[i].Min == tr[i].Max) {
            tr[lch].Min = tr[lch].Max = tr[i].Min;
            tr[rch].Min = tr[rch].Max = tr[i].Min;

            lz[lch] = 0;
            lz[rch] = 0;
        }
    }
    lz[i] = 0;
}
void upd(int i,int l,int r,int L,int R,int t,int v) {
    pus(i,l,r);
    if (l > R)  return;
    if (L > r)  return;
    if (t == 2 && tr[i].Max <= v)   return;
    if (t == 3 && tr[i].Min >= v)   return;

    int m = (l + r) / 2;

    if (L <= l && r <= R)   {
        if (t == 1) lz[i] = v;
        if (t == 2 && tr[i].Min >= v)   tr[i].Min = tr[i].Max = v;
        if (t == 3 && tr[i].Max <= v)   tr[i].Min = tr[i].Max = v;

        pus(i,l,r);

        if (t > 1 && tr[i].Min < v && tr[i].Max > v)   {
            upd(lch,l,m,L,R,t,v);   ++m;
            upd(rch,m,r,L,R,t,v);

            tr[i] = tr[lch] + tr[rch];
        }
        return;
    }
    upd(lch,l,m,L,R,t,v);   ++m;
    upd(rch,m,r,L,R,t,v);

    tr[i] = tr[lch] + tr[rch];
}
Node get(int i,int l,int r,int L,int R) {
    pus(i,l,r);
    if (L <= l && r <= R)   return  tr[i];

    int m = (l + r) / 2;

    if (R <= m) return  get(lch,l,m,L,R);
    if (m <  L) return  get(rch,m + 1,r,L,R);

    return  get(lch,l,m,L,R) + get(rch,m + 1,r,L,R);
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;  cin >> n;
    int q;  cin >> q;

    for(int i = 1 ; i <= n ; ++i)   {
        int x;  cin >> x;
        upd(1,1,n,i,i,1,x);
    }
    for(int i = 1 ; i <= q ; ++i)   {
        int t;  cin >> t;
        int l;  cin >> l;
        int r;  cin >> r;

        if (t < 4)  {
            int x;  cin >> x;
            upd(1,1,n,l,r,t,x);
        }
        else    {
            Node res = get(1,1,n,l,r);

            cout << res.Min << " ";
            cout << res.Max << "\n";
        }
    }
}
