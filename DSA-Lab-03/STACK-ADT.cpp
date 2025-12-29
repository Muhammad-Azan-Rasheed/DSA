/*
Task-1 
A palindrome is a word, phrase, number or other sequence of units that has the property of reading the 
same in either direction. Write a program that could determine whether the given string is a palindrome. 
Examples: 
Palindrome Words: 
Dad 
1221 
Racecar 
Rotator 
Level 
Civic 
Palindrome phrases: 
Too bad--I hid a boot. 
Do geese see God? 
Go Hang a Salami! I'm a Lasagna Hog! 
(title of a book on palindromes by Jon Agee, 1991) 
Note: Handle spaces and punctuation marks carefully. 
Task-2 
Check whether a string is of the form anbn where n = 0, 1, 2, 3, 4, ……. 
Examples: 
aaabbb – is of the form anbn 
bbbaaa – is not a form of anbn 
ababab – is not a form of anbn 
Task-3 
Write a program that reads from the user a mathematical expression like: 
1. Your program should check if the expression is correct 
An expression is correct if: 
The parentheses are correctly added and are balanced. 
Examples of good or bad expressions can be
*/
#include <iostream>
#include <string>
#include <array>
using namespace std;


class STACK
{
    protected:
    char q[100];
    int n;
    public:
    STACK():n(0){}
    
    bool isEmpty() { return this->n==0; }
    bool isFull() { return this->n==100; }
    int size() { return this->n; }
    int getTop()
    {
        return n-1;                //Yeah latest value ka index batata hai
    }
    char Stacktop() 
    {
        if(this->size()>0)         //Yeah Latest Value Batata hai without doing any changes
        {
            return this->q[n-1];
        }
        else
        {
            throw string("Empty");
        }
    }
    void push(char item)
   {
        if(this->size()<100)
        {
            this->q[n]=item;
            n++;
        }
        else
        {
            throw string("Full");
        }
    }
    char pop()
    {
        char item=this->q[n-1];
        q[n-1]=0;
        n--;
        return item;
    }
    
    STACK(const STACK& other) {
        n = other.n;
        for (int i = 0; i < n; i++) {
            q[i] = other.q[i];
        }
    }
    
};
//================================Task-01==========================
bool isPalindrome(string s)
{
    STACK st;
    string clean = "";

    for (char c : s)
        if (isalnum(c))
            clean += tolower(c);

    for (char c : clean)
        st.push(c);

    for (char c : clean)
        if (c != st.pop())
            return false;

    return true;
}
//=====================Task-02=======================
bool isanbn(string s)
{
    int i = 0;
    int countA = 0, countB = 0;

    while (i < s.length() && s[i] == 'a')
    {
        countA++;
        i++;
    }

    while (i < s.length() && s[i] == 'b')
    {
        countB++;
        i++;
    }

    return (i == s.length() && countA == countB);
}
//====================Task-03==========================
bool isExpressionCorrect(string exp)
{
    STACK st;

    for (char c : exp)
    {
        if (c == '(' || c == '{' || c == '[')
            st.push(c);

        else if (c == ')' || c == '}' || c == ']')
        {
            if (st.isEmpty())
                return false;

            char top = st.pop();

            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '['))
                return false;
        }
    }
    return st.isEmpty();
}

int main() 
{
    string s1 = "Too bad--I hid a boot.";
    cout << "Palindrome: " << isPalindrome(s1) << endl;

    string s2 = "aaabbb";
    cout << "anbn: " << isanbn(s2) << endl;

    string exp = "(3+5)*{2+[4-1]}";
    cout << "Expression Correct: " << isExpressionCorrect(exp) << endl;

    return 0;
}