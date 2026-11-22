#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;
class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}
    explicit Complex(double r) : re(r), im(0) {}
    Complex(double r, double i) : re(r), im(i) {}
    Complex operator+(const Complex& z) const {
        return Complex(re+z.re, im+z.im);
    }
    Complex operator-(const Complex& z) const {
        return Complex(re-z.re, im-z.im);
    }
    Complex operator*(const Complex& z) const {
        return Complex(re*z.re-im*z.im, re*z.im+im*z.re);
    }
    Complex operator/(const Complex& z) const {
        double d=z.re*z.re+z.im*z.im;
        if (d==0.0) throw domain_error("Division by zero impedance");
        return Complex((re*z.re+im*z.im)/d,
                       (im*z.re-re*z.im)/d);
    }
    bool operator==(const Complex& z) const {
        return re==z.re && im==z.im;
    }
    double magnitude() const { return hypot(re, im); }
    friend ostream& operator<<(ostream& os, const Complex& z) {
        return os << z.re << (z.im<0 ? " - j" : " + j") << fabs(z.im);
    }
};
int main() {
    const double w=100.0;
    const double R=10.0, L=0.2, C=0.001;
    Complex zr(R), zl(0,w*L), zc(0,-1/(w*C));
    Complex series = zr+zl+zc;
    Complex parallel = (zr*zl)/(zr+zl); // R parallel L, valid example
    cout << "Series RLC: " << series
         << ", |Z|=" << series.magnitude() << '\n';
    cout << "Parallel R-L: " << parallel
         << ", |Z|=" << parallel.magnitude() << '\n';
    try { cout << zr/Complex() << '\n'; }
    catch (const domain_error& e) { cout << e.what() << '\n'; }
}
