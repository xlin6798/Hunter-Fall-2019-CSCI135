/*
Author: Xinyi Lin
Course: CSCI-135
Instructor Genady Maryash
Assignment: E3.1

The program below asks user for 3 inputs and prints a statement using the 3 inputs.
*/
#include <iostream>

int main()
{
  int i;
  std::cout << "Enter a number" << std::endl;
  std::cin >> i;
  if (i > 0)
    std::cout << "positive" << std::endl;
  else if (i < 0)
    std::cout << "negative" << std::endl;
  else
    std::cout << "zero" << std::endl;
}
