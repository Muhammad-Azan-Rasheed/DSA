#include<iostream>
#include<string>

using namespace std;
void printND(int x)
{
    for(int i=1;i<=x;i++)
    {
        cout<<'+';
        cout<<'I'<<i;
        for(int j=i;j<x;j++)
        {
            cout<<'U'<<j+1;
        }
        
    }
}
int main()
{
    int n;
    cout<<"Enter:";
    cin>>n;
    printND(n);
    return 0;
}