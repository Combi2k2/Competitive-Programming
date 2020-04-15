include<bits/stdc++.h>

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

mt19937 rng(411200300);

/*
Refer to chemthan's implementation
Link: https://github.com/chemthan/chemthan/blob/master/Datastructure/Treap.cpp
Problem: https://codeforces.com/contest/863/problem/D
*/

struct Node {
    Node *l, *r;
    int key, pri;
    int nCh, rev;
    int val;

    Node(int key = 0,Node *l = 0,Node *r = 0,int pri = rng()) : key(key), l(l), r(r), pri(pri)  {
        nCh = 1;

        if (l)  nCh += l->nCh;
        if (r)  nCh += r->nCh;

        rev = 0;
        val = 0;
    }
};

int Siz(Node* x)    {
    if (x)  return  x->nCh;
    else    return  0;
}
void pull(Node* x)  {
    x->nCh = 1;
    x->nCh += Siz(x->l);
    x->nCh += Siz(x->r);
}
void push(Node* x)   {
    Node *u = x->l;
    Node *v = x->r;

    if (x->rev) {
        x->rev = 0;
        if (u)  swap(u->l,u->r), u->rev ^= 1;
        if (v)  swap(v->l,v->r), v->rev ^= 1;
    }
    if (x->val) {
        if (u)  u->key += x->val, u->val += x->val;
        if (v)  v->key += x->val, v->val += x->val;

        x->val = 0;
    }
}
Node* join(Node* x,Node* y)    {
    if (!x) return  y;
    if (!y) return  x;

    if (x->pri < y->pri)    {
        push(x);    x->r = join(x->r,y);
        pull(x);    return  x;
    }
    else    {
        push(y);    y->l = join(x,y->l);
        pull(y);    return  y;
    }
    assert(0);
}
void split(Node*x,Node*&l,Node*&r,int p)    {
    if (!x) {
        l = r = 0;
        return;
    }
    push(x);

    if (p >= Siz(x->l) + 1)   {
        p -= Siz(x->l) + 1;
        split(x->r,x->r,r,p);   pull(l = x);
    }
    else
        split(x->l,l,x->l,p),   pull(r = x);
}
void split(Node*x,Node*&l,Node*&r,const function<bool(Node*)> & go_right)   {
    if (!x) {
        l = r = 0;
        return;
    }
    push(x);
    if (go_right(x))
        split(x->r,x->r,r,go_right),    pull(l = x);
    else
        split(x->l,l,x->l,go_right),    pull(r = x);
}
void flip(Node*&x,int l,int r)   {
    Node *y, *z;

    split(x,x,y,l);
    split(y,y,z,r - l + 1);

    y->rev ^= 1;
    swap(y->l,y->r);

    y = join(y,z);
    x = join(x,y);
}
void add(Node*&x,int v) {
    Node *y;
    split(x,x,y,v);

    x = join(x,new Node(v));
    x = join(x,y);
}
void rem(Node*&x,int k) {
    if(!x)  return;
    if (x->key == k)
        x = join(x->l,x->r);
    else    {
        if (k < x->key) rem(x->l,k);
        if (k > x->key) rem(x->r,k);
    }
}
void upd(Node*&x,int l,int r,int v) {
    Node *y, *z;

    split(x,x,y,l);
    split(y,y,z,r - l + 1);

    y->val += v;
    y->key += v;

    y = join(y,z);
    x = join(x,y);
}

int a[N];
int tot = 0;

void show(Node* t,int isrt = 1) {
    if (!t) return;
    push(t);
    show(t->l,0);   a[tot++] = t->key;
    show(t->r,0);
    if (isrt)   {
        for(int i = 0 ; i < tot ; ++i)
            cerr << a[i] << " ";
        cerr << "\n";
        tot = 0;
    }
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Node* Rt = 0;

    int n;  cin >> n;
    int q;  cin >> q;
    int m;  cin >> m;

    for(int i = 0 ; i < n ; ++i)    {
        int x;  cin >> x;
        Rt = join(Rt,new Node(x));
    }
    for(int i = 0 ; i < q ; ++i)    {
        int t;  cin >> t;
        int l;  cin >> l;   --l;
        int r;  cin >> r;   --r;

        if (t == 1) {
            Node *y, *z, *t;
            split(Rt,Rt,y,l);
            split(y,y,z,r - l);
            split(z,z,t,1);

            y = join(z,y);
            y = join(y,t);
            Rt = join(Rt,y);
        }
        if (t == 2)
            flip(Rt,l,r);
    }
    show(Rt);
    for(int i = 0 ; i < m ; ++i)    {
        int p;  cin >> p;   --p;
        cout << a[p] << " ";
    }
}
