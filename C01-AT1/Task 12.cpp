#include <iostream>
#include <iomanip>
using namespace std;

constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;

enum class Zone {
    Inner = 0,
    Middle,
    Outer,
    Airport
};

constexpr long long FARES[] = {
    1000, 2000, 3000, 6000
};

class FareTable {
public:
    static long long calculateFare(
        Zone zone, bool peak, bool weekend) {

        int index = static_cast<int>(zone);

        if (index < 0 || index >= 4) {
            return -1;
        }

        long long fare = FARES[index];

        // Weekend discount does not combine with peak surcharge.
        if (weekend) {
            fare -= fare * WEEKEND_DISCOUNT_PERCENT / 100;
        } else if (peak) {
            fare += fare * PEAK_SURCHARGE_PERCENT / 100;
        }

        return fare;
    }
};

class MonthlyPass {
private:
    Zone zone1;
    Zone zone2;
    bool active;

public:
    MonthlyPass(Zone first, Zone second)
        : zone1(first), zone2(second), active(true) {}

    bool covers(Zone zone) const {
        return active && (zone == zone1 || zone == zone2);
    }

    void deactivate() {
        active = false;
    }
};

class SmartCard {
private:
    long long balance;

public:
    explicit SmartCard(long long initialBalance)
        : balance(initialBalance >= 0 ? initialBalance : 0) {}

    bool canTravel(long long fare) const {
        return fare >= 0 &&
               balance >= fare &&
               balance - fare >= MIN_BALANCE_PAISE;
    }

    bool deduct(long long fare) {
        if (!canTravel(fare)) {
            return false;
        }

        balance -= fare;
        return true;
    }

    long long getBalance() const {
        return balance;
    }
};

void printMoney(long long paise) {
    cout << "Rs " << paise / 100 << '.'
         << setw(2) << setfill('0') << paise % 100
         << setfill(' ');
}

int main() {
    SmartCard card(20000);

    MonthlyPass pass(Zone::Inner, Zone::Middle);

    struct Trip {
        Zone zone;
        bool peak;
        bool weekend;
    };

    Trip trips[] = {
        {Zone::Inner, false, false},
        {Zone::Airport, true, false},
        {Zone::Outer, false, true},
        {Zone::Middle, true, true},
        {Zone::Inner, true, false}
    };

    cout << "REVISED METRO FARE SYSTEM\n\n";

    int journeyNumber = 1;

    for (const Trip& trip : trips) {
        cout << "Journey " << journeyNumber++ << ": ";

        if (pass.covers(trip.zone)) {
            cout << "Monthly pass accepted";
        } else {
            long long fare = FareTable::calculateFare(
                trip.zone, trip.peak, trip.weekend
            );

            if (fare >= 0 && card.deduct(fare)) {
                cout << "Fare ";
                printMoney(fare);
            } else {
                cout << "Journey denied";
            }
        }

        cout << " | Balance: ";
        printMoney(card.getBalance());
        cout << '\n';
    }

    cout << "\nFARE RULE TESTS\n";

    cout << "Airport off-peak: ";
    printMoney(FareTable::calculateFare(
        Zone::Airport, false, false));
    cout << '\n';

    cout << "Inner peak weekday: ";
    printMoney(FareTable::calculateFare(
        Zone::Inner, true, false));
    cout << '\n';

    cout << "Inner weekend: ";
    printMoney(FareTable::calculateFare(
        Zone::Inner, true, true));
    cout << '\n';

    return 0;
}