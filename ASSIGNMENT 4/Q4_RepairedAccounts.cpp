#include <iostream>
#include <memory>
#include <vector>
using namespace std;
class Account {
public:
    virtual ~Account() { cout << "~Account\n"; }
    virtual double rate() const { return 3.5; }
};
class SeniorAccount : public Account {
    double* history = new double[100]{};
public:
    double rate() const override { return 4.0; }
    ~SeniorAccount() override {
        delete[] history;
        cout << "~SeniorAccount\n";
    }
};
int main() {
    vector<unique_ptr<Account>> accounts;
    accounts.push_back(make_unique<Account>());
    accounts.push_back(make_unique<SeniorAccount>());
    for (const auto& a : accounts) cout << a->rate() << '\n';
    accounts.clear();
}
