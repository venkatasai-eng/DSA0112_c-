#include <iostream>
#include <vector>
#include <chrono>
using Clock=std::chrono::steady_clock;
void shiftAdd(std::vector<int>& v,int k,int x){
    if((int)v.size()<k) v.push_back(x);
    else {for(int i=1;i<k;++i) v[i-1]=v[i];v[k-1]=x;}
}
struct Ring {
    std::vector<int> v;int start=0,count=0;
    explicit Ring(int k):v(k){}
    void add(int x){int k=(int)v.size();
        if(count<k){v[(start+count)%k]=x;++count;}
        else {v[start]=x;start=(start+1)%k;}
    }
    std::vector<int> ordered() const {
        std::vector<int> r;
        for(int i=0;i<count;++i)r.push_back(v[(start+i)%v.size()]);
        return r;
    }
};
int main(){
    for(int k:{10,50,1000}){
        constexpr int N=100000;
        std::vector<int> shifted;
        auto t1=Clock::now();
        for(int i=0;i<N;++i)shiftAdd(shifted,k,i);
        auto t2=Clock::now();
        Ring ring(k);
        for(int i=0;i<N;++i)ring.add(i);
        auto t3=Clock::now();
        std::cout<<"k="<<k<<" identical="<<std::boolalpha
                 <<(shifted==ring.ordered())
                 <<" shift_us="
                 <<std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()
                 <<" ring_us="
                 <<std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count()
                 <<'\n';
    }
}
