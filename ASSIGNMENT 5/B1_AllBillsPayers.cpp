#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
class Bill {
    string patient;
public:
    explicit Bill(string p): patient(std::move(p)) { if(patient.empty()) throw invalid_argument("missing patient"); }
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual string type() const = 0;
    const string& name() const noexcept { return patient; }
};
class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(string p,double c,double t):Bill(std::move(p)),consultation(c),tests(t) { if(c<0||t<0) throw invalid_argument("negative charge"); }
    double total() const override { return consultation+tests; }
    string type() const override { return "OP"; }
};
class InPatient : public Bill {
    int days; double rate,procedures,medicines;
public:
    InPatient(string p,int d,double r,double pr,double m):Bill(std::move(p)),days(d),rate(r),procedures(pr),medicines(m) {
        if(d<0||r<0||pr<0||m<0) throw invalid_argument("negative charge");
    }
    double total() const override { return days*rate+procedures+medicines; }
    string type() const override { return "IP"; }
};
class DayCare : public Bill {
    double package;
public:
    DayCare(string p,double cost):Bill(std::move(p)),package(cost) { if(cost<0) throw invalid_argument("negative charge"); }
    double total() const override { return package; }
    string type() const override { return "DAY"; }
};
class Emergency : public Bill {
    double base,hours,hourly;
public:
    Emergency(string p,double b,double h,double r):Bill(std::move(p)),base(b),hours(h),hourly(r) {
        if(b<0||h<0||r<0) throw invalid_argument("negative charge");
    }
    double total() const override { return base+hours*hourly; }
    string type() const override { return "ER"; }
};
class Payer {
public:
    virtual ~Payer()=default;
    virtual string type() const=0;
    virtual double amountCovered(const Bill& b) const=0;
};
class SelfPay : public Payer {
public:
    string type() const override { return "Self"; }
    double amountCovered(const Bill&) const override { return 0; }
};
class Insurance : public Payer {
    double limit,copay;
public:
    Insurance(double l,double p):limit(l),copay(p) { if(l<0||p<0||p>100) throw invalid_argument("invalid insurance"); }
    string type() const override { return "Insurance"; }
    double amountCovered(const Bill& b) const override { return min(limit,b.total()*(100-copay)/100); }
};
class GovernmentScheme : public Payer {
public:
    string type() const override { return "Govt"; }
    double amountCovered(const Bill& b) const override {
        double cap = b.type()=="OP"?1200 : b.type()=="IP"?30000 : b.type()=="DAY"?7000 : 1500;
        return min(cap,b.total());
    }
};
int main() {
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatient>("Ravi",500,1200));
    bills.push_back(make_unique<InPatient>("Meena",3,2500,40000,300));
    bills.push_back(make_unique<DayCare>("Asha",8000));
    bills.push_back(make_unique<Emergency>("Dev",1000,2,400));
    SelfPay self; Insurance ins(50000,10); GovernmentScheme govt;
    const Payer* payers[]={&self,&ins,&govt};
    cout<<fixed<<setprecision(2);
    double total=0;
    for(const auto& b:bills) {
        cout<<b->type()<<" "<<b->name()<<" bill="<<b->total();
        for(const Payer* p:payers) cout<<" "<<p->type()<<"="<<p->amountCovered(*b);
        cout<<'\n'; total+=b->total();
    }
    cout<<"Grand total="<<total<<'\n';
}
