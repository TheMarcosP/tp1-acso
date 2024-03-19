sim: shell.c sim.c sim_utilities.c sim_instructions.c
	gcc -g -O0 $^ -o $@

.PHONY: clean
clean:
	rm -rf *.o *~ sim

test: testing.c 
	gcc -g -O0 $^ -o $@