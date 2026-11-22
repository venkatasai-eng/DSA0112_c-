#include <iostream>
#include <string>
class BusTicket {
    static int issued;
    static const int CAPACITY=3;
    int seat=0;
    std::string name;
public:
    explicit BusTicket(const std::string& n):name(n) {
        if(issued<CAPACITY) seat=++issued;
    }
    static int count(){return issued;}
    void print() const { std::cout << name << ": "
        << (seat ? "Seat " + std::to_string(seat) : "Waiting") << '\n'; }
};
int BusTicket::issued=0;
void batch(const std::string& label) {
    BusTicket tickets[2]={BusTicket(label+"1"),BusTicket(label+"2")};
    for(const auto& t:tickets) t.print();
    std::cout << "Issued: " << BusTicket::count() << '\n';
}
int main(){batch("A");batch("B");}
