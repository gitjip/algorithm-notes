#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int BASE = 1000000000;
const int WIDTH = 9;
struct BigInt {
    vector<ll> num;
    bool neg;
    BigInt()
        : neg(false)
    {
    }
    BigInt(ll x)
    {
        neg = x < 0;
        x = std::abs(x);
        if (x == 0)
            num.push_back(0);
        else
            while (x) {
                num.push_back(x % BASE);
                x /= BASE;
            }
    }
    BigInt(const string& s)
    {
        neg = (s[0] == '-');
        int start = neg ? 1 : 0;
        num.clear();
        for (int i = s.size(); i > start; i -= WIDTH) {
            int l = max(start, i - WIDTH);
            ll val = 0;
            for (int j = l; j < i; j++)
                val = val * 10 + s[j] - '0';
            num.push_back(val);
        }
        if (num.empty())
            num.push_back(0);
        trim();
    }
    void trim()
    {
        while (num.size() > 1 && num.back() == 0)
            num.pop_back();
        if (num.size() == 1 && num[0] == 0)
            neg = false;
    }
    bool operator<(const BigInt& b) const
    {
        if (neg != b.neg)
            return neg;
        if (num.size() != b.num.size())
            return neg ^ (num.size() < b.num.size());
        for (int i = num.size() - 1; i >= 0; i--) {
            if (num[i] != b.num[i])
                return neg ^ (num[i] < b.num[i]);
        }
        return false;
    }
    bool operator>(const BigInt& b) const { return b < *this; }
    bool operator<=(const BigInt& b) const { return !(b < *this); }
    bool operator>=(const BigInt& b) const { return !(*this < b); }
    bool operator==(const BigInt& b) const
    {
        return neg == b.neg && num == b.num;
    }
    bool operator!=(const BigInt& b) const { return !(*this == b); }
    BigInt abs() const
    {
        BigInt res = *this;
        res.neg = false;
        return res;
    }
    friend BigInt add_abs(const BigInt& a, const BigInt& b)
    {
        BigInt res;
        res.num.clear();
        ll carry = 0;
        for (int i = 0; i < max(a.num.size(), b.num.size()) || carry; i++) {
            ll x = carry;
            if (i < a.num.size()) {
                x += a.num[i];
            }
            if (i < b.num.size()) {
                x += b.num[i];
            }
            res.num.push_back(x % BASE);
            carry = x / BASE;
        }
        res.trim();
        return res;
    }
    friend BigInt sub_abs(const BigInt& a, const BigInt& b)
    {
        BigInt res;
        res.num.clear();
        ll borrow = 0;
        for (int i = 0; i < a.num.size(); i++) {
            ll x = a.num[i] - borrow;
            if (i < b.num.size()) {
                x -= b.num[i];
            }
            borrow = x < 0;
            if (borrow) {
                x += BASE;
            }
            res.num.push_back(x);
        }
        res.trim();
        return res;
    }
    BigInt operator+(const BigInt& b) const
    {
        if (neg == b.neg) {
            BigInt res = add_abs(*this, b);
            res.neg = neg;
            return res;
        }
        if (abs() < b.abs()) {
            BigInt res = sub_abs(b.abs(), abs());
            res.neg = b.neg;
            return res;
        }
        BigInt res = sub_abs(abs(), b.abs());
        res.neg = neg;
        return res;
    }
    BigInt operator-(const BigInt& b) const
    {
        BigInt tmp = b;
        tmp.neg = !tmp.neg;
        return *this + tmp;
    }
    BigInt operator*(const BigInt& b) const
    {
        BigInt res;
        res.num.assign(num.size() + b.num.size(), 0);
        for (size_t i = 0; i < num.size(); ++i) {
            ll carry = 0;
            for (size_t j = 0; j < b.num.size() || carry; ++j) {
                ll cur = res.num[i + j] + num[i] * (j < b.num.size() ? b.num[j] : 0) + carry;
                res.num[i + j] = cur % BASE;
                carry = cur / BASE;
            }
        }
        res.neg = neg ^ b.neg;
        res.trim();
        return res;
    }
    friend pair<BigInt, BigInt> div_mod_abs(const BigInt& a, const BigInt& b)
    {
        // 竖式除法实现
        if (b == BigInt(0)) throw runtime_error("division by zero");
        BigInt dividend = a.abs();
        BigInt divisor = b.abs();
        BigInt quotient, remainder;
        quotient.num.resize(dividend.num.size(), 0);
        remainder.num.clear();
        for (int i = (int)dividend.num.size() - 1; i >= 0; --i) {
            // remainder = remainder * BASE + dividend.num[i]
            remainder.num.insert(remainder.num.begin(), dividend.num[i]);
            remainder.trim();
            ll l = 0, r = BASE - 1, ans = 0;
            while (l <= r) {
                ll mid = (l + r) / 2;
                BigInt t = divisor * BigInt(mid);
                if (t <= remainder) {
                    ans = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            quotient.num[i] = ans;
            remainder = remainder - divisor * BigInt(ans);
        }
        quotient.trim();
        remainder.trim();
        return {quotient, remainder};
    }
    BigInt operator/(const BigInt& b) const
    {
        if (b.abs() == BigInt(0))
            throw runtime_error("division by zero");
        auto [quot, rem] = div_mod_abs(*this, b);
        quot.neg = neg ^ b.neg;
        return quot;
    }
    BigInt operator%(const BigInt& b) const
    {
        if (b.abs() == BigInt(0))
            throw runtime_error("mod by zero");
        auto [quot, rem] = div_mod_abs(*this, b);
        rem.neg = neg;
        return rem;
    }
    string to_string() const
    {
        string res;
        if (neg)
            res += '-';
        res += ::to_string(num.empty() ? 0 : num.back());
        for (int i = num.size() - 2; i >= 0; i--) {
            string s = ::to_string(num[i]);
            res += string(WIDTH - s.size(), '0') + s;
        }
        return res;
    }
    ll to_ll() const
    {
        ll res = 0;
        for (int i = num.size() - 1; i >= 0; i--) {
            if (res > (LLONG_MAX - num[i]) / BASE)
                throw overflow_error("to_ll overflow");
            res = res * BASE + num[i];
        }
        return neg ? -res : res;
    }
    friend istream& operator>>(istream& in, BigInt& x)
    {
        string s;
        in >> s;
        x = BigInt(s);
        return in;
    }
    friend ostream& operator<<(ostream& out, const BigInt& x)
    {
        out << x.to_string();
        return out;
    }
};
// 测试样例
int main()
{
    BigInt a, b;
    cin >> a >> b;
    cout << "a+b=" << a + b << endl;
    cout << "a-b=" << a - b << endl;
    cout << "a*b=" << a * b << endl;
    if (b != BigInt(0)) {
        cout << "a/b=" << a / b << endl;
        cout << "a%b=" << a % b << endl;
    }
    cout << "a<b: " << (a < b) << endl;
    cout << "a>b: " << (a > b) << endl;
    cout << "a==b: " << (a == b) << endl;

    BigInt c = 1234567890123456789LL;
    cout << "c=" << c << endl;
    cout << "c to ll: " << c.to_ll() << endl;

    BigInt d = string("-9876543210987654321");
    cout << "d=" << d << endl;
    return 0;
}