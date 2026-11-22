#include <iostream>
#include <stdexcept>
using namespace std;
class Auditorium {
    int rows, seats, booked;
    bool** map;
public:
    Auditorium(int r, int s) : rows(r), seats(s), booked(0), map(nullptr) {
        if (r < 0 || s < 0) throw invalid_argument("Invalid dimensions");
        map = new bool*[rows]{};
        try {
            for (int i=0; i<rows; ++i) map[i] = new bool[seats]{};
        } catch (...) {
            for (int i=0; i<rows; ++i) delete[] map[i];
            delete[] map; throw;
        }
        cout << "Created " << rows << "x" << seats << '\n';
    }
    Auditorium(const Auditorium&) = delete;
    Auditorium& operator=(const Auditorium&) = delete;
    ~Auditorium() {
        cout << "Closed; booked: " << booked << '\n';
        for (int i=0; i<rows; ++i) delete[] map[i];
        delete[] map;
    }
    bool book(int r, int s) {
        if (r<0 || r>=rows || s<0 || s>=seats || map[r][s]) return false;
        map[r][s] = true; ++booked; return true;
    }
    bool cancel(int r, int s) {
        if (r<0 || r>=rows || s<0 || s>=seats || !map[r][s]) return false;
        map[r][s] = false; --booked; return true;
    }
};
int main() {
    Auditorium stackEvent(2,3);
    stackEvent.book(0,1);
    { Auditorium blockEvent(1,2); blockEvent.book(0,0); }
    Auditorium* heapEvent = new Auditorium(1,3);
    heapEvent->book(0,2);
    delete heapEvent;
    stackEvent.cancel(0,1);
    Auditorium zero(0,5);
}
