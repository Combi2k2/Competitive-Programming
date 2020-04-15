/*
problem: https://codeforces.com/problemset/problem/1043/G
target: find the longest repetition start at a particular position
*/

#pragma GCC optimize ("Ofast")
#include<bits/stdc++.h>

using namespace std;

#define ld  double

const int   N   = 2e5 + 5;
const int   mod1 = 1e9 + 7;
const int   mod2 = 1e9 + 9;

typedef long long   ll;
typedef vector<int> vi;

vector<int> p[N];

int n, q;

char s[N];

ll  H1[N], p1[N];
ll  H2[N], p2[N];

ll  get(int l,int r)    {
	ll  res1 = (H1[r] - H1[l - 1] * p1[r - l + 1]) % mod1;
	ll  res2 = (H2[r] - H2[l - 1] * p2[r - l + 1]) % mod2;
	if (res1 < 0)   res1 += mod1;
	if (res2 < 0)   res2 += mod2;
	return  res1 * mod2 + res2;
}

int cnt[N][26];

int count(int l,int r,int c)    {
	return  cnt[r][c] - cnt[l - 1][c];
}

unordered_map<ll,vi>    mp[N];

int repL[N];//the smallest length of tandem start at i
int repR[N];//the smallest lenght of tandem end at i
int rmq[N][20];

void Main_Lorentz() {
	for(int i = 2 ; i <= n ; ++i)
		if (p[i].empty())
			for(int j = i ; j <= n ; j += i)
				p[j].push_back(i);

	for(int k = 1 ; k <= n ; k <<= 1)
		for(int i = 1 ; i + k - 1 <= n ; ++i)
			mp[k][get(i,i + k - 1)].push_back(i);
	for(int i = 1 ; i <= n ; ++i)
		for(int k = 1 ; i + k - 1 <= n && !repL[i] ; k <<= 1)   {
			const vi &v = mp[k][get(i,i + k - 1)];
			int j = lower_bound(v.begin(),v.end(),i) - v.begin() + 1;
			int r = min((int)v.size(),j + 50);
			for(; j < r && v[j] - i <= 2 * k && !repL[i] ; ++j)  {
				int len  = v[j] - i;
				if (i + len + len >= n) break;
				if (get(i,i + len - 1) == get(i + len,i + len + len - 1))
					repL[i] = 2 * len;
			}
		}

	for(int i = 1 ; i <= n ; ++i)
		for(int k = 1 ; i - k + 1 >= 1 && !repR[i] ; k <<= 1)   {
			const vi &v = mp[k][get(i - k + 1,i)];
			int j = lower_bound(v.begin(),v.end(),i - k + 1) - v.begin() - 1;
			int l = max(-1,j - 50);
			for(; j > l && i - k + 1 - v[j] <= 2 * k && !repR[i] ; --j)   {
				int len  = i - k + 1 - v[j];
				if (i - len - len < 0)  break;
				if (get(i - len + 1,i) == get(i - len - len + 1,i - len))
					repR[i] = 2 * len;
			}
		}
	
	for(int i = 1 ; i <= n ; ++i)   {
		if (repL[i])    rmq[i][0] = i - 1 + repL[i];
		else            rmq[i][0] = n + 1;
	}
	for(int i = 0 ; i < 17 ; ++i)
	for(int j = 1 ; j + (2 << i) - 1 <= n ; ++j)
		rmq[j][i + 1] = min(rmq[j][i],rmq[j + (1 << i)][i]);
}

bool chk0(int l,int r)  {
	for(int i = 0 ; i < 26 ; ++i)
		if (count(l,r,i) > 1)   return  0;
	return  1;
}
bool chk1(int l,int r)  {
	for(int num : p[r - l + 1]) {
		int len = (r - l + 1) / num;
		if (get(l,r - len) == get(l + len,r))
			return  1;
	}
	return  0;
}
bool chk2(int l,int r)  {
	if (repL[l] && l + repL[l] - 1 <= r)    return  1;
	if (repR[r] && r - repR[r] + 1 >= l)    return  1;
	for(int k = 1 ; 2 * k <= r - l + 1 ; k <<= 1)   {
		const vi &v = mp[k][get(r - k + 1,r)];
		int i = lower_bound(v.begin(),v.end(),l) - v.begin();
		int j = lower_bound(v.begin(),v.end(),r - k + 1) - v.begin();
		int R = min(j,i + 51);
		for(int w = i ; w < R ; ++w)    {
			int len = k + v[w] - l;
			if (2 * len > r - l + 1 || len > k + k) break;
			if (get(l,l + len - 1) == get(r - len + 1,r))
				return  1;
		}
	}
	return  0;
}
int work()  {
	int L, R;   scanf("%d%d",&L,&R);
	if (chk0(L,R))  return -1;
	if (chk1(L,R))  return  1;
	if (!count(L + 1,R,s[L]) && !count(L,R - 1,s[R]))   {
		int k = log2(R - L + 1);
		return  4 - (min(rmq[L][k],rmq[R - (1 << k) + 1][k]) <= R);
	}
	return  3 - chk2(L,R);
}

int main()  {
	
	scanf("%d%s%d",&n,s + 1,&q);
	
	p1[0] = p2[0] = 1;
	
	for(int i = 1 ; i <= n ; ++i)   {
		s[i] -= 'a';
		p1[i] =  p1[i - 1] * 103 % mod1;
		p2[i] =  p2[i - 1] * 101 % mod2;
		H1[i] = (H1[i - 1] * 103 + s[i]) % mod1;
		H2[i] = (H2[i - 1] * 101 + s[i]) % mod2;
		for(int j = 0 ; j < 26 ; ++j)
			cnt[i][j] = cnt[i - 1][j];
		cnt[i][s[i]]++;
	}
	
	Main_Lorentz();
	
	for(int i = 1 ; i <= q ; ++i)
		printf("%d\n",work());
}
