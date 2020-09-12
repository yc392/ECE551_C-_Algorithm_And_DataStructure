#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv) {
  std::vector<std::string> v;
  std::ifstream read;
  std::string s;
  if (argc == 1) {
    if (!std::cin.eof() && !std::cin.good()) {
      std::cerr << "failed to read file" << std::endl;
      exit(EXIT_FAILURE);
    }
    while (!std::cin.eof()) {
      std::getline(std::cin, s);
      v.push_back(s);
      //      std::sort(v.begin(), v.end());
    }
    std::sort(v.begin(), v.end());
    std::vector<std::string>::iterator it = v.begin();
    while (it != v.end()) {
      std::cout << *it << "\n";
      ++it;
    }
    v.clear();
  }
  else {
    /*for (int i = 1; i < argc; i++) {
      read.open(argv[i]);
      if (read.fail()) {
        std::cerr << "cannot read from file" << std::endl;
        return EXIT_FAILURE;
      }
      while (!read.eof()) {
        std::getline(read, s);
        v.push_back(s);
      }
      // std::sort(v.begin(), v.end());
      read.close();
    }
    std::sort(v.begin(), v.end());
    std::vector<std::string>::iterator it = v.begin();
    it += 2;
    while (it != v.end()) {
      std::cout << *it << "\n";
      ++it;
    }
    }*/
    for (int i = 1; i < argc; i++) {
      read.open(argv[i]);
      if (read.fail()) {
        std::cerr << "cannot read from file" << std::endl;
        return EXIT_FAILURE;
      }
      while (!read.eof()) {
        std::getline(read, s);
        v.push_back(s);
      }
      //sort
      std::sort(v.begin(), v.end());
      //print
      //      std::sort(v.begin(), v.end());
      std::vector<std::string>::iterator it = v.begin();
      it += 2;
      while (it != v.end()) {
        std::cout << *it << "\n";
        ++it;
      }
      v.clear();
      read.close();
    }
  }

  return EXIT_SUCCESS;
}
