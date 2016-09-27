#include <iostream>
#include <fstream>
#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"
#include <string>
#include <regex>
#include <vector>

using namespace std;

string cipertext;
const int MAX_ATTEMPTS = 3;
int chances = 0; //number of attempts
void* sifter(void *);
void* decoder(void *);
void* substitute(void *);
void* hill(void *);
void* pinnacol(void *);
pthread_mutex_t mut;
string plaintext1, plaintext2, plaintext3;
string error1, error2, error3;


//if (pthread_join(thread1) != 0) {
//
//}

int main() {

  pthread_t thread1;
  pthread_create(&thread1, NULL, sifter, (void *)NULL);

  pthread_join(thread1, NULL);

  return 0;

  }
void* sifter(void *c) {


  chances = 0;
  while (true) {
    if (chances == MAX_ATTEMPTS) {
          cout << "You have exceeded the number of attempts, intruder!" << endl;
        return 0;
    }
    string line;
    getline(cin,line);
    if (line == "quit") {
      return 0;
    }
      else {
        plaintext1 = "";
        plaintext2 = "";
        plaintext3 = "";

        error1 = "";
        error2 = "";
        error3 = "";


  //split this regex up into 6 pieces so you can match AND split it

  //p1 means _*_***_**
  regex p1("(.*)\\*(.+)\\*\\*\\*(.+)\\*\\*(.+)");
  // p2 means _*_**_***
  regex p2("(.*)\\*(.+)\\*\\*(.+)\\*\\*\\*(.+)");
  // p3 means _**_***_*
  regex p3("(.*)\\*\\*(.+)\\*\\*\\*(.+)\\*(.+)");
  // p4 means _**_*_***
  regex p4("(.*)\\*\\*(.+)\\*(.+)\\*\\*\\*(.+)");
  // p5 means _***_*_**
  regex p5("(.*)\\*\\*\\*(.+)\\*(.+)\\*\\*(.+)");
  // p6 means _***_**_*
  regex p6("(.*)\\*\\*\\*(.+)\\*\\*(.+)\\*(.+)");

  int typeOfPattern = -1;
  vector<regex> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);
  v.push_back(p4);
  v.push_back(p5);
  v.push_back(p6);

  bool isValid = 1;

  for (int i = 0; i <= 5; i++) {
    if (regex_match(line, v[i])) {
      //cout << x << " matches the pattern " << "p" << i + 1 << endl;
      typeOfPattern = i;
      isValid = 1;
      break;
    }
    else {
      isValid = 0;
    }
  }
  if (!isValid) {
    cout << line + " does not match the pattern" << endl;
    chances++;
  }

if (typeOfPattern != -1) {
  line += to_string(typeOfPattern+1);
  pthread_t threadDecoder;
  pthread_create(&threadDecoder, NULL, decoder, (void *)&line);

  pthread_join(threadDecoder, NULL);
    }

  }
  if (plaintext1 != "") {
    cout << plaintext1 << endl << endl;
  } else {
    cout << error1 << endl;
  }
  if (plaintext2 != "") {
    cout << plaintext2 << endl << endl;
  } else {
    cout << error2 << endl;
  }
  if (plaintext3 != "") {
    cout << plaintext3 << endl << endl;
  } else {
    cout << error3 << endl;
  }


}
}

