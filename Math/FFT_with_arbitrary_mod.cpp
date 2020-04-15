#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 4096;
const int   mod = 1e9 + 7;
const ld    pi  = acos(-1);

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

template<typename T>    struct base {
    T  x, y;

    base(T _x = 0,T _y = 0) : x(_x), y(_y)  {}

    T   real()  {   return  x;  }
    T   imag()  {   return  y;  }

    base operator + (const base &rhs)   {   return  base(x + rhs.x,y + rhs.y);  }
    base operator - (const base &rhs)   {   return  base(x - rhs.x,y - rhs.y);  }
    base operator * (const base &rhs)   {   return  base(x * rhs.x - y * rhs.y,x * rhs.y + y * rhs.x);  }

    void operator += (const base &rhs)  {   x += rhs.x; y += rhs.y; }
    void operator -= (const base &rhs)  {   x -= rhs.x; y -= rhs.y; }
    void operator *= (const base &rhs)  {
        T  p = x * rhs.x - y * rhs.y;
        T  q = x * rhs.y + y * rhs.x;

        x = p;
        y = q;
    }
    void operator /= (T k)  {   x /= k; y /= k; }
    base operator /  (T k)  {   return  base(x / k,y / k);  }

    base conj() {   return  base(x,-y); }
    void print()    {
        cout << x << "+";
        cout << y << "i\n";
    }
};

typedef pair<int,int>   ii;
typedef base<double>    cpx;
typedef vector<int>     Pol;

cpx W[N];
cpx I[N];

void fft(vector<cpx>&a,bool inv)    {
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
        int add = N / k;

        for(int j = 0 ; j < k ; ++j)    {
            cpx u = a[i + j];
            cpx v = a[i + j + k] * (inv ? I[idx] : W[idx]);

            a[i + j]     = u + v;
            a[i + j + k] = u - v;

            idx += add;
        }
    }
    if (inv)    for(int i = 0 ; i < n ; ++i)    a[i] /= n;
}
cpx P1[N + N];
cpx Q1[N + N];

Pol Mul(Pol a,Pol b)    {
    int n = sz(a) + sz(b) - 1;
    int m = (2 << (int)log2(n));

    int MAGIC = sqrt(mod) + 5;

    vector<cpx> P(m);
    vector<cpx> Q(m);

    for(int i = 0 ; i < sz(a) ; ++i)    P[i] = cpx(a[i] % MAGIC,a[i] / MAGIC);
    for(int i = 0 ; i < sz(b) ; ++i)    Q[i] = cpx(b[i] % MAGIC,b[i] / MAGIC);

    fft(P,0);
    fft(Q,0);

    cpx AUX1;
    cpx AUX2;

    for(int i = 0 ; i < m ; ++i)    {
        AUX1 = P[i];
        AUX2 = P[(m - i) % m].conj();

        cpx A1 = (AUX1 + AUX2) * cpx(0.5,0);
        cpx A2 = (AUX1 - AUX2) * cpx(0,-0.5);

        AUX1 = Q[i];
        AUX2 = Q[(m - i) % m].conj();

        cpx B1 = (AUX1 + AUX2) * cpx(0.5,0);
        cpx B2 = (AUX1 - AUX2) * cpx(0,-0.5);

        P1[i] = A1 * B1 + A2 * B2 * cpx(0,1);
        Q1[i] = A1 * B2 + A2 * B1;
    }
    for(int i = 0 ; i < m ; ++i)
        P[i] = P1[i],
        Q[i] = Q1[i];

    fft(P,1);
    fft(Q,1);   a.resize(n);

    for(int i = 0 ; i < n ; ++i)    {
        a[i] = (ll)(P[i].imag() + 0.5) % mod;

        a[i] = mul(a[i],MAGIC); add(a[i],(ll)(Q[i].real() + 0.5) % mod);
        a[i] = mul(a[i],MAGIC); add(a[i],(ll)(P[i].real() + 0.5) % mod);
    }
    return  a;
}
int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int i = 0 ; i < N ; ++i)    {
        ld  ang = pi * i / N;

        W[i] = cpx(cos(ang), sin(ang));
        I[i] = cpx(cos(ang),-sin(ang));
    }

    Pol Polynomial1 = {2,3,4};
    Pol Polynomial2 = {5,4,7};

    Pol Result = Mul(Polynomial1,Polynomial2);

    for(int x : Result)
        cout << x << " ";
}
