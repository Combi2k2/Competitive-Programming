//Problem: 813F
//This is just basic implementation of this type

#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 1e5 + 5;

typedef pair<int,int>   ii;

int p[N];
int s[N];
int f[N];
int flag;

ii  lead(int x) {
    int v = 0;
    while (x != p[x])   {
        v ^= f[x];
        x  = p[x];
    }
    return  ii(x,v);
}

stack<pair<int*,int> >  ops;

void app(int*a,int v)   {   ops.push(make_pair(a,*a));  *a = v; }
void add(int x,int y)   {
    ii  pa = lead(x);
    ii  pb = lead(y);

    if (pa.X == pb.X)   {
        if (pa.Y == pb.Y)
            app(&flag,1);
        return;
    }
    if (s[pa.X] < s[pb.X])
        swap(pa,pb);

    app(p + pb.X,pa.X);
    app(f + pb.X,pa.Y ^ pb.Y ^ 1);
    app(s + pa.X,s[pa.X] + s[pb.X]);
}

vector<ii>  Que[N << 2];

#define lch     i << 1
#define rch     i << 1 | 1

void add(int i,int l,int r,int L,int R,ii  v)   {
    if (l > R)  return;
    if (L > r)  return;
    if (L <= l && r <= R)   {
        Que[i].pb(v);
        return;
    }
    int m = (l + r) / 2;

    add(lch,l,m,L,R,v); ++m;
    add(rch,m,r,L,R,v);
}
void cal(int i,int l,int r) {
    int len = ops.size();

    for(ii  E : Que[i])
        add(E.X,E.Y);
    
    if (l == r) {
        if (flag)   cout << "NO\n";
        else        cout << "YES\n";
    }
    else    {
        int m = (l + r) / 2;
        
        cal(lch,l,m);   ++m;
        cal(rch,m,r);
    }
    while (sz(ops) > len)   {
        *ops.top().X = ops.top().Y;
         ops.pop();
    }
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;  cin >> n;
    int q;  cin >> q;

    map<ii,int> mp;

    for(int i = 1 ; i <= q ; ++i)   {
        int x;  cin >> x;
        int y;  cin >> y;

        if (x > y)  swap(x,y);

        ii  e(x,y);

        if(!mp.count(e))    mp[e] = i;
        else    {
            add(1,1,q,mp[e],i - 1,e);
            mp.erase(e);
        }
    }
    for(auto it : mp)
        add(1,1,q,it.Y,q,it.X);
    
    iota(p + 1,p + 1 + n,1);
    fill(s + 1,s + 1 + n,1);

    cal(1,1,q);
}
