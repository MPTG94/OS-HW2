#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    // Setting weight of A to 3
    std::cout << "Now setting weight of A" << std::endl;
    int x = set_weight(3);
    assert (x == 0);
    int pidB = fork();
    if (pidB == 0) {
        // child
        setpgrp();
        std::cout << "Now setting weight of B" << std::endl;
        x = set_weight(4);
        assert (x == 0);
        int pidD = fork();
        if (pidD == 0) {
            setpgrp();
            //child of B
            std::cout << "Now setting weight of D" << std::endl;
            x = set_weight(5);
            assert(x == 0);
            std::cout << "Now getting total weight of D" << std::endl;
            x = get_total_weight();
            assert(x == 5);
            sleep(20);
            return 0;
        } else {
            sleep(5);
            // Getting total weight of B + D, should be 9
            std::cout << "Now getting total weight of B+D" << std::endl;
            x = get_total_weight();
            std::cout << "Received total: " << x << " from B node after forking ALL children" << std::endl;
            assert(x == 9);
            // int pidE = fork();
            // if (pidE == 0) {
            //    setpgrp();
            //     // 2nd child of B (E)
            //     x = set_weight(6);
            //     assert(x == 0);
            //     x = get_total_weight();
            //     assert(x == 6);
            //     int pidF = fork();
            //     if (pidF == 0) {
            //         setpgrp();
            //         // child of E (F)
            //         x = set_weight(3);
            //         assert(x == 0);
            //         // this call should fail since F doesn't have any children
            //         x = get_heaviest_child();
            //         assert(x == -10);
            //         return 0;
            //     } else {
            //         sleep(10);
            //         x = get_total_weight();
            //         assert(x== 9);
            //         x = get_heaviest_child();
            //         assert(x == pidF);
            //         return 0;
            //     }
            // } else {
                // BLOCK OF B after forking both children
                // sleep(10);
                // x = get_total_weight();
                // std::cout << "Received total: " << x << " from B node after forking ALL children" << std::endl;
                // // should return 18
                // assert(x == 9);
                x = get_heaviest_child();
                // should be 5 (D)
                assert(x == pidD);
                return 0;
            // }
        }
    } else {
        // PARENT OF ENTIRE TREE BLOCK
        sleep(10);
        int pidC = fork();
        if (pidC == 0) {
            setpgrp();
            // Child of A
            std::cout << "Now setting weight of C" << std::endl;
            x = set_weight(2);
            assert(x == 0);
            x = get_total_weight();
            assert(x == 2);
            return 0;
        } else {
            // Parent after forking C
            sleep(20);
            std::cout << "Now setting weight of entire tree" << std::endl;
            x = get_total_weight();
            std::cout << "Received total: " << x << " from A node after forking ALL children" << std::endl;
            // should be 14
            assert(x == 14);
            x = get_heaviest_child();
            // should be B (so pidB)
            assert(x == pidB);
        }
    }
    cout << "===== SUCCESS =====" << endl;
    return 0;
}

