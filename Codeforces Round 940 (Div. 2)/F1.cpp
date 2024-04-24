#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 100005
#define int long long

int read() {int x;cin>>x;return x;}
int mod1 = 998244353, mod2 = 1e9 + 7;

struct Tree {
    int n, tot = 0;
    vector<vector<int>> g;
    vector<int> dfn, id, sz, dep;
    vector<array<int,22>> st;
    Tree(int n):n(n),dfn(n + 1),id(n + 1),g(n + 1),sz(n + 1),dep(n + 1),st(n + 1) {}
    void dfs(int x, int fa) {
        dfn[x] = ++tot;
        id[tot] = x;
        sz[x] = 1;
        dep[x] = dep[fa] + 1;
        st[x][0] = fa;
        for(int i = 0; i < 20; i++) st[x][i + 1] = st[st[x][i]][i];
        for(int i : g[x]) {
            if(i == fa) continue;
            dfs(i, x);
            sz[x] += sz[i];
        }
    }
    int lca(int a, int b) {
        if(dep[a] < dep[b]) swap(a, b);
        for(int i = 20; i >= 0; i--) {
            if(dep[st[a][i]] >= dep[b]) a = st[a][i];
        }
        if(a == b) return a;
        for(int i = 20; i >= 0; i--) {
            if(st[a][i] != st[b][i]) {
                a = st[a][i];
                b = st[b][i];
            }
        }
        return st[a][0];
    }
};

struct node {
    int l, r, sum1, sum2;
}tr[maxn * 32];

int pw1[maxn], pw2[maxn];

struct ST {
    int tot = 0;

    void pushup(int k) {
        tr[k].sum1 = (tr[tr[k].l].sum1 + tr[tr[k].r].sum1) % mod1;
        tr[k].sum2 = (tr[tr[k].l].sum2 + tr[tr[k].r].sum2) % mod2;
    }

    void modify(int &k, int l, int r, int x, int val, int lt) {
        k = ++tot;
        // cout << k << " " << lt << "!!!!\n";
        tr[k] = tr[lt];
        if(l == r) {
            // if(x == 4) cout << l << " " << val << "!!\n" << pw1[x] << "!!!\n";
            tr[k].sum1 = (tr[k].sum1 + pw1[x]) % mod1;
            tr[k].sum2 = (tr[k].sum2 + pw2[x]) % mod2;
            return;
        }
        int mid = (l + r) >> 1;
        if(x <= mid) modify(tr[k].l, l, mid, x, val, tr[lt].l);
        else modify(tr[k].r, mid + 1, r, x, val, tr[lt].r);
        pushup(k);
    }

    // int query(int k, int l, int r, int x, int y) {
    //     // cout << l << " " << r << ">!>!>!>!\n";
    //     if(!k) return 0;
    //     if(x <= l && r <= y) {
    //         // cout << "k: " << k << "!!\n";
    //         return tr[k].sum1;
    //     } 
    //     int mid = (l + r) >> 1, ans = 0;
    //     if(x <= mid) ans += query(tr[k].l, l, mid, x, y);
    //     if(mid + 1 <= y) ans += query(tr[k].r, mid + 1, r, x, y);
    //     return ans % mod1;
    // }

    pair<int, int> get(int k1, int k2, int lca1, int lca2) {
        int v1 = ((tr[k1].sum1 + tr[k2].sum1 - tr[lca1].sum1 - tr[lca2].sum1) % mod1 + mod1) % mod1;
        int v2 = ((tr[k1].sum2 + tr[k2].sum2 - tr[lca1].sum2 - tr[lca2].sum2) % mod2 + mod2) % mod2;
        return {v1, v2};
    } 

