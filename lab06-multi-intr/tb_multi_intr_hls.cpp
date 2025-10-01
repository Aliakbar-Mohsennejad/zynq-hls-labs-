#include <iostream>
#include "multi_intr_hls.h"

int main() {
    ap_uint<2> irq, cpu;
    bool ig1, ig2, ig3;

    // Reset
    multi_intr_hls(true, irq, cpu, ig1, ig2, ig3);
    std::cout << "[0 ns] RESET\n";

    // Run 500 ns -> 50 ticks (10ns per tick)
    ap_uint<2> prev_irq = 0, prev_cpu = 0;
    bool p1=false, p2=false, p3=false;

    for (int t = 1; t <= 50; ++t) {
        multi_intr_hls(false, irq, cpu, ig1, ig2, ig3);
        int time_ns = t * 10;

        // Print only on changes to keep log compact
        if (ig1 != p1) { std::cout << "[" << time_ns << " ns] IG1 " << (ig1? "ON":"OFF") << "\n"; p1 = ig1; }
        if (ig2 != p2) { std::cout << "[" << time_ns << " ns] IG2 " << (ig2? "ON":"OFF") << "\n"; p2 = ig2; }
        if (ig3 != p3) { std::cout << "[" << time_ns << " ns] IG3 " << (ig3? "ON":"OFF") << "\n"; p3 = ig3; }
        if (irq != prev_irq) {
            std::cout << "[" << time_ns << " ns] IRQ=" << (unsigned)irq << "\n";
            prev_irq = irq;
        }
        if (cpu != prev_cpu) {
            if (cpu == 0) std::cout << "[" << time_ns << " ns] CPU Normal\n";
            else std::cout << "[" << time_ns << " ns] CPU ISR IG" << (unsigned)cpu << "\n";
            prev_cpu = cpu;
        }
    }
    return 0;
}
