#include <iostream>
#include "rational.h"

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(int64_t x, int64_t y) : numerator_(x), denominator_(y) {
  Reduction();
}

Rational::Rational(int64_t x) : numerator_(x), denominator_(1) {
  Reduction();
}

void Rational::Reduction() {
  if (denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  int64_t n = std::__gcd(numerator_, denominator_);
  numerator_ /= n;
  denominator_ /= n;
  if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  }
}

int64_t Rational::GetNumerator() const {
  return numerator_;
}

int64_t Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(const int64_t& x) {
  numerator_ = x;
  Reduction();
}

void Rational::SetDenominator(const int64_t& x) {
  denominator_ = x;
  Reduction();
}

Rational& Rational::operator=(const Rational& other) {
  if (*this != other) {
    numerator_ = other.numerator_;
    denominator_ = other.denominator_;
  }
  return *this;
}

Rational& Rational::operator+=(const Rational& other) {
  numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
  denominator_ *= other.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
  denominator_ *= other.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  numerator_ *= other.numerator_;
  denominator_ *= other.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  numerator_ *= other.denominator_;
  denominator_ *= other.numerator_;
  Reduction();
  return *this;
}

Rational operator+(const Rational& other1, const Rational& other2) {
  auto tmp = other1;
  return tmp += other2;
}

Rational operator-(const Rational& other1, const Rational& other2) {
  auto tmp = other1;
  return tmp -= other2;
}

Rational operator*(const Rational& other1, const Rational& other2) {
  auto tmp = other1;
  return tmp *= other2;
}

Rational operator/(const Rational& other1, const Rational& other2) {
  auto tmp = other1;
  return tmp /= other2;
}

std::istream& operator>>(std::istream& is, Rational& x) {
  int64_t tmp;
  is >> tmp;
  x.SetNumerator(tmp);
  if (is.peek() == '/') {
    is.ignore(1);
    is >> tmp;
    x.SetDenominator(tmp);
  } else {
    x.SetDenominator(1);
  }
  x.Reduction();
  return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& x) {
  if (x.GetDenominator() == 1) {
    os << x.GetNumerator();
  } else {
    os << x.GetNumerator() << '/' << x.GetDenominator();
  }
  return os;
}

bool operator<(const Rational& other1, const Rational& other2) {
  auto result = other1 - other2;
  return result.GetNumerator() < 0;
}

Rational& Rational::operator++() {
  numerator_ += denominator_;
  Reduction();
  return *this;
}

Rational Rational::operator++(int) {
  auto other = *this;
  numerator_ += denominator_;
  Reduction();
  return other;
}

Rational& Rational::operator--() {
  numerator_ -= denominator_;
  Reduction();
  return *this;
}

Rational Rational::operator--(int) {
  auto other = *this;
  numerator_ -= denominator_;
  Reduction();
  return other;
}

bool operator>=(const Rational& other1, const Rational& other2) {
  auto result = other1 - other2;
  return result.GetNumerator() >= 0;
}

bool operator==(const Rational& other1, const Rational& other2) {
  auto result = other1 - other2;
  return result.GetNumerator() == 0;
}

bool operator>(const Rational& other1, const Rational& other2) {
  auto result = other1 - other2;
  return result.GetNumerator() > 0;
}

bool operator<=(const Rational& other1, const Rational& other2) {
  auto result = other1 - other2;
  return result.GetNumerator() <= 0;
}

bool operator!=(const Rational& other1, const Rational& other2) {
  auto result = other1 - other2;
  return result.GetNumerator() != 0;
}

Rational Rational::operator-() const {
  return Rational(-this->numerator_, this->denominator_);
}

Rational Rational::operator+() const {
  return *this;
}