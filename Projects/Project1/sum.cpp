/*
Author: Xinyi Lin
Course: CSCI-135
Instructor: Gennadiy Maryash
Assignment: Project 1 Task A

The program below reads a sequence of integers from cin, and reports their sum.
*/

#include <iostream>

int main()
{
  int i;
  int sum = 0;
  
  while(std::cin >> i){
    sum += i;
  }
  
  std::cout << sum << std::endl;
}
