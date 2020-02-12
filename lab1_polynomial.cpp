#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <math.h>

#include "lab1_polynomial.hpp"
using namespace std;

Polynomial::Polynomial(int A[], int size)
{ // creating a new array with same values as array A
    data.resize(size);
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = A[i];
    }
}
Polynomial::Polynomial(int size)
{ // creating a new array with same values as array A
    data.resize(size);
}
Polynomial::Polynomial()
{ // creating a new random array with random size and random coefficients

    srand(time(0));
    int rand_size = rand() % 1001;
    data.resize(rand_size);

    for (int i = 0; i < rand_size; i++)
    {
        int rand_value = (rand() % 2001) - 1000;
        data[i] = rand_value;
    }
}
Polynomial::Polynomial(string fileName)
{
    ifstream infile;
    infile.open(fileName);

    int file_size;
    infile >> file_size;
    data.resize(file_size);

    // Check for error
    if (infile.fail())
    {
        cerr << "Error opening file" << endl; // C error (special output for errors)
        exit(1);
    }

    for (int i = 0; i < data.size(); i++)
    {
        infile >> data[i];
    }

    infile.close();
}

bool Polynomial::operator==(const Polynomial &target)
{
    if (data.size() == target.data.size()) // Checks if the degree of polynomial is the same
    {
        for (int i = 0; i < target.data.size(); i++)
        {
            if (data[i] != target.data[i])
                return false;
        }
        return true;
    }
    else
        return false;
}

Polynomial Polynomial::operator+(const Polynomial &target) // performs *this + target (data.size is assumed)
{
    int maxSize = max(data.size(), target.data.size());
    Polynomial polynomial_sum;
    polynomial_sum.data.resize(maxSize);
    Polynomial biggest;
    Polynomial smallest;

    if (data.size() >= target.data.size())
    {
        Polynomial biggest = *this;
        Polynomial smallest = target;
    }
    if (target.data.size() > data.size())
    {
        Polynomial biggest = target;
        Polynomial smallest = *this;
    }

    for (int i = 0; i < smallest.data.size(); i++)
    {
        polynomial_sum.data[i] = target.data[i] + data[i];
    }

    for (int i = smallest.data.size(); i < biggest.data.size(); i++)
    {
        polynomial_sum.data[i] = biggest.data[i];
    }
    return polynomial_sum;
}

Polynomial Polynomial::operator-(const Polynomial &target) // performs *this + target
{
    int maxSize = max(data.size(), target.data.size());
    Polynomial polynomial_diff;
    polynomial_diff.data.resize(maxSize);
    Polynomial biggest;
    Polynomial smallest;

    if (data.size() >= target.data.size())
    {
        Polynomial biggest = *this;
        Polynomial smallest = target;
    }
    if (target.data.size() > data.size())
    {
        Polynomial biggest = target;
        Polynomial smallest = *this;
    }

    for (int i = 0; i < smallest.data.size(); i++)
    {
        polynomial_diff.data[i] = data[i] - target.data[i];
    }

    if (data.size() >= target.data.size()) // if first array ( *this) is bigger than left over is positive
    {
        for (int i = smallest.data.size(); i < biggest.data.size(); i++)
        {
            polynomial_diff.data[i] = biggest.data[i];
        }
    }
    if (target.data.size() > data.size()) // if second array (target) is bigger than left over is negative
    {
        for (int i = smallest.data.size(); i < biggest.data.size(); i++)
        {
            polynomial_diff.data[i] = -biggest.data[i];
        }
    }
    return polynomial_diff;
}

Polynomial Polynomial::operator*(const Polynomial &target) // performs *this * target
{
    Polynomial polynomial_prod(data.size() + (target.data).size() - 1);

    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < target.data.size(); j++)
        {
            polynomial_prod.data[i + j] += data[i] * target.data[j]; // += bc we want to add the value to the existed number at that index
        }
    }
    return polynomial_prod;
}

Polynomial Polynomial::derivative() // performs *this
{
    Polynomial polynomial_prod(data.size() - 1);
    if (data.size() > 0)
    {
        for (int i = 1; i < data.size(); i++)
        {

            polynomial_prod.data[i - 1] = i * (data[i]);
        }
        return polynomial_prod;
    }
    else
    {
        return polynomial_prod;
    }
}
void Polynomial::print()
{ //should print function have parameters passed to it
    for (int i = data.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            cout << data[i] << endl;
        }

        else if (i == 1)
        {
            cout << "(" << data[i] << "x"
                 << ")"
                 << " + ";
        }

        else
        {
            cout << "(" << data[i] << "x^" << i << ")"
                 << " + ";
        }
    }
}

