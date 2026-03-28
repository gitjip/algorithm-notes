// 快速求前n项欧拉函数
// https://www.luogu.com.cn/problem/P2568
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  vector<ll> phi(n + 1), pre(n + 1);
  vector<bool> vis(n + 1);
  phi[1] = 1;
  vis[1] = true;
  for (ll i = 2; i <= n; ++i) {
    if (phi[i] == 0) phi[i] = i - 1;
    for (ll j = 2; j <= n / i; ++j) {
      vis[j * i] = true;
      if (i % j == 0) {
        phi[i * j] = phi[i] * j;
        break;
      } else {
        phi[i * j] = phi[i] * (j - 1);
      }
    }
    pre[i] = pre[i - 1] + phi[i];
  }
  ll ans = 0;
  for (ll i = 2; i <= n; ++i) {
    if (vis[i]) continue;
    ans += pre[n / i] * 2 + 1;
  }
  cout << ans << "\n";
  return 0;
}