#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 105
#define int long long

int read() {int x;cin>>x;return x;}

// int F[maxn][maxn][maxn];

void solve() {
    int n = read(), m = read(), k = read();

    vector<tuple<int, int, int, int>> ans;
    map<int, int> vis;
    // map<tuple<int, int, int>, int> F;
    auto add = [&](int x, int y, int z, int c) -> void {
        if(!vis[c]) return;
        // if(F[{x, y, z}]) {
            // cout << x << " " << y << " " << z << "!!\n";
            // return;
        // }
        // F[{x, y, z}] = 1;
        // F[x][y][z] = c;
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
        for(int j = 1; j <= 50; j += 2) {
            for(int z = 2; z <= 100; z++) {
                add(i, j, z, f[i][j]);
            }
        } 
        for(int j = 2; j <= 50; j += 2) {
            for(int z = 51; z <= 100; z++) {
                add(i, j, z, z - 50);
            }
        }
        for(int j = 2; j <= 50; j += 2) {
            for(int z = 2; z <= (50 - i + 1); z++) {
                add(i, j, z, f[i][j]);
            }
            int z = 50 - i + 1;
            for(int ii = i + 1; ii <= 100; ii++) {
                add(ii, j, z, f[i][j]);
            }
        }
    }


    for(int j = 1; j <= 50; j++) {
        for(int z = 52; z <= 100; z++) {
            add(51, j, z, z - 50);
        }
    }

    for(int i = 51; i <= 100; i++) {
        for(int j = 1; j <= 50; j += 2) {
            for(int z = 1; z <= 50; z++) {
                add(i, j, z, i - 50);
            }
        }
        for(int j = 1; j <= 50; j++) {
            add(i, j, 51, i - 50);
        }
    }
    // return;

    for(int i = 52; i <= 100; i++) {
        for(int z = 52; z <= 100; z++) {
            int val = max(i - 50, z - 50);
            add(i, 1, z, val);
            // cout << i << " " << 1 << " " << z << " " << val << "!!\n";
        }
    }

    // for(int z = 1; z <= 100; z++) {
    //     cout << "Z:=" << z << "\n"; 
    //     for(int i = 1; i <= 10; i++) {
    //         for(int j = 1; j <= 10; j++) {
    //             cout << F[i][j][z] << " \n"[j == 10];
    //         }
    //     }
    //     cout << "!\n";
    // }
    // return;

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