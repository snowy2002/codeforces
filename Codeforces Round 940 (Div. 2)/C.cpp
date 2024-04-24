#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}
const int mod = 1e9 + 7;

int f[maxn];

int cal(int x) {
    if(f[x]) return f[x];
    int val = cal(x - 1) + (x - 1) * 2 % mod * cal(x - 2) % mod;
    val %= mod;
    f[x] = val;
    return f[x];
}

void solve() {
    int n = read(), k = read();
    f[0] = 1; f[1] = 1;
    for(int i = 1; i <= k; i++) {
        int aa = read(), bb = read();
        if(aa == bb) n -= 1;
        else n -= 2;
    }
    // cout << n << "!!\n";
    cout << cal(n) << "\n";
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