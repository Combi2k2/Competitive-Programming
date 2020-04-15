//Problem: https://oj.uz/problem/view/JOI19_examination
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

namespace BIT2D {
    vector<int> val[N];
    vector<int> bit[N];

    void init() {
        for(int i = 1 ; i < N ; ++i)    {
            sort(all(val[i]));
            val[i].resize(unique(all(val[i])) - val[i].begin());
            bit[i].resize(sz(val[i]) + 5);
        }
    }
    void add(int x,int y)   {
        for(; x > 0 ; x -= x & -x)
            val[x].pb(y);
    }
    void upd(int x,int y)   {
        for(; x > 0 ; x -= x & -x)  {
            int p = upper_bound(all(val[x]),y) - val[x].begin();
            for(; p > 0 ; p -= p & -p)
                bit[x][p]++;
        }
    }
    int get(int x,int y)    {
        int ans = 0;
        for(; x < N ; x += x & -x)  {
            int p = lower_bound(all(val[x]),y) - val[x].begin() + 1;
            for(; p < sz(bit[x]) ; p += p & -p)
                ans += bit[x][p];
        }
        return  ans;
    }
}

typedef pair<int,int>   ii;

vector<ii>  Poi;
vector<int> Que;

int Math[N];
int Info[N];
int Sum[N];
int ans[N];

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;  cin >> n;   Poi.resize(n);
    int q;  cin >> q;

    vector<int> row = {-1};
    vector<int> col = {-1};

    for(ii &p : Poi)    {
        cin >> p.X >> p.Y;
        row.pb(p.X);
        col.pb(p.Y);
    }
    sort(all(Poi),[&](const ii &a,const ii &b)  {
         return  a.X + a.Y > b.X + b.Y;
    });

    sort(all(row)); row.erase(unique(all(row)),row.end());
    sort(all(col)); col.erase(unique(all(col)),col.end());

    for(ii &p : Poi)    {
        p.X = lower_bound(all(row),p.X) - row.begin();
        p.Y = lower_bound(all(col),p.Y) - col.begin();

        BIT2D::add(p.X,p.Y);
    }

    for(int i = 0 ; i < q ; ++i)    {
        int M;  cin >> M;   Math[i] = lower_bound(all(row),M) - row.begin();
        int I;  cin >> I;   Info[i] = lower_bound(all(col),I) - col.begin();
        cin >> Sum[i];
        Que.pb(i);
    }

    sort(all(Que),[&](const int &a,const int &b)    {
         return  Sum[a] > Sum[b];
    });

    BIT2D::init();
    int ptr = 0;

    for(int i : Que)    {
        for(; ptr < sz(Poi) ; ++ptr)    {
            int x = Poi[ptr].X;
            int y = Poi[ptr].Y;
            if (row[x] + col[y] < Sum[i])
                break;
            BIT2D::upd(x,y);
        }
        ans[i] = BIT2D::get(Math[i],Info[i]);
    }

    for(int i = 0 ; i < q ; ++i)
        cout << ans[i] << "\n";
}
