#include "verilated.h"
#include "verilated_fst_c.h"
#include "Vmodule_a.h"
#include "Vmodule_b.h"
#include <cstdint>

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vmodule_a *top_a = new Vmodule_a;
    Vmodule_b *top_b = new Vmodule_b;

    VerilatedFstC* tfp = new VerilatedFstC;
    top_a->trace(tfp, 99);
    top_b->trace(tfp, 99);

    tfp->open("trace.fst");

    uint8_t global_clock = 0;
    uint8_t global_reset = 1;


    uint64_t time = 0;
    uint64_t max_time = 1000;

    for (int i = 0; i < 10; i++) {
        top_a->reset = global_reset;
        top_a->clock = global_clock;
        top_a->eval();
        top_b->reset = global_reset;
        top_b->clock = global_clock;
        top_b->eval();
        global_clock = !global_clock;
    }

    global_reset = 0;

    while (!Verilated::gotFinish() && time < max_time) {
        top_a->clock = global_clock;
        top_a->reset = global_reset;
        top_a->eval();
        top_b->clock = global_clock;
        top_b->reset = global_reset;
        top_b->eval();
        /*
            Note: if there exist a combinational logic which changes the
            signals between module_a and module_b, we should connect the
            signals and eval them until the signals are stable.
         */
        top_a->cnt_en = top_b->cnt_en;
        tfp->dump(time++);

        global_clock = !global_clock;
        printf("data = %d\n", top_a->data);
    }

    tfp->close();
    top_a->final();
    top_b->final();
    return 0;
}