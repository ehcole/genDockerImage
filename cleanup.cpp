#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main(int argc, char** argv) {
  cout << "Cleaning up." << endl;
  system("rm -rf cleanup CMakeFiles CMakeCache.txt cmake_install.cmake Makefile genDockerfile");
  return 0;
}
