
#include "bstree.h"
#include <string>

using namespace std;

BSTree::BSTree() = default;

void BSTree::helpDelete(Node *node) {
  if (node->left != nullptr) {
    helpDelete(node->left);
  }
  if (node->right != nullptr) {
    helpDelete(node->right);
  }
  if (node != nullptr) {
    delete node;
    return;
  }
}

BSTree::~BSTree() {
  if (!this->isEmpty()) {
    clear();
    helpDelete(root);
  }
}

bool BSTree::helpInsert(Account *account, Node *node) {
  if (account->idNumber == node->account->idNumber) {
    delete account;
    return false;
  }
  if (account->idNumber < node->account->idNumber) {
    if (node->left == nullptr || node->left->account == nullptr) {
      node->left = new Node(account);
      return true;
    }
    return helpInsert(account, node->left);
  }
  if (node->right == nullptr || node->right->account == nullptr) {
    node->right = new Node(account);
    return true;
  }
  return helpInsert(account, node->right);
}

bool BSTree::insert(Account *account) {
  if (root->account == nullptr) {
    root->account = account;
    return true;
  }
  return helpInsert(account, root);
}

bool BSTree::helpRetrieve(const int &accountNumber, Account *&account,
                          Node *node) const {
  if (node->account->idNumber == accountNumber) {
    account = node->account;
    return true;
  }
  if (accountNumber < node->account->idNumber) {
    if (node->left == nullptr || node->left->account == nullptr) {
      return false;
    }
    return helpRetrieve(accountNumber, account, node->left);
  }
  if (node->right == nullptr || node->right->account == nullptr) {
    return false;
  }
  return helpRetrieve(accountNumber, account, node->right);
}

bool BSTree::retrieve(const int &accountNumber, Account *&account) const {
  if (root->account == nullptr) {
    account = root->account;
    return false;
  }
  return helpRetrieve(accountNumber, account, root);
}

void BSTree::helpDisplay(Node *node) const {
  if (node->left != nullptr) {
    helpDisplay(node->left);
  }
  cout << endl
       << node->account->lastName << ' ' << node->account->firstName
       << " Account ID: " << node->account->idNumberString << endl;
  for (int i = 0; i < 10; i++) {
    cout << "        " << node->account->funds[i] << ": $"
         << node->account->assets[i] << endl;
  }
  if (node->right != nullptr) {
    helpDisplay(node->right);
  }
}

void BSTree::display() const {
  cout << endl << "Processing Done. Final Balances." << endl;
  helpDisplay(root);
}

void BSTree::helpClear(Node *node) {
  if (node->left != nullptr) {
    helpClear(node->left);
  }
  if (node->right != nullptr) {
    helpClear(node->right);
  }
  if (node->account != nullptr) {
    delete node->account;
    return;
  }
}

void BSTree::clear() { helpClear(root); }

bool BSTree::isEmpty() const { return root == nullptr; }
