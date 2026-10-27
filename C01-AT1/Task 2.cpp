#include <iostream>
using namespace std;

// Constants
constexpr int INNER_FARE = 1000;
constexpr int MIDDLE_FARE = 2000;
constexpr int OUTER_FARE = 3000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

// Zone enumeration
enum class Zone {
    Inner,
    Middle,
    Outer
};

int main() {
    Zone zone = Zone::Inner;
    int fare = INNER_FARE;
    bool peak = true;

    // Calculate peak surcharge
    if (peak) {
        fare += fare * PEAK_SURCHARGE_PERCENT / 100;
    }

    cout << "Base fare: Rs " << INNER_FARE / 100 << '\n';
    cout << "Peak surcharge: " << PEAK_SURCHARGE_PERCENT << "%\n";
    cout << "Final fare: Rs " << fare / 100 << '\n';
    cout << "Minimum balance: Rs "
         << MIN_BALANCE_PAISE / 100 << '\n';

    if (zone == Zone::Inner) {
        cout << "Zone: Inner\n";
    }

    return 0;
}
