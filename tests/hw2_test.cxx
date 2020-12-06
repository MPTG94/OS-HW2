#include "hw2_test.h"

int set_weight(int weight) {
    long r = syscall(334, weight);
    return r;
}

int get_total_weight() {
	long r = syscall(335);
    return r;
}

pid_t get_heaviest_child() {
	long r = syscall(336);
    return (pid_t) r;
}
