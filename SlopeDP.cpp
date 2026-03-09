#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5000;
int n, s;
ll t[N + 1], f[N + 1], dp[N + 1];
int q[N + 1], l = 1, r;
ll dx(int i, int j) { return f[i] - f[j]; }
ll dy(int i, int j) { return dp[i] - dp[j]; }
// 斜率优化DP:yj=ki*xj+bi
// bi=dpi-ti*fi-s*fn
// yj=dpj
// ki=ti+s
// xj=fj xj要递增
// P2365
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> f[i];
        t[i] += t[i - 1];
        f[i] += f[i - 1];
    }
    for (int i = 1; i <= n; ++i) {
        while (l < r && dy(i - 1, q[r]) * dx(q[r], q[r - 1]) <= dy(q[r], q[r - 1]) * dx(i - 1, q[r])) {
            --r;
        }
        q[++r] = i - 1;
        while (l < r && dy(q[l + 1], q[l]) <= dx(q[l + 1], q[l]) * (t[i] + s)) {
            ++l;
        }
        int j = q[l];
        dp[i] = dp[j] + t[i] * (f[i] - f[j]) + s * (f[n] - f[j]);
    }
    cout << dp[n] << "\n";
    return 0;
}