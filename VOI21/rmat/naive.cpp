#include <bits/stdc++.h>

using namespace std;
const string problem = "rmat";

#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)
// DEBUGING TEMPLETE ////////////////////////////////////////////////////////////////////////
#define db(val) "["#val" = "<<(val)<<"] "
#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#ifdef LOCAL_DEBUG   
#   define clog cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#   define DB() debug_block CONCAT(dbbl, __LINE__)
    int __db_level = 0;
    struct debug_block {
        debug_block() { clog << "{" << endl; ++__db_level; }
        ~debug_block() { --__db_level; clog << "}" << endl; }
    };
#else
#   define clog if (0) cerr
#   define DB(...)
#endif

template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}

const int MAXN = 1e6+7;
int m, n, ans;
int a[MAXN];
int s_table[MAXN];

void input() {
    cin >> m >> n;
    for (int i = 0; i < m*n; ++i) cin >> a[i];
}


int get_case() {
    if (m == 1 && n <= 10) return 1;
    else if (m == 1 && n <= 100) return 2;
    else if (m * n <= 500) return 3;
    else if (m * n <= 5000) return 4;
    return 1000;
}

void summed_table() {
    for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j) {
        int idx = i * n + j;
        s_table[idx] = a[idx];
        if (i > 0) {
            s_table[idx] = s_table[idx] + s_table[idx - n];
        }
        if (j > 0) {
            s_table[idx] = s_table[idx] + s_table[idx - 1];
        }
        if (i > 0 && j > 0) {
            s_table[idx] = s_table[idx] - s_table[idx - 1 - n];
        }
        // clog << db(idx) << s_table[idx] <<endl;
    }
}

int get_table(int x1, int y1, int x2, int y2) {
    int idx = x2 * n + y2;
    int ret = s_table[idx];
    // DB();
    // clog << db(idx) << db(s_table[idx]) << db(ret) <<endl;

    if (x1) {
        idx = (x1 - 1) * n + y2;
        ret -= s_table[idx];
    }
    // clog << db(ret) <<endl;
    if (y1) {
        idx = x2 * n + y1 - 1;
        ret -= s_table[idx];
    }
    // clog << db(ret) <<endl;
    if (x1 && y1) {
        idx = (x1 - 1) * n + y1 - 1;
        ret += s_table[idx];
    }
    return ret;
}

int sub12() {
    summed_table();
    
    int ret = 0;
    vector<int> f(n, 0);    
    vector<vector<int>> is_collapse(n+1, vector<int>(n+1, 0));


    for (int i = 0; i < n; ++i) is_collapse[i][i] = 1;

    for (int r = 0; r < n; ++r) {
        // is_collapse[l][l] = 1;
        for (int l = r-1; l >= 0; --l) {
            for (int k = l+1; k <= r; ++k)  {
                // clog << db(l) << db(k-1) << db(r) << db(get_table(0, l, 0, k-1)) << db(get_table(0, k, 0, r)) << endl;
                if (get_table(0, l, 0, k-1) == get_table(0, k, 0, r)) {
                    if (!is_collapse[l][k-1]) break;
                    if (!is_collapse[k][r]) break;
                    is_collapse[l][r] = 1;
                    // clog << db(l) << db(r) <<endl;
                }
            }
        }
    }

    for (int l = 0; l < n; ++l)
    for (int r = l; r < n; ++r)
    clog << db(l) << db(r) << db(is_collapse[l][r]) <<endl;

    for (int i = 0; i < n; ++i) {
        f[i] = i+1;
        for (int j = 0; j <= i; ++j)
        if (is_collapse[j][i]) {
            if (j == 0) f[i] = 1;
            else f[i] = min(f[i], f[j-1] + 1);
        }
    }


    ret = f[n-1];
    return ret;
}

