#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    int x = get_total_weight();
	cout << "total: " << x << endl;
	assert(x == 0);
    x = set_weight(5);
	cout << "set_weight returns: " << x << endl;
	assert(x == 0);
    x = get_total_weight();
	cout << "new total: " << x << endl;
	assert(x == 5);
    cout << "===== SUCCESS =====" << endl;
    return 0;
}

