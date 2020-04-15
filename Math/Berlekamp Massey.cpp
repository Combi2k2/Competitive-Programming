//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

//problem: https://www.codechef.com/APRIL20A/problems/TRIPWAYS
//my solution using berlekamp did not achieve but what i need here is implementation of this algorithm

#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 4005;
const int   mod = 1e9 + 7;

void add(int &a,int b)  {
    a += b;
    if (a >= mod)
        a -= mod;
}
void sub(int &a,int b)  {
    a -= b;
    if (a <  0)
        a += mod;
}
int mul(int a,int b)    {
    return  1ll * a * b % mod;
}
int Pow(int a,int b)    {
    int ans = 1;
    while (b)   {
        if(b & 1)   ans = mul(ans,a);
        a = mul(a,a);   b >>= 1;
    }
    return  ans;
}
int inv(int a,int p)    {
    return  a == 1 ? 1 : p - 1ll * p * inv(p % a,a) / a;
}
typedef pair<int,int>   ii;
typedef vector<int>     vi;

/***This is start of needed implementation***/

vi  BM(vi  arr) {
    vi  res, cur;
    int pos, val;

    for(int i = 0 ; i < sz(arr) ; ++i)  {
        int V = 0;

        for(int j = 0 ; j < sz(cur) ; ++j)
            add(V,mul(arr[i - j - 1],cur[j]));

        if (arr[i] == V)    continue;
        if (cur.empty())    {
            cur.resize(i + 1);
            pos = i;
            val = (V - arr[i] + mod) % mod;
            continue;
        }
        V = mul(V + mod - arr[i],inv(val,mod));

        vi  now(i - pos - 1);
            now.pb(V);

        for(int j = 0 ; j < sz(res) ; ++j)
            now.pb(mul(mod - res[j],V));

        if (now.size() < cur.size())
            now.resize(sz(cur));

        for(int j = 0 ; j < sz(cur) ; ++j)
            add(now[j],cur[j]);

        if (res.size() + i - pos >= cur.size()) {
            res = cur;
            pos = i;
            val = mul(V,val);
        }
        cur = now;
    }
    return  cur;
}
vi  LFSR;

void Mul(vi &P,vi  Q)   {
    vector<int> R(sz(P) + sz(Q) - 1);

    for(int i = 0 ; i < sz(P) ; ++i)
    for(int j = 0 ; j < sz(Q) ; ++j)
        add(R[i + j],mul(P[i],Q[j]));

    for(int i = sz(R) - 1 ; i >= sz(P) ; --i)
    for(int j = sz(P) - 1 ; j >= 0     ; --j)
        add(R[i - j - 1],mul(R[i],LFSR[j]));

    for(int i = 0 ; i < sz(P) ; ++i)
        P[i] = R[i];
}
vi  calc(ll  n) {
    vi  mg(sz(LFSR));
    vi  st(sz(LFSR));

    mg[0] = 1;

    if(sz(st) > 1)  st[1] = 1;
    else            st[0] = LFSR[0];

    while (n)   {
        if(n & 1)   Mul(mg,st);
        Mul(st,st); n >>= 1;
    }
    return  mg;
}
/***Implementation end here. Thanks for watching***/
vector<int> g[N];

int a[N];
int d[N];
int f[N][N + N];

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;  cin >> n;
    int m;  cin >> m;
    int q;  cin >> q;

    for(int i = 1 ; i <= n ; ++i)   cin >> a[i];
    for(int i = 1 ; i <= m ; ++i)   {
        int x;  cin >> x;
        int y;  cin >> y;

        g[x].pb(y);
    }
    fill(d + 2,d + 1 + n,1e9);

    f[1][0] = 1;

    for(int i = 1 ; i <= n ; ++i)   {
        for(int x : g[i])
            if (d[x] > d[i] + 1)
                d[x] = d[i] + 1;

        for(int j = d[i] ; j < N ; ++j) {
            add(f[i][j + 1],mul(f[i][j],a[i]));

            for(int x : g[i])
                add(f[x][j + 1],f[i][j]);
        }
    }
    vector<int> F;

    for(int i = 0 ; i < N ; ++i)
        F.pb(f[n][i]);

    LFSR = BM(F);

    for(int i = 0 ; i < q ; ++i)    {
        ll  D;  cin >> D;

        if (n > 100 && D <= 50000) {
            for(int k = sz(F) ; k <= D ; ++k)   {
                int v = 0;
                for(int j = 0 ; j < sz(LFSR) ; ++j)
                    add(v,mul(LFSR[j],F[k - j - 1]));

                F.pb(v);
            }
        }
        if (D < sz(F))  {
            cout << F[D] << "\n";
            continue;
        }
        if (LFSR.empty())   {
            cout << "0\n";
            continue;
        }
        vi  arr = calc(D);
        int ans = 0;

        for(int i = 0 ; i < sz(arr) ; ++i)
            add(ans,mul(arr[i],F[i]));

        cout << ans << "\n";
    }
}
