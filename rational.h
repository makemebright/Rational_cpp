#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdexcept>
#include <algorithm>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
  int64_t numerator_;
  int64_t denominator_;

 public:
  Rational();

  Rational(int64_t x, int64_t y);

  Rational(int64_t x);  // NOLINT

  int64_t GetNumerator() const;

  int64_t GetDenominator() const;

  void Reduction();

  void SetNumerator(const int64_t& x);

  void SetDenominator(const int64_t& x);

  Rational& operator=(const Rational& other);

  Rational& operator+=(const Rational& other);

  Rational& operator-=(const Rational& other);

  Rational& operator*=(const Rational& other);

  Rational& operator/=(const Rational& other);

  Rational operator-() const;

  Rational operator+() const;

  Rational& operator++();

  Rational& operator--();

  Rational operator++(int);

  Rational operator--(int);
};

Rational operator/(const Rational& other1, const Rational& other2);

Rational operator*(const Rational& other1, const Rational& other2);

std::istream& operator>>(std::istream& is, Rational& x);

std::ostream& operator<<(std::ostream& os, const Rational& x);

bool operator<(const Rational& other1, const Rational& other2);

bool operator>(const Rational& other1, const Rational& other2);

bool operator==(const Rational& other1, const Rational& other2);

bool operator<=(const Rational& other1, const Rational& other2);

bool operator>=(const Rational& other1, const Rational& other2);

bool operator!=(const Rational& other1, const Rational& other2);

Rational operator+(const Rational& other1, const Rational& other2);

Rational operator-(const Rational& other1, const Rational& other2);

#endif