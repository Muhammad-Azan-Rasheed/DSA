/*
Task 2      
String words Reverse  
Your task is to implement a function that receives a string and reverses each word in it using stack. You can assume that 
the string only consists of alphabets and spaces. The order of the words should remain same but characters within each 
word should get reversed.  
 
For example:  
String: “Welcome to DSA”  
Modified string: “emocleW ot ASD”  
 
string reverseWords(const string &str)  
*/
#include <iostream>
#include <string>
using namespace std;

constexpr int S_Size = 100;

class STACK
{
private:
    char q[S_Size];
    int n;

public:
    STACK() : n(0) {}

    bool isEmpty() { return n == 0; }
    bool isFull() { return n == S_Size; }

    void push(char item)
    {
        if (!isFull())
            q[n++] = item;
    }

    char pop()
    {
        if (!isEmpty())
            return q[--n];
        return '\0';
    }
};
string reverseWords(const string &str)
{
    STACK st;
    string result;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
        {
            st.push(str[i]);
        }
        else
        {
            while (!st.isEmpty())
                result += st.pop();

            result += ' ';
        }
    }

    // Reverse last word (if no trailing space)
    while (!st.isEmpty())
        result += st.pop();

    return result;
}
int main()
{
    string s = "Welcome to DSA";
    cout << "Modified string: " << reverseWords(s) << endl;
    return 0;
}

