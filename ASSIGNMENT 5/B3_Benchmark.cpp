#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
using namespace std;
using Clock=chrono::steady_clock;
struct AbstractBill { virtual ~AbstractBill()=default; virtual int total()const=0; };
struct OP:AbstractBill { int v;explicit OP(int x):v(x){} int total()const override {return v+100;} };
struct IP:AbstractBill { int v;explicit IP(int x):v(x){} int total()const override {return v+200;} };
struct Flat { int type,v;};
static volatile long long sink=0;
template<class Fn> double milliseconds(Fn f){auto t=Clock::now();f();return chrono::duration<double,milli>(Clock::now()-t).count();}
int main(){
    cout<<fixed<<setprecision(3);
    for(int n : {10,1000,1000000,10000000}){
        vector<unique_ptr<AbstractBill>> polymorphic;
        vector<Flat> flat;
        polymorphic.reserve(n);flat.reserve(n);
        for(int i=0;i<n;i++){int v=i%100;if(i%2) polymorphic.push_back(make_unique<IP>(v)); else polymorphic.push_back(make_unique<OP>(v)); flat.push_back({i%2,v});}
        long long vSum=0,sSum=0;
        double virtualMs=milliseconds([&]{for(const auto& p:polymorphic)vSum+=p->total();sink=vSum;});
        double switchMs=milliseconds([&]{for(const auto& p:flat)sSum+=p.v+(p.type==0?100:200);sink=sSum;});
        cout<<"bills="<<n<<" virtual_sum="<<vSum<<" switch_sum="<<sSum<<" virtual_ms="<<virtualMs<<" switch_ms="<<switchMs<<" agree="<<boolalpha<<(vSum==sSum)<<'\n';
    }
    constexpr int n=1000000;
    for(int pct:{0,1,50}){
        int bad=0;
        double codeMs=milliseconds([&]{ for(int i=0;i<n;i++){bool valid=(i%100)>=pct;if(!valid)++bad;}sink=bad;});
        int caught=0;
        double exceptionMs=milliseconds([&]{for(int i=0;i<n;i++){
            try {if(i%100<pct)throw invalid_argument("invalid");}
            catch(const invalid_argument&){++caught;}
        }sink=caught;});
        cout<<"invalid="<<pct<<"% return_code_ms="<<codeMs<<" exception_ms="<<exceptionMs<<" rejected="<<caught<<'\n';
    }
}
