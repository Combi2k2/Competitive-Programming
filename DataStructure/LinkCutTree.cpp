//problem: https://codeforces.com/gym/100960/problem/H
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
typedef pair<int,ii>    pii;

struct Node {
    Node *l, *r;
    Node *p;

    bool rev;
    int  nCh;
    int  Sum, w;
    Node() : l(0), r(0), p(0), rev(0), nCh(1), Sum(0), w(1) {}
}   pool[N];

bool isrt(Node *x)  {
    if (x -> p) {
        if (x -> p -> l == x)   return  0;
        if (x -> p -> r == x)   return  0;
    }
    return  1;
}
bool left(Node *x)  {   return  x -> p -> l == x;   }

void setChild(Node *x,Node *p,bool L)   {
    if (L)  p -> l = x;
    else    p -> r = x;

    if (x)  x -> p = p;
}
void pull(Node *x)  {
    x -> nCh = 1;
    x -> Sum = x -> w;

    if (x -> l) x -> nCh += x -> l -> nCh,  x -> Sum += x -> l -> Sum;
    if (x -> r) x -> nCh += x -> r -> nCh,  x -> Sum += x -> r -> Sum;
}
void push(Node *x)  {
    Node *u = x -> l;
    Node *v = x -> r;

    if (x -> rev)   {
        x -> rev = 0;
        if (u)  swap(u -> l,u -> r), u -> rev ^= 1;
        if (v)  swap(v -> l,v -> r), v -> rev ^= 1;
    }
}
void flip(Node *x)  {
    Node *p = x -> p;
    Node *g = p -> p;

    bool L = left(x);

    if (L)  setChild(x -> r,p,1);
    else    setChild(x -> l,p,0);

    if (!isrt(p))   setChild(x,g,left(p));
    else            x -> p = g;

    setChild(p,x,L ^ 1);
    pull(p);
}
Node *splay(Node *x)    {
    push(x);
    while (!isrt(x))    {
        Node *p = x -> p;
        Node *g = p -> p;

        if (g)  push(g);

        push(p);
        push(x);

        if(!isrt(p))
            flip(left(x) != left(p) ? x : p);

        flip(x);
    }
    pull(x);
    return  x;
}
Node *access(Node *x)   {
    Node *lst = 0;

    for(Node *u = x ; u ; u = u -> p)   {
        splay(u);
        u -> w += (u -> r ? u -> r -> Sum : 0); u -> r = lst;
        u -> w -= (u -> r ? u -> r -> Sum : 0);

        pull(lst = u);
    }
    splay(x);

    return  lst;
}
void makeroot(int R)    {
    Node *x = pool + R;
    access(x);
    x -> rev ^= 1;
    swap(x -> l,x -> r);
}
void link(int x,int p)  {
    Node *u = pool + x; makeroot(x);
    Node *v = pool + p;

    u -> p = v;
    v -> w += u -> Sum;
}
void cut(int x,int y)   {
    Node *u = pool + x; makeroot(x);
    Node *v = pool + y; access(v);

    v -> l = 0;
    u -> p = 0;
}
int findroot(int x) {
    Node *u = pool + x;
    access(u);

    while (u -> l)
        push(u),
        u = u -> l;

    push(u);

    return  splay(u) - pool;
}
int lca(int x,int y)    {
    Node *u = pool + x;
    Node *v = pool + y;

    access(u);

    return  access(v) - pool;
}
int p[N];

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;  cin >> n;

    while (1)   {
        char type;  cin >> type;
        if (type == 'E')
            break;

        int x;  cin >> x;
        int y;  cin >> y;

        if (type == 'C')    link(x,y);
        if (type == 'D')    cut(x,y);
        if (type == 'T')
            cout << (findroot(x) == findroot(y) ? "YES" : "NO") << endl;
    }
}