class PolynomialTest
{
    // within this class we want to test every single function to verify its working
    // we also want to test special cases such as: empty polynomial, negative exponents, and so on
public:
    void test_constructor1() // Visual tesitng
    {
        cout << " " << endl;
        cout << "---- Test for Constructor 1 ( copy constructor )----" << endl;

        // case 1: sending in normal array
        // - verifying they are of the same size
        // - verifying they have the same values
        cout << " " << endl;
        cout << "Case #1:" << endl;
        int array1_1[3] = {4, 2, 6};
        Polynomial test1_1(array1_1, 3);

        cout << "Expected Output: " << endl;
        cout << "(6x^2) + (2x) + 4" << endl;
        cout << "Test Output: " << endl;
        test1_1.print();

        // case 2: sending in empty array
        // - verifying they are of the same size
        // - verifying they have the same values
        cout << " " << endl;
        cout << "Case #2:" << endl;
        int array1_2[] = {};
        Polynomial test1_2(array1_2, 0);

        cout << "Expected Output: " << endl;
        cout << "Test Output: " << endl;
        test1_2.print();

        // case 3: with some 0 coefficients

        cout << " " << endl;
        cout << "Case #3:" << endl;
        int array1_3[] = {4, 0, 1, 3};
        Polynomial test1_3(array1_3, 4);

        cout << "Expected Output: " << endl;
        cout << "(3x^3) + (1x^2) + (0x) + 4 " << endl;
        cout << "Test Output: " << endl;
        test1_3.print();
        cout << " " << endl;
    }

    void test_constructor2() // Assertions
    {
        cout << " " << endl;
        cout << "---- Test for Constructor 2 ( random array ) ----" << endl;

        // case 1:  tests to make sure random array size is within range 1 - 1000

        Polynomial test2_1;
        cout << "Case #1:" << endl;

        assert(test2_1.data.size() > 0 && test2_1.data.size() < 1001);
        cout << "test_constructor2_1 passed" << endl;

        cout << " " << endl;

        // case 2:  tests to make sure values are between -1000 and 1000
        cout << "Case #2:" << endl;

        for (int i = 0; i < test2_1.data.size(); i++)
        {
            assert(test2_1.data[i] <= 1000 && test2_1.data[i] >= -1000);
        }
        cout << "test_constructor2_2 passed" << endl;
    }

    void test_constructor3() // Visual Testing
    {
        cout << " " << endl;
        cout << "---- Test for Constructor 3 ( polynomial from file ) ----" << endl;
        // case 1: input values from file

        cout << " " << endl;
        cout << "Case #1:" << endl;
        Polynomial test3_1("text3_1.txt");

        cout << "Expected Output: " << endl;
        cout << "(7x^2) + (2x) + 4 " << endl;
        cout << "Test Output: " << endl;
        test3_1.print();

        // case 2: input negative exponents from file (should fail)

        cout << " " << endl;
        cout << "Case #2:" << endl;
        Polynomial test3_2("text3_2.txt");

        cout << "Expected Output: " << endl;
        cout << "(5x^2) + (3x) + 1 " << endl; // ignores negative values
        cout << "Test Output: " << endl;
        test3_2.print();
    }

    void test_operator_equals()
    {
        cout << " " << endl;
        cout << "---- Test for Operator Equals ----" << endl;

        int A1[3] = {4, 2, 6};
        Polynomial P1(A1, 3);

        int A2[3] = {4, 2, 6};
        Polynomial P2(A2, 3);

        int A3[4] = {4, 2, 8, 9};
        Polynomial P3(A3, 4);

        int A4[3] = {1, 9, 5};
        Polynomial P4(A4, 3);

        // case 1: tests two equal polynomials
        assert(P1 == P2);
        cout << "Case 1: test for equal operator passed" << endl;

        // case 2: tests two polynomials that are not equal
        assert(!(P1 == P3));
        cout << "Case 2: test for equal operator passed" << endl;

        // case 3: tests polynomials with different numbers but same size
        assert(!(P1 == P4));
        cout << "Case 3: test for equal operator passed" << endl;
    }

    void test_operator_add()
    {
        cout << " " << endl;
        cout << "---- Test for Operator Addition ----" << endl;

        int A1[3] = {4, 1, 3};
        Polynomial P1(A1, 3);

        int A2[3] = {4, 5, 2};
        Polynomial P2(A2, 3);

        int A3[4] = {1, 2, 3, 5};
        Polynomial P3(A3, 4);

        int A12sum[3] = {8, 6, 5};
        Polynomial P12sum(A12sum, 3);

        int A13sum[4] = {5, 3, 6, 5};
        Polynomial P13sum(A13sum, 4);

        // case 1: add two polynomials of the same size
        assert((P1 + P2) == P12sum);
        cout << "Case #1: test for addition operator passed" << endl;

        // case 2: add two polynomials, first smaller second polynomial larger
        assert((P1 + P3) == P13sum);
        cout << "Case #2: test for addition operator passed" << endl;

        // case 3: add two polynomials, first larger second polynomial smaller
        assert((P3 + P1) == P13sum);
        cout << "Case #3: test for addition operator passed" << endl;
    }

