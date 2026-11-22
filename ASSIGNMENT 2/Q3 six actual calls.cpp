#include <iostream>
#include <string>
struct Parcel { double kg; bool express; bool insured; };
double charge(double kg, bool express=false, bool insured=false) {
    return kg*50 + (express?30:0) + (insured?20:0);
}
double charge(int grams) { return charge(grams/1000.0); }
double charge(const Parcel& p) { return charge(p.kg,p.express,p.insured); }
int main() {
    Parcel p{3.0,true,true};
    std::cout << charge(2) << '\n';
    std::cout << charge(2.0f) << '\n';
    std::cout << charge(2.0) << '\n';
    std::cout << charge(2.0,true) << '\n';
    std::cout << charge(2.0,true,true) << '\n';
    std::cout << charge(p) << '\n';
}
