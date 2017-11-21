#include <iostream>
#include <string>
#include "polynomial.h"
#include "interpolator.h"

using namespace std;

int main()
{
    /*Interpolator test = Interpolator(11);
    test.xyDump();
    test.lagrangeInterpInit();
    test.dump("lagrange_dump.csv", Interpolator::lagrangeInterpEval);
    test.newtonInterpInit();
    test.dump("newton_dump.csv", Interpolator::newtonInterpEval);
    test.dump("gsl_dump.csv", Interpolator::gslInterpEval);*/


    //3 methods comparison


    /*string l = "lagrange", n = "newton", g = "gsl", path = "times.csv";
    ofstream file;
    file.open(path);
    file << "size, time, method" << endl;
    file.close();
    for(int i = 100; i < 201; ++i){
        Interpolator probe = Interpolator(i);
        for(int j = 0; j < 10; ++j){
            probe.measureTime(path, l, Interpolator::lagrangeFormula);
            probe.measureTime(path, n, Interpolator::newtonFormula);
            probe.measureTime(path, g, Interpolator::gslInterpEval);
        }
    }*/


    //3 gsl methods

    /*string p = "poly", c = "cspline", a = "akima", path = "times2.csv";
    ofstream file;
    file.open(path);
    file << "size, time, method" << endl;
    file.close();

    Interpolator    poly = Interpolator(100),
                    cspline = Interpolator(100, gsl_interp_cspline),
                    akima = Interpolator(100, gsl_interp_akima);

    poly.dump("gsl_poly.csv", Interpolator::gslInterpEval);
    cspline.dump("gsl_cspline.csv", Interpolator::gslInterpEval);
    akima.dump("gsl_akima.csv", Interpolator::gslInterpEval);


    //3 gsl methods comparison


    for(int i = 1000; i < 2001; i += 10){
        Interpolator probe1 = Interpolator(i);
        Interpolator probe2 = Interpolator(i, gsl_interp_cspline);
        Interpolator probe3 = Interpolator(i, gsl_interp_akima);
        for(int j = 0; j < 10; ++j){
            probe1.measureTime(path, p, Interpolator::gslInterpEval);
            probe2.measureTime(path, c, Interpolator::gslInterpEval);
            probe3.measureTime(path, a, Interpolator::gslInterpEval);
        }
    }*/
    return 0;
}
