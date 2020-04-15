#include<bits/stdc++.h>

using namespace std;

#define ll      long long
#define all(x)  x.begin(),x.end()
#define sz(x)   x.size()

#define FOR(i,a,b)  for(int i = a ; i < b ; ++i)

const int   N   = 5e5 + 1;
const int   inf = 1e9 + 1;

typedef vector<int> arr;

struct  BIT2D   {
    vector<int> val[N];
    vector<int> bit[N];

    void add(int x,int y)   {
        for(; x > 0 ; x -= x & -x)
            val[x].push_back(y);
    }
    void ini()  {
        FOR(i,1,N)  {
            sort(all(val[i]));
            val[i].resize(unique(all(val[i])) - val[i].begin());
            bit[i].resize(sz(val[i]) + 5);
        }
    }
    void upd(int x,int y,int v) {
        for(; x > 0 ; x -= x & -x)  {
            int p = upper_bound(all(val[x]),y) - val[x].begin();
            int K = bit[x].size();

            for(; p < K ; p += p & -p)
                bit[x][p] += v;
        }
    }
    int get(int x,int y)    {
        int ans = 0;
        for(; x < N ; x += x & -x)  {
            int p = upper_bound(all(val[x]),y) - val[x].begin();

            for(; p > 0 ; p -= p & -p)
                ans += bit[x][p];
        }
        return  ans;
    }
}   T1, T2;

void fakeup(int x,int y)    {
    T1.add(x,y);    x = N - x;  y = inf - y;
    T2.add(x,y);
}

int upd(int p,int x,int v)  {
    int ans = 0;

    ans += T1.get(p + 1,x - 1); T1.upd(p,x,v);  p = N - p;  x = inf - x;
    ans += T2.get(p + 1,x - 1); T2.upd(p,x,v);

    return  ans;
}

vector<ll>  countScans(arr a,arr p,arr x)   {
    int n = a.size();
    int q = p.size();

    ll  ans = 0;

    FOR(i,0,n)  fakeup(i + 1,a[i]);
    FOR(i,0,q)  fakeup(p[i] + 1,x[i]);

    T1.ini();
    T2.ini();

    vector<ll>  res;

    FOR(i,0,n)  ans += upd(i + 1,a[i],1);
    FOR(i,0,q)  {
        int P = p[i];
        int V = x[i];
        ans -= upd(P + 1,a[P],-1);  a[P] = V;
        ans += upd(P + 1,a[P], 1);

        res.push_back(ans);
    }

    return  res;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<ll>  v = countScans({1,2,3,4},{0,2},{3,1});

    for(int x : v)  cout << x << " ";
}
