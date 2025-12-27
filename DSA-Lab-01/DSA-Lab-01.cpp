/*
Task 1: Polynomial ADT in C++ 
A polynomial is an equation of the form: P(x) = a0xe0 + a1xe1 + … +anxen      
where ai 
belongs to Coefficient ei belongs to Exponent.  Your target is to store this form of 
equation in Computer and be able to perform the operations listed below.  
Selection of data members for this ADT is upto you but you should be able to justify the 
need of all data members.  
You should always implement the Def-Ctor/Copy-Ctor/Dtor/= methods in case of 
dynamic memory allocation to class data members. 
While coding keep in mind the concept behind Problem Solving Guidelines and basic 
principles that we studied in OOP and also take care of Coding Convention. You must 
also use exception handling mechanism wherever needed. 
Public Functions 
1. 
Ctor 
Constructor method to initialize the Polynomial object. 
2. 
addTerm(coefficient, power) 
Add a new term xpower term in the polynomial and set its coefficient. 
3. 
getDegree()  
Returns the degree of a polynomial. For example, when p1 = 4x5 + 7x3 - x2 + 9, p1 
degree is 5. 
4. 
getCoefficient(power)  
Returns the coefficient of the x power term. For example, when p1 = 4x5 + 7x3 - x2 + 9 
p1.getCoefficient (3) is 7 
5. 
operator(value)  
For example, given a polynomial in "p1", p1(x) will evaluate the polynomial for the 
given value of x.  
6. Dtor / Copy-Ctor / = 
7. 
Arithmetic Operation +  
Add two polynomials. For instance, assuming p1 = 4x5 + 7x3 - x2 + 9 and p2 = 6x4 + 3x2 
+ 2x, then the answer of p1 + p2 must be 4x5 + 6x4 + 7x3 + 2x2 + 2x + 9.  
8. 
derivative()  
Return a polynomial that is the derivative of the given polynomial. For instance, 
assuming p1 = 4x5 + 7x3 - x2 + 9, the derivative polynomial would be 20x4 + 21x2 - 2x. 
9. 
antiDerivative()  
Return a polynomial that is the anti-derivative of the given polynomial. For instance, 
assuming p1 = 20x4 + 21x2 - 2x, the derivative polynomial would be 4x5 + 7x3 - x2 + C, 
Where C is a random constant value.  
10. 
addToCoefficient(coefficient, power)  
Adds the given amount to the coefficient of the xpower term. For example, if  p1 = 20x4 
+ 21x2 - 2x,  then p1.addToCoefficient (2.5, 3) changes the coefficient of x3 to 9.5 
11.  
clear()  
Set the coefficient of all terms in the polynomial to zero. 
12. 
setCoefficient(newCoefficient, power)  
Sets the coefficient of the xpower term with newCoeffcient. For instance, 
p1.setCoefficient (-3, 7) produces the polynomial p1 = -3x7 + 4x5 + 7x3 - x2 + 9. Note that 
if the term does not exist in the polynomial, it is added. 
13. 
Arithmetic Operations *, - 
Perform multiplication and subtraction of two polynomials. 
14. ostream& operator<<(ostream &out, const Polynomial &p) 
Used with Polynomial objects to display their string representations. For example 
20x4 + 21x2 - 2x will be displayed in the following format 20x^4 + 21x^2 +  -2^x
*/
#include <iostream>
#include <stdexcept>
using namespace std;

class Polynomial {
protected:
    int a[100];   // coefficients
    int exp[100]; // exponents
    int asize;    // number of terms

public:
    // Default Constructor
    Polynomial() {
        asize = 0;
        for (int i = 0; i < 100; i++) {
            a[i] = 0;
            exp[i] = 0;
        }
    }

    // Parameterized Constructor
    Polynomial(int c, int p) {
        asize = 1;
        a[0] = c;
        exp[0] = p;
        for (int i = 1; i < 100; i++) {
            a[i] = 0;
            exp[i] = 0;
        }
    }

    // Copy Constructor
    Polynomial(const Polynomial &other) {
        asize = other.asize;
        for (int i = 0; i < asize; i++) {
            a[i] = other.a[i];
            exp[i] = other.exp[i];
        }
    }

    // Destructor
    ~Polynomial() {
        cout << "Object Destroyed" << endl;
    }

    // Add Term
    void addTerm(int c, int p) {
        if (asize >= 100) throw runtime_error("Insufficient Memory");

    // check if exponent already exists
    for (int i = 0; i < asize; i++) {
        if (exp[i] == p) {
            a[i] += c; // combine coefficients
            return;
        }
    }

    // otherwise add new term
    a[asize] = c;
    exp[asize] = p;
    asize++;

    }

