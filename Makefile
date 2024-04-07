VERILATOR_ARGS = --cc --trace --trace-fst -Wno-fatal --CFLAGS "-Os" -j `nproc`

obj_dir/Vmodule_a__ALL.a: vsrc/* obj_dir/Vmodule_b__ALL.a csrc/*
	verilator $(VERILATOR_ARGS) --build --exe $(realpath $^) --top module_a

obj_dir/Vmodule_b__ALL.a: vsrc/*
	verilator $(VERILATOR_ARGS) --build $^ --top module_b