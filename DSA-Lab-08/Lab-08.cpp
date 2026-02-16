#include <iostream>
#include <string>
#include <queue>
#include <cmath>
using namespace std;

template <typename T>
class BinaryTree {
    int height;
    T* data;
    bool* status;

public:
    //---------------------TASK-01---------------------
    BinaryTree(int h) {
        height = h;
        int size = pow(2, h) - 1;
        data = new T[size];
        status = new bool[size];
        for (int i = 0; i < size; i++) {
            status[i] = 0;
        }
    }

    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    int parent(int i) { return (i - 1) / 2; }

    //---------------------Task-02-----------------------
    void setRoot(T v) {
        if (!status[0]) {
            data[0] = v;
            status[0] = true;
            cout << "Root set to " << v << endl;
        }
        else {
            cout << "Root already exists!" << endl;
        }
    }

    //--------------------Task-03------------------------
    T getRoot() {
        if (status[0]) {
            return data[0];
        }
        else {
            cout << "Root doesn't exist." << endl;
            return T();
        }
    }

    //--------------------Task-04------------------------
    void setLeftChild(T p, T v) {
        int size = pow(2, height) - 1;
        for (int i = 0; i < size; i++) {
            if (status[i] && data[i] == p) {
                int li = leftChild(i);
                if (li < size && !status[li]) {
                    data[li] = v;
                    status[li] = true;
                    cout << "Left child of " << p << " set to " << v << endl;
                }
                else
                    cout << "Left child already exists!" << endl;
                return;
            }
        }
        cout << "Parent " << p << " not found!" << endl;
    }

    //--------------------Task-05------------------------
    void setRightChild(T p, T v) {
        int size = pow(2, height) - 1;
        for (int i = 0; i < size; i++) {
            if (status[i] && data[i] == p) {
                int ri = rightChild(i);
                if (ri < size && !status[ri]) {
                    data[ri] = v;
                    status[ri] = true;
                    cout << "Right child of " << p << " set to " << v << endl;
                }
                else
                    cout << "Right child already exists!" << endl;
                return;
            }
        }
        cout << "Parent " << p << " not found!" << endl;
    }

    //---------------------Task-06-------------------------
    T getParent(T value) {
        int idx = search(value);
        if (idx <= 0) return T();
        return data[parent(idx)];
    }

    int search(T value) {
        int size = pow(2, height) - 1;
        for (int i = 0; i < size; i++) {
            if (status[i] && data[i] == value) return i;
        }
        return -1;
    }

    //---------------------Task-07-----------------------
    void remove(T value) {
        int idx = search(value);
        if (idx == -1) {
            cout << "Node not found!" << endl;
            return;
        }

        int size = pow(2, height) - 1;
        queue<int> q;
        q.push(idx);
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            if (i < size && status[i]) {
                int li = leftChild(i);
                int ri = rightChild(i);
                if (li < size) q.push(li);
                if (ri < size) q.push(ri);
                status[i] = false;
            }
        }
        cout << "Subtree with root " << value << " removed." << endl;
    }

    //-------------------Task-08-----------------------
    void displayAncestors(T node) {
        if (node == getRoot()) return;
        int idx = search(node);
        if (idx <= 0) return;
        int parent_idx = parent(idx);
        cout << data[parent_idx] << " ";
        displayAncestors(data[parent_idx]);
    }

    //-------------------Task-09-----------------------
    void displayDescendents(T node) {
        int idx = search(node);
        if (idx == -1) return;
        preOrder(idx, true); // skip root itself
    }

    void preOrder(int i=0, bool skipRoot = false) {
        int size = pow(2, height) - 1;
        if (i >= size || !status[i]) return;
        if (!skipRoot) cout << data[i] << " ";
        preOrder(leftChild(i));
        preOrder(rightChild(i));
    }

    //-------------------Task-11-----------------------
    void postOrder(int i = 0) {
        int size = pow(2, height) - 1;
        if (i >= size || !status[i]) return;
        postOrder(leftChild(i));
        postOrder(rightChild(i));
        cout << data[i] << " ";
    }

    //-------------------Task-12-----------------------
    void inOrder(int i = 0) {
        int size = pow(2, height) - 1;
        if (i >= size || !status[i]) return;
        inOrder(leftChild(i));
        cout << data[i] << " ";
        inOrder(rightChild(i));
    }

    //-------------------Task-14-----------------------
    void levelOrder() {
        int size = pow(2, height) - 1;
        for (int i = 0; i < size; i++) {
            if (status[i]) cout << data[i] << " ";
        }
        cout << endl;
    }

    void display() {
        int size = pow(2, height) - 1;
        cout << "Binary Tree (Array Representation): ";
        for (int i = 0; i < size; i++) {
            if (status[i]) cout << data[i] << " ";
            else cout << "_ ";
        }
        cout << endl;
    }

    //-------------------Task-15-----------------------
    void displayLevel(int levelNo) {
        int size = pow(2, height) - 1;
        cout << "Nodes at Level " << levelNo << ": ";
        for (int i = 0; i < size; i++) {
            if (status[i] && findLevelOfNode(data[i]) == levelNo) {
                cout << data[i] << " ";
            }
        }
        cout << endl;
    }

    //-------------------Task-16-----------------------
    int findLevelOfNode(T node, int depth = 0) {
        if (node == getRoot()) return depth;
        int idx = search(node);
        if (idx <= 0) return -1;
        return findLevelOfNode(data[parent(idx)], depth + 1);
    }

    ~BinaryTree() {
        delete[] data;
        delete[] status;
    }
};

int main() {
    BinaryTree<int> B1(4);
    B1.setRoot(1);
    B1.setLeftChild(1, 2);
    B1.setRightChild(1, 3);
    B1.setLeftChild(2, 4);
    B1.setRightChild(2, 5);
    B1.setLeftChild(3, 6);
    B1.setRightChild(3, 7);
    B1.setLeftChild(4, 8);
    B1.setRightChild(4, 9);
    B1.setLeftChild(5, 10);
    B1.setRightChild(5, 11);
    B1.setLeftChild(6, 12);
    B1.setRightChild(6, 13);
    B1.setLeftChild(7, 14);
    B1.setRightChild(7, 15);

    B1.display();
    cout << "Parent of child node 7 is: " << B1.getParent(7) << endl;
    cout << "Pre-Order: "; B1.preOrder(); cout << endl;
    cout << "Post-Order: "; B1.postOrder(); cout << endl;
    cout << "In-Order: "; B1.inOrder(); cout << endl;
    cout << "Level-Order: "; B1.levelOrder();
    cout << "Ancestors of 14: "; B1.displayAncestors(14); cout << endl;
    cout << "Descendents of 2: "; B1.displayDescendents(2); cout << endl;
    cout << "Depth/Level of 8 is: " << B1.findLevelOfNode(8) << endl;
    B1.displayLevel(3);

    return 0;
}
