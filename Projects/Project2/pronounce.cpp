/*
Author: Xinyi Lin
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 2

The program below reads a word and implements a linguistic application that uses a pronunciation dictionary for finding words with similar pronunciation.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <vector>

void splitOnSpace(std::string, std::string&, std::string&);

bool ignoreOr(std::string);
bool spaceExist(std::string);
bool compareTwoVectors(std::vector<std::string>, std::vector<std::string>);

std::string addPhoneme(std::string);
std::string toUpperCase(std::string);
std::string removePhoneme(std::string);
std::string replacePhoneme(std::string);
std::string findPronounciation(std::string);
std::string findIdentical(std::string, std::string);
std::vector<std::string> splitIntoVector(std::string);

int main()
{
  std::string userInput;
  std::cin >> userInput;
  userInput = toUpperCase(userInput);
  std::string pro;
  if (ignoreOr(userInput)){   
     pro = findPronounciation(userInput);
    if (pro != "Not found"){
      std::cout << "Pronunciation    :" + pro + '\n';
      std::cout << "Identical        : " + findIdentical(userInput, pro) + '\n';
      std::cout << "Add phoneme      : " + addPhoneme(pro) + '\n';
      std::cout << "Remove phoneme   : " + removePhoneme(pro) + '\n';
      std::cout << "Replace phoneme  : " + replacePhoneme(pro) + '\n';
    }
    else
      std::cout << pro;
  }
}

bool ignoreOr(std::string str)  //check if word contains non-aplhabet characters besides '
{
  for (int i = 0; i < str.length(); i++){
    if (str.at(i) == '(')
      return false;
    if (!((str.at(i) >= 'A' && str.at(i) <= 'Z') || str.at(i) != ';'))
      return false;
  }
  return true;
}

std::string findPronounciation(std::string userInput)
{
  std::ifstream fin("cmudict.0.7a");
  if (fin.fail()){
    std::cerr << "File cannot be opened for reading." << '\n';  //output error if file not found or cannot be opened
    exit(1);
  }

  for (int i = 1; i <= 118; i++){  //ignore junk lines from beginning
    std::string junk;
    getline(fin, junk);
  }

  std::string line;
  while (getline(fin, line)){ 
    std::string before;  //words
    std::string after;  //phoneme
    splitOnSpace(line, before, after);
    if (!ignoreOr(before))
      continue;
    if (before.compare(userInput) == 0){  //if word found in file
      fin.close();
      return after;
    }
  }

  fin.close();
  return "Not found";  //if word not found in file
}

std::string findIdentical(std::string userInput, std::string str)
{
  std::string ret = "";
  std::ifstream fin("cmudict.0.7a");
  if (fin.fail()){
    std::cerr << "File cannot be opened for reading." << '\n';
    exit(1);
  }

  for (int i = 1; i <= 118; i++){
    std::string junk;
    getline(fin, junk);
  }

  std::string line;
  while (getline(fin, line)){ 
    std::string before;
    std::string after;
    splitOnSpace(line, before, after);
    if (before.find('(') != std::string::npos)
      continue;
    if (after.compare(str) == 0 && before.compare(userInput) != 0){  //if words have identical phoneme
      ret += before + " ";
    }
  }

  fin.close();

  return ret;  //return all identical words
}

std::string replacePhoneme(std::string pro)
{
  std::string ret = "";
  std::ifstream fin("cmudict.0.7a");
  if (fin.fail()){
    std::cerr << "File cannot be opened for reading." << '\n';
    exit(1);
  }

  for (int i = 1; i <= 118; i++){
    std::string junk;
    getline(fin, junk);
  }

  std::vector<std::string> strs1 = splitIntoVector(pro.substr(1, pro.length() - 1));  //splits into vector by space
  std::string line;
  while (getline(fin, line)){ 
    std::string before;
    std::string after;
    splitOnSpace(line, before, after);
    if (!ignoreOr(before))
      continue;
    std::vector<std::string> strs2 = splitIntoVector(after.substr(1, after.length() - 1));  //splits into vector by space
    if (strs1.size() == strs2.size()){
      if (compareTwoVectors(strs1, strs2))
	ret += before + " ";
    } 
  }

  fin.close();

  return ret;
}

std::string addPhoneme(std::string pro)
{
  std::string ret = "";
  std::ifstream fin("cmudict.0.7a");
  if (fin.fail()){
    std::cerr << "File cannot be opened for reading." << '\n';
    exit(1);
  }

  for (int i = 1; i <= 118; i++){
    std::string junk;
    getline(fin, junk);
  }

  std::vector<std::string> strs1 = splitIntoVector(pro.substr(1, pro.length() - 1));
  std::string line;
  while (getline(fin, line)){ 
    std::string before;
    std::string after;
    splitOnSpace(line, before, after);
    if (!ignoreOr(before))
      continue;
    std::vector<std::string> strs2 = splitIntoVector(after.substr(1, after.length() - 1));
    if (strs1.size() == strs2.size() - 1){  //if strs1 has exactly one less element than strs2
      if (compareTwoVectors(strs2, strs1))  //compare the two vectors, strs2 is first argument because its size is larger
	ret += before + " ";
    } 
  }

  fin.close();

  return ret;
}

std::string removePhoneme(std::string pro)
{
  std::string ret = "";
  std::ifstream fin("cmudict.0.7a");
  if (fin.fail()){
    std::cerr << "File cannot be opened for reading." << '\n';
    exit(1);
  }

  for (int i = 1; i <= 118; i++){
    std::string junk;
    getline(fin, junk);
  }

  std::vector<std::string> strs1 = splitIntoVector(pro.substr(1, pro.length() - 1));
  std::string line;
  while (getline(fin, line)){ 
    std::string before;
    std::string after;
    splitOnSpace(line, before, after);
    if (!ignoreOr(before))
      continue;
    std::vector<std::string> strs2 = splitIntoVector(after.substr(1, after.length() - 1));
    if (strs1.size() == strs2.size() + 1){  //if strs1 has exactly one more element than strs2
      if (compareTwoVectors(strs1, strs2))  //compare the two vectors, strs1 is first argument because its size is larger
	ret += before + " ";
    } 
  }

  fin.close();

  return ret;
}

void splitOnSpace(std::string s, std::string & before, std::string & after) {
  // reset strings
    before = ""; 
    after = "";
  // accumulate before space
    int i = 0;
    while (i < s.size() && not isspace(s[i])) { 
        before = before + s[i]; 
        i++; 
    }
  // skip the space
    i++;
    // accumulate after space
    while (i < s.size()) { 
        after = after + s[i]; 
        i++; 
    }
}

std::string toUpperCase(std::string str)  //returns a word in all uppercase letters
{
  std::string ret = "";
  for (int i = 0; i < str.length(); i++)
    ret += toupper(str.at(i));
  return ret;
}

std::vector<std::string> splitIntoVector(std::string str)
{
  std::vector<std::string> strs;
  std::string before;  //words
  std::string after;  //phoneme
  while (spaceExist(str)){  
    splitOnSpace(str, before, after);
    str = after;
    strs.push_back(before);
  }
  strs.push_back(after);
  return strs;
}

bool spaceExist(std::string str)  //checks if there is space in a string
{
  for (auto c : str)
    if (isspace(c))
      return true;
  return false;
}

bool compareTwoVectors(std::vector<std::string> strs1, std::vector<std::string> strs2)  //compares two vectors based on conditions
{
  int i = 0;
  if (strs1.size() == strs2.size()){  //checks if all elements match but one, in the same order
    for (int x = 0; x < strs1.size(); x++){
      if (strs1.at(x).compare(strs2.at(x)) == 0)
	i++;
    }
    if (i == strs1.size() - 1)
      return true;
  }
  else if (strs1.size() == strs2.size() + 1){  //checks if strs1 has all elements from strs2, in the same order, but this time strs1 has exactly one element more than strs2
    for (int x = 0; x <strs1.size(); x++){
      if (strs1.at(x).compare(strs2.at(i)) == 0)
	i++;
      if (i == strs2.size())
	return true;
    }
  }
  
  return false;
}
