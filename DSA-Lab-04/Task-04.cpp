/*
Task 4          
30 marks 
There are n people in a line queuing to buy tickets, where the 0th person is at the front of the line and the (n - 1)th person 
is at the back of the line. 
You are given a 0-indexed integer array tickets of length n where the number of tickets that the ith person would like to 
buy is tickets[i]. 
Each person takes exactly 1 second to buy a ticket. A person can only buy 1 ticket at a time and has to go back to the 
end of the line (which happens instantaneously) in order to buy more tickets. If a person does not have any tickets left 
to buy, the person will leave the line.  
Return the time taken for the person at position k (0-indexed) to finish buying tickets. 
Example 1: 
Input: tickets = [2,3,2], k = 2 
Output: 6 
Example 2: 
Input: tickets = [5,1,1,1], k = 0 
Output: 8 
*/
#include <iostream>
using namespace std;

struct Person {
    int tickets;
    bool isK;
};

int timeRequiredToBuy(int tickets[], int n, int k)
{
    Person* q = new Person[n * 10];   // safe size
    int front = 0, rear = 0;

    // initialize queue
    for (int i = 0; i < n; i++)
    {
        q[rear++] = {tickets[i], i == k};
    }

    int time = 0;

    while (true)
    {
        Person p = q[front++];
        time++;

        p.tickets--;

        // if this person was k and finished
        if (p.isK && p.tickets == 0)
            break;

        // if tickets remain, go back to queue
        if (p.tickets > 0)
            q[rear++] = p;
    }

    delete[] q;
    return time;
}
int main()
{
    int tickets1[] = {2,3,2};
    cout << timeRequiredToBuy(tickets1, 3, 2) << endl;  // 6

    int tickets2[] = {5,1,1,1};
    cout << timeRequiredToBuy(tickets2, 4, 0) << endl;  // 8

    return 0;
}