//type of pattern is encoded in whatever string this recieves, it is the last char.
//need to splice string's last char and split new string for 1 of 6 patterns
void* decoder(void *c) {
string &x = *static_cast<string*>(c);
//cout << "The string created is: " << x << endl;

char ch = x[x.length() - 1];
//cut off last digit
x.pop_back();
//cout << ch << endl;
int startOne, startTwo, startThree;
int lengthOne, lengthTwo, lengthThree;
vector<string> result;
switch(ch) {
  case '1':

  for(int i = 0; i < x.length(); i++) {
    if (x[i] == '*') {
      startOne = i + 1;
      break;
    }
  }
  for(int i = startOne; i < x.length(); i++) {
    if (x[i] == '*') {
      startThree = i + 3;
      break;
    }
  }
  for(int i = startThree; i < x.length(); i++) {
    if (x[i] == '*') {
      startTwo = i + 2;
      break;
    }
  }
  lengthOne = startThree - startOne - 3;
  lengthThree = startTwo - startThree - 2;
  lengthTwo = x.length() - startTwo;

  //cout << "Lengths are: " << to_string(lengthOne) << " " << to_string(lengthThree) << " " << to_string(lengthTwo) << endl;

  result.push_back(x.substr(startOne,lengthOne));
  result.push_back(x.substr(startTwo,lengthTwo));
  result.push_back(x.substr(startThree,lengthThree));
  break;
  case '2':
  for(int i = 0; i < x.length(); i++) {
    if (x[i] == '*') {
      startOne = i + 1;
      break;
    }
  }
  for(int i = startOne; i < x.length(); i++) {
    if (x[i] == '*') {
      startTwo = i + 2;
      break;
    }
  }
  for(int i = startTwo; i < x.length(); i++) {
    if (x[i] == '*') {
      startThree = i + 3;
      break;
    }
  }
  lengthOne = startTwo - startOne - 2;
  lengthTwo = startThree - startTwo - 3;
  lengthThree = x.length() - startThree;

  //cout << "Lengths are: " << to_string(lengthOne) << " " << to_string(lengthTwo) << " " << to_string(lengthThree) << endl;

  result.push_back(x.substr(startOne,lengthOne));
  result.push_back(x.substr(startTwo,lengthTwo));
  result.push_back(x.substr(startThree,lengthThree));

  break;

  case '3':

  for(int i = 0; i < x.length(); i++) {
    if (x[i] == '*') {
      startTwo = i + 2;
      break;
    }
  }
  for(int i = startTwo; i < x.length(); i++) {
    if (x[i] == '*') {
      startThree = i + 3;
      break;
    }
  }
  for(int i = startThree; i < x.length(); i++) {
    if (x[i] == '*') {
      startOne = i + 1;
      break;
    }
  }
  lengthTwo = startThree - startTwo - 3;
  lengthThree = startOne - startThree - 1;
  lengthOne = x.length() - startOne;

  //cout << "Lengths are: " << to_string(lengthTwo) << " " << to_string(lengthThree) << " " << to_string(lengthOne) << endl;

  result.push_back(x.substr(startOne,lengthOne));
  result.push_back(x.substr(startTwo,lengthTwo));
  result.push_back(x.substr(startThree,lengthThree));

  break;
  case '4':
  // 2_1_3_

  for(int i = 0; i < x.length(); i++) {
    if (x[i] == '*') {
      startTwo = i + 2;
      break;
    }
  }
  for(int i = startTwo; i < x.length(); i++) {
    if (x[i] == '*') {
      startOne = i + 1;
      break;
    }
  }
  for(int i = startOne; i < x.length(); i++) {
    if (x[i] == '*') {
      startThree = i + 3;
      break;
    }
  }
  lengthTwo = startOne - startTwo - 1;
  lengthOne = startThree - startOne - 3;
  lengthThree = x.length() - startThree;

  //cout << "Lengths are: " << to_string(lengthTwo) << " " << to_string(lengthOne) << " " << to_string(lengthThree) << endl;

  result.push_back(x.substr(startOne,lengthOne));
  result.push_back(x.substr(startTwo,lengthTwo));
  result.push_back(x.substr(startThree,lengthThree));

  break;
  case '5':
  //3_1_2_
  for(int i = 0; i < x.length(); i++) {
    if (x[i] == '*') {
      startThree = i + 3;
      break;
    }
  }
  for(int i = startThree; i < x.length(); i++) {
    if (x[i] == '*') {
      startOne = i + 1;
      break;
    }
  }
  for(int i = startOne; i < x.length(); i++) {
    if (x[i] == '*') {
      startTwo = i + 2;
      break;
    }
  }
  lengthThree = startOne - startThree - 1;
  lengthOne = startTwo - startOne - 2;
  lengthTwo = x.length() - startTwo;

  //cout << "Lengths are: " << to_string(lengthThree) << " " << to_string(lengthOne) << " " << to_string(lengthTwo) << endl;

  result.push_back(x.substr(startOne,lengthOne));
  result.push_back(x.substr(startTwo,lengthTwo));
  result.push_back(x.substr(startThree,lengthThree));

  break;

  case '6':
  //3_2_1_
  for(int i = 0; i < x.length(); i++) {
    if (x[i] == '*') {
      startThree = i + 3;
      break;
    }
  }
  for(int i = startThree; i < x.length(); i++) {
    if (x[i] == '*') {
      startTwo = i + 2;
      break;
    }
  }
  for(int i = startTwo; i < x.length(); i++) {
    if (x[i] == '*') {
      startOne = i + 1;
      break;
    }
  }
  lengthThree = startTwo - startThree - 2;
  lengthTwo = startOne - startTwo - 1;
  lengthOne = x.length() - startOne;

  //cout << "Lengths are: " << to_string(lengthThree) << " " << to_string(lengthTwo) << " " << to_string(lengthOne) << endl;

  result.push_back(x.substr(startOne,lengthOne));
  result.push_back(x.substr(startTwo,lengthTwo));
  result.push_back(x.substr(startThree,lengthThree));



  break;
}

/* print the vector
for(string &e: result) {
  cout << e << endl;
}
*/

pthread_t p2;
pthread_t p3;
pthread_t p4;

pthread_create(&p2, NULL, substitute, (void *)&result[0]);

pthread_create(&p3, NULL, hill, (void *)&result[1]);

pthread_create(&p4, NULL, pinnacol, (void *)&result[2]);


pthread_join(p2, NULL);
pthread_join(p3, NULL);
pthread_join(p4, NULL);


}



