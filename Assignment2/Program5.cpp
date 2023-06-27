#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <random>
using namespace std;

class BST {
private:
    int node_count;

    struct Node {
        int data;
        int matrix[2097152];  // Fixed-size matrix == 2^20
        Node* left;
        Node* right;
        int height;
    };

    Node* root;

    Node* insert(int x, Node* t) {
        if (t == NULL) {
            count_insert++;
            t = new Node;
            t->data = x;
            node_count++;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if (x < t->data) {
            t->left = insert(x, t->left);
            if (height(t->left) - height(t->right) == 2) {
                if (x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if (x > t->data) {
            t->right = insert(x, t->right);
            if (height(t->right) - height(t->left) == 2) {
                if (x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    Node* singleRightRotate(Node* t) {
        Node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        return u;
    }

    Node* singleLeftRotate(Node* t) {
        Node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }

    Node* doubleLeftRotate(Node* t) {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    Node* doubleRightRotate(Node* t) {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    Node* findMin(Node* t) {
        if (t == NULL)
            return NULL;
        while (t->left != NULL)
            t = t->left;
        return t;
    }

    Node* remove(int x, Node* t) {
        if (t == NULL)
            return NULL;

        if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);
        else {
            if (t->left && t->right) {
                Node* temp = findMin(t->right);
                t->data = temp->data;
                t->right = remove(t->data, t->right);
            }
            else {
                Node* temp = t;
                if (t->left == NULL)
                    t = t->right;
                else if (t->right == NULL)
                    t = t->left;
                delete temp;
                count_delete++;
                node_count--;
            }
        }

        if (t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right)) + 1;

        if (height(t->left) - height(t->right) == 2) {
            if (height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            else
                return doubleLeftRotate(t);
        }
        else if (height(t->right) - height(t->left) == 2) {
            if (height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            else
                return doubleRightRotate(t);
        }

        return t;
    }

    int height(Node* t) {
        return (t == NULL) ? -1 : t->height;
    }

public:
    int count_insert;
    int count_delete;

    BST() {
        root = NULL;
        node_count = 0;
        count_insert = 0;
        count_delete = 0;
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    int get_count() {
        return node_count;
    }

    int insert_count() {
        return count_insert;
    }

    int delete_count() {
        return count_delete;
    }

    void set_count() {
        count_insert = 0;
    }

    void inorder(Node* t) {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
};

int main() {
    BST node;
    float startinsert = 0;
    float insert = 0;
    float del = 0;
    float start, stop, time;
    int* array = new int[2097152];
    int counter = 0;
    for (int i = 0; i < 2097152; i++) {
        array[i] = rand() % 299 + 1;
    }

    int arrnum = 0;
    start = clock();
    while (node.get_count() < 50) { //tree never contains more than 50 nodes
        arrnum++;
        node.insert(array[arrnum]);
    }
    stop = clock();
    time = (stop - start);
    startinsert += time;
    node.set_count();  // Resets insert count to 0

    for (int i = 0; i < 100000; i++) { //large number of values between 0 and 299
        while (node.get_count() < 50) { //tree never contains more than 50 nodes
            arrnum++;
            start = clock();
            node.insert(array[arrnum]);
            stop = clock();
            time = (stop - start);
            insert += time;
        }

        while (node.get_count() >= 50) { //tree never contains more than 50 nodes
            start = clock();
            node.remove(array[arrnum]);
            stop = clock();
            time = (stop - start);
            del += time;
        }
    }

    cout << "Average Initial Insertion time: " << setprecision(5) << startinsert / 50.00 << " milliseconds." << endl;
    cout << "Average Insert time: " << setprecision(5) << insert / node.count_insert << " milliseconds." << endl;
    cout << "Average Deletion time: " << setprecision(5) << del / node.count_delete << " milliseconds." << endl;

    return 0;
}

/*
Used code implementation from Geeks4Geeks for AVL trees

DATA STRUCTURES USED - 
Binary Search Tree (BST): The main data structure used in this code is a binary search tree, which is a tree-based data structure where 
each node has at most two children. In this implementation, the BST is used to store and organize the integers. The BST provides 
efficient search, insertion, and deletion operations.
Explanation of the Code Flow:

NOTES -
The code begins by including necessary header files and defining the namespace std.
The BST class is defined, which represents the binary search tree. It contains private and public members.
Inside the private section of the BST class, the Node structure is defined to represent the nodes of the tree. Each node contains 
an integer value (data), a fixed-size matrix, and pointers to its left and right child nodes (left and right). The height variable 
stores the height of the node in the tree.
The private section of the BST class also contains the implementation of BST operations, including insertion, removal, rotations, 
and other helper functions.
The public section of the BST class declares public member functions and variables that provide access to the BST and its statistics, 
such as node counts and insertion/deletion counts.
The main function begins by initializing variables and setting up the BST.
An array num_array of size 200,000 is created, and random integers between 1 and 299 are generated and stored in the array.
An instance of the BST class, named node, is created.
The while loop is used to insert elements from num_array into the BST until the node count reaches 50. The insertion time is measured 
using the clock function.
After reaching the desired node count, the time taken for initial insertion is calculated and stored in the variable initial_insertion.
The set_count function is called to reset the insert count to 0.
Two nested for loops are used to simulate insertion and deletion operations on the BST. The insertion and deletion times are measured 
for each operation using the clock function.
Finally, the average initial insertion time, average insertion time, and average deletion time are calculated and displayed using cout 
and setprecision.
Please note that the code could be further improved in terms of error handling, memory management, and adherence to best practices.

The average time for initial insertion represents the time it takes to insert the first 50 nodes into the tree. The average 
insertion/deletion time refers to the average time it takes to insert or delete a single node from the tree. As the program 
starts deleting or inserting nodes, it may result in memory fragmentation, which requires memory compaction to fill the gaps 
in memory. This suggests that the average insertion time, when the program begins deleting nodes, should be higher than the 
average time when initially inserting 50 nodes into the tree. However, in my program, this was not the case. The average insertion 
time remained much faster than the initial insertion time. I believe this is because my computer has effective memory management. Despite 
running on Windows and disabling VMM (Virtual Memory Manager), it still effectively manages fragmented memory. The deletion times 
are faster than the insertion times because deallocating memory is much faster than allocating memory.

Time Complexity:
The time complexity of the BST operations in the insert and remove functions depends on the height of the tree. In the worst-case 
scenario, when the tree is unbalanced and resembles a linked list, the height is O(n), where n is the number of nodes in the tree.
However, on average, balanced BSTs have a height of O(log n), providing efficient search, insertion, and deletion operations.
The time complexity of searching, inserting, and removing a node in a balanced BST is O(log n) on average. However, in the worst-case 
scenario, where the tree is unbalanced, these operations can take O(n) time.
The time complexity of traversing the BST using the inorder function is O(n), as it visits each node once.

Space Complexity:
The space complexity of the BST depends on the number of nodes in the tree. In the Node structure, each node contains an array matrix 
with a fixed size of 2097152(2^20), which contributes to the space complexity. The space complexity of the BST is O(n), where n is the 
number of nodes in the tree.
*/
