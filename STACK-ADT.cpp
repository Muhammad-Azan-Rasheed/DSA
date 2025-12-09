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
int main() 
{    
    cout<<"Hello World!!!"<<endl;
    cout<<"This is STACK ADT"<<endl;
    return 0;
}