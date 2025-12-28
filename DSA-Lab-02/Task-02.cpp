/*Task 2:
Requirements: 
Even though the multidimensional array is provided as a standard data object in C++, it is often useful 
to define your own class for multidimensional arrays. This gives a more robust class that: 
• Does require the index set in each dimension to start at any number (Є Set of Integers). 
• Selects range of each dimension of the array during runtime. 
• Provide mechanism to determine the size of array. 
No specific data structure is being told to you for this task so intelligently do a proper structure 
selection yourself and when feels confident then also discuss your structure with Instructor before 
start coding. 
Sample Program Run 
int dim-size[3]={5,3,10}; 
NDArray arr(3, dim-size); 
int index-set[3]={4,2,8}; 
cout<<arr.calculateIndex( indexset )<<endl; 
arr.setValue( index-set , val); 
cout<<arr.getValue(index-set);
*/

#include <iostream>
using namespace std;

class NDArray
{
private:
    int dims;           // number of dimensions
    int* dimSize;       // size of each dimension
    int totalSize;      // total elements
    int* data;          // 1D storage (row-major)

public:
    // Constructor
    NDArray(int d, int sizes[])
    {
        dims = d;
        dimSize = new int[dims];

        totalSize = 1;
        for (int i = 0; i < dims; i++)
        {
            dimSize[i] = sizes[i];
            totalSize *= sizes[i];
        }

        data = new int[totalSize];
        for (int i = 0; i < totalSize; i++)
            data[i] = 0;
    }

    // Row-major index calculation
    int calculateIndex(int indexSet[])
    {
        int index = 0;
        int multiplier = 1;

        for (int i = dims - 1; i >= 0; i--)
        {
            index += indexSet[i] * multiplier;
            multiplier *= dimSize[i];
        }
        return index;
    }

    // Set value
    void setValue(int indexSet[], int value)
    {
        int idx = calculateIndex(indexSet);
        data[idx] = value;
    }

    // Get value
    int getValue(int indexSet[])
    {
        int idx = calculateIndex(indexSet);
        return data[idx];
    }

    // Destructor
    ~NDArray()
    {
        delete[] dimSize;
        delete[] data;
    }
};

int main()
{
    int dimSize[3] = {5, 3, 10};
    NDArray arr(3, dimSize);

    int indexSet[3] = {4, 2, 8};

    cout << arr.calculateIndex(indexSet) << endl;

    arr.setValue(indexSet, 999);
    cout << arr.getValue(indexSet) << endl;

    return 0;
}
