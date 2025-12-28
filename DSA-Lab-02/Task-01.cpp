/*
Task 1 
Define a function which prints the Row-Major based ND-array formula against a given number of 
dimensions. 
For Example; 
If the function is called as “printND(3)” then the following should be displayed on console: 
I1U2U3 + I2U3 + I3 
for  “printND(1)” 
I1 
for “printND(2)” 
I1U2 + I2 
Where I1 , I2 , I3 , …, IN represents the index set and 
U1 , U2 , U3 , …, UN represents the dimension set.
*/
#include <iostream>
using namespace std;

void printND(int x)
{
    for (int i = 1; i <= x; i++)
    {
        // Print '+' only between terms
        if (i > 1)
            cout << " + ";

        // Print index
        cout << "I" << i;

        // Print dimensions
        for (int j = i + 1; j <= x; j++)
        {
            cout << "U" << j;
        }
    }
}

int main()
{
    int n;
    cout << "Enter: ";
    cin >> n;

    printND(n);
    return 0;
}
