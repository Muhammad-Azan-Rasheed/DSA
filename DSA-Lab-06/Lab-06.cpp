#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node() : data(0), next(nullptr) {}
    Node(int d) : data(d), next(nullptr) {}
};
class LinkedList
{
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList()
    {
        while (head)
            removeAtHead();
    }

    // ---------- Task 0 : Basic Operations ----------

    void insertAtHead(int val)
    {
        Node* n = new Node(val);
        n->next = head;
        head = n;
    }

    void insertAtTail(int val)
    {
        Node* n = new Node(val);
        if (!head)
        {
            head = n;
            return;
        }
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = n;
    }

    void removeAtHead()
    {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void removeAtTail()
    {
        if (!head || !head->next)
        {
            removeAtHead();
            return;
        }
        Node* temp = head;
        while (temp->next->next)
            temp = temp->next;
        delete temp->next;
        temp->next = nullptr;
    }

    void remove(int val)
    {
        if (!head) return;
        if (head->data == val)
        {
            removeAtHead();
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->data != val)
            temp = temp->next;
        if (temp->next)
        {
            Node* del = temp->next;
            temp->next = del->next;
            delete del;
        }
    }

    bool search(int key)
    {
        Node* temp = head;
        while (temp)
        {
            if (temp->data == key)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void update(int key, int val)
    {
        Node* temp = head;
        while (temp)
        {
            if (temp->data == key)
            {
                temp->data = val;
                return;
            }
            temp = temp->next;
        }
    }

    int countNodes()
    {
        int count = 0;
        Node* temp = head;
        while (temp)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display()
    {
        Node* temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // ---------- Task 1 : Remove Kth Node ----------

    bool removeKthNode(int k, int& val)
    {
        if (k <= 0 || !head) return false;

        if (k == 1)
        {
            val = head->data;
            removeAtHead();
            return true;
        }

        Node* temp = head;
        for (int i = 1; i < k - 1 && temp; i++)
            temp = temp->next;

        if (!temp || !temp->next)
            return false;

        Node* del = temp->next;
        val = del->data;
        temp->next = del->next;
        delete del;
        return true;
    }

    // ---------- Task 2 : Combine Lists ----------

    void combine(LinkedList& list1, LinkedList& list2)
    {
        head = list1.head;

        if (!head)
            head = list2.head;
        else
        {
            Node* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = list2.head;
        }

        list1.head = nullptr;
        list2.head = nullptr;
    }

    // ---------- Task 3 : Shuffle Merge ----------

    void shuffleMerge(LinkedList& list1, LinkedList& list2)
    {
        Node* p1 = list1.head;
        Node* p2 = list2.head;
        Node* tail = nullptr;

        while (p1 && p2)
        {
            Node* t1 = p1;
            Node* t2 = p2;
            p1 = p1->next;
            p2 = p2->next;

            if (!head)
            {
                head = t1;
                tail = t1;
            }
            else
            {
                tail->next = t1;
                tail = tail->next;
            }

            tail->next = t2;
            tail = tail->next;
        }
        tail->next = nullptr;

        list1.head = nullptr;
        list2.head = nullptr;
    }

    // ---------- Task 4 : Reverse List ----------

    void reverseList()
    {
        Node* prev = nullptr;
        Node* curr = head;

        while (curr)
        {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // ---------- Task 5 : Remove Duplicates ----------

    void removeDuplicates()
    {
        Node* curr = head;

        while (curr)
        {
            Node* prev = curr;
            Node* temp = curr->next;

            while (temp)
            {
                if (temp->data == curr->data)
                {
                    prev->next = temp->next;
                    delete temp;
                    temp = prev->next;
                }
                else
                {
                    prev = temp;
                    temp = temp->next;
                }
            }
            curr = curr->next;
        }
    }
};
int main()
{
    LinkedList list;
    list.insertAtTail(4);
    list.insertAtTail(2);
    list.insertAtTail(8);
    list.insertAtTail(1);
    list.insertAtTail(9);
    list.insertAtTail(5);
    list.insertAtTail(4);
    list.insertAtTail(6);

    cout << "Original List: ";
    list.display();

    int val;
    list.removeKthNode(4, val);
    cout << "After removing 4th node (" << val << "): ";
    list.display();

    LinkedList l1, l2, l3;
    l1.insertAtTail(7);
    l1.insertAtTail(3);
    l1.insertAtTail(4);
    l1.insertAtTail(2);

    l2.insertAtTail(5);
    l2.insertAtTail(9);

    l3.combine(l1, l2);
    cout << "Combined List: ";
    l3.display();

    LinkedList a, b, c;
    a.insertAtTail(2);
    a.insertAtTail(6);
    a.insertAtTail(4);

    b.insertAtTail(8);
    b.insertAtTail(1);
    b.insertAtTail(3);

    c.shuffleMerge(a, b);
    cout << "Shuffle Merge: ";
    c.display();

    c.reverseList();
    cout << "Reversed List: ";
    c.display();

    LinkedList d;
    d.insertAtTail(23);
    d.insertAtTail(5);
    d.insertAtTail(4);
    d.insertAtTail(23);
    d.insertAtTail(6);
    d.insertAtTail(78);
    d.insertAtTail(4);
    d.insertAtTail(5);

    d.removeDuplicates();
    cout << "After Removing Duplicates: ";
    d.display();

    return 0;
}
