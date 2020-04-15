//This is code for "Ada and Jobs" problem
#include<bits/stdc++.h>

using namespace std;

#define sz(x)   x.size()
#define pb      push_back

const int   N   = 2e6 + 1;

typedef map<char,int>   mci;

vector<int> g[N];
int st[N], en[N];
int tot = 0;

int dfs(int u)  {
    st[u] = ++tot;
    for(int v : g[u])
        dfs(v);
    en[u] = tot + 1;
    return  1;
}

struct  Aho {
    vector<mci> g;
    vector<int> f;
    vector<int> t;
    int add(string s)   {
        int R = 0;
        for(char c : s) {
            if(!g[R].count(c))
                g[R][c] = sz(g),
                g.push_back({});
            R = g[R][c];
        }
        return  1;
    }
    int FSM()   {
        f.assign(sz(g),0);
        t.assign(sz(g),0);  t.pb(0);
        queue<int>  q;
        q.push(0);  f[0] = -1;
        while (q.size())    {
            int u = q.front();  q.pop();
            for(auto it : g[u]) {
                int v = it.second;
                int z = f[u];
                for(; z >= 0 ; z = f[z])
                    if (g[z].count(it.first))   {
                        f[v] = g[z][it.first];
                        break;
                    }
                q.push(v);
            }
        }
        return  1;
    }
    int dfs(string s,int p) {
        int R = 0;
        for(char c : s) {
            for(; R >= 0 ; R = f[R])    if (g[R].count(c))  {
                R = g[R][c];
                break;
            }
            if (R < 0)  R = 0;
            if (p == 0) {
                int res = 0;
                for(int x = st[R] ; x > 0 ; x -= x & -x)
                    res += t[x];
                if (res)    return  1;
            }
        }
        if (p)  {
            for(int x = st[R] ; x < sz(t) ; x += x & -x)    t[x]++;
            for(int x = en[R] ; x < sz(t) ; x += x & -x)    t[x]--;
        }
        return  0;
    }
};

string s[N];
int type[N];

int main()  {
    int q;  scanf("%d",&q);
    Aho T;  T.g.push_back({});

    for(int i = 1 ; i <= q ; ++i)   {
        scanf("%d",&type[i]);
        cin >> s[i];
        if (!type[i])
            T.add(s[i]);
    }

    T.FSM();
    for(int i = 1 ; i < T.sz(g) ; ++i)
        g[T.f[i]].push_back(i);
    dfs(0);

    for(int i = 1 ; i <= q ; ++i)   {
        if (type[i] == 0)   T.dfs(s[i],1);
        if (type[i] == 1)
            puts(T.dfs(s[i],0) ? "YES" : "NO");
    }
}
