#include <array>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

bool is_safe(const std::vector<int> &list);
bool is_increasing_or_decreasing(const std::vector<int> &list);
bool dampener(const std::vector<int> &list);

int main(int argc, char **argv) {

  std::array<std::vector<int>, 1000> list;
  int inp{};
  int safe_count{};

  for (int i = 0; i < 1000; i++) {
    std::string line;
    if (!std::getline(std::cin, line)) { // Read the entire line
      std::cerr << "Error reading input. Terminating." << std::endl;
      break;
    }
    std::istringstream input(line);
    int number{};
    while (input >> number) {
      list[i].push_back(number);
    }
  }

  std::cout << "----------------------DONE-------------------" << std::endl;

  // Process each report
  for (const auto &report : list) {
    if (is_safe(report) && is_increasing_or_decreasing(report)) {
      ++safe_count; // Safe without modification
    } else if (dampener(report)) {
      ++safe_count; // Safe after applying Problem Dampener
    }
  }

  std::cout << safe_count << std::endl;
  return 0;
}

bool dampener(std::vector<int> &list, const int i) {
  list.erase(list.begin() + i);
  return true;
}

// Check if the report's adjacent differences are within the range [1, 3]
bool is_safe(const std::vector<int> &list) {
  for (size_t i = 0; i < list.size() - 1; ++i) {
    int diff = std::abs(list[i] - list[i + 1]);
    if (diff < 1 || diff > 3) {
      return false;
    }
  }
  return true;
}

// Check if the report is either increasing or decreasing
bool is_increasing_or_decreasing(const std::vector<int> &list) {
  bool increasing = true, decreasing = true;
  for (size_t i = 0; i < list.size() - 1; ++i) {
    if (list[i] >= list[i + 1]) {
      increasing = false;
    }
    if (list[i] <= list[i + 1]) {
      decreasing = false;
    }
  }
  return increasing || decreasing;
}

// Apply the Problem Dampener logic: try removing one level and check
bool dampener(const std::vector<int> &list) {
  for (size_t i = 0; i < list.size(); ++i) {
    std::vector<int> modified_list = list;
    modified_list.erase(modified_list.begin() + i); // Remove one level
    if (is_safe(modified_list) && is_increasing_or_decreasing(modified_list)) {
      return true;
    }
  }
  return false;
}