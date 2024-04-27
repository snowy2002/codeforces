#include<bits/stdc++.h>
using namespace std;
#define time chrono::system_clock::now().time_since_epoch().count()
mt19937_64 rnd(time);
#define maxn 1000005
#define int long long

int read() {int x;cin>>x;return x;}

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
        // st[x][0] = fa;
        // for(int i = 0; i < 20; i++) st[x][i + 1] = st[st[x][i]][i];
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
    int ma, mi, sum, tag = 0;
};
node operator + (node a, node b) {
    node c;
    c.ma = max(a.ma, b.ma);
    c.mi = min(a.mi, b.mi);
    c.sum = a.sum + b.sum;
    return c;
}

struct ST {
    node tr[maxn << 2];
    int a[maxn];
    void build(int k, int l, int r) {
        if(l == r) {
            tr[k].ma = tr[k].mi = tr[k].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(k << 1, l, mid);
        build(k << 1 | 1, mid + 1, r);
        tr[k] = tr[k << 1] + tr[k << 1 | 1];
    }
    void pushdown(int k, int l, int r, int mid) {
        tr[k << 1].ma += tr[k].tag;
        tr[k << 1].mi += tr[k].tag;
        tr[k << 1].sum += tr[k].tag * (mid - l + 1);
        tr[k << 1 | 1].ma += tr[k].tag;
        tr[k << 1 | 1].mi += tr[k].tag;
        tr[k << 1 | 1].sum += tr[k].tag * (r - mid);
        tr[k << 1].tag += tr[k].tag;
        tr[k << 1 | 1].tag += tr[k].tag;
        tr[k].tag = 0;
    }
    void modify(int k, int l, int r, int x, int y, int val) {
        if(x <= l && r <= y) {
            tr[k].tag += val;
            tr[k].ma += val;
            tr[k].mi += val;
            tr[k].sum += (r - l + 1) * val;
            return;
        }
        int mid = (l + r) >> 1;
        if(tr[k].tag) pushdown(k, l, r, mid);
        if(x <= mid) modify(k << 1, l, mid, x, y, val);
        if(mid + 1 <= y) modify(k << 1 | 1, mid + 1, r, x, y, val);
        tr[k] = tr[k << 1] + tr[k << 1 | 1];
    }
    node query(int k, int l, int r, int x, int y) {
        if(x <= l && r <= y) return tr[k];
        int mid = (l + r) >> 1;
        node ans;
        ans.ma = -1e18, ans.mi = 1e18, ans.sum = 0;
        if(tr[k].tag) pushdown(k, l, r, mid);
        if(x <= mid) ans = ans + query(k << 1, l, mid, x, y);
        if(mid + 1 <= y) ans = ans + query(k << 1 | 1, mid + 1, r, x, y);
        return ans;
    }
}st;

void solve() {
    int n = read();
    Tree tr(n);
    for(int i = 2; i <= n; i++) {
        int fa = read();
        tr.g[fa].push_back(i);
    }

    vector<int> a(n + 1);

    for(int i = 1; i <= n; i++) {
        a[i] = read();
    }

    tr.dfs(1, 0);
    for(int i = 1; i <= n; i++) {
        int id = tr.dfn[i];
        st.modify(1, 1, n, id, id, tr.dep[i]);
    }

    int ans = 1;
    vector<int> val(n + 1);
    vector<vector<int>> op(n + 1);
    auto dfs = [&](auto dfs, int x) -> void {
        if(val[a[x]]) op[val[a[x]]].push_back(x);
        int lt = val[a[x]];
        val[a[x]] = x;
        for(int i : tr.g[x]) {
            dfs(dfs, i);
        }
        val[a[x]] = lt;
        for(int i : op[x]) {
            int l = tr.dfn[i], r = tr.dfn[i] + tr.sz[i] - 1;
            st.modify(1, 1, n, l, r, -1);
        }
        vector<int> v;
        for(int i : tr.g[x]) {
            int l = tr.dfn[i], r = tr.dfn[i] + tr.sz[i] - 1;
            int res = st.query(1, 1, n, l, r).ma - tr.dep[x] + 1;
            v.push_back(res);
        }
        if(v.size() == 0) return;
        sort(v.begin(), v.end(), greater<int>());
        if(v.size() == 1) ans = max(ans, v[0]);
        else ans = max(ans, v[0] * v[1]);
    };
    dfs(dfs, 1);
    cout << ans << "\n";
    for(int i = 1; i <= 4 * n; i++) {
        st.tr[i].ma = st.tr[i].tag = st.tr[i].mi = st.tr[i].sum = 0;
    }
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