#include <iostream>
/*
Author: Xinyi Lin
Course: CSCI-135
Instructor Gennadiy Maryash
Assignment: E2.10

The program below asks user for 3 inputs and prints a statement using the 3 inputs.
*/
using namespace std;
int main()
{
	float numOfGal;
	float fuelEff;
	float cost;
        cout << "The number of gallons of gas in the tank: ";
	cin >> numOfGal;
        cout << "The fuel efficiency in miles per gallon: ";
	cin >> fuelEff;
        cout << "The price of gas per gallon:  ";
        cin >> cost;
	cout << "The cost per 100 miles is " <<  100/fuelEff*cost << " and the car can go " << numOfGal*fuelEff << " miles with the gas in the tank" << endl;
	return 0;
}


