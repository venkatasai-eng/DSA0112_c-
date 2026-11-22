#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
struct Bill { virtual ~Bill()=default; virtual double total() const=0; virtual string type() const=0; };
struct OutPatient final:Bill { double total() const override{return 1700;} string type()const override{return "OP";} };
struct Telemedicine final:Bill { // New bill added without editing Bill or OutPatient
    double consult,platform;
    Telemedicine(double c,double p):consult(c),platform(p) { if(c<0||p<0) throw invalid_argument("negative charge"); }
    double total() const override{return consult+platform;}
    string type()const override{return "Telemedicine";}
};
struct Payer { virtual ~Payer()=default; virtual double amountCovered(const Bill&)const=0; virtual string type()const=0; };
struct SelfPay final:Payer { double amountCovered(const Bill&)const override{return 0;} string type()const override{return "Self";} };
struct CorporateTieUp final:Payer { // New payer without editing Payer or SelfPay
    double amountCovered(const Bill& b) const override {return min(1000.0,b.total()*0.8);}
    string type()const override{return "Corporate";}
};
struct Guard { ~Guard(){ cout<<"RAII: guard destroyed\n"; } };
int main() {
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatient>());
    bills.push_back(make_unique<Telemedicine>(600,100));
    SelfPay self;CorporateTieUp corporate;
    const Payer* payers[]={&self,&corporate};
    for(const auto& b:bills) for(const auto* p:payers)
        cout<<b->type()<<" "<<p->type()<<" bill="<<b->total()<<" covered="<<p->amountCovered(*b)<<'\n';
    try { Guard g; throw runtime_error("simulated invalid claim"); }
    catch(const exception& e){cout<<"Recovered: "<<e.what()<<'\n';}
    cout<<"Continued safely\n";
}
