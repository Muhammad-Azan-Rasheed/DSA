#include <iostream>
using namespace std;

class DNode {
public:
    int data;
    DNode* next;
    DNode* prev;

    DNode(int d = 0) {
        data = d;
        next = prev = nullptr;
    }
};

class CDLinkedList {
private:
    DNode* head;   // dummy header node

    bool isEmpty() const {
        return head->next == head;
    }

public:
    // Constructor
    CDLinkedList() {
        head = new DNode();
        head->next = head;
        head->prev = head;
    }

    // Destructor
    ~CDLinkedList() {
        while (!isEmpty())
            removeAtHead();
        delete head;
    }

    // ---------------- Utility Functions ----------------
    int countNodes() {
        int count = 0;
        DNode* temp = head->next;
        while (temp != head) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    bool search(int key) {
        DNode* temp = head->next;
        while (temp != head) {
            if (temp->data == key)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void update(int key, int val) {
        DNode* temp = head->next;
        while (temp != head) {
            if (temp->data == key) {
                temp->data = val;
                return;
            }
            temp = temp->next;
        }
    }

    void display() {
        DNode* temp = head->next;
        while (temp != head) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // ---------------- Insertion ----------------
    void insertAtHead(int val) {
        DNode* n = new DNode(val);
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
    }

    void insertAtTail(int val) {
        DNode* n = new DNode(val);
        n->prev = head->prev;
        n->next = head;
        head->prev->next = n;
        head->prev = n;
    }

    // ---------------- Deletion ----------------
    void removeAtHead() {
        if (isEmpty()) return;
        DNode* temp = head->next;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
    }

    void removeAtTail() {
        if (isEmpty()) return;
        DNode* temp = head->prev;
        head->prev = temp->prev;
        temp->prev->next = head;
        delete temp;
    }

    void remove(int val) {
        DNode* temp = head->next;
        while (temp != head) {
            if (temp->data == val) {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                return;
            }
            temp = temp->next;
        }
    }

    // =====================================================
    // Task #1 — Merge two SORTED CDLLs into this list
    // =====================================================
    void merge(CDLinkedList& list1, CDLinkedList& list2) {
        DNode* p1 = list1.head->next;
        DNode* p2 = list2.head->next;

        while (p1 != list1.head && p2 != list2.head) {
            if (p1->data <= p2->data) {
                DNode* next = p1->next;
                attachNode(p1);
                p1 = next;
            } else {
                DNode* next = p2->next;
                attachNode(p2);
                p2 = next;
            }
        }

        while (p1 != list1.head) {
            DNode* next = p1->next;
            attachNode(p1);
            p1 = next;
        }

        while (p2 != list2.head) {
            DNode* next = p2->next;
            attachNode(p2);
            p2 = next;
        }

        list1.makeEmpty();
        list2.makeEmpty();
    }

    // =====================================================
    // Task #2 — Split list into two halves
    // =====================================================
    void splitList(CDLinkedList& left, CDLinkedList& right) {
        int total = countNodes();
        int leftCount = (total + 1) / 2;

        DNode* curr = head->next;
        for (int i = 0; i < leftCount; i++) {
            DNode* next = curr->next;
            left.attachNode(curr);
            curr = next;
        }

        while (curr != head) {
            DNode* next = curr->next;
            right.attachNode(curr);
            curr = next;
        }

        makeEmpty();
    }

    // =====================================================
    // Task #3 — Combine (O(1)) and Shuffle Merge
    // =====================================================
    void combine(CDLinkedList& l1, CDLinkedList& l2) {
        if (!l1.isEmpty()) {
            head->next = l1.head->next;
            head->next->prev = head;
            head->prev = l1.head->prev;
            head->prev->next = head;
        }

        if (!l2.isEmpty()) {
            if (isEmpty()) {
                head->next = l2.head->next;
                head->prev = l2.head->prev;
                head->next->prev = head;
                head->prev->next = head;
            } else {
                head->prev->next = l2.head->next;
                l2.head->next->prev = head->prev;
                head->prev = l2.head->prev;
                head->prev->next = head;
            }
        }

        l1.makeEmpty();
        l2.makeEmpty();
    }

    void shuffleMerge(CDLinkedList& l1, CDLinkedList& l2) {
        DNode* p1 = l1.head->next;
        DNode* p2 = l2.head->next;

        while (p1 != l1.head && p2 != l2.head) {
            DNode* n1 = p1->next;
            DNode* n2 = p2->next;
            attachNode(p1);
            attachNode(p2);
            p1 = n1;
            p2 = n2;
        }

        l1.makeEmpty();
        l2.makeEmpty();
    }

private:
    void attachNode(DNode* node) {
        node->prev = head->prev;
        node->next = head;
        head->prev->next = node;
        head->prev = node;
    }

    void makeEmpty() {
        head->next = head;
        head->prev = head;
    }
};

// ================= Driver Code =================
int main() {
    CDLinkedList l1, l2, l3;

    l1.insertAtTail(4);
    l1.insertAtTail(7);
    l1.insertAtTail(10);
    l1.insertAtTail(12);

    l2.insertAtTail(1);
    l2.insertAtTail(3);
    l2.insertAtTail(6);
    l2.insertAtTail(8);
    l2.insertAtTail(9);
    l2.insertAtTail(15);

    cout << "Merged List: ";
    l3.merge(l1, l2);
    l3.display();

    CDLinkedList a, left, right;
    a.insertAtTail(1);
    a.insertAtTail(3);
    a.insertAtTail(5);
    a.insertAtTail(6);
    a.insertAtTail(8);
    a.insertAtTail(12);
    a.insertAtTail(14);

    a.splitList(left, right);
    cout << "Left Half: ";
    left.display();
    cout << "Right Half: ";
    right.display();

    return 0;
}
