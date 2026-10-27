#include <iostream>
#include <iomanip>
using namespace std;

constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;

enum class Zone {
    Inner,
    Middle,
    Outer
};

class FareTable {
public:
    static constexpr long long FARES[] = {
        1000, 2000, 3000
    };

    static long long calculateFare(Zone zone, bool peak) {
        long long fare = 0;

        switch (zone) {
            case Zone::Inner:
                fare = FARES[0];
                break;

            case Zone::Middle:
                fare = FARES[1];
                break;

            case Zone::Outer:
                fare = FARES[2];
                break;

            default:
                return -1;
        }

        if (peak) {
            fare += fare * PEAK_SURCHARGE_PERCENT / 100;
        }

        return fare;
    }
};

constexpr long long FareTable::FARES[];

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
    SmartCard card(10000);

    struct Trip {
        Zone zone;
        bool peak;
    };

    Trip trips[] = {
        {Zone::Inner, false},
        {Zone::Outer, true},
        {Zone::Middle, false}
    };

    cout << "FINAL METRO FARE SYSTEM\n\n";

    int journeyNumber = 1;

    for (const Trip& trip : trips) {
        long long fare =
            FareTable::calculateFare(trip.zone, trip.peak);

        cout << "Journey " << journeyNumber++ << ": ";

        if (card.deduct(fare)) {
            cout << "Approved | Fare: ";
            printMoney(fare);
        } else {
            cout << "Denied | Insufficient balance";
        }

        cout << " | Balance: ";
        printMoney(card.getBalance());
        cout << '\n';
    }

    cout << "\nFinal balance: ";
    printMoney(card.getBalance());
    cout << '\n';

    return 0;
}