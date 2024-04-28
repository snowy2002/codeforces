#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}

void solve() {
    int n = read();
    string s;
    cin >> s;
    s = " " + s;
    int ansl = 1, ansr = 1, now = 1, op = 1;
    for(int i = 2; i <= n; i++) {
        int c = s[i] - '0';
        if(c != ((s[1] - '0' + now + 1) % 2 + 2) % 2) {
            now += op;
            ansr = max(ansr, now);
            ansl = min(ansl, now);
        }
        else {
            op = -op;
        }
    }
    cout << ansr - ansl + 1 << "\n";
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