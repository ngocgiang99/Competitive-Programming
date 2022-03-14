#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN_SUB12 = 205;
const int MAXN = 1e6 + 5;

int n, k, l, r, ans;
int dp_12[MAXN_SUB12][1 << 8];
int a[MAXN];
int fac[MAXN];
int cnt_a[MAXN];
int f[1 << 20];

void input() {
    cin >> n >> k >> l >> r;
    for (int i = 0; i < n; ++i) cin >> a[i];
}

int check_case() {
    int max_a = 0;
    for (int i = 0; i < n; ++i) 
        max_a = max(max_a, a[i]);

    if (n <= 20 && max_a <= 200) return 1;
    else if (n <= 200 && max_a <= 200) return 2;

    for (int i = 0; i < n; ++i) {
        int x = a[i];
        while (x > 1) {
            if (x&1) return 4;
            x >>= 1;
        }
    }
    return 3;
}

int dp_sub12() {
    // cerr << "Case 12\n"; 
    dp_12[0][0] = 1;
    int max_or = 1 << 8;
    for (int i = 0; i < n; ++i) {
        for (int n_id = k; n_id >= 0; --n_id)
        for (int num_or = 0; num_or < max_or; ++num_or)
        if (dp_12[n_id][num_or]) {
            dp_12[n_id+1][num_or | a[i]] += dp_12[n_id][num_or];
            dp_12[n_id+1][num_or | a[i]] %= MOD;
            // if (num_or | a[i] == 95) 
            //     cerr << i <<' '<< dp_12[n_id+1][num_or | a[i]] << endl;
        }
    }

    int ret = 0;
    r = min(r, max_or);
    for (int num_or = l; num_or <= r; ++num_or)
    if (num_or % 3 == 0) {
        ret = (ret + dp_12[k][num_or]) % MOD;
        cerr << num_or <<' '<< dp_12[k][num_or] <<endl;
    }
    return ret;
}

int pow(int a, int n) {
    int ret = 1;
    while (n) {
        if (n&1) ret = 1ll * ret * a % MOD;
        a = 1ll * a * a % MOD;
        n >>= 1;
    }
    return ret;
}

void init_factorial() {
    fac[0] = 1;
    fac[1] = 1;

    for (int i = 2; i < MAXN; ++i) fac[i] = 1ll * fac[i-1] * i % MOD;
}

int combination_sub3() {
    if (r % 3 != 0) return 0;
    init_factorial();

    int bits[30];
    for (int i = 0; i < 30; ++i) bits[i] = 0;
    for (int i = 0; i < n; ++i) {
        int id = 0;
        int x = a[i];
        while (x) {
            ++id;
            x >>= 1;
        }
        ++bits[id];
    }

    int n_ones_mask = __builtin_popcount(l);
    int ret = 0;
    for(int mask = r; mask; mask = (mask - 1) & r) {
        int n_ones = __builtin_popcount(mask);
        int sign = (n_ones_mask&1) == (n_ones&1) ? 1 : -1;
        

        int cnt = 0;
        int id = 0;
        int x =  mask;
        while(x) {
            ++id;
            if (x&1) cnt += bits[id];
            x >>= 1;
        }

        if (cnt < k) continue;

        int numer = fac[cnt];
        int denom = 1ll * fac[k] * fac[cnt - k] % MOD;
        denom = pow(denom, MOD - 2);

        int tmp = 1ll * numer * denom % MOD;

        ret = (ret + sign * tmp) % MOD;
        ret = (ret + MOD) % MOD;
    }
    return ret;
}

int dp_sos_sub4() {
    init_factorial();
    int ret = 0;

    for (int i = 0; i < n; ++i) ++cnt_a[a[i]];
    // for (int i = 0; i <= r; ++i) f[i] = cnt_a[i];

    for (int i = 0; i < 20; ++i)
    for (int mask = 0; mask <= r; ++mask)
    if (mask & (1 << i)) {
        cnt_a[mask] += cnt_a[mask ^ (1<<i)];
        
    }

    
    int n_ones_mask = __builtin_popcount(r);
    for(int mask = r; mask; mask = (mask - 1) & r) {
        int n_ones = __builtin_popcount(mask);
        int sign = (n_ones_mask&1) == (n_ones&1) ? 1 : -1;

        int cnt = cnt_a[mask];
        cerr << mask <<' '<< cnt <<endl;
        if (cnt < k) continue;
        // cerr << mask <<' '<< cnt <<endl;

        int numer = fac[cnt];
        int denom = 1ll * fac[k] * fac[cnt - k] % MOD;
        denom = pow(denom, MOD - 2);
    
        int tmp = 1ll * numer * denom % MOD;
        cerr << sign * tmp << endl;

        ret = (ret + sign * tmp) % MOD;
        // ret = (ret + MOD) % MOD;
    }

    ret = (ret + MOD) % MOD;

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
     #ifndef ONLINE_JUDGE
    freopen("voi21_or.in", "r", stdin);
    freopen("voi21_or.ans", "w", stdout);
    #endif  

    input();
    switch (check_case()) {
        case 1:
        case 2:
            ans = dp_sub12();
            break;
        case 3:
            ans = combination_sub3(); 
            break;
        case 4:
            ans = dp_sos_sub4();
            break;

        default:
            break;
    }

    cerr << ans <<endl;
    cout << ans <<endl;
    return 0;
}