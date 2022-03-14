#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1001;

int n, d;
int c[MAXN << 1];
int f[MAXN << 1][22];
vector<int> gift[MAXN << 1];
int bit[MAXN << 1];


int get(int x) {
    int ret = 0;
    while (x) {
        ret = max(ret, bit[x]);
        x -= x & (-x);
    }

    return ret;
}

void update(int x, int val) {
    while (x <= 2*n) {
        bit[x] = max(bit[x], val);
        x += x & (-x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
     #ifndef ONLINE_JUDGE
    freopen("bai1.in", "r", stdin);
    freopen("bai1.out", "w", stdout);
    #endif  
    cin >> n >> d;

    // if (n > 100) return 0;
    int n2 = n<<1;
    // cout << "test " << n2 <<endl;

    for (int i = 0; i < n2; ++i) cin>> c[i];


    for (int i = 0; i < n2; ++i) { 

        for (int j = i + 1; j < n2; ++j) 
        if (abs(c[i] - c[j]) <= d) gift[i].push_back(j+1);
    }

    int res = 0;

    for (int k = 1; k <= n2; ++k) {
        for (int i = 1; i <= n2; ++i) bit[i] = 0;

        for (int i = 0; i < k; ++i) {
            int first_j = upper_bound(gift[i].begin(), gift[i].end(), k) - gift[i].begin();
            // cout << k <<' '<< i <<' '<< gift[i].size() <<' '<< first_j <<endl;
            for (int j = gift[i].size() - 1; j >= first_j; --j) {
                // cout << k <<' '<< i <<' '<< j <<' '<< gift[i][j] << endl;
                f[i][j] = get(gift[i][j]) + 1;
                update(gift[i][j]+1, f[i][j]);
                res = max(res, f[i][j]);
            }
        }
    }
    

    cout << res <<endl;

    return 0;
}