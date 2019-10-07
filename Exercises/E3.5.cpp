/*
Author: Xinyi Lin
Course: CSCI-135
Instructor: Genady Maryash
Assignment: E3.5

The program below reads three numbers and prints out whether they are in increasing or decreasing order or neither.
*/

#include <iostream>
int main()
{
  float a, b, c;
  std::cin >> a >> b >> c;
     if (a > b && b > c)
       std::cout << "decreasing";
     else if (a < b && b < c)
       std::cout << "increasing";
     else
       std::cout << "neither";
     std::cout << "\n";
}
