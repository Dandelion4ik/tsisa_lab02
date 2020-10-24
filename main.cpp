#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <vector>

double function_value(const double &x) { return -sqrt(x) * sin(x) + 2; }

double function_value_sin5x(const double &x) {
  return (-sqrt(x) * sin(x) + 2) * sin(5 * x);
}

double finding_the_minimum(const double &n) {
  std::random_device rd;
  std::vector<double> vec = {};
  for (int i = 0; i < n; ++i) {
    auto x = (rd() % 3001 + 1000) * 0.001;
    vec.push_back(function_value(x));
  }
  return *std::min_element(vec.begin(), vec.end());
}

double finding_the_minimum_sin5x(const double &n) {
  std::random_device rd;
  std::vector<double> vec = {};
  for (int i = 0; i < n; ++i) {
    auto x = (rd() % 3001 + 1000) * 0.001;
    vec.push_back(function_value_sin5x(x));
  }
  return *std::min_element(vec.begin(), vec.end());
}

void line() {
  for (int i = 0; i < 11; ++i) {
    std::cout << "+--------";
  }
  std::cout << "+" << std::endl;
}

void cap() {
  line();
  std::cout << '|' << std::setw(8) << std::right << "q/p" << '|';
  for (size_t i = 90; i < 100; i += 1) {
    std::cout << std::setw(8) << std::right << i * 0.01 << '|';
  }
  std::cout << std::endl;
  line();
}

void print(std::map<double, std::vector<double>> &columns) {
  cap();
  for (size_t i = 5; i <= 100; i += 5) {
    std::cout << '|' << std::setw(8) << std::right << i * 0.001 << '|';
    for (auto &it : columns[i * 0.001]) {
      std::cout << std::setw(8) << std::right << it << '|';
    }
    std::cout << std::endl;
  }
  line();
}

void print_n_p_q(const std::vector<double> &p, const std::vector<double> &q) {
  std::cout << "Dependence of N on P and q" << std::endl;
  cap();
  for (auto &it_q : q) {
    std::cout << '|' << std::setw(8) << std::right << it_q << '|';
    for (auto &it_p : p) {
      int n = (int)(log(1 - it_p) / log(1 - it_q));
      std::cout << std::setw(8) << std::right << n << '|';
    }
    std::cout << std::endl;
  }
  line();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}

int main() {
  std::vector<double> p = {};
  std::vector<double> q = {};
  std::map<double, std::vector<double>> columns;
  std::map<double, std::vector<double>> columns_sin5x;
  for (size_t i = 90; i < 100; i += 1) {
    p.push_back(0.01 * i);
  }
  for (size_t i = 5; i <= 100; i += 5) {
    q.push_back(0.001 * i);
  }
  print_n_p_q(p, q);
  for (auto &it_p : p) {
    for (auto &it_q : q) {
      int n = (int)(log(1 - it_p) / log(1 - it_q));
      columns[it_q].push_back(finding_the_minimum(n));
    }
  }
  for (auto &it_p : p) {
    for (auto &it_q : q) {
      int n = (int)(log(1 - it_p) / log(1 - it_q));
      columns_sin5x[it_q].push_back(finding_the_minimum_sin5x(n));
    }
  }
  std::cout << "Search results for the extremum depending on P and q"
            << std::endl;
  print(columns);
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Search results for the extremum depending on P and q for a "
               "multimodal function"
            << std::endl;
  print(columns_sin5x);
  return 0;
}
