#include "polynomial.h"

using namespace std;

void Polynomial::upgradeToDegree(int new_degree){
    for(int i = this->degree; i < new_degree; ++i){
        this->a.push_back(0.0);
    }
    this->degree = new_degree;
}

Polynomial::Polynomial(double an, vector<double> &args) : Polynomial(args){
    this->a.push_back(an);
    this->degree++;
    int sign = -1;
    for(int i = args.size() - 1; i >= 0; --i){
        this->a[i] = sign * an * vieteFactor(args, 0, args.size(), args.size()-i);
        //cout << "a[" << i << "]: " << vieteFactor(args, 0, args.size(), args.size()-i) << endl;
        sign *= -1;
    }
}

double vieteFactor(vector<double> &args, int begin, int end, int elem){
    int res = 0;
    if(elem > 1){
        for(int i = begin, j = end+1-elem; i < j; ++i){
            //cout << res << " + args[" << i << "] * f(args, " << i+1 << ", " << end << ", " << elem-1 << ")" << endl;
            res += args[i] * vieteFactor(args, i+1, end, elem-1);
        }
    }
    else{
        for(int i = begin; i < end; ++i){
            //cout << res << " + args[" << i << "]" << endl;
            res += args[i];
        }
    }
    return res;
}

void Polynomial::print(){
    int nr = 0;
    for(double x : this->a){
        cout << "a_" << nr << " = " << x << endl;
        nr++;
    }
}

Polynomial Polynomial::operator+=(const Polynomial &pp){
    if(this->degree < pp.degree){
        this->upgradeToDegree(pp.degree);
    }
    for(unsigned int i = 0; i < pp.a.size(); ++i){
        this->a[i] += pp.a[i];
    }
    return *this;
}

const Polynomial Polynomial::operator+(const Polynomial &pp) const{
    return Polynomial(*this) += pp;
}
