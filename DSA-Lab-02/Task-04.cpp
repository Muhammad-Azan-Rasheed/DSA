/*
Task 4: Deals with buffered reading!  
  
Write a function which display all the Student records stored in "studentdatabase.txt" in Task-3.  
[Maybe you noticed or not: its 343 MB file]  
 
Note: Write two versions of display all records as follows:  
  
➔ readAllRecordsUnBuffered() //:It reads records from file one by one i.e. unbuffered.  
➔ readAllRecordsBuffered() //:It reads records from file in a buffer.  
  
Then observe the response time of both functions by getting the system time
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <windows.h>
using namespace std;

struct Student
{
    int roll;
    char name[30];

    Student() : roll(0)
    {
        strcpy(name, "none");
    }
};
void readAllRecordsUnBuffered()
{
    ifstream ifs("studentdatabase.txt", ios::binary | ios::in);
    Student s;

    while (ifs.read((char*)&s, sizeof(Student)))
    {
        // Display optional (commented to avoid huge output)
        // cout << s.roll << " " << s.name << endl;
    }

    ifs.close();
}
void readAllRecordsBuffered()
{
    ifstream ifs("studentdatabase.txt", ios::binary | ios::in);

    const int BUFFER_SIZE = 100000;   // records per read
    vector<Student> buffer(BUFFER_SIZE);

    while (ifs.read((char*)buffer.data(),
           BUFFER_SIZE * sizeof(Student)) ||
           ifs.gcount() > 0)
    {
        int recordsRead = ifs.gcount() / sizeof(Student);

        for (int i = 0; i < recordsRead; i++)
        {
            // Display optional (commented)
            // cout << buffer[i].roll << " " << buffer[i].name << endl;
        }
    }

    ifs.close();
}
int main()
{
    SYSTEMTIME systime;

    cout << "\nUnbuffered Reading Start:";
    GetLocalTime(&systime);
    cout << " " << systime.wHour << ":"
         << systime.wMinute << ":"
         << systime.wSecond << ":"
         << systime.wMilliseconds << endl;

    readAllRecordsUnBuffered();

    GetLocalTime(&systime);
    cout << "Unbuffered Reading End:";
    cout << " " << systime.wHour << ":"
         << systime.wMinute << ":"
         << systime.wSecond << ":"
         << systime.wMilliseconds << endl;


    cout << "\nBuffered Reading Start:";
    GetLocalTime(&systime);
    cout << " " << systime.wHour << ":"
         << systime.wMinute << ":"
         << systime.wSecond << ":"
         << systime.wMilliseconds << endl;

    readAllRecordsBuffered();

    GetLocalTime(&systime);
    cout << "Buffered Reading End:";
    cout << " " << systime.wHour << ":"
         << systime.wMinute << ":"
         << systime.wSecond << ":"
         << systime.wMilliseconds << endl;

    return 0;
}
