#include <iomanip>
#include <iostream>
class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p) {}
    // TODO 1: member + returns a fresh Money object
    Money operator+(const Money& other) const {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }
    // TODO 2: member == and friend <<
    bool operator==(const Money& other) const {
        return paise == other.paise;
    }
    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long v = m.paise;
        if (v < 0) { os << '-'; v = -v; }
        return os << "Rs " << v / 100 << '.'
                  << std::setw(2) << std::setfill('0') << v % 100
                  << std::setfill(' ');
    }
};
int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha
              << (c == Money(200)) << '\n';
}
