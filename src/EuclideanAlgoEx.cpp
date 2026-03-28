// 扩展欧几里得
// https://www.luogu.com.cn/problem/P1516
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll x, y, m, n, l;
    cin >> x >> y >> m >> n >> l;
    if (m < n) {
        swap(x, y);
        swap(m, n);
    }
    ll s, t;
    ll d = exgcd(m - n, l, s, t);
    // cout << d << "\n";
    if ((y - x) % d) {
        cout << "Impossible\n";
    } else {
        ll ld = l / d;
        cout << ((y - x) / d * s % ld + ld) % ld << "\n";
    }
    return 0;
}