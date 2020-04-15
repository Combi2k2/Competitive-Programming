#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 1 << 18;
const int   mod = 998244353;

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
typedef vector<int>     Pol;

int W[N];
int I[N];

void fft(Pol&a,bool inv)    {
    int n = sz(a);
    for(int i = 0 ; i < n ; ++i)    {
        int x = i;
        for(int j = 0, k = log2(n) - 1 ; j < k ; ++j, --k)
            if((x >> j & 1) != (x >> k & 1))    {
                x ^= (1 << j);
                x ^= (1 << k);
            }
        if (i < x)  swap(a[i],a[x]);
    }
    for(int k = 1 ; k < n ; k <<= 1)
    for(int i = 0 ; i < n ; i += k + k) {
        int idx = 0;
        int gap = N / k;

        for(int j = 0 ; j < k ; ++j, idx += gap)    {
            int x = a[i + j];
            int y = mul(a[i + j + k],inv ? I[idx] : W[idx]);

            add(a[i + j],y);    a[i + j + k] = x;
            sub(a[i + j + k],y);
        }
    }
    if (inv)    {
        int m = Pow(n,mod - 2);

        for(int&x : a)
            x = mul(x,m);
    }
}
Pol Mul(Pol a,Pol b)    {
    int n = sz(a) + sz(b) - 1;
    int m = (2 << (int)(log2(n)));

    a.resize(m);    fft(a,0);
    b.resize(m);    fft(b,0);

    for(int i = 0 ; i < m ; ++i)
        a[i] = mul(a[i],b[i]);

    fft(a,1);   a.resize(n);

    return  a;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int i = 0 ; i < N ; ++i)    {
        int exp = (mod / 2 / N) * i;

        W[i] = Pow(3,exp);
        I[i] = Pow(3,mod - exp - 1);
    }
    Pol a = {2,3,4};
    Pol b = {5,4,7};

    Pol ans = Mul(a,b);

    for(int x : ans)
        cout << x << " ";
}
