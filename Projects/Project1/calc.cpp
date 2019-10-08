/*
Author: Xinyi Lin
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 1 Task B

The program below reads a sequence of integers from cin, and reports their sum.
*/

#include <iostream>
#include <string>
#include <vector>

int main()
{
    
    std::string s;
    
    std::vector<std::string> strArr;
    
    while(std::cin >> s)
    {
        int x = 0;  //x serves as a temporary index value
        bool cont = false;
        while(!cont)
        {
            if (s.length() == 1)    //if string s length is equal to 1, add string s into the back of string array strArr
            {
                strArr.push_back(s);
                cont = true;
            }
            else if (s.at(x) == '+' || s.at(x) == '-')  //if index x of string s is + or -
            {
                if (x == 0) //if x is 0
                {
                    strArr.push_back(s.substr(0, 1));
                    s = s.substr(1, s.length() - 1);
                }
                else if(x > 0)  //if x is greater than 0
                {
                    if(x == s.length() - 1) //if x is the last index of string s
                    {
                        cont = true;
                    }
                    strArr.push_back(s.substr(0, x));
                    strArr.push_back(s.substr(x, 1));
                    s = s.substr(x + 1, s.length() - x - 1);
                }
                    x = 0;
            }
            else
            {
                x++;
            }
            
            if(x == s.length() && !cont)    //if index x is out of bound and if cont is true
            {
                strArr.push_back(s);
                cont = true;
            }
                
            
        }
    }
    
    int res = std::stoi(strArr.at(0));  //initialize integer res with the first value of strArr
    
    if(strArr.size() > 1) //
    {
        for(int i = 1; i < strArr.size(); i+=2)
        {
            if(strArr.at(i) == "+")
                res += std::stoi(strArr.at(i+1));
            else
                res -= std::stoi(strArr.at(i+1));
        }
    }
    
    std::cout << res << "\n";   //prints final result
    
    return 0;
}
