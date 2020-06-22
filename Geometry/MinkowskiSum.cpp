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

ii  operator + (const ii&a,const ii&b)  {   return  ii(a.X + b.X,a.Y + b.Y);    }
ii  operator - (const ii&a,const ii&b)  {   return  ii(a.X - b.X,a.Y - b.Y);    }

ll  cro(ii  a,ii  b)    {   return  1ll * a.X * b.Y - 1ll * a.Y * b.X;  }
ll  ccw(ii  a,ii  b,ii  c)  {
    b = b - a;
    c = c - a;

    return  cro(b,c);
}
vector<ii>  Msum(vector<ii> A,vector<ii> B) { //A and B will be two convex Polygon and their vertices are enumerated in counterclockwise order
    rotate(A.begin(),min_element(all(A)),A.end());
    rotate(B.begin(),min_element(all(B)),B.end());

    vector<ii>  L;
    vector<ii>  R;

    for(int i = 0 ; i < sz(A) ; ++i)    L.pb(A[(i + 1) % sz(A)] - A[i]);
    for(int i = 0 ; i < sz(B) ; ++i)    R.pb(B[(i + 1) % sz(B)] - B[i]);

    vector<ii>  res;
    res.pb(A[0] + B[0]);

    int i = 0;
    int j = 0;

    while (i < sz(L) && j < sz(R))  res.pb(res.back() + (cro(L[i],R[j]) >= 0 ? L[i++] : R[j++]));
    while (i < sz(L))   res.pb(res.back() + L[i++]);
    while (j < sz(R))   res.pb(res.back() + R[j++]);

    res.pop_back();
    
    return  res;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);   
}
