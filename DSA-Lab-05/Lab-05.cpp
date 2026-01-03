#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> // Required for abs() in some environments

using namespace std;

// --- Task 1: Decimal to Octal Conversion ---
int dec2oct(int n) {
    if (n == 0) {
        return 0;
    }
    return (dec2oct(n / 8) * 10) + (n % 8);
}

// --- Task 2: Identifying a "Good" Digit String ---
bool isPrimeDigit(char digit) {
    int val = digit - '0';
    return (val == 2 || val == 3 || val == 5 || val == 7);
}

bool isGoodNumber(const string &s, int index = 0) {
    if (index >= s.length()) {
        return true;
    }

    int digit = s[index] - '0';
    bool current_digit_ok;

    if (index % 2 == 0) {
        current_digit_ok = (digit % 2 == 0);
    } else {
        current_digit_ok = isPrimeDigit(s[index]);
    }

    if (!current_digit_ok) {
        return false;
    }

    return isGoodNumber(s, index + 1);
}

// --- Task 3: Counting Ways to Climb a Staircase ---
// This is the Fibonacci sequence. The base cases must be correct:
// F(1) = 1 (1 way: 1)
// F(2) = 2 (2 ways: 1+1, 2)
int countWays(int numStairs) {
    if (numStairs <= 0) {
        return 0; // Invalid input or 0 ways to climb a negative stair count
    }
    if (numStairs == 1) {
        return 1;
    }
    if (numStairs == 2) {
        return 2;
    }
    return countWays(numStairs - 1) + countWays(numStairs - 2);
}

// --- Task 4: Counting Squares Surrounding a Point ---
bool isContained(int px, int py, int k, int cx, int cy) {
    // A square of size k centered at (cx, cy) contains (px, py)
    return (abs(px - cx) <= k) && (abs(py - cy) <= k);
}

int countSurroundingSquares(int k, int px, int py, int cx, int cy) {
    // Base Case 1: The square size is smaller than the smallest permissible (size 1).
    if (k < 1) { 
        return 0;
    }

    bool contains = isContained(px, py, k, cx, cy);
    int count = contains ? 1 : 0;
    
    // Base Case 2: If the smallest permissible square of size 1 is reached, stop recursion.
    if (k == 1) {
        return count;
    }

    // Recursive Step: If the point is contained and k > 1, check the four corner squares.
    if (contains) {
        int k_prime = k / 2;
        int offset = k; 

        // Corner centers are located k points away from the current center.
        // 1. Top-Left: (cx - k, cy - k)
        count += countSurroundingSquares(k_prime, px, py, cx - offset, cy - offset);
        // 2. Top-Right: (cx + k, cy - k)
        count += countSurroundingSquares(k_prime, px, py, cx + offset, cy - offset);
        // 3. Bottom-Left: (cx - k, cy + k)
        count += countSurroundingSquares(k_prime, px, py, cx - offset, cy + offset);
        // 4. Bottom-Right: (cx + k, cy + k)
        count += countSurroundingSquares(k_prime, px, py, cx + offset, cy + offset);
    }
    
    return count;
}


// --- Main Driver Function ---
int main() {
    // Task 1 Driver
    int n1 = 69;
    cout << "Octal equivalent of " << n1 << " is: " << dec2oct(n1) << endl;
    int n2 = 389;
    cout << "Octal equivalent of " << n2 << " is: " << dec2oct(n2) << endl;
    
    // Task 2 Driver
    string digit_strings[] = {"02468", "23478", "224365"};
    for (string digits: digit_strings) {
        bool is_good = isGoodNumber(digits, 0);
        cout << "Digit string: " << digits
             << " is " << (is_good? "good" : "not good") << endl;
    }
    
    // Task 3 Driver (3 steps = 3 ways: 1+1+1, 1+2, 2+1; 4 steps = 5 ways)
    int stairs3 = 3;
    cout << "Ways to climb " << stairs3 << " stairs: " << countWays(stairs3) << endl; 
    int stairs4 = 4;
    cout << "Ways to climb " << stairs4 << " stairs: " << countWays(stairs4) << endl; 
    
    // Task 4 Driver (Input Reading & Sample Tests)
    // The largest square is centered at (1024, 1024)
    
    // Sample 1: 500 113 941 -> 5
    cout << "Input: 500 113 941. Output: " << countSurroundingSquares(500, 113, 941, 1024, 1024) << endl;
    
    // Sample 2: 300 100 200 -> 0
    cout << "Input: 300 100 200. Output: " << countSurroundingSquares(300, 100, 200, 1024, 1024) << endl;

    // Sample 3: 300 1024 1024 -> 1
    cout << "Input: 300 1024 1024. Output: " << countSurroundingSquares(300, 1024, 1024, 1024, 1024) << endl;
    
    return 0;
}