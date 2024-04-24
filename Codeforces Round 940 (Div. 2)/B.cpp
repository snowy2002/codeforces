#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}

void solve() {
    int n = read(), k = read();
    if(n == 1) {
        cout << k << "\n";
        return;
    }
    int cnt = __builtin_popcount(k);
    if((1 << cnt) - 1 == k) {
        for(int i = 1; i <= n; i++) {
            if(i == 1) cout << k << " \n"[i == n];
            else cout << 0 << " \n"[i == n];
        }
        return;
    }
    int f = __lg(k);
    int val = (1 << f) - 1; 
    cout << val << " " << k - val << " ";
    for(int i = 3; i <= n; i++) cout << 0 << " ";
    cout << "\n";
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