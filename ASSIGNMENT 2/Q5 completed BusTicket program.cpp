#include <iostream>
#include <string>
using namespace std;

class BusTicket {
    static int issued;
    static const int CAPACITY = 3;

    int seat;
    string name;

public:
    explicit BusTicket(const string& n) : seat(0), name(n)
    {
        // TODO 1: Assign seat if available
        if (issued < CAPACITY)
            seat = ++issued;
    }

    static int count()
    {
        // TODO 2: Return total issued seats
        return issued;
    }

    void print() const
    {
        cout << name << ": "
             << (seat ? "Seat " + to_string(seat)
                      : string("Waiting"))
             << '\n';
    }
};

int BusTicket::issued = 0;

int main()
{
    BusTicket trip[4] = {
        BusTicket("Asha"),
        BusTicket("Bala"),
        BusTicket("Chitra"),
        BusTicket("Dev")
    };

    for (const BusTicket& t : trip)
        t.print();
      
    cout << "Issued: " << BusTicket::count() << '\n';
    

    return 0;
}
