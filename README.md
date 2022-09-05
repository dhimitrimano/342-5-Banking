
// TODO(student)

Group name: Dhimitri Mano

Programmers: Dhimitri Mano

# Contribution by each person
Dhimitri Mano: made the .cpp files
Andrew Koltko & Aylin Onalan (Design Group Teammates): helped make the .h files

# Data structures used
Binary Search Tree, which is a sort of list made of nodes which each have a value and pointers to their left and right nodes. The root node is where the tree begins, and all other nodes can be access from the root node. To the left of a node are values which are less than the node's value, and to the right of a node are values which are greater than the node's value. This gives its search an efficient time complexity of O(log n). A Binary Search Tree is used here to store all of the accounts in order

Array, which is an index based sequential collection of same-type elements with a fixed size. It is lightweight and fast compared to vectors. Strings are arrays of chars. Arrays are used here to store the account's funds, assets, and transaction history.

Queue, which is a sort of vector, which is a sequential container of elements without a fixed size which occupies more memory and is more slow than arrays, which operates in a 'first in first out' order, where the data can only be accessed in the order that it was put into the list, with the first inserted data being the first accessed. The current front data must be deleted for the next front data to be read. The front data can be edited as the .front() method returns a reference. The queue here is used to store the commands from the text file.# 342-5-Banking
