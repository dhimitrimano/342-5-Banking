#include "bank.h"

Bank::Bank() = default;

void Bank::processTransactionFile(const string &fileName) {
  string str;
  ifstream input(fileName);
  while (getline(input, str)) {
    actions.push(str);
  }
  transactionHandler();
}

void Bank::transactionHandler() {
  int id1 = -1;
  int id2 = -1;
  Account *acc1;
  Account *acc2;
  int fund1 = -1;
  int fund2 = -1;
  int asset = -1;
  int nameLength = -1;
  string firstN;
  string lastN;
  while (!actions.empty()) {
    if (actions.front().at(0) == 'O') {
      id1 = stoi(actions.front().substr(actions.front().size() - 4));
      nameLength = 0;
      for (int i = 2; i < actions.front().size(); i++) {
        if (actions.front().at(i) == ' ') {
          break;
        }
        nameLength++;
      }
      lastN = actions.front().substr(2, nameLength);
      nameLength = 0;
      for (int i = 2 + lastN.size() + 1; i < actions.front().size(); i++) {
        if (actions.front().at(i) == ' ') {
          break;
        }
        nameLength++;
      }
      firstN = actions.front().substr(2 + lastN.size() + 1, nameLength);
      if (!accounts.insert(new Account(firstN, lastN, id1))) {
        cout << "ERROR: Account "
             << actions.front().substr(actions.front().size() - 4)
             << " is already open. Creation refused." << endl;
      }
    }
    if (actions.front().at(0) == 'D') {
      id1 = stoi(actions.front().substr(2, 4));
      fund1 = actions.front().at(6) - '0';
      if (accounts.retrieve(id1, acc1)) {
        asset = stoi(actions.front().substr(8));
        manipulate(acc1, fund1, asset);
      } else {
        cout << "ERROR: Could not find Account " << actions.front().substr(2, 4)
             << ". Deposit cancelled." << endl;
      }
    }
    if (actions.front().at(0) == 'W') {
      id1 = stoi(actions.front().substr(2, 4));
      fund1 = actions.front().at(6) - '0';
      if (accounts.retrieve(id1, acc1)) {
        asset = stoi(actions.front().substr(8));
        manipulate(acc1, fund1 + 10, asset);
      } else {
        cout << "ERROR: Could not find Account " << actions.front().substr(2, 4)
             << ". Withdrawal cancelled." << endl;
      }
    }
    if (actions.front().at(0) == 'T') {
      id1 = stoi(actions.front().substr(2, 4));
      fund1 = actions.front().at(6) - '0';
      id2 = stoi(actions.front().substr(actions.front().size() - 5, 4));
      fund2 = actions.front().at(actions.front().size() - 1) - '0';
      if (accounts.retrieve(id1, acc1) && accounts.retrieve(id2, acc2)) {
        asset = stoi(actions.front().substr(8, actions.front().size() - 14));
        transfer(acc1, acc2, fund1, fund2, asset);
      }
      if (!accounts.retrieve(id1, acc1)) {
        cout << "ERROR: Could not find Account " << actions.front().substr(2, 4)
             << ". Transfer cancelled." << endl;
      }
      if (!accounts.retrieve(id2, acc2)) {
        cout << "ERROR: Could not find Account "
             << actions.front().substr(actions.front().size() - 5, 4)
             << ". Transfer cancelled." << endl;
      }
    }
    if (actions.front().at(0) == 'H') {
      id1 = stoi(actions.front().substr(2, 4));
      if (accounts.retrieve(id1, acc1)) {
        cout << endl
             << "Displaying Transaction History for " << acc1->lastName << " "
             << acc1->firstName;
        if (actions.front().size() == 7) {
          cout << "'s " << acc1->funds[actions.front().at(6) - '0'] << ": $"
               << acc1->assets[actions.front().at(6) - '0'] << endl
               << acc1->history[actions.front().at(6) - '0'];
        } else {
          cout << " by fund." << endl;
          for (int i = 0; i < 10; i++) {
            cout << acc1->funds[i] << ": $" << acc1->assets[i];
            if (!acc1->history[i].empty()) {
              cout << endl << acc1->history[i];
            } else {
              cout << endl;
            }
          }
        }
      } else {
        cout << "ERROR: Could not find Account " << actions.front().substr(2, 4)
             << ". History not printed." << endl;
      }
    }
    actions.pop();
  }
  accounts.display();
}

void Bank::manipulate(Account *acc, int fund, int assets) {
  stringstream ss;
  if (fund > 9) {
    assets = 0 - assets;
    fund -= 10;
    ss << "        W ";
    ss << acc->idNumberString << fund << " " << 0 - assets;
  } else {
    ss << "        D ";
    ss << acc->idNumberString << fund << " " << assets;
  }
  int leftovers = (0 - assets) - acc->assets[fund];
  if (acc->assets[fund] + assets >= 0) {
    acc->assets[fund] += assets;
  } else if (fund == 0 && acc->assets[1] - leftovers >= 0) {
    acc->assets[1] -= (0 - assets) - leftovers;
    manipulate(acc, 11, leftovers);
    ss << " (Failed, withdrew from Prime Money Market instead)";
  } else if (fund == 1 && acc->assets[0] - leftovers >= 0) {
    acc->assets[0] -= (0 - assets) - leftovers;
    manipulate(acc, 10, leftovers);
    ss << " (Failed, withdrew from Money Market instead)";
  } else if (fund == 2 && acc->assets[3] - leftovers >= 0) {
    acc->assets[3] -= (0 - assets) - leftovers;
    manipulate(acc, 13, leftovers);
    ss << " (Failed, withdrew from Short-Term Bond instead)";
  } else if (fund == 3 && acc->assets[2] - leftovers >= 0) {
    acc->assets[2] -= (0 - assets) - leftovers;
    manipulate(acc, 12, leftovers);
    ss << " (Failed, withdrew from Long-Term Bond instead)";
  } else {
    ss << " (Failed)";
  }
  ss << "\n";
  acc->history[fund].append(ss.str());
}

void Bank::transfer(Account *accWith, Account *accDep, int fundWith,
                    int fundDep, int assets) {
  stringstream ss;
  ss << "        T ";
  ss << accWith->idNumberString << fundWith << " " << assets << " "
     << accDep->idNumberString << fundDep;
  if (accWith->assets[fundWith] - assets >= 0) {
    accWith->assets[fundWith] -= assets;
    manipulate(accDep, fundDep, assets);
  } else {
    ss << " (Failed)";
  }
  ss << "\n";
  accDep->history[fundWith].append(ss.str());
}