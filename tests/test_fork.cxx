#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <unistd.h>

using namespace std;

int main() {
    int x = get_total_weight();
	cout << "total: " << x << endl;
	assert(x == 0);
    x = set_weight(5);
	cout << "set_weight returns: " << x << endl;
	assert(x == 0);
	int pid = fork();
	if (pid == 0) {
		//child
		x = set_weight(13);
		cout << "set_weight returns: " << x << endl;
		return 0;
	} else {
		sleep(5);
		x = get_total_weight();
		cout << "new_total: " << x << endl;
		assert (x == 18);
	}
//    x = get_total_weight();
//	cout << "new total: " << x << endl;
//	assert(x == 5);
    cout << "===== SUCCESS =====" << endl;
    return 0;
}

