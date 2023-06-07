#include "biginteger.h"

BigInteger::BigInteger() : buffer({0}), is_negative(false) {}

BigInteger::BigInteger(int Int) {
    is_negative = (Int < 0);
    if (Int < 0) {
        Int = -Int;
    }
    else if (Int == 0) {
        buffer.push_back(0);
    }
    while (Int > 0) {
        buffer.push_back(Int % base);
        Int /= base;
    }
}

BigInteger::BigInteger(std::string str) {
    if (str.length() == 0) {
        is_negative = false;
        buffer.push_back(0);
    }
    else {
        is_negative = (str[0] == '-');
        if (str[0] == '-') {
            str = str.substr(1);
        }
        buffer.resize(str.length());
        for (size_t i = 0; i < str.length(); ++i) {
            buffer[str.length() - i - 1] = str[i] - '0';
        }
        remove_first_zeros();
    }
}

BigInteger::BigInteger(const BigInteger &other) {
    is_negative = other.is_negative;
    for (size_t i = 0; i < other.buffer.size(); ++i) {
        buffer.push_back(other.buffer[i]);
    }
}

void BigInteger::remove_first_zeros() {
    while (buffer.size() > 1 && buffer.back() == 0) {
        buffer.pop_back();
    }
    if (buffer[0] == 0 && buffer.size() == 1) { // исключение отрицательного нуля
        is_negative = false;
    }
}

std::string BigInteger::toString() const {
    std::string strBI;
    if (is_negative) {
        strBI.append("-");
    }
    for (size_t i = 0; i < buffer.size(); ++i) {
        strBI += std::to_string(buffer[buffer.size() - 1 - i]);
    }
    return strBI;
}

std::ostream& operator<< (std::ostream& out, const BigInteger& bi) {
    out << bi.toString();
    return out;
}

std::istream& operator>> (std::istream& in, BigInteger& bi) {
    std::string str;
    in >> str;
    bi = BigInteger(str);
    return in;
}

BigInteger& BigInteger::operator= (const BigInteger& other) {
    if (this == &other) {
        return *this;
    }
    is_negative = other.is_negative;
    buffer = other.buffer;
    return *this;
}

BigInteger BigInteger::operator+ () const {
    return *this;
}

BigInteger BigInteger::operator- () const {
    if (*this == BigInteger(0)) {
        return *this;
    }
    BigInteger copy(*this);
    copy.is_negative = !copy.is_negative;
    return copy;
}

bool operator< (const BigInteger& left, const BigInteger& right) {
    if (left.is_negative) {
        return right.is_negative ? (-right) < (-left) : true;
    }
    if (right.is_negative) {
        return false;
    }
    if (left.buffer.size() != right.buffer.size()) {
        return left.buffer.size() < right.buffer.size();
    }
    for (size_t i = 0; i < left.buffer.size(); ++i) {
        if (left.buffer[left.buffer.size() - 1 - i] != right.buffer[left.buffer.size() - 1 - i]) {
            return left.buffer[left.buffer.size() - 1 - i] < right.buffer[left.buffer.size() - 1 - i];
        }
    }
    return false;
}

bool operator== (const BigInteger& left, const BigInteger& right) {
    if (left.is_negative != right.is_negative) {
        return false;
    }
    if (left.buffer.size() != right.buffer.size()) {
        return false;
    }
    for (size_t i = 0; i < left.buffer.size(); ++i) {
        if (left.buffer[i] != right.buffer[i]) {
            return false;
        }
    }
    return true;
}

bool operator!= (const BigInteger& left, const BigInteger& right) {
    return !(left == right);
}

bool operator<= (const BigInteger& left, const BigInteger& right) {
    return (left < right) || (left == right);
}

bool operator>= (const BigInteger& left, const BigInteger& right) {
    return !(left < right);
}

bool operator> (const BigInteger& left, const BigInteger& right) {
    return (left >= right) && (left != right);
}

int& BigInteger::operator[] (size_t index) {
    return buffer[index];
}

const int& BigInteger::operator[] (size_t index) const {
    return buffer[index];
}

size_t BigInteger::length() const {
    return buffer.size();
}

BigInteger operator+ (const BigInteger& left, const BigInteger& right) {
    BigInteger result(left);
    result += right;
    return result;
}

BigInteger operator- (const BigInteger& left, const BigInteger& right) {
    BigInteger result(left);
    result -= right;
    return result;
}

BigInteger& BigInteger::operator+= (const BigInteger& other) {
    // при вызове + и - вызываются += и -= соответственно, при этом зацикливания не возникает, тк все сводится к случаю, когда оба числа положительны
    if (is_negative) {
        if (other.is_negative) {
            *this = -((-*this) + (-other));
            return *this;
        }
        else {
            *this = other - (-*this);
            return *this;
        }
    }
    size_t carry = 0; // флаг переноса из предыдущего разряда
    for (size_t i = 0; i < (buffer.size() < other.buffer.size() ? other.buffer.size() : buffer.size()) || carry != 0; ++i) {
        if (i == buffer.size()) {
            buffer.push_back(0);
        }
        buffer[i] += carry + (i < other.buffer.size() ? other.buffer[i] : 0);
        carry = buffer[i] / base;
        buffer[i] %= base;
    }
    remove_first_zeros();
    return *this;
}

BigInteger& BigInteger::operator-= (const BigInteger& other) {
    // при вызове + и - вызываются += и -= соответственно, при этом зацикливания не возникает, тк все сводится к случаю, когда оба числа положительны
    if (other.is_negative) {
        *this += (-other);
        return *this;
    }
    if (is_negative) {
        *this = -(-*this + other);
        return *this;
    }
    if (*this < other) {
        *this = -(other - *this);
        return *this;
    }
    int carry = 0;
    for (size_t i = 0; i < other.buffer.size() || carry != 0; ++i) { // гарантируется, что правое число меньше левого
        buffer[i] -= carry + (i < other.buffer.size() ? other.buffer[i] : 0);
        carry = (buffer[i] < 0);
        if (carry != 0) {
            buffer[i] += base;
        }
    }
    remove_first_zeros();
    return *this;
}

