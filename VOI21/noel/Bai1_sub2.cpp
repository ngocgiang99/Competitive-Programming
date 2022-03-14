#include <bits/stdc++.h>

using namespace std;


int n, d;
int c[1000];
int f[205][205];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
     #ifndef ONLINE_JUDGE
    freopen("bai1.in", "r", stdin);
    freopen("bai1.ans", "w", stdout);
    #endif  
    cin >> n >> d;

    if (n > 100) return 0;

    for (int i = 0; i < 2*n; ++i) cin>> c[i];

    int res = 0;
    for (int k = 1; k <= 2*n; ++k) {
        int k1 = k;
        int k2 = 2*n - k1;
        int tmp = 0;

        // cout << k <<endl;
        for (int i = 1; i <= k1; ++i)
        for (int j = 1; j <= k2; ++j) {
            f[i][j] = max(f[i-1][j], f[i][j-1]);
            if (abs(c[i - 1] - c[j + k1 - 1]) <= d) {
                f[i][j] = max(f[i][j], f[i-1][j-1] + 1);
                res = max(res, f[i][j]);
                tmp = max(tmp, f[i][j]);
                // cout << i <<' '<< j <<' '<< f[i][j] <<endl;
            }
        }
        cerr << k <<' '<< tmp << endl;
    }

    cout << res <<endl;

    return 0;
}