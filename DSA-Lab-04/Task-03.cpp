#include <iostream>
using namespace std;

template <typename T>
class CircularQueue {
private:
    int front;
    T* data;
    int capacity;
    int rear;
    int no_of_element;  // to track number of elements

public:
    // Constructor
    CircularQueue(int cap) {
        capacity = cap;
        data = new T[capacity];
        front = 0;
        rear = -1;
        no_of_element = 0;
    }

    // Destructor
    ~CircularQueue() {
        delete[] data;
    }

    // Check if queue is empty
    bool isEmpty() {
        return no_of_element == 0;
    }

    // Check if queue is full
    bool isFull() {
        return no_of_element == capacity;
    }

    // Get current size
    int size() {
        return no_of_element;
    }

    // Enqueue operation - O(1)
    void enqueue(T value) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        data[rear] = value;
        no_of_element++;
    }

    // Dequeue operation - O(1) as requested
    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T(); // return default value
        }
        T value = data[front];
        front = (front + 1) % capacity;  // Simply move front pointer - O(1)
        no_of_element--;
        return value;
    }
  
    // Get front element without removing
    T getFront() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        return data[front];
    }

    // Display queue contents
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "Queue: ";
        for (int i = 0; i < no_of_element; i++) {
            int index = (front + i) % capacity;
            cout << data[index] << " ";
        }
        cout << endl;
    }

    // Clear the queue
    void clear() {
        front = 0;
        rear = -1;
        no_of_element = 0;
    }

    // Resize the queue to new capacity - O(n)
    void resize(int newCapacity) {
        if (newCapacity < no_of_element) {
            cout << "Error: New capacity cannot be smaller than current size!" << endl;
            return;
        }
        
        // Create new array with new capacity
        T* newData = new T[newCapacity];
        
        // Copy existing elements to new array in correct order
        for (int i = 0; i < no_of_element; i++) {
            int index = (front + i) % capacity;
            newData[i] = data[index];
        }
        
        // Delete old array and update pointers
        delete[] data;
        data = newData;
        capacity = newCapacity;
        front = 0;
        rear = (no_of_element > 0) ? no_of_element-1:-1;
    }
};

int main()
{
    CircularQueue<int> q(5); 
 
    q.enqueue(14); 
    q.enqueue(22); 
    q.enqueue(13); 
    q.enqueue(-6); 
    q.display(); 
    cout<<"Deleted Value = "<<q.dequeue()<<endl; 
    cout<<"Deleted Value = "<<q.dequeue()<<endl; 
    q.display(); 
  
    q.enqueue(9); 
    q.enqueue(20); 
    q.enqueue(5); 
    q.display(); 
    return 0;
}