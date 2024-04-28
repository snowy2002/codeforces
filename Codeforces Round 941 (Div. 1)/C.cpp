#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}

struct Hash {
    const int mod1 = 998244353, mod2 = 1e9 + 7;
    int b1 = 17, b2 = 233, n;
    vector<int> f1, f2, B1, B2;
    Hash(){}
    Hash(string s):n(s.length()), f1(n + 1), f2(n + 1), B1(n + 1), B2(n + 1) {
        B1[0] = B2[0] = 1;
        for(int i = 1; i <= n; i++) {
            B1[i] = B1[i - 1] * b1 % mod1;
            B2[i] = B2[i - 1] * b2 % mod2;
            f1[i] = (f1[i - 1] * b1 + s[i] - '0') % mod1;
            f2[i] = (f2[i - 1] * b2 + s[i] - '0') % mod2; 
        }
    }
    pair<int, int> get(int l, int r) {
        int a1 = ((f1[r] - f1[l - 1] * B1[r - l + 1]) % mod1 + mod1) % mod1;
        int a2 = ((f2[r] - f2[l - 1] * B2[r - l + 1]) % mod2 + mod2) % mod2;
        return {a1, a2};
    } 
    pair<int, int> iget(int l, int r) {
        return get(n - r, n - l);
    }
};

void solve() {
    int n = read();
    string s, t;
    cin >> s;
    s = " " + s;
    // t = " ";
    int L = 1, R = n;
    while(L + 1 <= n && s[L] == s[L + 1]) L += 1;
    while(R - 1 >= 1 && s[R] == s[R - 1]) R -= 1;
    if(L == n) {
        cout << 1 << "\n";
        return;
    }
    for(int i = L; i <= R;) {
        int r = i;
        while(r + 1 <= R) {
            if(s[r + 1] == s[i]) {
                r += 1;
            }
            else break;
        }
        if((r - i + 1) % 2 == 1) {
            t.push_back(s[i]);
        }
        else {
            t.push_back(s[i]);
            t.push_back(s[i]);
        }
        i = r + 1;
    }
    // cout << t << "\n";
    n = t.length();
    string invt = t;
    reverse(invt.begin(), invt.end());
    t = " " + t;
    invt = " " + invt;
    int l = 1, r = n, now = 1;

    Hash h1 = Hash(t);
    Hash h2 = Hash(invt);
    // cout << h2.n << "!!!\n";
    // cout << t << "!!!\n";

            // cout << h1.get(1, 1).first << " " << h2.iget(2, 2).first << ">>>>>>>!!";
    while(now * 2 <= r - l + 1) {
        // cout << l << " " << r << " " << now << "!!\n";
        int ok = 0; 
        if(rnd() & 1) {
            if(h1.get(l, l + now - 1) == h2.iget(l + now, l + now + now - 1)) {
                l = l + now;
                // ok = 1;
                now = 1;
                continue;
            }
            if(h1.get(r - now + 1, r) == h2.iget(r - now - now + 1, r - now)) {
                r = r - now;
                now = 1;
                continue;
                // ok = 1;
            }
        }
        else {
            if(h1.get(r - now + 1, r) == h2.iget(r - now - now + 1, r - now)) {
                r = r - now;
                now = 1;
                continue;
                // ok = 1;
            }
            if(h1.get(l, l + now - 1) == h2.iget(l + now, l + now + now - 1)) {
                l = l + now;
                // ok = 1;
                now = 1;
                continue;
            }
        }
        now += 1;
    }
    cout << r - l + 1 << "\n";
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