// 求前n项乘法逆元，间接阶乘法
// https://www.luogu.com.cn/problem/P3811
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll qp(ll a, ll b, ll p) {
  ll res = 1;
  while (b) {
    if (b & 1) res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, p;
  cin >> n >> p;
  vector<ll> fac(n + 1), invfac(n + 1);
  fac[0] = 1;
  for (ll i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % p;
  }
  invfac[n] = qp(fac[n], p - 2, p);
  for (ll i = n - 1; i >= 1; --i) {
    invfac[i] = invfac[i + 1] * (i + 1) % p;
  }
  for (ll i = 1; i <= n; ++i) {
    cout << invfac[i] * fac[i - 1] % p << "\n";
  }
  return 0;
}