    void test_operator_minus()
    {
        cout << " " << endl;
        cout << "---- Test for Operator Subtraction ----" << endl;

        int A1[3] = {4, 1, 3};
        Polynomial P1(A1, 3);

        int A2[3] = {3, 1, 2};
        Polynomial P2(A2, 3);

        int A3[4] = {1, 2, 3, 5};
        Polynomial P3(A3, 4);

        int A12sum[3] = {1, 0, 1};
        Polynomial P12sum(A12sum, 3);

        int A13sum[4] = {3, -1, 0, -5};
        Polynomial P13sum(A13sum, 4);

        int A14sum[4] = {-3, 1, 0, 5};
        Polynomial P14sum(A14sum, 4);

        // case 1: add two polynomials of the same size
        assert((P1 - P2) == P12sum);
        cout << "Case #1: test for addition operator passed" << endl;

        // case 2: add two polynomials, first smaller second polynomial larger
        assert((P1 - P3) == P13sum);
        cout << "Case #2: test for addition operator passed" << endl;

        // case 3: add two polynomials, first larger second polynomial smaller
        assert((P3 - P1) == P14sum);
        cout << "Case #3: test for addition operator passed" << endl;
    }

    void test_operator_prod()
    {
        cout << " " << endl;
        cout << "---- Test for Operator Multiplication ----" << endl;
        // case 1: multiply two polynomials (same size)
        int p1Test1Array[2] = {4, 5};
        int p2Test1Array[2] = {9, 10};
        int multiplyTest1Array[3] = {36, 85, 50};

        Polynomial p1T1(p1Test1Array, 2);
        Polynomial p2T1(p2Test1Array, 2);
        Polynomial multiplyT1(multiplyTest1Array, 3);

        assert((p1T1 * p2T1) == multiplyT1);
        cout << "Case 1: test for the multiplication operator passed" << endl;
        assert((p1T1 * p2T1).data.size() == 3);
        cout << "Case 1.2: for the multiplication operator passed" << endl;

        // case 2: difference of squares

        int p1Test2Array[2] = {4, 5};
        int p2Test2Array[2] = {4, 5};
        int multiplyTest2Array[3] = {16, 40, 25};

        Polynomial p1T2(p1Test2Array, 2);
        Polynomial p2T2(p2Test2Array, 2);
        Polynomial multiplyT2(multiplyTest2Array, 3);
        assert((p1T2 * p2T2) == multiplyT2);
        cout << "Case 2: test for the multiplication operator passed" << endl;
        assert((p1T2 * p2T2).data.size() == 3);
        cout << "Case 2.1: test for the multiplication operator passed" << endl;
    }

    void test_operator_derivative()
    {
        cout << " " << endl;
        cout << "---- Test for Operator Derivative ----" << endl;

        int p1Test1Array[4] = {4, 5, 0, 8};
        Polynomial P1T1(p1Test1Array, 4);
        int derivativeTest1Array[3] = {5, 0, 24};
        Polynomial DT1(derivativeTest1Array, 3);

        // case 1: check derivative of same polynomial size
        assert((P1T1.derivative()) == DT1);
        cout << "Case 1: for the derivative operator passed" << endl;
    }

    void test_print()
    {
        cout << " " << endl;
        cout << "---- Test for Print Function ----" << endl;
        int A1[3] = {4, 2, 6};
        Polynomial P1(A1, 3);

        int A2[0] = {};
        Polynomial P2(A2, 0);

        int A3[6] = {4, 2, 0, 9, 1, 3};
        Polynomial P3(A3, 6);

        // case 1: print a polynomial
        cout << " " << endl;
        cout << "Case #1:" << endl;
        cout << "Expected Output: " << endl;
        cout << "(6x^2) + (2x) + 4" << endl;
        cout << "Test Output: " << endl;
        P1.print();

        // case 2: print empty polynomial
        cout << " " << endl;
        cout << "Case #2:" << endl;
        cout << "Expected Output: " << endl;
        cout << "Test Output: " << endl;
        P2.print();

        // case 3: print array with 0s
        cout << " " << endl;
        cout << "Case #3:" << endl;
        cout << "Expected Output: " << endl;
        cout << "(3x^5) + (1x^4) + (9x^3) + (0x^2) + (2x) + 4 " << endl;
        cout << "Test Output: " << endl;
        P3.print();
    }

    void run()
    {
        test_constructor1();
        cout << "Finished Test for Constructors1. All tests Passed" << endl;
        test_constructor2();
        cout << "Finished Test for Constructors2. All tests Passed" << endl;
        test_constructor3();
        cout << "Finished Test for Constructors3. All tests Passed" << endl;
        test_operator_equals();
        cout << "Finished Test for Equals Operator. All tests Passed" << endl;
        test_operator_add();
        cout << "Finished Test for Addition Operator. All tests Passed" << endl;
        test_operator_minus();
        cout << "Finished Test for Subtraction Operator. All tests Passed" << endl;
        test_operator_prod();
        cout << "Finished Test for Multiplication Operator. All tests Passed" << endl;
        test_operator_derivative();
        cout << "Finished Test for Derivative Operator. All tests Passed" << endl;
        test_print();
        cout << "Finished Test for Print Function. All tests Passed" << endl;
    }
};

int main()
{
    PolynomialTest my_test;
    my_test.run();
}