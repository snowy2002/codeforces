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
    for(int i = 1; i <= n; i++) {
        a[i] = read();
    }
    sort(a.begin() + 1, a.end());
    int now = 0;
    for(int i = n; i >= 0; i--) {
        if(i == n) {
            now = 0;
        }
        else {
            if(a[i] == a[i + 1]) continue;
            if(a[i] == a[i + 1] - 1) {
                now = now ^ 1;
            }
            else now = 1;
        }
    }
    if(now == 0) cout << "Bob\n";
    else cout << "Alice\n";
}

signed main() {
    #ifdef ONLINE_JUDGE
        ios::sync_with_stdio(false);
        cin.tie(0);cout.tie(0);
    #else
        // freopen("a.in", "r", stdin);
    #endif

    int t = read();
    while(t--) solve();
    return 0;
}