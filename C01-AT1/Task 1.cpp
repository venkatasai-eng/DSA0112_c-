#include <iostream>
#include <string>
using namespace std;

constexpr long long MIN_BALANCE_PAISE = 5000;

enum class Zone {
    Inner,
    Middle,
    Outer
};

class Passenger {
private:
    string name;
    bool student;
    bool seniorCitizen;

public:
    Passenger(string n, bool s, bool senior)
        : name(n), student(s), seniorCitizen(senior) {}

    string getName() const {
        return name;
    }

    bool isEligibleForConcession() const {
        return student || seniorCitizen;
    }
};

class FareTable {
public:
    static constexpr long long BASE_FARE[] = {
        1000, 2000, 3000
    };

    static long long calculateFare(Zone zone, bool peak,
                                   bool concession) {
        long long fare = 0;

        switch (zone) {
            case Zone::Inner:
                fare = BASE_FARE[0];
                break;
            case Zone::Middle:
                fare = BASE_FARE[1];
                break;
            case Zone::Outer:
                fare = BASE_FARE[2];
                break;
        }

        if (peak) {
            fare += fare * 20 / 100;
        }

        if (concession) {
            fare -= fare * 10 / 100;
        }

        return fare;
    }
};

constexpr long long FareTable::BASE_FARE[];

class SmartCard {
private:
    long long balance;

public:
    explicit SmartCard(long long initialBalance)
        : balance(initialBalance) {}

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

class Journey {
private:
    Passenger passenger;
    Zone zone;
    bool peak;

public:
    Journey(Passenger p, Zone z, bool isPeak)
        : passenger(p), zone(z), peak(isPeak) {}

    void process(SmartCard& card) const {
        long long fare = FareTable::calculateFare(
            zone, peak, passenger.isEligibleForConcession()
        );

        cout << "Passenger: " << passenger.getName() << '\n';

        if (card.deduct(fare)) {
            cout << "Fare: Rs "
                 << fare / 100 << '.';

            if (fare % 100 < 10) {
                cout << '0';
            }

            cout << fare % 100 << '\n';
        } else {
            cout << "Journey denied: Insufficient balance\n";
        }

        cout << "Balance: Rs "
             << card.getBalance() / 100 << '.';

        if (card.getBalance() % 100 < 10) {
            cout << '0';
        }

        cout << card.getBalance() % 100 << "\n\n";
    }
};

int main() {
    Passenger p1("Sai", true, false);
    SmartCard card(10000);

    Journey j1(p1, Zone::Inner, false);
    Journey j2(p1, Zone::Middle, true);
    Journey j3(p1, Zone::Outer, false);

    j1.process(card);
    j2.process(card);
    j3.process(card);

    return 0;
}