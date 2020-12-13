#include "hw2_test.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <cassert>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


using namespace std;

int main() {
srand(time(NULL));
int top = rand()%100;
int mid = rand()%100;
int low =rand()%100;
int mid2 = rand()%100;

//	std::cout << "enter weights for top, mid, mid2, bottom"<< std::endl;
//	std::cin >> top >> mid >> mid2 >> low;

    	set_weight(top);
	//std::cout << "the top alone (should be "<< top<< " ) weight is: " << get_total_weight() << std::endl;
	assert(get_total_weight() == top);

	pid_t pid1 = fork();
	if (pid1==0){
		set_weight(mid);
		//std::cout << "the mid alone (should be " << mid << ") weight is: " << get_total_weight() << std::endl;
		assert(get_total_weight()==mid);
		pid_t pid2 = fork();
		if (pid2 == 0){
			set_weight(low);
			//std::cout << "the bottom alone, son of mid (should be " << low << ") weight is: " << get_total_weight() << std::endl;
			assert(get_total_weight() == low);
			sleep(10);
		}
		else{
			sleep(1);
			//std::cout << "the mid together with bottom (should be " << low+mid << ") weight is: " << get_total_weight() << std::endl;
			assert(get_total_weight() == low+mid);
			assert(get_heaviest_child() == pid2);
			sleep(10);
		}
	}
	else{
		pid_t second_lane = fork();
		if(second_lane == 0){
			set_weight(mid2);
			sleep(10);
		}
		else{
			sleep(2);
			//std::cout << "the top together (should be " << low+mid+mid2+top << " ) weight is: " << get_total_weight() << std::endl;
			assert(get_total_weight()==low+mid+mid2+top);
			//std::cout << "the pid of first branch (mid-bottom) is: " << pid1 << " and it's total weight is: " << low+mid << std::endl;
			//std::cout << "the pid of second branch (of mid2) is: " << second_lane << " and it's total weight is: " << mid2 <<  std::endl;
			//std::cout << "the func returns the pid: " << get_heaviest_child() << std::endl;
			pid_t bigger = get_heaviest_child();
			(low+mid > mid2) ? assert(bigger==pid1) : assert (bigger==second_lane);
			std::cout << "=====GREAT SUCCESS!=====" << endl;
		}
	}
	sleep(2);
	return 0;
}





/*
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
*/