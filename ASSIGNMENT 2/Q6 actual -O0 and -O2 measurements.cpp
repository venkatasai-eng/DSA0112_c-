#include <iostream>
#include <chrono>
class Time {
    int h,m;
public:
    Time(int hh,int mm):h(hh),m(mm){}
    friend int inlineDiff(const Time&,const Time&);
    friend int plainDiff(const Time&,const Time&);
};
inline int inlineDiff(const Time& a,const Time& b) {
    int d=(a.h*60+a.m)-(b.h*60+b.m);return d<0?-d:d;
}
int plainDiff(const Time& a,const Time& b) {
    int d=(a.h*60+a.m)-(b.h*60+b.m);return d<0?-d:d;
}
int main(){
    Time a(9,45), b(13,10), same(9,45);
    std::cout << "Across noon: " << plainDiff(a,b)
              << " Same time: " << plainDiff(a,same) << '\n';
    for(int mode=0;mode<2;++mode){
        volatile long long sum=0;
        auto start=std::chrono::steady_clock::now();
        for(int i=0;i<10000000;++i) {
            // Vary inputs to discourage folding an identical constant result.
            Time x(i%24,(i/24)%60);
            sum=sum+(mode==0?inlineDiff(x,b):plainDiff(x,b));
        }
        auto end=std::chrono::steady_clock::now();
        std::cout<<(mode==0?"inline: ":"non-inline: ")
            <<std::chrono::duration<double,std::milli>(end-start).count()
            <<" ms; checksum="<<sum<<'\n';
    }
}
