#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
struct Guard { ~Guard() { std::cout << "Guard destroyed\n"; } };
int main() {
    for (int test = 0; test < 5; ++test) {
        try {
            Guard g;
            if (test == 0) throw std::invalid_argument("negative charge");
            if (test == 1) throw std::runtime_error("claim exceeds cover");
            if (test == 2) throw std::out_of_range("unknown package");
            if (test == 3) { (void)std::stod("not-a-number"); }
            if (test == 4) throw std::bad_alloc(); // deterministic allocation-failure simulation
        } catch (const std::bad_alloc&) { std::cout << "caught bad_alloc\n"; }
          catch (const std::exception& e) { std::cout << "caught: " << e.what() << '\n'; }
          catch (...) { std::cout << "caught unknown error\n"; }
    }
}
