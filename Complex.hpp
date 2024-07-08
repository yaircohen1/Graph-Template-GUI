// coheny405@gmail.com
#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <ostream>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double real, double imag);

    // Copy constructor
    Complex(const Complex& other);

    // Destructor
    ~Complex();

    
    Complex& operator=(const Complex& other);
    Complex operator+(const Complex& other) const;    
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    bool operator<(const Complex& other) const;
    bool operator>(const Complex& other) const;
    bool operator<=(const Complex& other) const;
    bool operator>=(const Complex& other) const;

    double getReal() const;
    double getImag() const;
   
    void setReal(double real);
    void setImag(double imag);

    // Function to convert the complex number to a string
    std::string toString() const;

    // Operator overloading for the << operator
    friend std::ostream& operator <<(std::ostream& os, const Complex& complex);



};