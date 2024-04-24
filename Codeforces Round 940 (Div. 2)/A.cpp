#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}

void solve() {
    int n = read();
    vector<int> a(n + 1);
    map<int, int> mp;
    int ans = 0;
    for(int i = 1; i <= n; i++) a[i] = read(), mp[a[i]] += 1;
    for(auto [key, val] : mp) {
        ans += val / 3;
    }
    cout << ans << "\n";
}

signed main() {
    #ifdef ONLINE_JUDGE
        ios::sync_with_stdio(false);
        cin.tie(0);cout.tie(0);
    #else
        freopen("a.in", "r", stdin);
    #endif
    int t = read();
    while(t--) solve();
    return 0;
}