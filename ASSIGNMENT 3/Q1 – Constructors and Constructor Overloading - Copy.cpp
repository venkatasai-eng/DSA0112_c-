#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
class Book {
    string title, author;
    int copies;
public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(string t) : Book(t, "Unknown", 1) {}
    Book(string t, string a, int n)
        : title(t), author(a), copies(validate(n)) {}
    static int validate(int n) {
        if (n < 0) throw invalid_argument("Negative copies not allowed");
        return n;
    }
    void print() const {
        cout << title << " | " << author << " | Copies: " << copies << '\n';
    }
};
int main() {
    Book empty, donated("Donated Book"), full("C++ Basics", "Ravi", 5);
    empty.print(); donated.print(); full.print();
    try { Book bad("Wrong", "Test", -2); bad.print(); }
    catch (const invalid_argument& e) { cout << "Rejected: " << e.what() << '\n'; }
}
