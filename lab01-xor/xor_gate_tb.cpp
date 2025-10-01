#include <iostream>
#include "xor_gate.h"

int main() {
    bool a, b, out;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a = i;
            b = j;
            xor_gate(a, b, out);
            std::cout << "a = " << a << ", b = " << b << " -> out = " << out << std::endl;
        }
    }

    return 0;
}
