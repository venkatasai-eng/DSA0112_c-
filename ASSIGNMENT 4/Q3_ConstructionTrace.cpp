#include <iostream>
#include <string>
using namespace std;
struct Address {
    string city;
    Address(string c) : city(c) { cout << "Address "; }
    ~Address() { cout << "~Address "; }
};
struct Course {
    string title;
    Course(string t) : title(t) { cout << "Course "; }
    ~Course() { cout << "~Course "; }
};
struct Person {
    string name; Address home;
    Person(string n, string city) : name(n), home(city) { cout << "Person "; }
    virtual ~Person() { cout << "~Person "; }
};
struct Student : virtual Person {
    Course course;
    Student(string n, string city, string c)
      : Person(n,city), course(c) { cout << "Student "; }
    ~Student() override { cout << "~Student "; }
};
struct Staff : virtual Person {
    Staff(string n,string city) : Person(n,city) { cout << "Staff "; }
    ~Staff() override { cout << "~Staff "; }
};
struct TeachingAssistant : Student, Staff {
    TeachingAssistant(string n,string city,string c)
      : Person(n,city), Student(n,city,c), Staff(n,city) { cout << "TA "; }
    ~TeachingAssistant() override { cout << "~TA "; }
};
int main() {
    { Student s("Ana","Salem","C++"); cout << "| "; }
    cout << '\n';
    { Staff s("Bala","Chennai"); cout << "| "; }
    cout << '\n';
    { TeachingAssistant t("Kavya","Salem","AI"); cout << "| "; }
    cout << '\n';
}
