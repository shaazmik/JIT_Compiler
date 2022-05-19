all:
	g++ main.cpp JIT_function.cpp -no-pie -g -masm=intel;