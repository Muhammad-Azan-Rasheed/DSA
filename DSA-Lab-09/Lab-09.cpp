#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class Node {
public:
    T info;
    Node<T>* left;
    Node<T>* right;

    Node(T val = 0) {
        info = val;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class BinaryTree {
private:
    Node<T>* root;

    Node<T>* Search(Node<T>* curr, T val) {
        if (!curr) return nullptr;
        if (curr->info == val) return curr;

        Node<T>* found = Search(curr->left, val);
        if (found) return found;
        return Search(curr->right, val);
    }

    Node<T>* SearchParent(Node<T>* curr, Node<T>* child) {
        if (!curr || !child) return nullptr;
        if (curr->left == child || curr->right == child) return curr;

        Node<T>* leftRes = SearchParent(curr->left, child);
        if (leftRes) return leftRes;
        return SearchParent(curr->right, child);
    }

    void RemoveSubtree(Node<T>* curr) {
        if (!curr) return;
        RemoveSubtree(curr->left);
        RemoveSubtree(curr->right);
        delete curr;
    }

    void PreOrder(Node<T>* curr) {
        if (!curr) return;
        cout << curr->info << " ";
        PreOrder(curr->left);
        PreOrder(curr->right);
    }

    void PostOrder(Node<T>* curr) {
        if (!curr) return;
        PostOrder(curr->left);
        PostOrder(curr->right);
        cout << curr->info << " ";
    }

    void InOrder(Node<T>* curr) {
        if (!curr) return;
        InOrder(curr->left);
        cout << curr->info << " ";
        InOrder(curr->right);
    }

    void displayParenthesizedView(Node<T>* curr) {
        if (!curr) return;
        cout << curr->info;
        if (curr->left || curr->right) {
            cout << "(";
            displayParenthesizedView(curr->left);
            if (curr->right) cout << ",";
            displayParenthesizedView(curr->right);
            cout << ")";
        }
    }

public:
    //-----------------Task 1-----------------
    BinaryTree() { root = nullptr; }

    //-----------------Task 2-----------------
    void setRoot(T val) {
        if (!root) root = new Node<T>(val);
        else root->info = val;
    }

    //-----------------Task 3-----------------
    T getRoot() {
        if (root) return root->info;
        throw runtime_error("Root does not exist!");
    }

    //-----------------Task 4-----------------
    void setLeftChild(T parentVal, T childVal) {
        Node<T>* parent = Search(root, parentVal);
        if (!parent) return;
        if (!parent->left) parent->left = new Node<T>(childVal);
        else parent->left->info = childVal;
    }

    //-----------------Task 5-----------------
    void setRightChild(T parentVal, T childVal) {
        Node<T>* parent = Search(root, parentVal);
        if (!parent) return;
        if (!parent->right) parent->right = new Node<T>(childVal);
        else parent->right->info = childVal;
    }

    //-----------------Task 6-----------------
    T getParent(T nodeVal) {
        Node<T>* child = Search(root, nodeVal);
        Node<T>* parent = SearchParent(root, child);
        if (parent) return parent->info;
        throw runtime_error("Parent not found!");
    }

    //-----------------Task 7-----------------
    void remove(T nodeVal) {
        Node<T>* node = Search(root, nodeVal);
        if (!node) return;

        if (node == root) {
            RemoveSubtree(root);
            root = nullptr;
        } else {
            Node<T>* parent = SearchParent(root, node);
            if (parent->left == node) parent->left = nullptr;
            if (parent->right == node) parent->right = nullptr;
            RemoveSubtree(node);
        }
    }

    //-----------------Task 8-----------------
    int isInternalNode(T nodeVal) {
        Node<T>* node = Search(root, nodeVal);
        return node && (node->left || node->right) ? 1 : 0;
    }

    //-----------------Task 9-----------------
    int isExternalNode(T nodeVal) {
        Node<T>* node = Search(root, nodeVal);
        return node && !node->left && !node->right ? 1 : 0;
    }

    //-----------------Task 10-----------------
    T findNodeSiblings(T nodeVal) {
        Node<T>* node = Search(root, nodeVal);
        Node<T>* parent = SearchParent(root, node);
        if (!parent) throw runtime_error("No sibling exists!");
        if (parent->left && parent->left->info != nodeVal) return parent->left->info;
        if (parent->right && parent->right->info != nodeVal) return parent->right->info;
        throw runtime_error("No sibling exists!");
    }

    //-----------------Task 11-14-----------------
    void preOrder() { PreOrder(root); cout << endl; }
    void postOrder() { PostOrder(root); cout << endl; }
    void inOrder() { InOrder(root); cout << endl; }

    void levelOrder() {
        if (!root) return;
        queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<T>* curr = q.front();
            q.pop();
            cout << curr->info << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
    }

    //-----------------Task 15-----------------
    void displayDescendents(T nodeVal) {
        Node<T>* node = Search(root, nodeVal);
        if (!node) return;
        queue<Node<T>*> q;
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);

        while (!q.empty()) {
            Node<T>* curr = q.front();
            q.pop();
            cout << curr->info << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
    }

    //-----------------Task 16-----------------
    int heightOfTree() {
        return Height(root);
    }
    int Height(Node<T>* node) {
        if (!node) return 0;
        return 1 + max(Height(node->left), Height(node->right));
    }

    //-----------------Task 17-----------------
    void displayParenthesizedView() {
        displayParenthesizedView(root);
        cout << endl;
    }

    //-----------------Task 18-----------------
    ~BinaryTree() { RemoveSubtree(root); root = nullptr; }
};

//======================== MAIN ========================
int main() {
    BinaryTree<int> tree;

    tree.setRoot(1);
    tree.setLeftChild(1, 2);
    tree.setRightChild(1, 3);
    tree.setLeftChild(2, 4);
    tree.setRightChild(2, 5);
    tree.setLeftChild(3, 6);
    tree.setRightChild(3, 7);

    cout << "PreOrder: "; tree.preOrder();
    cout << "PostOrder: "; tree.postOrder();
    cout << "InOrder: "; tree.inOrder();
    cout << "LevelOrder: "; tree.levelOrder();

    cout << "Descendents of 1: "; tree.displayDescendents(1);

    cout << "Is 7 internal node? " << tree.isInternalNode(7) << endl;
    cout << "Is 3 external node? " << tree.isExternalNode(3) << endl;
    cout << "Parent of 5 is: " << tree.getParent(5) << endl;
    cout << "Sibling of 4 is: " << tree.findNodeSiblings(4) << endl;

    cout << "Height of tree: " << tree.heightOfTree() << endl;

    cout << "Parenthesized view of tree: ";
    tree.displayParenthesizedView();

    return 0;
}
