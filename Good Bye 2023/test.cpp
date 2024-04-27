#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}

signed main() {
    #ifdef ONLINE_JUDGE
        ios::sync_with_stdio(false);
        cin.tie(0);cout.tie(0);
    #else
        freopen("a.in", "r", stdin);
    #endif

    map<int,vector<int>> mp;
    mp[1].push_back(1);
    cout << mp.size() << "\n";
    mp[2].push_back(2);
    cout << mp.size() << "\n";
    mp[1].push_back(1);
    cout << mp.size() << "\n";
}