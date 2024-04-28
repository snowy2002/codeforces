#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}



void solve() {
    int n = read(), m = read(), k = read();

    vector<tuple<int, int, int, int>> ans;
    map<int, int> vis;
    auto add = [&](int x, int y, int z, int c) -> void {
        if(vis[c] <= 1) return;
        ans.push_back({x, y, z, c});
    };
    vector f(51, vector(51, 0ll));
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> f[i][j];
            vis[f[i][j]] += 1;
        }
    }

    for(int i = 1; i <= 50; i++) {
        for(int j = 1; j <= 50; j++) {
            if(i > n || j > m) {
                add(i, j, 1, f[n][m]);
                f[i][j] = f[n][m];
            }
        }
    }

    for(int i = 1; i <= 50; i++) {
        for(int j = 1; j <= 50; j++) {
            // int z = 1;
            for(int z = 2; z <= 1 + (50 - j) * 2; z++) {
                add(i, j, z, f[i][j]);
            }
            int z = 1 + (50 - j) * 2;
            for(int j1 = j; j1 < j + 50; j1++) {
                if(j1 != j) add(i, j1, z, f[i][j]);
                add(i, j1, z + 1, j1 - j + 1);
            }
        }
    }

    for(int j = 1; j <= 50; j++) {
        for(int z = 1; z <= 99; z += 2) {
            add(50 + j, j, z, j);
        }
        for(int z = 2; z <= 100; z += 2) {
            add(50 + j, j, z, j);
            if(z == 100) {
                for(int i = 51; i < 50 + j; i++) {
                    add(i, j, z, j);
                }
            }
            else {
                int J = j + (100 - z) / 2;
                for(int i = 51; i <= 50 + j; i++) {
                    add(i, J, z, j);
                }
                for(int jj = j + 1; jj < J; jj++) {
                    add(50 + j, jj, z, j);
                }
            }
        }
    }

    cout << ans.size() << "\n";
    
    for(auto [x, y, z, c] : ans) {
        cout << x << " " << y << " " << z << " " << c << "\n";
    }
}

signed main() {
    #ifdef ONLINE_JUDGE
        ios::sync_with_stdio(false);
        cin.tie(0);cout.tie(0);
    #else
        // freopen("a.in", "r", stdin);
    #endif

    solve();
}