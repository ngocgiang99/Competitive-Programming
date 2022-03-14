#include <bits/stdc++.h>
using namespace std;
// Tên chương trình
const string NAME = "bai1";
// Số test kiểm tra
const int NTEST = 100;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

// Viết lại hàm random để sử dụng cho thuận tiện. Hàm random này sinh ngẫu nhiên số trong phạm vi long long, số sinh ra >= l và <= h.
long long Rand(long long l, long long h) {
    assert(l <= h);
    return l + rd() * 1LL * rd() % (h - l + 1);
}

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp((NAME + ".in").c_str());
        // Code phần sinh test ở đây
        int n = Rand(50, 100);
        int d = Rand(1, 5);
        inp << n <<' '<< d <<endl;
        vector<int> c;
        for (int i = 0; i < 2*n; ++i) c.push_back(i);
        int step = Rand(1,1000);
        for (int i = 0; i < step; ++i) {
            int u = Rand(1, 2*n) - 1;
            int v = Rand(1, 2*n) - 1;
            swap(c[u], c[v]);
        }
        for (int i = 0; i < 2*n; ++i)
        inp << c[i] <<endl;

        inp.close();
        // Nếu dùng Linux thì "./" + Tên chương trình
        system(("./" + NAME).c_str());
        system(("./" + NAME + "_trau").c_str());
        // Nếu dùng linux thì thay fc bằng diff
        if (system(("diff " + NAME + ".out " + NAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}