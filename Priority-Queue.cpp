#include <iostream>
#include <vector>
using namespace std;

// ---------------------------------------
// Priority Queue implemented using Max-Heap
// ---------------------------------------
class PriorityQueue {
private:
    vector<int> pq;   // Internal heap array

    // Get parent, left child, right child
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Restore heap upward (for insertion)
    void heapifyUp(int index) {
        while (index != 0 && pq[parent(index)] < pq[index]) {
            swap(pq[parent(index)], pq[index]);
            index = parent(index);
        }
    }

    // Restore heap downward (for deletion)
    void heapifyDown(int index) {
        int n = pq.size();
        while (true) {
            int l = left(index);
            int r = right(index);
            int largest = index;

            if (l < n && pq[l] > pq[largest]) largest = l;
            if (r < n && pq[r] > pq[largest]) largest = r;

            if (largest == index) break;

            swap(pq[index], pq[largest]);
            index = largest;
        }
    }

public:

    // Insert element into priority queue
    void push(int value) {
        pq.push_back(value);
        heapifyUp(pq.size() - 1);
    }

    // Return highest priority element
    int top() {
        if (pq.empty()) throw runtime_error("Priority Queue is empty!");
        return pq[0];
    }

    // Delete and return highest priority element
    int pop() {
        if (pq.empty()) throw runtime_error("Priority Queue is empty!");

        int maxValue = pq[0];
        pq[0] = pq.back();
        pq.pop_back();

        if (!pq.empty()) heapifyDown(0);

        return maxValue;
    }

    // Check if PQ is empty
    bool empty() {
        return pq.size() == 0;
    }

    // Get current size
    int size() {
        return pq.size();
    }

    // Print the priority queue (heap structure)
    void print() {
        cout << "Priority Queue (Max-Heap): ";
        for (int x : pq) cout << x << " ";
        cout << endl;
    }
};

// ---------------------------------------
// Example Usage
// ---------------------------------------
int main() {
    PriorityQueue pq;

    pq.push(40);
    pq.push(10);
    pq.push(50);
    pq.push(30);
    pq.push(20);

    pq.print();

    cout << "Top element: " << pq.top() << endl;

    cout << "Popping elements: ";
    while (!pq.empty()) {
        cout << pq.pop() << " ";
    }
    cout << endl;

    return 0;
}
