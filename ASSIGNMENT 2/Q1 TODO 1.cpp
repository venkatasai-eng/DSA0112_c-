#include <iostream>
void byValue(long long fee, int pct) { fee -= fee * pct / 100; }
void byReference(long long& fee, int pct) { fee -= fee * pct / 100; }
void byPointer(long long* fee, int pct) {
    if (fee) *fee -= *fee * pct / 100;
}
int main() {
    long long a=45000, b=45000, c=45000;
    byValue(a,10); byReference(b,10); byPointer(&c,10);
    std::cout << "Value: " << a << "\nReference: " << b
              << "\nPointer: " << c << '\n';
}

void applyConcession(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