int sub3() {
    clog << "Sub3 " <<endl;
    summed_table();
    
    int ret = 0;
    vector<int> f(n, 0);    
    vector<vector<int>> is_collapse_col(n+1, vector<int>(n+1, 0));


    for (int i = 0; i < n; ++i) is_collapse_col[i][i] = 1;
    for (int r = 0; r < n; ++r) {
        // is_collapse_col[l][l] = 1;
        for (int l = r-1; l >= 0; --l) {
            for (int k = l+1; k <= r; ++k)  {
                clog << db(l) << db(k-1) << db(r) << db(get_table(0, l, m-1, k-1)) << db(get_table(0, k, m-1, r)) << endl;
                if (get_table(0, l, m-1, k-1) == get_table(0, k, m-1, r)) {
                    if (!is_collapse_col[l][k-1]) break;
                    if (!is_collapse_col[k][r]) break;
                    is_collapse_col[l][r] = 1;
                    clog << db(l) << db(r) <<endl;
                    break;
                }
            }
        }
    }
    for (int l = 0; l < n; ++l)
    for (int r = l; r < n; ++r)
    clog << db(l) << db(r) << db(is_collapse_col[l][r]) <<endl;

    for (int i = 0; i < n; ++i) {
        f[i] = i+1;
        for (int j = 0; j <= i; ++j)
        if (is_collapse_col[j][i]) {
            if (j == 0) f[i] = 1;
            else f[i] = min(f[i], f[j-1] + 1);
        }
    }
    // ret = f[n-1];
    clog << db(f[n-1]) <<endl;

    vector<int> g(m, 0);    
    vector<vector<int>> is_collapse_row(m+1, vector<int>(m+1, 0));


    for (int i = 0; i < m; ++i) is_collapse_row[i][i] = 1;
    for (int r = 0; r < m; ++r) {
        // is_collapse_row[l][l] = 1;
        for (int l = r-1; l >= 0; --l) {
            for (int k = l+1; k <= r; ++k)  {
                if (get_table(l, 0, k-1, n-1) == get_table(k, 0, r, n-1)) {
                    if (!is_collapse_row[l][k-1]) break;
                    if (!is_collapse_row[k][r]) break;
                    is_collapse_row[l][r] = 1;
                    // clog << db(l) << db(r) <<endl;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        g[i] = i+1;
        for (int j = 0; j <= i; ++j)
        if (is_collapse_row[j][i]) {
            if (j == 0) g[i] = 1;
            else g[i] = min(g[i], g[j-1] + 1);
        }
    }
    clog << db(g[m-1]) << endl;


    ret = f[n-1] * g[m-1];
    return ret;
}

int sub4() {
    clog << "Sub4 " <<endl;
    summed_table();
    
    int ret = 0;
    vector<int> f(n, 0);    
    vector<vector<int>> is_collapse_col(n+1, vector<int>(n+1, 0));


    for (int i = 0; i < n; ++i) is_collapse_col[i][i] = 1;
    for (int r = 0; r < n; ++r) {
        // is_collapse_col[l][l] = 1;
        map<int, int> k_idx;
        int sum = get_table(0, r, m-1, r);
        k_idx[sum] = r;
        for (int l = r-1; l >= 0; --l) {
            
            sum = get_table(0, l, m-1, r);
            if ((sum&1) || k_idx.find(sum >> 1) == k_idx.end()) {
                k_idx[sum] = l;
                continue;
            }
            int k = k_idx[sum >> 1]; // Note: Find k
            k_idx[sum] = l;



            if (!is_collapse_col[l][k-1]) continue;
            if (!is_collapse_col[k][r]) continue;
            is_collapse_col[l][r] = 1;
            // clog << db(l) << db(r) <<endl;
        }
    }
    // for (int l = 0; l < n; ++l)
    // for (int r = l; r < n; ++r)
    // clog << db(l) << db(r) << db(is_collapse_col[l][r]) <<endl;

    for (int i = 0; i < n; ++i) {
        f[i] = i+1;
        for (int j = 0; j <= i; ++j)
        if (is_collapse_col[j][i]) {
            if (j == 0) f[i] = 1;
            else f[i] = min(f[i], f[j-1] + 1);
        }
    }
    // ret = f[n-1];
    clog << db(f[n-1]) <<endl;

    vector<int> g(m, 0);    
    vector<vector<int>> is_collapse_row(m+1, vector<int>(m+1, 0));


    for (int i = 0; i < m; ++i) is_collapse_row[i][i] = 1;
    for (int r = 0; r < m; ++r) {
        // is_collapse_row[l][l] = 1;
        map<int, int> k_idx;
        int sum = get_table(r, 0, r, n-1);
        k_idx[sum] = r;
        for (int l = r-1; l >= 0; --l) {
            sum = get_table(l, 0, r, n-1);
            if ((sum&1) || k_idx.find(sum >> 1) == k_idx.end()) {
                k_idx[sum] = l;
                continue;
            }
            int k = k_idx[sum >> 1]; // Note: Find k
            k_idx[sum] = l;
            
            if (k == -1) continue;

            if (!is_collapse_row[l][k-1]) continue;
            if (!is_collapse_row[k][r]) continue;
            is_collapse_row[l][r] = 1;
            // clog << db(l) << db(r) <<endl;
        }
    }

    for (int i = 0; i < m; ++i) {
        g[i] = i+1;
        for (int j = 0; j <= i; ++j)
        if (is_collapse_row[j][i]) {
            if (j == 0) g[i] = 1;
            else g[i] = min(g[i], g[j-1] + 1);
        }
    }
    clog << db(g[m-1]) << endl;


    ret = f[n-1] * g[m-1];
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen((problem + ".in").c_str(), "r", stdin);
    freopen((problem + ".ans").c_str(), "w", stdout);
    freopen((problem + "_debug.log").c_str(), "w", stderr);
    #endif  

    input();

    switch (get_case()) {
        case 1:
        case 2:
            ans = sub12();
            break;
        case 3:
            ans = sub3();
            break;
        case 4:
            ans = sub4();
            break;

        default:
            break;

    }
    cout << ans <<endl;

    return 0;
}