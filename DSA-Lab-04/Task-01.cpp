//========================Task-01(MAZE Problem)===========================
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
int main() {
    char maze[6][6] = {
        {'*', '*', '*', '*', '*', '*'},
        {'*', ' ', ' ', '*', ' ', '*'},
        {'P', ' ', '*', '*', ' ', 'T'},
        {'*', ' ', ' ', ' ', ' ', '*'},
        {'*', '*', '*', '*', ' ', '*'},
        {'*', '*', '*', '*', '*', '*'}
    };

    int rows = 6;
    int cols = 6;
    int start_x, start_y, end_x, end_y;

    // Find start and end points
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'P') {
                start_x = i;
                start_y = j;
            } else if (maze[i][j] == 'T') {
                end_x = i;
                end_y = j;
            }
        }
    }
      // Directions to move in the maze
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    CircularQueue<pair<int, int>> q(100);
    q.enqueue({start_x, start_y});
    maze[start_x][start_y] = 'V'; // Mark as visited

    while (!q.isEmpty()) {
        pair<int, int> curr = q.dequeue();
        if (curr.first == end_x && curr.second == end_y) {
            cout << "Maze solved!" << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.first + dx[i];
            int ny = curr.second + dy[i];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                (maze[nx][ny] == ' ' || maze[nx][ny] == 'T')) {
                q.enqueue({nx, ny});
                maze[nx][ny] = 'V'; // Mark as visited
            }
        }
    }

    cout << "No solution found!" << endl;
    return 0;
}