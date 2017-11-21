#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <gsl/gsl_interp.h>
#include "polynomial.h"

using namespace std;

class Interpolator
{
    public:
        Interpolator(int, const gsl_interp_type * = gsl_interp_polynomial);
        ~Interpolator(){ gsl_interp_free(this->gsl); gsl_interp_accel_free(this->gsl_lut);}
        double dividedDifferences(int, int);
        void lagrangeInterpInit();
        double lagrangeInterpEval(double);
        void newtonInterpInit();
        double newtonInterpEval(double);
        double gslInterpEval(double);
        void xyDump();
        void dump(string, double(Interpolator::*)(double));
        double lagrangeFormula(double);
        double newtonFormula(double);
        void measureTime(string, string, double(Interpolator::*)(double));

    protected:

    private:
        int N;
        vector<double> X;
        vector<double> Y;
        gsl_interp* gsl;
        gsl_interp_accel* gsl_lut;
        Polynomial lagrange = Polynomial({0});
        Polynomial newton = Polynomial({0});
        map<pair<int, int>, double> dd_lut;
        void xyGenerator(int);
};

#endif // INTERPOLATOR_H
