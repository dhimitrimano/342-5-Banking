#ifndef BANK_H
#define BANK_H

#include "bstree.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

class Bank {
public:
  // default constructor
  explicit Bank();

  // goes through each line of the file and pushes them into the transaction queue
  void processTransactionFile(const string &fileName);

private:
  BSTree accounts;
  queue<string> actions;

  // handles the transactions
  void transactionHandler();

  // deposits or withdraws assets into a fund (numbered 0-9) inside an account. returns true if successful
  void manipulate(Account *acc, int fund, int assets);

  // transfers assets from one fund to another
  void transfer(Account *accW, Account *accD, int fundW, int fundD, int assets);

};
#endif // BANK_H