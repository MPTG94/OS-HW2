#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    int x = get_total_weight();
    cout << "total: " << x << endl;
    assert(x == 0);
    // Setting weight of A to 3
    x = set_weight(3);
    assert (x == 0);
    int pidB = fork();
    if (pidB == 0) {
        // child
        x = set_weight(4);
        assert (x == 0);
        int pidD = fork();
        if (pidD == 0) {
            //child of B
            x = set_weight(5);
            assert(x == 0);
            x = get_total_weight();
            assert(x == 5);
            return 0;
        } else {
            sleep(10);
            // Getting total weight of B + D, should be 9
            x = get_total_weight();
            assert(x == 9);
            int pidE = fork();
            if (pidE == 0) {
                // 2nd child of B (E)
                x = set_weight(6);
                assert(x == 0);
                x = get_total_weight();
                assert(x == 6);
                int pidF = fork();
                if (pidF == 0) {
                    // child of E (F)
                    x = set_weight(3);
                    assert(x == 0);
                    // this call should fail since F doesn't have any children
                    x = get_heaviest_child();
                    assert(x == -10);
                    return 0;
                } else {
                    sleep(10);
                    x = get_total_weight();
                    assert(x== 9);
                    x = get_heaviest_child();
                    assert(x == pidF);
                    return 0;
                }
            } else {
                // BLOCK OF B after forking both children
                sleep(40);
                x = get_total_weight();
                std::cout << "Received total: " << x << " from B node after forking ALL children" << std::endl;
                // should return 18
                assert(x == 18);
                x = get_heaviest_child();
                // should be 6
                assert(x == 6);
                return 0;
            }
        }
    } else {
        // PARENT OF ENTIRE TREE BLOCK
        sleep(30);
        int pidC = fork();
        if (pidC == 0) {
            // Child of A
            x = set_weight(2);
            assert(x == 0);
            x = get_total_weight();
            assert(x == 2);
            return 0;
        } else {
            // Parent after forking C
            sleep(60);
            x = get_total_weight();
            std::cout << "Received total: " << x << " from A node after forking ALL children" << std::endl;
            // should be 23
            assert(x == 23);
            x = get_heaviest_child();
            // should be B (so pidB)
            assert(x == pidB);
        }
    }
    cout << "===== SUCCESS =====" << endl;
    return 0;
}

