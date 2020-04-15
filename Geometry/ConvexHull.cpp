//problem: https://open.kattis.com/problems/convexhull
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

ii  operator + (const ii&a,const ii&b)  {   return  ii(a.X + b.X,a.Y + b.Y);    }
ii  operator - (const ii&a,const ii&b)  {   return  ii(a.X - b.X,a.Y - b.Y);    }

ll  ccw(ii  a,ii  b,ii  c)  {
    b = b - a;
    c = c - a;

    return  1ll * b.X * c.Y - 1ll * b.Y * c.X;
}
vector<ii>  Hull(vector<ii> vec)    {
    sort(all(vec));

    vector<ii>  upp;
    vector<ii>  low;

    for(ii  P : vec)    {
        while (sz(upp) > 1 && ccw(upp[sz(upp) - 2],upp.back(),P) >= 0)  upp.pop_back();
        while (sz(low) > 1 && ccw(low[sz(low) - 2],low.back(),P) <= 0)  low.pop_back();

        upp.pb(P);
        low.pb(P);
    }
    reverse(all(low));
    low.pop_back();
    vec.clear();

    for(int i = 0 ; i < sz(upp) ; ++i)  vec.pb(upp[i]);
    for(int i = 1 ; i < sz(low) ; ++i)  vec.pb(low[i]);

    return  vec;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while (1)   {
        int n;  cin >> n;

        if (n == 0)
            break;

        vector<ii>  vec(n);

        for(ii &P : vec)
            cin >> P.X,
            cin >> P.Y;

        vec.erase(unique(all(vec)),vec.end());
        vec = Hull(vec);

        reverse(all(vec));

        cout << vec.size() << "\n";

        for(ii  P : vec)
            cout << P.X << " ",
            cout << P.Y << "\n";
    }
}
