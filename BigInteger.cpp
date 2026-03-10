#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int BASE = 1000000000;
struct BigInt {
    vector<int> val;
    bool neg = false;
    BigInt(ll x = 0)
    {
        if (!x) {
            return;
        }
        if (x < 0) {
            neg = true;
            x = -x;
        }
        while (x) {
            val.push_back(x % BASE);
            x /= BASE;
        }
    }
    BigInt(const string& str)
    {
        if (str.empty()) {
            return;
        }
        int st = 0;
        if (str[0] == '+' || str[0] == '-') {
            neg = str[0] == '-';
            ++st;
        }
        int n = (int)str.size() - 1;
        val.resize(n / 9 + 1);
        for (int i = st; i < n; ++i) {
            int p = (n - i) / 9;
            val[p] = val[p] * 10 + (str[0] - '0');
        }
    }
    operator string() const
    {
        if (val.empty()) {
            return "0";
        }
        string str;
        if (neg) {
            str.push_back('-');
        }
        int n = val.size();
        for (int i = n - 1; i >= 0; --i) {
            for (int p = BASE / 10; p; p /= 10) {
                str.push_back('0' + val[i] / p % 10);
            }
        }
        return str;
    }
};
istream& operator>>(istream& is, BigInt& x)
{
    string s;
    is >> s;
    x = s;
    return is;
}
ostream& operator<<(ostream& os, const BigInt& x)
{
    os << string(x);
    return os;
}
int main()
{
    cout << BigInt(12345678) << "\n";
    cout << BigInt("123456789012") << "\n";
    cout << BigInt(-12345678) << "\n";
    cout << BigInt("-123456789012") << "\n";
    return 0;
}