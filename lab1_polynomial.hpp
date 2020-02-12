#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Polynomial
{
    vector<int> data; //size already inside vector

public:
    Polynomial(int A[], int size);
    Polynomial(int size);
    Polynomial();
    Polynomial(string fileName);

    bool operator==(const Polynomial &target);
    Polynomial operator+(const Polynomial &target);
    Polynomial operator-(const Polynomial &target);
    Polynomial operator*(const Polynomial &target);
    Polynomial derivative();
    void print();

    friend class PolynomialTest;
};
#endif