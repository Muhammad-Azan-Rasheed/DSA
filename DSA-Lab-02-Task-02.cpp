#include<iostream>
#include<string>

using namespace std;
class NDArray
{
    protected:
    int a[1000];
    int size=0;
    public:
    NDArray()
    {
        for(int i=0;i<1000;i++)
        {
            a[i]=0;    
        }
    }
    NDArray(int dim_size,int arr[100])
    {
        int n=1;
        for(int i=0;i<dim_size;i++)
        {
            n*=arr[i];    
        }
        this->size=n;
        
    }
    double getValue(int _a[100])
    {
        int v=1;
        for(int i=0;i<100;i++)
        {
            v*=_a[i];    
        }
        double value;
        value=this->a[v];
        return value;
    }
    void setValue(int _a[100],int value)
    {
        int var=1;
        for(int i=0;i<100;i++)
        {
            var*=_a[i];    
        }
        this->a[var]=value;
    }

};
int main()
{
    int dim_size[4]={2,3,4,5};
    NDArray arr(4,dim_size);
    
    int index_set[4]={2,2,3,2};
    arr.setValue(index_set,999);
    cout<<"Value:"<<arr.getValue(index_set)<<endl;
    
    int index_set_1[3]={2,5,3};
    arr.setValue(index_set,888);
    cout<<"Value:"<<arr.getValue(index_set)<<endl;
    
    return 0;
}