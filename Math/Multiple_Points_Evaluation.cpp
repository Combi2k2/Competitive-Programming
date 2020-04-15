#include<bits/stdc++.h>
#include "FFT_with_FFTmod.h"

using namespace std;

Pol Inv(Pol A)  {
    int n = sz(A);
    int m = n + 1 >> 1;

    if (n == 1) return  {Pow(A[0],mod - 2)};

	Pol B = A;

	B.resize(m);
	B = Inv(B);

    A = Mul(A,B);   sub(A[0],2);    for(int&x : A)  x = (x > 0 ? mod - x : 0);
    A = Mul(A,B);
    A.resize(n);

	return  A;
}
Pol Div(Pol A,Pol B)    {
    int n = sz(A);
    int m = sz(B);

    if (n < m)  return  Pol();

    reverse(all(A));
	reverse(all(B));

	B.resize(n - m + 1);    B = Mul(A,Inv(B));
	B.resize(n - m + 1);

	reverse(all(B));

	return B;
}
Pol Mod(Pol A,Pol B)    {
	int n = sz(A);
	int m = sz(B);

	if (n < m)  return  A;

	Pol Q = Mul(Div(A,B),B);

	for(int i = 0 ; i < m - 1 ; ++i)
        sub(A[i],Q[i]);

    A.resize(m - 1);

    return  A;
}
Pol T[N << 2];
Pol a;
Pol C;

#define lch     i << 1
#define rch     i << 1 | 1

void ini(int i,int l,int r) {
    if (l == r) {
        T[i] = {mod - a[l],1};
        return;
    }
    int m = (l + r) / 2;

    ini(lch,l,m);   ++m;
    ini(rch,m,r);

    T[i] = Mul(T[lch],T[rch]);
}
void cal(int i,int l,int r,Pol A,Pol B) {
    if (i > 1)  A = Mod(A,T[i]),
                B = Mod(B,T[i]);

    if (l == r) {
        int ans = Pow(B[0],mod - 2);

        ans = mul(ans,A[0]);
        ans = mul(ans,a[l]);

        cout << ans << " ";
        return;
    }
    int m = (l + r) / 2;

    cal(lch,l,m,A,B);   ++m;
    cal(rch,m,r,A,B);
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    init();

    int n;  cin >> n;

    a.resize(n);    for(int&x : a)  cin >> x;
    C.resize(n);    for(int&x : C)  cin >> x;

    ini(1,0,n - 1);

    Pol Q = T[1];   reverse(all(Q));    C = Mul(C,Q);

    for(int i = 0 ; i < n ; ++i)    {
        Q[i] = mul(Q[i + 1],i + 1);
        Q[i] = mod - Q[i];
    }
	C.resize(n);    reverse(all(C));
	Q.resize(n);    reverse(all(Q));

	cal(1,0,n - 1,C,Q);
}
