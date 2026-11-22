#include <cstring>
#include <iostream>
#include <utility>
using namespace std;
class Text {
    char* data;
public:
    explicit Text(const char* s="") {
        size_t n = strlen(s);
        data = new char[n+1];
        memcpy(data, s, n+1);
    }
    Text(const Text& other) : Text(other.data) {}
    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        char* fresh = new char[strlen(other.data)+1];
        strcpy(fresh, other.data);
        delete[] data;
        data = fresh;
        return *this;
    }
    ~Text() { delete[] data; }
    friend Text operator+(const Text& a, const Text& b) {
        size_t na=strlen(a.data), nb=strlen(b.data);
        char* buf = new char[na+nb+1];
        memcpy(buf, a.data, na);
        memcpy(buf+na, b.data, nb+1);
        Text result(buf);
        delete[] buf;
        return result;
    }
    bool operator==(const Text& rhs) const {
        return strcmp(data, rhs.data)==0;
    }
    bool operator!=(const Text& rhs) const { return !(*this==rhs); }
    friend ostream& operator<<(ostream& os, const Text& t) {
        return os << t.data;
    }
};
int main() {
    Text a("Hello"), b(" "), c("world"), empty("");
    Text result = a+b+c;
    cout << result << '\n';
    cout << boolalpha << (a!=c) << ' ' << (empty==Text("")) << '\n';
    result=result; // self-assignment
    cout << result << '\n';
}
