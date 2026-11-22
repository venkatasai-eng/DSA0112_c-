#include <iostream>
#include <string>
using namespace std;
class Person {
private:
    string phone;
protected:
    string name; int id;
public:
    Person(string n, int i, string ph) : phone(ph), name(n), id(i) {}
    virtual ~Person() = default;
    string getName() const { return name; }
};
class Student : virtual public Person {
protected: string programme; double cgpa;
public:
    Student(string n, int i, string ph, string pr, double g)
      : Person(n,i,ph), programme(pr), cgpa(g) {}
};
class Staff : virtual public Person {
protected: string department; double salary;
public:
    Staff(string n, int i, string ph, string dep, double s)
      : Person(n,i,ph), department(dep), salary(s) {}
};
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n, int i, string ph, string pr,
                      double g, string dep, double s)
      : Person(n,i,ph), Student(n,i,ph,pr,g), Staff(n,i,ph,dep,s) {}
};
class ResearchScholar : public Student {
    double fellowship;
public:
    ResearchScholar(string n, int i, string ph, string pr,
                    double g, double f)
      : Person(n,i,ph), Student(n,i,ph,pr,g), fellowship(f) {}
};
int main() {
    TeachingAssistant ta("Asha", 10, "999", "CSE", 9.1, "AI", 22000);
    cout << ta.getName() << '\n';
}
