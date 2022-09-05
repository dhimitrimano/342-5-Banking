#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>

using namespace std;

class Account {

private:
  string firstName = "";
  string lastName = "";
  int idNumber = 0;
  string idNumberString = "";

  // array containing the names of funds
  string funds[10] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index"};

  // array containing the assets in each fund, each fund's index number being the same as their asset's index number
  int assets[10] = {0};

  // array of fund history. index 10 contains errors
  string history[10] = {""};

  // the constructor, initializes idNumberString as well as firstName, lastName, and idNumber
  explicit Account(string &firstN, string &lastN, int &idN);

  friend class BSTree;
  friend class Bank;

};
#endif // ACCOUNT_H