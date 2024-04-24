#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 100005
#define int long long

int read() {int x;cin>>x;return x;}

int S(int x, int y) {
    return (x >> y) & 1;
}

int f[maxn][31][2];
int g[maxn][31][2];

void solve() {
    int n = read();
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int j = 0; j <= 30; j++) {
        f[0][j][0] = f[0][j][1] = 0;
        g[n + 1][j][0] = g[n + 1][j][1] = 0;
    }
    // vector f(n + 2, vector(31, vector(2, 0ll)));
    // vector g = f;
    // vector sf = f, sg = g;
    vector sum(31, 0ll);
    
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= 30; j++) {
            if(S(a[i], j)) { // 1
                f[i][j][1] = f[i - 1][j][0] + 1;
                f[i][j][0] = f[i - 1][j][1];
            }
            else {
                f[i][j][0] = f[i - 1][j][0] + 1;
                f[i][j][1] = f[i - 1][j][1];
            }
            sum[j] += f[i][j][0];
        }    
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= 30; j++) {
            f[i][j][0] = f[i - 1][j][0] + f[i][j][0];
        }
    }
    for(int i = n; i >= 1; i--) {
        for(int j = 0; j <= 30; j++) {
            if(S(a[i], j)) {
                g[i][j][1] = g[i + 1][j][0] + 1;
                g[i][j][0] = g[i + 1][j][1];
            }
            else {
                g[i][j][0] = g[i + 1][j][0] + 1;
                g[i][j][1] = g[i + 1][j][1];
            } 
        }  
    }

    for(int i = n; i >= 1; i--) {
        for(int j = 0; j <= 30; j++) {
            g[i][j][0] = g[i + 1][j][0] + g[i][j][0];
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int j = __lg(a[i]);
        ans += sum[j] - f[i - 1][j][0] - g[i + 1][j][0];
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