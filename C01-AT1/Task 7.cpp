#include <iostream>
using namespace std;

constexpr long long MIN_BALANCE_PAISE = 5000;

// PROCEDURAL APPROACH
bool proceduralCanTravel(long long balance, long long fare) {
    return fare >= 0 &&
           balance >= fare &&
           balance - fare >= MIN_BALANCE_PAISE;
}

bool proceduralDeduct(long long& balance, long long fare) {
    if (!proceduralCanTravel(balance, fare)) {
        return false;
    }

    balance -= fare;
    return true;
}

// OBJECT-ORIENTED APPROACH
class SmartCard {
private:
    long long balance;

public:
    explicit SmartCard(long long initialBalance) {
        balance = initialBalance >= 0 ? initialBalance : 0;
    }

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

int main() {
    // Procedural version
    long long balance = 10000;
    long long fare = 3000;

    cout << "PROCEDURAL APPROACH\n";

    if (proceduralDeduct(balance, fare)) {
        cout << "Journey approved\n";
    } else {
        cout << "Journey denied\n";
    }

    cout << "Balance: Rs " << balance / 100 << '\n';

    // Object-oriented version
    SmartCard card(10000);

    cout << "\nOBJECT-ORIENTED APPROACH\n";

    if (card.deduct(fare)) {
        cout << "Journey approved\n";
    } else {
        cout << "Journey denied\n";
    }

    cout << "Balance: Rs "
         << card.getBalance() / 100 << '\n';

    // Test insufficient balance
    cout << "\nINSUFFICIENT BALANCE TEST\n";

    if (card.deduct(3000)) {
        cout << "Journey approved\n";
    } else {
        cout << "Journey denied\n";
    }

    cout << "Balance: Rs "
         << card.getBalance() / 100 << '\n';

    return 0;
}