#include<bits/stdc++.h>

using namespace std;

int Root(int p) {
	function<int(int,int)>  add = [&](int a,int b)  {
		a += b;
		if(a >= p)  a -= p;
		return  a;
	};
	function<int(int,int)>  sub = [&](int a,int b)  {
		a -= b;
		if(a <  0)  a += p;
		return  a;
	};
	function<int(int,int)>  mul = [&](int a,int b)  {
		return  (long long)a * b % p;
	};
	function<int(int,int)> qpow = [&](int a,int b)  {
		int ans = 1;
		while (b)   {
			if(b & 1)   ans = mul(ans,a);
			a = mul(a,a);   b >>= 1;
		}
		return  ans;
	};
	vector<int> v;
	int x = p - 1;
	for(int i = 2 ; i * i <= x ; ++i)   {
		if (x % i)  continue;
		while (x % i == 0)  x /= i;
		v.push_back(i);
	}
	if (x > 1)  v.push_back(x);
	for(int r = 1 ;; ++r)   {
		int ch = 1;
		for(int x : v)
			ch &= (qpow(r,p / x) != 1);
		if (ch) return  r;
	}
}

int main()  {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int p;  cin >> p;
	
	cout << Root(p);
}
