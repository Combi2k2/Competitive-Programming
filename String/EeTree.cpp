//Problem: https://oj.uz/problem/view/APIO14_palindrome
//2014 is also the year when EeTree was born

#include<bits/stdc++.h>
 
using namespace std;
 
#define pb  push_back
#define mci map<char,int>
 
const int   N   = 6e5 + 1;
 
int cur = 0;
int tot = 0;
 
vector<mci> nxt;
vector<int> len;
vector<int> link;
 
void NewNode()  {
    nxt.pb({});
    len.pb(0);
    link.pb(0);
}
 
int cnt[N];
 
int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    string s;   cin >> s;
 
    NewNode();  ++tot;
    NewNode();  ++tot;
 
    len[0] = -1;
 
    for(int i = 0 ; i < s.size() ; ++i) {
        while (1)   {
            if(i > len[cur] && s[i - len[cur] - 1] == s[i])
                break;
            cur = link[cur];
        }
 
        if (nxt[cur].count(s[i]))   {
            cur = nxt[cur][s[i]];
            cnt[cur]++;
            continue;
        }
 
        NewNode();
        nxt[cur][s[i]] = tot;
        len[tot] = len[cur] + 2;
        cnt[tot] = 1;
 
        if (len[tot] == 1)  {
            link[tot] = 1;
            cur = tot++;
            continue;
        }
 
        while (1)   {
            cur = link[cur];
            if (i > len[cur] && s[i - len[cur] - 1] == s[i])    {
                link[tot] = nxt[cur][s[i]];
                break;
            }
        }
        cur = tot++;
    }
 
    vector<int> vec(tot - 1);
 
    iota(vec.begin(),vec.end(),1);
    sort(vec.begin(),vec.end(),[&](int x,int y) {
        return  len[x] > len[y];
    });
 
    long long ans = 0;
 
    for(int x : vec)
        cnt[link[x]] += cnt[x],
        ans = max(ans,1ll * cnt[x] * len[x]);
 
    cout << ans << endl;
}
