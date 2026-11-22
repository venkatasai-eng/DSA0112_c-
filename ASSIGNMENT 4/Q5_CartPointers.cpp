#include <iostream>
using namespace std;
class Cart {
    double amount = 0;
public:
    Cart& add(double x) { amount += x; return *this; }
    double total() const { return amount; }
};
int main() {
    Cart c1, c2;
    c1.add(20).add(30);
    c2.add(90);
    cout << "Direct: " << c1.total() << '\n';
    Cart* p = &c1;
    cout << "Pointer: " << p->total() << '\n';
    Cart& ref = c2;
    cout << "Reference: " << ref.total() << '\n';
    Cart* heap = new Cart;
    heap->add(40);
    cout << "Heap: " << heap->total() << '\n';
    Cart* carts[] = {&c1, &c2, heap};
    Cart* best = carts[0];
    for (Cart* x : carts) if (x->total() > best->total()) best = x;
    cout << "Highest: " << best->total() << '\n';
    delete heap;
}
