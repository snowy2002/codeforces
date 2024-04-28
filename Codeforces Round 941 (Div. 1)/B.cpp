#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}

void solve() {
    int n = read(), k = read();
    int val = k - 1;
    vector<int> ans;

    for(int i = 1; i <= val; i *= 2) {
        ans.push_back(i);
        val -= i;
    }
    if(val) ans.push_back(val);

    for(int i = k + 1; i <= 2e6; i *= 2) {
        ans.push_back(i);
    }
    // k - 1  k + 1     2 * k + 2       4 * k + 4
    ans.push_back(2 * k + 1);
    sort(ans.begin(), ans.end());
    // int cnt = 0;


    cout << ans.size() << "\n";
    for(auto i : ans) {
        cout << i << " ";
    }
    cout << "\n";
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