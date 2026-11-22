#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;
class Staff {
    string name; int id;
public:
    Staff(string n, int i) : name(n), id(i) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    void print() const { cout << id << " " << name << " Rs " << pay() << '\n'; }
};
class Professor : public Staff {
    double basic, research;
public:
    Professor(string n, int i, double b, double r)
      : Staff(n, i), basic(b), research(r) {}
    double pay() const override { return basic * 1.42 + research; }
};
class LabAssistant : public Staff {
    double basic;
public:
    LabAssistant(string n, int i, double b) : Staff(n, i), basic(b) {}
    double pay() const override { return basic * 1.42; }
};
class GuestFaculty : public Staff {
    double hours, ratePerHour;
public:
    GuestFaculty(string n, int i, double h, double r)
      : Staff(n, i), hours(h), ratePerHour(r) {}
    double pay() const override { return hours * ratePerHour; }
};
int main() {
    vector<unique_ptr<Staff>> staff;
    staff.push_back(make_unique<Professor>("Anu", 1, 50000, 5000));
    staff.push_back(make_unique<LabAssistant>("Bala", 2, 25000));
    staff.push_back(make_unique<GuestFaculty>("Dev", 3, 20, 1000));
    for (const auto& x : staff) x->print();
}