void* substitute(void *c) {
string &x = *static_cast<string*>(c);
//cout << x << endl;
//check the string
if (x.length() <= 2) {
  error1 += "The substring after * is not long enough!\n";
  return 0;
}
bool valid = 1;
if (!isalpha(x.at(0))) {
  error1 += "The first character must be in the alphabet!\n";
  return 0;
}
for (int i = 2; i < x.length(); i++) {
  if (!isalpha(x.at(i))) {
    valid = 0;
  }
}

if (!valid) {
  error1 += "The second token must consist of only alphabet characters!\n";
  return 0;
}

//If the string passed, set global plaintext1
string y = x.substr(2, x.length() - 2);
//cout << y << endl;
int numberOfShifts;
int abcCode;
numberOfShifts =((toupper(x.at(0)) - 65) % 10) + 2;
//cout << numberOfShifts << endl;
for (int i = 0; i < y.length(); i++) {
  abcCode = toupper(y.at(i)) - 65;
  //cout << abcCode << endl;
  int temp = (((abcCode - numberOfShifts) % 26) + 26) % 26;
  //cout << temp << endl;
  char ch = (65 + temp);
  y.at(i) = ch;

}
plaintext1 = y;



}

void* hill(void *f) {
string &x = *static_cast<string*>(f);
if (x.length() <= 9) {
  error2 += "The substring after ** is not even long enough!\n";
  return 0;
}
//split it up
int space;
for (int i = 0; i < x.length(); i++) {
  if (x.at(i) == ' ') {
    space = i;
    break;
  }
}
string firstToken = x.substr(0, space);
//cout << "first token: " << firstToken << endl;
string secondToken = x.substr(space + 1, x.length() - space - 1);
//cout << "second token: " << secondToken << endl;
//check token 1
int count = 0;
for (int i = 0; i < firstToken.length(); i++) {
  if (!isalpha(firstToken.at(i))) {
    error2 += "The first token in Hill must be alphabet characters!\n";
    return 0;
  }
  else {
    count++;
  }
}
if (count % 2 != 0) {
  error2 += "The number of characters in Hill token 1 must be even\n";
  return 0;
}
//check token 2
count = 0;
for (int i = 0; i < secondToken.length(); i+=2) {
  if (!isdigit(secondToken.at(i))) {
    error2 += "The second token in Hill must be digit characters!\n";
    return 0;
  }
  else {
    count++;
  }
}
if (count != 4) {
  error2 += "The number of characters in Hill token 2 must be 4\n";
  return 0;
}

//If the string passed, set global plaintext2

//make S, a 2x2 array
count = 0;
int s[2][2];
for (int i = 0; i < 2; i++) {
  for (int j = 0; j < 2; j++) {
    s[i][j] = secondToken.at(count) - '0';
    count +=2;
    //cout << "s[" << i << "][" << j << "] = " << s[i][j] << endl;

  }
}

//

//make inital c, 2x1 array of first two chars of first token, iterate through each cipher and add those chars to plaintext2
int c[2];
int result[2];
for (int i = 0; i < firstToken.length(); i+=2) {
c[0] = toupper(firstToken.at(i)) - 65;
c[1] = toupper(firstToken.at(i + 1)) - 65;
//cout << "c[0] =" << c[0] << " and c[1] =" << c[1] << endl;

result[0] = ((s[0][0] * c[0]) + (s[0][1] * c[1])) % 26;
result[1] = ((s[1][0] * c[0]) + (s[1][1] * c[1])) % 26;

//add the chars to plaintext2
char a = 65 + result[0];
char b = 65 + result[1];
plaintext2 += a;
plaintext2 += b;



  }


}

