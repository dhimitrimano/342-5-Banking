
#ifndef BSTREE_H
#define BSTREE_H

#include "account.h"
#include <iostream>

struct Node {
public:
  Account *account;
  Node *right;
  Node *left;
  explicit Node(Account *acc) : account(acc), right(nullptr), left(nullptr) {}
};

class BSTree {
public:
  // Create BST
  BSTree();

  // Delete all nodes in BST
  ~BSTree();

  // inserts a new account and returns true if it is inserted successfully
  bool insert(Account *account);

  // returns true if successful AND *Account points to account
  bool retrieve(const int &accountNumber, Account *&account) const;

  // displays information on all accounts
  void display() const;

  // deletes all information in AccountTree
  void clear();

  // returns true if tree is empty
  bool isEmpty() const;

  // copy not allowed
  BSTree(const BSTree &other) = delete;

  // move not allowed
  BSTree(BSTree &&other) = delete;

  // assignment not allowed
  BSTree &operator=(const BSTree &other) = delete;

  // move assignment not allowed
  BSTree &operator=(BSTree &&other) = delete;

private:
  Node *root = new Node(nullptr);

  // Helper function for destructor
  void helpDelete(Node *node);

  // Helper function for insert. deletes the account if it is not inserted successfully
  bool helpInsert(Account *account, Node *node);

  // Helper function for retrieve
  bool helpRetrieve(const int &accountNumber, Account *&account, Node *node) const;

  // Helper function for display
  void helpDisplay(Node *node) const;

  // Helper function for clear
  void helpClear(Node *node);
};
#endif // BSTREE_H
