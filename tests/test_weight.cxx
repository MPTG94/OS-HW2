#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>

int main(){
  int ret = syscall(334, 4);
  std::cout << "parent set weight=4 returned " << ret << "\n";
  int fork_ret = fork();
  if (fork_ret < 0){
    std::cout << "fork failed";
    return -1;
  } else if (fork_ret == 0){
    // child
    ret = syscall(335);
    std::cout << "child get total weight returned " << ret << "\n";
    ret = syscall(336);
    std::cout << "child get heaviest1 returned " << ret << "\n";
    ret = syscall(334, 5);
    std::cout << "child set weight=5 returned " << ret << "\n";
    fork_ret = fork();
    if (fork_ret < 0){
      std::cout << "fork2 failed";
      return -1;
    } else if (fork_ret == 0){
      ret = syscall(334, 6);
      std::cout << "child2 set weight=6 returned " << ret << "\n";
      sleep(5);
      _exit(0);
    }
    sleep(1);
    ret = syscall(336);
    std::cout << "child get heaviest2 returned " << ret << "\n";
    sleep(5);
    _exit(0);
  }
  // parent
  sleep(2);
  ret = syscall(335);
  std::cout << "parent get total weight returned " << ret << "\n";
  ret = syscall(336);
  std::cout << "parent get heaviest returned " << ret << "\n";
  return 0;
}
  
