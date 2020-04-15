#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  push_back
#define X   first
#define Y   second

const int   N   = 2e5 + 5;

typedef pair<int,int>   ii;
typedef map<char,int>   mci;

struct SuffixAutomaton  {
    vector<mci> nxt;
    vector<int> len;
    vector<int> link;
    int last;

    SuffixAutomaton(string s) : nxt({}), len({}), link({}), last(-1)    {
        nxt.pb({}); link.pb(-1);
        len.pb(0);  last = 0;

        for(int i = 0 ; i < sz(s) ; ++i)    {
            char c = s[i];
            nxt.pb({});
            len.pb(i + 1);
            link.pb(0);

            int R = sz(nxt) - 1;
            int P = last;
            last = R;

            while (~P && !nxt[P].count(c))
                nxt[P][c] = R,
                P = link[P];

            if (P < 0)  continue;

            int Q = nxt[P][c];

            if (len[Q] == len[P] + 1)   {
                link[R] = Q;
                continue;
            }
            nxt.pb(nxt[Q]);
            len.pb(len[P] + 1);
            link.pb(link[Q]);

            link[Q] = link[R] = sz(nxt) - 1;

            while (~P && nxt[P].count(c) && nxt[P][c] == Q)
                nxt[P][c] = sz(nxt) - 1,
                P = link[P];
        }
    }
};

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
