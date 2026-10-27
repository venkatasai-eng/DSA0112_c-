#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int main() {
    const long long farePaise = 3000;

    const long long journeys[] = {
        20000,
        500000,
        3000000
    };

    cout << fixed << setprecision(2);
    cout << "METRO FARE COMPARISON\n\n";

    for (long long n : journeys) {
        long long totalPaise = n * farePaise;

        double totalDouble = n * 30.00;

        cout << "Journeys: " << n << '\n';

        cout << "Integer-paise total: Rs "
             << static_cast<double>(totalPaise) / 100.0
             << '\n';

        cout << "Double total: Rs "
             << totalDouble << '\n';

        cout << "Difference: Rs "
             << (static_cast<double>(totalPaise) / 100.0
                 - totalDouble)
             << "\n\n";
    }

    cout << "INTEGER RANGE ANALYSIS\n";
    cout << "INT_MAX: " << INT_MAX << '\n';

    long long networkTotalPaise =
        3000000LL * farePaise;

    cout << "Network total in paise: "
         << networkTotalPaise << '\n';

    cout << "Network total in rupees: Rs "
         << static_cast<double>(networkTotalPaise) / 100.0
         << '\n';

    cout << "\nINTEGER OVERFLOW DEMONSTRATION\n";

    int journeysInt = 3000000;
    int fareInt = 3000;

    long long safeTotal =
        static_cast<long long>(journeysInt) * fareInt;

    cout << "Safe total using long long: "
         << safeTotal << " paise\n";

    cout << "\nDATA TYPE SIZES\n";
    cout << "sizeof(int): " << sizeof(int) << " bytes\n";
    cout << "sizeof(long long): "
         << sizeof(long long) << " bytes\n";
    cout << "sizeof(double): "
         << sizeof(double) << " bytes\n";

    return 0;
}