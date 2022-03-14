#include <bits/stdc++.h>
using namespace std;
// Tên chương trình
const string NAME = "voi21_or";
// Số test kiểm tra
const int NTEST = 100000;

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
        int n = Rand(100, 200);
        int k = Rand(1, n);
        int l = Rand(50, 200);
        while(l%3) l = Rand(50, 200);
        int r = l + Rand(0, 200 - l);
        inp << n << ' ' << k <<' '<< l <<' '<< r << endl;
        for (int i = 0; i < n; ++i)
        inp << Rand(1, 200) <<endl;
        
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