    // Get Degree
    int getDegree() const {
        int max = 0;
        for (int i = 0; i < asize; i++) {
            if (exp[i] > max) max = exp[i];
        }
        return max;
    }

    // Get Coefficient of x^p
    int getCoefficient(int p) const {
        for (int i = 0; i < asize; i++) {
            if (exp[i] == p) return a[i];
        }
        return 0; // if not found
    }

    // Set Coefficient
    void setCoefficient(int newC, int p) {
        for (int i = 0; i < asize; i++) {
            if (exp[i] == p) {
                a[i] = newC;
                return;
            }
        }
        addTerm(newC, p);
    }

    // Add to Coefficient
    void addToCoefficient(int c, int p) {
        for (int i = 0; i < asize; i++) {
            if (exp[i] == p) {
                a[i] += c;
                return;
            }
        }
        addTerm(c, p);
    }

    // Clear polynomial
    void clear() {
        for (int i = 0; i < 100; i++) {
            a[i] = 0;
            exp[i] = 0;
        }
        asize = 0;
    }

    // Evaluate polynomial at x        Is mien "e" evaluate nhi ho raha
    int operator()(int x) const {
        int result = 0;
        for (int i = 0; i < asize; i++) {
            int term = a[i];
            for (int j = 0; j < exp[i]; j++) 
            {
                term *= x;
                result += term;
            }    
        }
        return result;
    }

    // Assignment operator
    Polynomial& operator=(const Polynomial &other) {
        if (this != &other) {
            asize = other.asize;
            for (int i = 0; i < asize; i++) {
                a[i] = other.a[i];
                exp[i] = other.exp[i];
            }
        }
        return *this;
    }

    // Addition        
    Polynomial operator+(const Polynomial &rhs) const {
        Polynomial res = *this;
        for (int i = 0; i < rhs.asize; i++) {
            res.addToCoefficient(rhs.a[i], rhs.exp[i]);
        }
        return res;
    }

    // Subtraction         Is mien bhi ghalti hai
    Polynomial operator-(const Polynomial &rhs) const {
        Polynomial res = *this;
        for (int i = 0; i < rhs.asize; i++) {
            res.addToCoefficient(-rhs.a[i], rhs.exp[i]);
        }
        return res;
    }

    // Multiplication
    Polynomial operator*(const Polynomial &rhs) const {
        Polynomial res;
        for (int i = 0; i < asize; i++) {
            for (int j = 0; j < rhs.asize; j++) {
                res.addToCoefficient(a[i] * rhs.a[j], exp[i] + rhs.exp[j]);
            }
        }
        return res;
    }

    // Derivative
    Polynomial derivative() const {
        Polynomial res;
        for (int i = 0; i < asize; i++) {
            if (exp[i] > 0)
                res.addTerm(a[i] * exp[i], exp[i] - 1);
        }
        return res;
    }

    // Anti-derivative
    Polynomial antiDerivative() const {
        Polynomial res;
        for (int i = 0; i < asize; i++) {
            res.addTerm(a[i] / (exp[i] + 1), exp[i] + 1);
        }
        res.addTerm(1, 0); // constant C
        return res;
    }

    // Output operator
    friend ostream& operator<<(ostream &out, const Polynomial &p) {
        for (int i = 0; i < p.asize; i++) {
            if (p.a[i] != 0) {
                if (i > 0 && p.a[i] > 0) out << " + ";
                else if (p.a[i] < 0) out << " - ";
                out << abs(p.a[i]) << "x^" << p.exp[i];
            }
        }
        return out;
    }
};

// ---------------- MAIN ----------------
int main() {
    Polynomial p1(8, 4);
    p1.addTerm(7, 3);
    p1.addTerm(6, 2);
    p1.addTerm(5, 1);

    cout << "p1 = " << p1 << endl;
    cout << "Degree of p1: " << p1.getDegree() << endl;
    cout << "Coefficient of x^2: " << p1.getCoefficient(2) << endl;
    cout << "p1(2) = " << p1(2) << endl;

    Polynomial p2(5, 3);
    p2.addTerm(4, 2);
    p2.addTerm(3, 1);
    p2.addTerm(2, 0);

    cout << "p2 = " << p2 << endl;

    Polynomial p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;

    Polynomial p4 = p1 - p2;
    cout << "p1 - p2 = " << p4 << endl;

    Polynomial p5 = p1 * p2;
    cout << "p1 * p2 = " << p5 << endl;

    Polynomial dp1 = p1.derivative();
    cout << "Derivative of p1 = " << dp1 << endl;

    Polynomial ap1 = p1.antiDerivative();
    cout << "Antiderivative of p1 = " << ap1 << endl;

    return 0;
}


