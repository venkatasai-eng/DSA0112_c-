#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
class Time {
    int seconds;
public:
    explicit Time(int s=0) : seconds(s) {}
    Time& operator++() { ++seconds; return *this; }       // prefix
    Time operator++(int) { Time old=*this; ++*this; return old; }
    bool operator==(const Time& t) const { return seconds==t.seconds; }
    bool operator<(const Time& t) const { return seconds<t.seconds; }
    void show() const {
        cout << seconds/3600 << ':' << (seconds/60)%60 << ':' << seconds%60;
    }
};
class Playlist {
    vector<string> tracks;
public:
    Playlist(initializer_list<string> items) : tracks(items) {}
    string& operator[](int i) {
        if (i<0 || static_cast<size_t>(i)>=tracks.size())
            throw out_of_range("Track index out of range");
        return tracks[i];
    }
    const string& operator[](int i) const {
        if (i<0 || static_cast<size_t>(i)>=tracks.size())
            throw out_of_range("Track index out of range");
        return tracks[i];
    }
};
int main() {
    Playlist list{"Intro", "Theme", "Finale"};
    Time t(3599), a=t++, b=++t;
    cout << "Track: " << list[1] << '\n';
    cout << "a="; a.show(); cout << " b="; b.show();
    cout << " t="; t.show(); cout << '\n';
    try { cout << list[-1] << '\n'; }
    catch (const out_of_range& e) { cout << e.what() << '\n'; }
    try { cout << list[3] << '\n'; }
    catch (const out_of_range& e) { cout << e.what() << '\n'; }
}
