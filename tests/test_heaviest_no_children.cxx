#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    int x = get_total_weight();
	cout << "total: " << x << endl;
	assert(x == 0);
    x = get_heaviest_child();
	cout << "should return error: " << x << endl;
	assert(x == -1);
    cout << "===== SUCCESS =====" << endl;
    return 0;
}

