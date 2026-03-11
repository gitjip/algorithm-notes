#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll qp(ll a, ll b, ll p)
{
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
/// @brief 链接：https://www.luogu.com.cn/problem/P3811
/// @return 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, p;
    cin >> n >> p;
    // 时间复杂度O(nlogp)，太慢
    for (ll i = 1; i <= n; ++i) {
        cout << qp(i, p - 2, p) << "\n"; // 求i的逆元
    }
    return 0;
}