void* pinnacol(void *f) {
string &x = *static_cast<string*>(f);
if (x.length() <= 20) {
  error3 += "The substring after *** is not even long enough!\n";
  return 0;
}
//split it up
int space;
for (int i = 0; i < x.length(); i++) {
  if (x.at(i) == ' ') {
    space = i;
    break;
  }
}
string firstToken = x.substr(0, space);
//cout << "first token: " << firstToken << endl;
string secondToken = x.substr(space + 1, x.length() - space - 1);
//cout << "second token: " << secondToken << endl;
//check token 1
int count = 0;
for (int i = 0; i < firstToken.length(); i++) {
  if (!isalpha(firstToken.at(i))) {
    error3 += "The first token in pinnacol must be alphabet characters!\n";
    return 0;
  }
  else {
    count++;
  }
}
if (count % 3 != 0) {
  error3 += "The number of characters in pinnacol token 1 must be divisible by 3!\n";
  return 0;
}
//check token 2
count = 0;
for (int i = 0; i < secondToken.length(); i+=2) {
  if (!isdigit(secondToken.at(i))) {
    error3 += "The second token in pinnacol must be digit characters!\n";
    return 0;
  }
  else {
    count++;
  }
}
if (count != 9) {
  error3 += "The number of characters in pinnacol token 2 must be 9!\n";
  return 0;
}

//If the string passed, set global plaintext2

//make S, a 3x3 array
count = 0;
int s[3][3];
for (int i = 0; i < 3; i++) {
  for (int j = 0; j < 3; j++) {
      s[i][j] = secondToken.at(count) - '0';
      count +=2;
      //cout << "s[" << i << "][" << j << "] = " << s[i][j] << endl;
  }
}

//

//make inital c, 2x1 array of first two chars of first token, iterate through each cipher and add those chars to plaintext2
int c[3];
int result[3];
for (int i = 0; i < firstToken.length(); i+=3) {
c[0] = toupper(firstToken.at(i)) - 65;
c[1] = toupper(firstToken.at(i + 1)) - 65;
c[2] = toupper(firstToken.at(i + 2)) - 65;
//cout << "c[0] =" << c[0] << " c[1] =" << c[1] << " and c[2] =" << c[2] << endl;

result[0] = ((s[0][0] * c[0]) + (s[0][1] * c[1]) + (s[0][2] * c[2])) % 26;
result[1] = ((s[1][0] * c[0]) + (s[1][1] * c[1]) + (s[1][2] * c[2])) % 26;
result[2] = ((s[2][0] * c[0]) + (s[2][1] * c[1]) + (s[2][2] * c[2])) % 26;

//add the chars to plaintext2
char a = 65 + result[0];
char b = 65 + result[1];
char d = 65 + result[2];
plaintext3 += a;
plaintext3 += b;
plaintext3 += d;

//cout << plaintext2 << endl;

  }
  //cout << plaintext2 << endl;
}
