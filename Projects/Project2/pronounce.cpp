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
#include <cctype> 
#include <string>

void splitOnSpace(std::string, std::string&, std::string&);

bool ignoreOr(std::string);
bool spaceExist(std::string);
bool compareTwoArray(std::string*, int, std::string*, int);


int countLength(std::string);

std::string addPhoneme(std::string);
std::string toUpperCase(std::string);
std::string removePhoneme(std::string);
std::string replacePhoneme(std::string);
std::string findPronounciation(std::string);
std::string findIdentical(std::string, std::string);
std::string* splitIntoArray(std::string);

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

  std::string* strs1 = splitIntoArray(pro.substr(1, pro.length() - 1));
  int strs1len = countLength(pro.substr(1, pro.length() - 1));
  std::string line;
  while (getline(fin, line)){ 
    std::string before;
    std::string after;
    splitOnSpace(line, before, after);
    if (!ignoreOr(before))
      continue;
    std::string* strs2 = splitIntoArray(after.substr(1, after.length() - 1));
    int strs2len = countLength(after.substr(1, after.length() - 1));
    if (strs1len == strs2len){  //if strs1 has exactly one less element than strs2
      if (compareTwoArray(strs2, strs2len, strs1, strs1len))  //compare the two arrays, strs2 is first argument because its size is larger
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

  std::string* strs1 = splitIntoArray(pro.substr(1, pro.length() - 1));
  int strs1len = countLength(pro.substr(1, pro.length() - 1));
  std::string line;
  while (getline(fin, line)){ 
    std::string before;
    std::string after;
    splitOnSpace(line, before, after);
    if (!ignoreOr(before))
      continue;
    std::string* strs2 = splitIntoArray(after.substr(1, after.length() - 1));
    int strs2len = countLength(after.substr(1, after.length() - 1));
    if (strs1len == strs2len - 1){  //if strs1 has exactly one less element than strs2
      if (compareTwoArray(strs2, strs2len, strs1, strs1len))  //compare the two arrays, strs2 is first argument because its size is larger
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

  std::string* strs1 = splitIntoArray(pro.substr(1, pro.length() - 1));
  int strs1len = countLength(pro.substr(1, pro.length() - 1));
  std::string line;
  while (getline(fin, line)){ 
    std::string before;
    std::string after;
    splitOnSpace(line, before, after);
    if (!ignoreOr(before))
      continue;
    std::string* strs2 = splitIntoArray(after.substr(1, after.length() - 1));
    int strs2len = countLength(after.substr(1, after.length() - 1));
    if (strs1len == strs2len + 1){  //if strs1 has exactly one less element than strs2
      if (compareTwoArray(strs1, strs1len, strs2, strs2len))  //compare the two arrays, strs2 is first argument because its size is larger
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
    while (i < s.length() && not isspace(s[i])) { 
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

int countLength(std::string str)
{
  int count = 0;
  for (int i = 0; i < str.length(); i++) {
    if (isspace(str.at(i)))
      count ++;
  }
  return count + 1;
}

std::string* splitIntoArray(std::string str)
{
  int strLen = countLength(str);
  std::string* strs = new std::string[strLen];
  std::string before;  //words
  std::string after;  //phoneme
  int i = 0;
  while (spaceExist(str)){  
    splitOnSpace(str, before, after);
    str = after;
    strs[i] = before;
    i++;
  }
  strs[i] = after;
  return strs;
}

bool spaceExist(std::string str)  //checks if there is space in a string
{
  for (auto c : str)
    if (isspace(c))
      return true;
  return false;
}

bool compareTwoArray(std::string strs1[], int strs1len, std::string strs2[], int strs2len)  //compares two strings based on conditions
{
  int i = 0;
  strs1[1];
  if (strs1len == strs2len){  //checks if all elements match but one, in the same order
    for (int x = 0; x < strs1len; x++){
      if (strs1[x].compare(strs2[x]) == 0)
	i++;
    }
    if (i == strs1len - 1)
      return true;
  }
  else if (strs1len == strs2len + 1){  //checks if strs1 has all elements from strs2, in the same order, but this time strs1 has exactly one element more than strs2
    for (int x = 0; x <strs1len; x++){
      if (strs1[x].compare(strs2[i]) == 0)
	i++;
      if (i == strs2len)
	return true;
    }
  }
  
  return false;
}
