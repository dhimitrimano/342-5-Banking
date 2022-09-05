#include "account.h"

Account::Account(string &firstN, string &lastN, int &idN) {
  firstName = firstN;
  lastName = lastN;
  idNumber = idN;
  idNumberString = to_string(idNumber);
  while (idNumberString.length() != 4) {
    idNumberString.insert(0, "0");
  }
}