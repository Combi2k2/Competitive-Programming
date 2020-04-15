/**
*   Problem statement:
*   A sequence of parentheses, you have 3 type of query
*   Type 1: flip the i-th character (from '(' to ')')
*   Type 2: find the minimal number of character that you have to add so that certain substring become normal parentheses sequence
*   Type 3: change the current string into the version of its before i-th query
**/

#include<bits/stdc++.h>

using namespace std;

#define pb      push_back
#define sz(x)   (int)x.size()

#define lch     tr[i].lef
#define rch     tr[i].rig

const int   N   = 1e6 + 1;

struct Node {
    int Sum, Min;
    int lef, rig;
    Node(int _s = 0,int _m = 0) : Sum(_s), Min(_m), lef(0), rig(0)  {}
};
void Merge(Node &a,Node b,Node c)   {
    a.Sum = b.Sum + c.Sum;
    a.Min = min(b.Min,b.Sum + c.Min);
}

vector<Node> tr;
vector<int>  Rt;

string s;

void ini(int i,int l,int r) {
    assert(i < sz(tr));
    if (l == r) {
        if (s[l] == '(')    tr[i] = Node( 1, 0);
        if (s[l] == ')')    tr[i] = Node(-1,-1);

        return;
    }
    int m = (l + r) / 2;

    lch = sz(tr);   tr.pb(Node());  ini(lch,l,m);   ++m;
    rch = sz(tr);   tr.pb(Node());  ini(rch,m,r);

    Merge(tr[i],tr[lch],tr[rch]);
}
void upd(int i,int l,int r,int p)   {
    assert(i < sz(tr));
    if (l == r) {
        if (tr[i].Sum > 0)  tr[i] = Node(-1,-1);
        else                tr[i] = Node( 1, 0);
        return;
    }
    int m = (l + r) / 2;

    if (m >= p) {   tr.pb(tr[lch]); lch = sz(tr) - 1;   upd(lch,l,m,p);     }
    else        {   tr.pb(tr[rch]); rch = sz(tr) - 1;   upd(rch,m + 1,r,p); }

    Merge(tr[i],tr[lch],tr[rch]);
}
Node get(int i,int l,int r,int L,int R) {
    assert(i < sz(tr));
    if (l > R)  return  Node();
    if (L > r)  return  Node();

    if (L <= l && r <= R)
        return  tr[i];

    int m = (l + r) / 2;

    Node ans;

    Merge(ans,get(lch,l,m,L,R),get(rch,m + 1,r,L,R));

    return  ans;
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #ifndef combi
    freopen("fixstr.inp","r",stdin);
    freopen("fixstr.out","w",stdout);
    #endif // combi

    tr.pb(Node());
    Rt.pb(0);

    cin >> s;   s = "#" + s;

    int n = s.size() - 1;
    int q;  cin >> q;

    ini(0,1,n);

    for(int i = 1 ; i <= q ; ++i)   {
        char c; cin >> c;
        if (c == 'C')   {
            int p;  cin >> p;

            tr.pb(tr[Rt.back()]);
            Rt.pb(sz(tr) - 1);

            upd(Rt.back(),1,n,p);
        }
        if (c == 'U')   {
            int p;  cin >> p;

            Rt.pb(Rt[p - 1]);
        }
        if (c == 'Q')   {
            int l;  cin >> l;
            int r;  cin >> r;

            Rt.pb(Rt.back());

            Node res = get(Rt.back(),1,n,l,r);

            cout << res.Sum - res.Min * 2 << "\n";
        }
    }
}
/*
((()))
10
C 1
Q 2 5
C 5
Q 1 6
U 3
C 4
Q 3 6
U 5
C 1
Q 1 5
*/
