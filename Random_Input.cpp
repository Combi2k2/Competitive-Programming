#include<bits/stdc++.h>

using namespace std;

#define X       first
#define Y       second
#define pb      push_back
#define all(x)  x.begin(),x.end()
#define sz(x)   x.size()

const int   N   = 1e5 + 1;

typedef pair<int,int>    ii;
typedef vector<int>      vi;
typedef vector<ii>       vii;

int rd(int l,int r) {
	return  (long long)rand() * rand() % (r - l + 1) + l;
}
vi  RdAr(int n,int L,int R) {   //random array of size n in range [L,R]
	vi  a(n);
	for(int i = 0 ; i < n ; ++i)
		a[i] = rd(L,R);
	return  a;
}
vi  RdPe(int n) {   //random permutation of size n
	vi  a(n);
	for(int i = 0 ; i < n ; ++i)
		a[i] = i + 1;
	random_shuffle(all(a));
	return  a;
}
vii RdTr(int n) {   //random tree with n vertices
	vi  x = RdPe(n);
	vii E;
	for(int i = 2 ; i <= n ; ++i)
		E.pb(ii(i,rd(1,i - 1)));
	for(int i = 0 ; i < n - 1 ; ++i)    {
		ii &e = E[i];
		e.X = x[e.X - 1];
		e.Y = x[e.Y - 1];
	}
	return  E;
}
vii RdGr(int n) {   //random graph with n vertices
	vii E = RdTr(n);
	map<ii,int> mp;
	for(int i = 0 ; i < n - 1 ; ++i)    {
		if(E[i].X > E[i].Y)
			swap(E[i].X,E[i].Y);
		mp[E[i]]++;
	}
	int m = min((n - 1) * (n - 2) / 2,N + N - 1 - n);
	while(m--)  {
		int x, y;
		while(1)    {
			y = rd(1,n);
			x = rd(1,y - 1);
			if(!mp.count(ii(x,y)))
				break;
		}
		E.pb(ii(x,y));
		mp[ii(x,y)]++;
	}
	random_shuffle(all(E));
	return  E;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    srand(time(NULL));
}
