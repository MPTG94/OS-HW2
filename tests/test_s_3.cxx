#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

using namespace std;


int main() {

    int x = set_weight(3);

    int pid2 = fork();
    if (pid2 == 0) {
        x = set_weight(4);

        int pid3 = fork();
        if (pid3 == 0) {
            x = set_weight(5);

            int pid4 = fork();
            if (pid4 == 0) {
                x = set_weight(30);

                int pid5 = fork();
                if (pid5 == 0) {
                    // weight should be 30
                    sleep (1);
                    return 0;
                }

                sleep(2);
                return 0;
            }

            sleep(2);
            return 0;
        }
        sleep(2);
        return 0;
    }

    pid2 = fork();
    if (pid2 == 0) {
        x = set_weight(5);

        int pid3 = fork();
        if (pid3 == 0) {
            x = set_weight(2);

            int pid4 = fork();
            if (pid4 == 0) {
                x = set_weight(100);
                sleep(1);
                return 0;
            }

            sleep(2);
            return 0;
        }
        sleep(2);
        return 0;
    }

    sleep(1);
    x = get_total_weight();
    if (x == 179) {
        cout << "PASS" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }

}

