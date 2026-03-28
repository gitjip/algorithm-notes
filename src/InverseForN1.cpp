// 求前n项乘法逆元，直接公式法
// https://www.luogu.com.cn/problem/P3811
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, p;
  cin >> n >> p;
  vector<ll> f(n + 1);
  f[1] = 1;
  for (ll i = 2; i <= n; ++i) {
    f[i] = (p - (p / i) * f[p % i] % p) % p;
  }
  for (ll i = 1; i <= n; ++i) {
    cout << f[i] << "\n";
  }
  return 0;
}