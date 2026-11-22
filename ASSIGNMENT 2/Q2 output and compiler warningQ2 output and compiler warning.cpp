#include <iostream>
#include <cstddef>
int& highest(int (&a)[5]) {
    int best=0;
    for(int i=1;i<5;++i) if(a[i]>a[best]) best=i;
    return a[best];
}
const int& highestReadOnly(const int (&a)[5]) {
    int best=0;
    for(int i=1;i<5;++i) if(a[i]>a[best]) best=i;
    return a[best];
}
int highestCopy(const int (&a)[5]) {
    int best=a[0];
    for(int i=1;i<5;++i) if(a[i]>best) best=a[i];
    return best;
}
// Unsafe example for compiler-warning evidence; NEVER call it:
int& dangling() { int local=99; return local; }
int main() {
    int marks[5]={65,88,74,91,80};
    std::cout << "Before: " << highest(marks) << '\n';
    highest(marks) = 93;
    std::cout << "After: " << marks[3] << '\n';
    std::cout << "Read-only: " << highestReadOnly(marks)
              << " Copy: " << highestCopy(marks) << '\n';
}
https://www.onlinegdb.com/online_c++_compiler#tab-stdin