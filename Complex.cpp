// coheny405@gmail.com
#include "Complex.hpp"
#include <sstream>


Complex::Complex(double real, double imag) : real(real), imag(imag) {} 

Complex::Complex(const Complex& other) : real(other.real), imag(other.imag) {}

Complex::~Complex() {}  

Complex& Complex::operator=(const Complex& other) {
    if (this != &other) {
        real = other.real;
        imag = other.imag;
    }
    return *this; // Return the object itself
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    return Complex((real * other.real + imag * other.imag) / denominator, (imag * other.real - real * other.imag) / denominator);
}

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    imag -= other.imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double tempReal = real;
    real = real * other.real - imag * other.imag;
    imag = tempReal * other.imag + imag * other.real;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double tempReal = real;
    double denominator = other.real * other.real + other.imag * other.imag;
    real = (real * other.real + imag * other.imag) / denominator;
    imag = (imag * other.real - tempReal * other.imag) / denominator;
    return *this;
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

bool Complex::operator<(const Complex& other) const {
    return real < other.real || (real == other.real && imag < other.imag);
}

bool Complex::operator>(const Complex& other) const {
    return real > other.real || (real == other.real && imag > other.imag);
}

bool Complex::operator<=(const Complex& other) const {
    return !(*this > other);
}

bool Complex::operator>=(const Complex& other) const {
    return !(*this < other);
}

double Complex::getReal() const {
    return real;
}

double Complex::getImag() const {
    return imag;
}

void Complex::setReal(double real) {
    this->real = real;
}

void Complex::setImag(double imag) {
    this->imag = imag;
}

std::string Complex::toString() const {
     std::ostringstream oss;
        oss << real<< (imag >= 0 ? "+" : "") << imag << "i";
        return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Complex& complex) {
    os << complex.toString();
    return os;
}

