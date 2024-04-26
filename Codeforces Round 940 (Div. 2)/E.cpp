#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}
const int mod = 1e9 + 7;

void solve() {
    int n = read();
}

signed main() {
    #ifdef ONLINE_JUDGE
        ios::sync_with_stdio(false);
        cin.tie(0);cout.tie(0);
    #else
        // freopen("a.in", "r", stdin);
    #endif

    vector f(1e6 + 1, 0ll), vis(1e6 + 1, 0ll);
    for(int i = 2; i <= 1e6; i++) {
        if(vis[i]) continue;
        int lt = 0;
        for(int j = i; j <= 1e6; j += i) {
            vis[j] = 1;
            f[j] -= lt;
            f[j] += (j / i) * (i - 1) % i;
            lt = (j / i) * (i - 1) % i;
        } 
    }


    for(int i = 2; i <= 1e6; i++) {
        f[i] = (f[i - 1] + f[i]) % mod;
        // f[i] += (i / 4) * 2 % 4;
        f[i] %= mod;
    }

    // for(int i = 2 )

    for(int i = 2; i <= 1e6; i++) {
        f[i] = (f[i - 1] + f[i]) % mod;
        f[i] += (i / 4) * 2 % 4;
        f[i] %= mod;
    }



    int t = read();
    while(t--) {
        int n = read();
        cout << f[n] << "\n";
    }
    return 0;
}