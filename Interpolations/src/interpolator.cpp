#include "interpolator.h"

using namespace std;

Interpolator::Interpolator(int n, const gsl_interp_type *type) : N(n)
{
    this->xyGenerator(n);
    lagrange.upgradeToDegree(n);
    newton.upgradeToDegree(n);
    this->gsl = gsl_interp_alloc(type, n);
    gsl_interp_init(gsl, this->X.data(), this->Y.data(), n);
    gsl_lut = gsl_interp_accel_alloc();
}

void Interpolator::xyGenerator(int n){
    srand((unsigned int) time (NULL));
    this->X.clear();
    this->Y.clear();
    double x = -1;
    double dx = 2.0/(n-1);
    for(int i = 0; i<n; i++){
        this->X.push_back(x);
        this->Y.push_back(1/(1 - 25*x*x));
        x += dx;
    }
}

double Interpolator::dividedDifferences(int i1, int i2){
    if(i1 == i2)    return this->Y[i1];
    if(this->dd_lut.find(make_pair(i1,i2)) == this->dd_lut.end()){
        this->dd_lut[make_pair(i1,i2)] =    (this->dividedDifferences(i1+1,i2) - this->dividedDifferences(i1,i2-1))
                                            /(this->X[i2] - this->X[i1]);
    }
    return this->dd_lut[make_pair(i1,i2)];
}

void Interpolator::lagrangeInterpInit(){
    vector<double> product;
    for(int i = 0; i < this->N; ++i){
        product.clear();
        double a_n = this->Y[i];
        for(int j = 0; j < this->N; ++j){
            if(j != i){
                product.push_back(this->X[j]);
                a_n /= (this->X[i] - this->X[j]);
                //cout << "a_n: " << a_n << ", x_0: " << this->X[j] << ", x_i: " << this->X[i] << endl;
            }
        }
        Polynomial pp = Polynomial(a_n, product);
        //pp.print();
        lagrange += pp;
    }
}

double Interpolator::lagrangeInterpEval(double x){
    double res = 0.0;
    double x_power = 1.0;
    for(double a_i : this->lagrange.a){
        res += a_i * x_power;
        x_power *= x;
    }
    return res;
}

void Interpolator::newtonInterpInit(){
    vector<double> product;
    for(int i = 0; i < this->N; ++i){
        product.clear();
        double a_n = dividedDifferences(0, i);
        for(int j = 0; j < i; ++j){
            product.push_back(this->X[j]);
        }
        Polynomial pp = Polynomial(a_n, product);
        newton += pp;
    }
}

double Interpolator::newtonInterpEval(double x){
    double res = 0.0;
    double x_power = 1.0;
    for(double a_i : this->newton.a){
        res += a_i * x_power;
        x_power *= x;
    }
    return res;
}

double Interpolator::gslInterpEval(double x){
    return gsl_interp_eval(this->gsl, this->X.data(), this->Y.data(), x, this->gsl_lut);
}

void Interpolator::xyDump(){
    ofstream dump_file;
    dump_file.open("xy_dump.csv", ios::out | ios::trunc);
    dump_file << "x, y" << endl;
    for(int i = 0; i < this->N; ++i){
        dump_file << this->X[i] << "," << this->Y[i] << endl;
    }
    dump_file.close();
}

void Interpolator::dump(string s, double(Interpolator::*eval)(double)){
    ofstream dump_file;
    dump_file.open(s, ios::out | ios::trunc);
    dump_file << "x, f" << endl;
    double a = this->X[0], b = this->X[this->X.size()-1];
    double c = (b - a) / (this->N) / 10;
    for(; a < b; a += c){
        dump_file << a << "," << (*this.*eval)(a) << endl;
    }
    dump_file.close();
}

double Interpolator::lagrangeFormula(double x){
    double res = 0.0;
    for(int i = 0; i < this->N; ++i){
        double product = this->Y[i];
        for(int j = 0; j < this->N; ++j){
            if(j != i) product *= (x - this->X[j]) / (this->X[i] - this->X[j]);
        }
        res += product;
    }
    return res;
}

double Interpolator::newtonFormula(double x){
    double res = 0.0;
    for(int i = 0; i < this->N; ++i){
        double n = 1.0;
        for(int j = 0; j < i; ++j){
                n *= x - this->X[j];
        }
        res += n * this->dividedDifferences(0,i);;
    }
    return res;
}

void Interpolator::measureTime(string filename, string method, double(Interpolator::*func)(double)){
    ofstream output;
    output.open(filename, ios::out | ios::app);
    chrono::high_resolution_clock::time_point t1, t2;

    t1 = chrono::high_resolution_clock::now();
    (*this.*func)(this->Y[this->Y.size()-1]);
    t2 = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
    output << this->N << ", " << duration << ", " << method << endl;

    output.close();
}
