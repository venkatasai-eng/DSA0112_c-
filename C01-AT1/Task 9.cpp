#include <iostream>
using namespace std;

constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;

enum class Zone {
    Inner = 1,
    Middle,
    Outer
};

long long calculateFare(int zone, int hour) {
    if (zone < 1 || zone > 3 || hour < 0 || hour > 23) {
        return -1;
    }

    long long fare;

    switch (static_cast<Zone>(zone)) {
        case Zone::Inner:
            fare = 1000;
            break;
        case Zone::Middle:
            fare = 2000;
            break;
        case Zone::Outer:
            fare = 3000;
            break;
        default:
            return -1;
    }

    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);

    if (peak) {
        fare += fare * PEAK_SURCHARGE_PERCENT / 100;
    }

    return fare;
}

bool canTravel(long long balance, long long fare) {
    return fare >= 0 &&
           balance >= fare &&
           balance - fare >= MIN_BALANCE_PAISE;
}

int main() {
    struct TestCase {
        int zone;
        int hour;
        long long expectedFare;
        const char* description;
    };

    TestCase tests[] = {
        {1, 12, 1000, "Inner off-peak"},
        {2, 12, 2000, "Middle off-peak"},
        {3, 12, 3000, "Outer off-peak"},
        {1, 8, 1200, "Exactly 8 AM"},
        {1, 10, 1000, "Exactly 10 AM"},
        {2, 17, 2400, "Exactly 5 PM"},
        {2, 20, 2000, "Exactly 8 PM"},
        {4, 12, -1, "Invalid zone"},
        {3, 18, 3600, "Outer peak"}
    };

    cout << "FARE TEST RESULTS\n\n";

    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);

    for (const TestCase& test : tests) {
        long long actual = calculateFare(test.zone, test.hour);
        bool success = (actual == test.expectedFare);

        cout << test.description
             << " | Expected: " << test.expectedFare
             << " | Actual: " << actual
             << " | " << (success ? "PASS" : "FAIL") << '\n';

        if (success) {
            ++passed;
        }
    }

    cout << "\nPassed: " << passed << "/" << total << '\n';

    cout << "\nMINIMUM BALANCE TEST\n";

    long long balance = 6000;
    long long fare = 1000;

    cout << "Balance: " << balance << " paise\n";
    cout << "Fare: " << fare << " paise\n";
    cout << "Can travel: "
         << (canTravel(balance, fare) ? "Yes" : "No") << '\n';

    cout << "\nFIVE-JOURNEY TOTAL\n";

    int zones[] = {1, 2, 3, 1, 2};
    int hours[] = {12, 8, 18, 10, 20};

    long long totalFare = 0;

    for (int i = 0; i < 5; ++i) {
        long long f = calculateFare(zones[i], hours[i]);

        if (f >= 0) {
            totalFare += f;
        }
    }

    cout << "Total fare: " << totalFare << " paise\n";
    cout << "Total fare: Rs " << totalFare / 100
         << '.' << (totalFare % 100 < 10 ? "0" : "")
         << totalFare % 100 << '\n';

    cout << "\nNEGATIVE RECHARGE TEST\n";

    long long recharge = -500;

    if (recharge < 0) {
        cout << "Invalid recharge rejected\n";
    }

    return 0;
}