const BigInteger BigInteger::operator++ (int) {
    BigInteger tmp = *this;
    ++* this;
    remove_first_zeros();
    return tmp;
}

BigInteger& BigInteger::operator++ () {
    *this += 1;
    return *this;
}

const BigInteger BigInteger::operator-- (int) {
    BigInteger tmp = *this;
    --* this;
    remove_first_zeros();
    return tmp;
}

BigInteger& BigInteger::operator-- () {
    *this -= BigInteger(1);
    return *this;
}

void BigInteger::balance_vector(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        if (vec[i] > 0) {
            vec[i + 1] += vec[i] / 10;
            vec[i] %= 10;
        }
        else if (vec[i] < 0) {
            vec[i + 1] += (vec[i] / 10) - 1;
            vec[i] = vec[i] % 10 + 10;
        }
    }
}

std::vector<int> BigInteger::naive_mul(const std::vector<int>& left, const std::vector<int>& right) {
    size_t len = left.size();
    std::vector<int> res(2 * len);
    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            res[i + j] += left[i] * right[j];
        }
    }
    return res;
}

std::vector<int> BigInteger::karatsuba_mul(std::vector<int>& left, std::vector<int>& right) {
    size_t len = left.size();
    size_t old_len = len;
    if (len % 2 == 1) {
        len++;
    }
    while (right.size() < len) {
        right.push_back(0);
    }
    while (left.size() < len) {
        left.push_back(0);
    }
    std::vector<int> res(2 * len, 0);
    if (len <= len_for_naive_mul) {
        return naive_mul(left, right);
    }
    size_t k = len / 2; // разделитель
    std::vector<int> XR{ left.begin(), left.begin() + k };
    std::vector<int> XL{ left.begin() + k, left.end() };
    std::vector<int> YR{ right.begin(), right.begin() + k };
    std::vector<int> YL{ right.begin() + k, right.end() };
    std::vector<int> YLR(k);
    std::vector<int> XLR(k);
    for (size_t i = 0; i < k; ++i) {
        XLR[i] = XR[i] + XL[i];
        YLR[i] = YR[i] + YL[i];
    }
    std::vector<int> T1 = karatsuba_mul(XL, YL);
    std::vector<int> T2 = karatsuba_mul(XR, YR);
    std::vector<int> T3 = karatsuba_mul(XLR, YLR);
    for (size_t i = 0; i < len; ++i) {
        T3[i] -= T2[i] + T1[i];
    }
    balance_vector(T3);
    for (size_t i = 0; i < len; ++i) {
        res[i] = T2[i];
    }
    for (size_t i = len; i < 2 * len; ++i) {
        res[i] = T1[i - len];
    }
    for (size_t i = k; i < len + k; ++i) {
        res[i] += T3[i - k];
    }
    balance_vector(res);
    while (res.size() > old_len * 2) {
        res.pop_back();
    }
    return res;
}

BigInteger& BigInteger::operator*= (const BigInteger& other) {
    is_negative = is_negative != other.is_negative;
    std::vector<int> vec_R = other.buffer;
    size_t len = buffer.size() < vec_R.size() ? vec_R.size() : buffer.size();
    if (len % 2 == 1) {
        len++;
    }
    while (buffer.size() < len) {
        buffer.push_back(0);
    }
    while (vec_R.size() < len) {
        vec_R.push_back(0);
    }
    buffer = karatsuba_mul(buffer, vec_R);
    balance_vector(buffer);
    remove_first_zeros();
    return *this;
}

BigInteger operator* (const BigInteger& left, const BigInteger& right) {
    BigInteger result(left);
    result *= right;
    return result;
}

void BigInteger::shift_right() {
    if (*this == BigInteger(0)) {
        return;
    }
    buffer.push_back(buffer.back());
    for (size_t i = 0; i < buffer.size() - 2; ++i) {
        buffer[buffer.size() - 2 - i] = buffer[buffer.size() - 3 - i];
    }
    buffer[0] = 0;
}

BigInteger& BigInteger::operator/= (const BigInteger& other) {
    if (this == &other) {
        *this = BigInteger(1);
        return *this;
    }
    BigInteger right = other.is_negative ? -other : other;
    BigInteger current;
    for (size_t i = 0; i < buffer.size(); ++i) {
        current.shift_right();
        current.buffer[0] = buffer[buffer.size() - 1 - i];
        current.remove_first_zeros();
        int l = 0;
        int r = base;
        BigInteger j = BigInteger(10);
        BigInteger t;
        BigInteger one = BigInteger(10);
        while (l + 1 < r) {
            int m = (l + r) / 2;
            t = right * BigInteger(m);
            if ((t <= current)) {
                l = m;
            }
            else {
                r = m;
            }
        }
        buffer[buffer.size() - 1 - i] = l;
        current -= right * BigInteger(l);
    }
    is_negative = is_negative != other.is_negative;
    remove_first_zeros();
    return *this;
}

BigInteger operator/ (const BigInteger& left, const BigInteger& right) {
    BigInteger result(left);
    result /= right;
    return result;
}

BigInteger& BigInteger::operator%= (const BigInteger& other) {
    *this -= (*this / other) * other;
    return *this;
}

BigInteger operator% (const BigInteger& left, const BigInteger& right) {
    BigInteger result(left);
    result %= right;
    return result;
}

BigInteger::operator bool() const {
    return (buffer.back() != 0);
}
