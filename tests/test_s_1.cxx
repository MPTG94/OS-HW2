#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

using namespace std;

int main() {

    int x = set_weight(1);

    int pid2 = fork();
    if (pid2 == 0) {
        x = set_weight(4);

        int pid3 = fork();
        if (pid3 == 0) {
            x = set_weight(7);
            sleep(2);
            exit(0);
        }
        sleep(2);
        exit(0);
    }

    sleep(1);
    x = get_total_weight();
    if (x == 12) {
        cout << "PASS" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }
}

