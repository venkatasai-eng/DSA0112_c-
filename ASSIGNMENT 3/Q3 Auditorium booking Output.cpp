#include <iostream>
using namespace std;

class Auditorium {
private:
    int rows, seats;
    int** seatMap;
    int booked;

public:
    Auditorium(int r, int s) {
        rows = r;
        seats = s;
        booked = 0;

        seatMap = new int*[rows];

        for (int i = 0; i < rows; i++) {
            seatMap[i] = new int[seats]{};
        }

        cout << "Constructor: Auditorium created" << endl;
    }

    void bookSeat(int r, int s) {
        if (r < 1 || r > rows || s < 1 || s > seats) {
            cout << "Invalid seat!" << endl;
            return;
        }

        if (seatMap[r-1][s-1] == 0) {
            seatMap[r-1][s-1] = 1;
            booked++;
            cout << "Seat booked: " << r << "-" << s << endl;
        } else {
            cout << "Seat already booked!" << endl;
        }
    }

    void cancelSeat(int r, int s) {
        if (r < 1 || r > rows || s < 1 || s > seats) {
            cout << "Invalid seat!" << endl;
            return;
        }

        if (seatMap[r-1][s-1] == 1) {
            seatMap[r-1][s-1] = 0;
            booked--;
            cout << "Seat cancelled: " << r << "-" << s << endl;
        } else {
            cout << "Seat not booked!" << endl;
        }
    }

    void display() {
        cout << "Seat Map:" << endl;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < seats; j++) {
                cout << seatMap[i][j] << " ";
            }
            cout << endl;
        }
    }

    ~Auditorium() {
        cout << "Destructor: Closing auditorium" << endl;
        cout << "Total booked seats: " << booked << endl;

        for (int i = 0; i < rows; i++) {
            delete[] seatMap[i];
        }

        delete[] seatMap;

        cout << "Memory released successfully" << endl;
    }
};

int main() {
    cout << "STACK OBJECT" << endl;

    Auditorium a(2, 3);

    a.bookSeat(1, 1);
    a.bookSeat(1, 2);
    a.bookSeat(2, 3);

    a.cancelSeat(1, 2);

    a.display();

    cout << "\nBLOCK OBJECT" << endl;

    {
        Auditorium b(1, 2);
        b.bookSeat(1, 1);
    }

    cout << "\nHEAP OBJECT" << endl;

    Auditorium* c = new Auditorium(1, 3);
    c->bookSeat(1, 2);
    delete c;

    cout << "\nZERO ROW TEST" << endl;

    {
        Auditorium d(0, 3);
        d.display();
    }

    cout << "\nEnd of main function" << endl;

    return 0;
}