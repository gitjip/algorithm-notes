// 扩展欧拉定理
// https://www.luogu.com.cn/problem/P5091
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll qpow(ll a, ll b, ll p) {
  ll res = 1;
  while (b) {
    if (b & 1) res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}
ll phi(ll x) {
  ll res = x;
  for (ll i = 2; i <= x / i; ++i) {
    if (x % i) continue;
    while (x % i == 0) x /= i;
    res = res / i * (i - 1);
  }
  if (x > 1) res = res / x * (x - 1);
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll a, m, b = 0;
  string sb;
  cin >> a >> m >> sb;
  ll ph = phi(m);
  ll nb = sb.size();
  for (ll i = 0; i < nb; ++i) {
    b = (b * 10 % ph + (sb[i] - '0')) % ph;
  }
  ll nph = 0;
  for (ll t = m; t; t /= 10) nph++;
  if (nb <= nph) {
    ll tb = 0;
    for (ll i = 0; i < nb; ++i) {
      tb = tb * 10 + (sb[i] - '0');
    }
    if (tb < ph) {
      cout << qpow(a, tb, m) << "\n";
      return 0;
    }
  }
  cout << qpow(a, b + ph, m) << "\n";
  return 0;
}