    int query_rk(int k1, int k2, int lca1, int lca2, int k3, int k4, int lca3, int lca4, int l, int r, int x, int y) {
        // if(l == r) return l;
        // cout << l << " " << r << " " << x << " " << y << "\n";
        if(get(k1, k2, lca1, lca2) == get(k3, k4, lca3, lca4)) return -1;
        int mid = (l + r) >> 1;
        if(x <= l && r <= y) {
            if(l == r) return l;
            if(get(tr[k1].l, tr[k2].l, tr[lca1].l, tr[lca2].l) != get(tr[k3].l, tr[k4].l, tr[lca3].l, tr[lca4].l)) 
                return query_rk(tr[k1].l, tr[k2].l, tr[lca1].l, tr[lca2].l, tr[k3].l, tr[k4].l, tr[lca3].l, tr[lca4].l, l, mid, x, y);
            return query_rk(tr[k1].r, tr[k2].r, tr[lca1].r, tr[lca2].r, tr[k3].r, tr[k4].r, tr[lca3].r, tr[lca4].r, mid + 1, r, x, y);
        }
        if(y <= mid) return query_rk(tr[k1].l, tr[k2].l, tr[lca1].l, tr[lca2].l, tr[k3].l, tr[k4].l, tr[lca3].l, tr[lca4].l, l, mid, x, y);
        if(x >= mid + 1) return query_rk(tr[k1].r, tr[k2].r, tr[lca1].r, tr[lca2].r, tr[k3].r, tr[k4].r, tr[lca3].r, tr[lca4].r, mid + 1, r, x, y);
        int val = query_rk(tr[k1].l, tr[k2].l, tr[lca1].l, tr[lca2].l, tr[k3].l, tr[k4].l, tr[lca3].l, tr[lca4].l, l, mid, x, y);
        if(val != -1) return val;
        return query_rk(tr[k1].r, tr[k2].r, tr[lca1].r, tr[lca2].r, tr[k3].r, tr[k4].r, tr[lca3].r, tr[lca4].r, mid + 1, r, x, y);
    }

    // void merge(int &k, int x, int y, int l, int r) {
    //     if(!x) {k = y; return;}
    //     if(!y) {k = x; return;}
    //     k = ++tot;
    //     if(l == r) {tr[k] = tr[x]; tr[k].sum += tr[y].sum; return;}
    //     int mid = (l + r) >> 1;
    //     merge(tr[k].l, tr[x].l, tr[y].l, l, mid);
    //     merge(tr[k].r, tr[x].r, tr[y].r, mid + 1, r);
    //     pushup(k);
    // }
}st;

const int N = 1e5;

void solve() {
    int n = read();
    Tree tr(n);
    vector<int> a(n + 1);

    pw1[0] = pw2[0] = 1;
    int B1 = 1e5 + 9;
    int B2 = 1e6 + 9;
    // pw1[1] = 1e5 + 9;
    // pw2[1] = 1e6 + 9;

    for(int i = 1; i <= N; i++) {
        pw1[i] = pw1[i - 1] * B1 % mod1;
        pw2[i] = pw2[i - 1] * B2 % mod2;
    }

    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i < n; i++) {
        int aa = read(), bb = read();
        tr.g[aa].push_back(bb);
        tr.g[bb].push_back(aa);
    }   
    tr.dfs(1, 0);


    vector<int> root(n + 1);
    // cout << st.query(root[4], 1, N, 4, 4) << "!!!\n";
    // cout << st.query(root[2], 1, N, 4, 4) << "!!!!!!\n";
    auto dfs = [&](auto dfs, int x, int fa) -> void {
        // if(x == 4) {
            // cout << "X:" << x << " " << "fa:" << fa << "\n";
        // }
        // cout << a[x] << "!!!>>>>\n";
        st.modify(root[x], 1, N, a[x], 1, root[fa]);
        for(int i : tr.g[x]) {
            if(i == fa) continue;
            dfs(dfs, i, x);
        }
    };

    dfs(dfs, 1, 0);
    int q = read();
    while(q--) {
        int u1 = read(), v1 = read(), u2 = read(), v2 = read(), k = read();
        int lca1 = tr.lca(u1, v1), lca2 = tr.st[lca1][0];
        int lca3 = tr.lca(u2, v2), lca4 = tr.st[lca3][0];
        // cout << lca1 << " " << lca3 << "\n";
        vector<int> ans;
        int now = 1;
        while(k--) {
            now = st.query_rk(root[u1], root[v1], root[lca1], root[lca2], root[u2], root[v2], root[lca3], root[lca4], 1, N, now, N);
            if(now == -1) break;
            ans.push_back(now);
            now += 1;
        }
        cout << ans.size() << " ";
        for(auto i : ans) cout << i << " ";
        cout << "\n";
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
    return 0;
}