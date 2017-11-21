#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <vector>
#include <numeric>
#include <functional>
#include <iostream>

using namespace std;
double vieteFactor(vector<double>&, int, int, int);

class Interpolator;

class Polynomial
{
    public:
        Polynomial(vector<double> args) : a(args) { degree = args.size() - 1;}
        Polynomial(double, vector<double>&);
        void upgradeToDegree(int);
        void print();
        Polynomial operator+=(const Polynomial &);
        const Polynomial operator+(const Polynomial &) const;

    protected:

    private:
        int degree;
        vector<double> a;
        friend Interpolator;
};

#endif // POLYNOMIAL_H
