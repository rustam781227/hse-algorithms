#include <iostream>
#include <string>
#include <vector>

class BigInteger {
public:

    BigInteger();

    BigInteger(int Int);

    explicit BigInteger(std::string str);

    BigInteger(const BigInteger& other);

    friend bool operator< (const BigInteger& left, const BigInteger& right);

    friend bool operator== (const BigInteger& left, const BigInteger& right);

    int& operator[] (size_t index);

    const int& operator[] (size_t index) const;

    size_t length() const;

    BigInteger& operator= (const BigInteger& other);

    BigInteger operator+ () const;

    BigInteger operator- () const;

    BigInteger& operator+= (const BigInteger& other);

    BigInteger& operator-=  (const BigInteger& other);

    const BigInteger operator++ (int);

    BigInteger& operator++ ();

    const BigInteger operator-- (int);

    BigInteger& operator-- ();

    BigInteger& operator*= (const BigInteger& other);

    BigInteger& operator/= (const BigInteger& other);

    BigInteger& operator%= (const BigInteger& other);

    std::string toString() const; // представление в виде строки

    operator bool() const;

    friend std::ostream& operator<< (std::ostream& out, const BigInteger& bi);

    friend std::istream& operator>> (std::istream& in, BigInteger& bi);

private:

    std::vector<int> buffer; // буфер(число в нашей системе счисления, порядок обратный)

    bool is_negative; // отрицательно ли число?

    static const int base = 10; // основание системы счисления

    void remove_first_zeros();  // удаление ведущих нулей

    void balance_vector(std::vector<int>& vec);

    std::vector<int> naive_mul(const std::vector<int>& left, const std::vector<int>& right);

    size_t len_for_naive_mul = 120;

    std::vector<int> karatsuba_mul(std::vector<int>& left, std::vector<int>& right);

    void shift_right(); // сдвиг буфера вправо
};