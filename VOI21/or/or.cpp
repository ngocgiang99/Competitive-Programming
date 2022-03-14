#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

int n, k, l, r, ans;
int a[MAXN];
int fac[MAXN];
int cnt[MAXN];
int f[1 << 20];

void input() {
    cin >> n >> k >> l >> r;
    for (int i = 0; i < n; ++i) cin >> a[i];
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

void dp_sum_over_subsets() {
    init_factorial();
    for (int i = 0; i < n; ++i) ++cnt[a[i]];

    for (int i = 0; i < 20; ++i)
    for (int mask = 0; mask <= r; ++mask)
    if (mask & (1 << i)) {
        cnt[mask] += cnt[mask ^ (1<<i)];
    }

    for (int mask = 0; mask <= r; ++mask) {
        int n_ones_mask = __builtin_popcount(mask);
        int sign = (n_ones_mask&1) ? 1 : -1;

        if (cnt[mask] < k) continue;

        int numer = fac[cnt[mask]];
        int denom = 1ll * fac[k] * fac[cnt[mask] - k] % MOD;
        denom = pow(denom, MOD - 2);

        int tmp = 1ll * numer * denom % MOD;
        f[mask] = sign * tmp;

        // if (l <= mask && mask <= r) 
        //     cerr << mask <<' '<< f[mask] <<' '<< numer <<' '<< denom <<endl;
    }

    for (int i = 0; i < 20; ++i)
    for (int mask = 0; mask <= r; ++mask)
    if (mask & (1 << i)) {
        f[mask] = (f[mask] + f[mask ^ (1<<i)]) % MOD;
        int n_ones_mask = __builtin_popcount(mask);
        if (n_ones_mask&1)
            f[mask] = (f[mask] + MOD) % MOD;
        else 
            f[mask] = (f[mask] - MOD) % MOD;

        // f[mask] = (f[mask] + MOD) % MOD;
        // if (mask == 63) 
        // cerr <<' '<< mask <<' '<< f[mask] <<endl;
    }

    for (int mask = l; mask <= r; ++mask)
    if (mask%3 == 0) {
        // f[mask] = (f[mask] + MOD) % MOD;
        ans = (ans + abs(f[mask])) % MOD;
        // cerr << mask <<' '<< abs(f[mask]) <<endl;
        // ans = (ans + f[mask]) % MOD;
    }
    ans = (ans + MOD) % MOD;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
     #ifndef ONLINE_JUDGE
    freopen("voi21_or.in", "r", stdin);
    freopen("voi21_or.out", "w", stdout);
    #endif  

    input();
    dp_sum_over_subsets();

    cout << ans <<endl;
    return 0;
}