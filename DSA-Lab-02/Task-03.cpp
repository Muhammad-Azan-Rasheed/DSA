/*
Task 3:  Deals with buffered writing!  
Objective:   
• The main objective of this is to experience the effect on performance (time) with the use of 
buffered reading/writing.  
• Getting the basic concept of indexing and its advantage on performance (time).  
• Hands on STL.  
Prerequisite Setup:  
 
1. Define a struct ‘Student’ as follows:  
struct Student 
{ 
 int roll; 
 char name[30]; 
 Student():roll(0) 
 { 
  strcpy(name,"none"); 
 } 
}; 
2. The following code stores 10 million records of ‘Student’ in a file in binary mode pass N 
= 10000000  
void addToStudentUnBuffered(int N) 
{ 
 ofstream  ofs("studentdatabase.txt",ios::binary|ios::out); 
 Student s;  
 for (int i=1; i<N; i++) 
 { 
  s.roll = i; 
  ofs.write((char*)(&s),sizeof(Student)); 
 } 
 ofs.close(); 
} 
3. Write the following code in main:  [Required header files stdio.h and windows.h]   
 
SYSTEMTIME systime;  
cout<<"\nWriting Records to File one by one";  
GetLocalTime(&systime);  
cout<<endl<<systime.wHour<<":"<<systime.wMinute<<":"<<systime.wSecond<<":"<<systi
me.wMilliseconds;  
addToStudentUnBuffered();  
GetLocalTime(&systime);  
cout<<endl<<systime.wHour<<":"<<systime.wMinute<<":"<<systime.wSecond<<":"<<systi
me.wMilliseconds; 
  
Can you improve the performance of addToStudentUnBuffered ?  
Idea is to go for buffered writing. Name your function as addToStudentBuffered  
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
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

// Unbuffered version (given)
void addToStudentUnBuffered(int N)
{
    ofstream ofs("studentdatabase_unbuffered.txt",
                 ios::binary | ios::out);

    Student s;
    for (int i = 1; i <= N; i++)
    {
        s.roll = i;
        ofs.write((char*)&s, sizeof(Student));
    }
    ofs.close();
}

// ✅ Buffered version (Improved)
void addToStudentBuffered(int N)
{
    ofstream ofs("studentdatabase_buffered.txt",
                 ios::binary | ios::out);

    const int BUFFER_SIZE = 100000;   // records per buffer
    vector<Student> buffer;
    buffer.reserve(BUFFER_SIZE);

    for (int i = 1; i <= N; i++)
    {
        Student s;
        s.roll = i;
        buffer.push_back(s);

        // Write buffer when full
        if (buffer.size() == BUFFER_SIZE)
        {
            ofs.write((char*)buffer.data(),
                      buffer.size() * sizeof(Student));
            buffer.clear();
        }
    }

    // Write remaining records
    if (!buffer.empty())
    {
        ofs.write((char*)buffer.data(),
                  buffer.size() * sizeof(Student));
    }

    ofs.close();
}
#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
    SYSTEMTIME systime;
    int N = 10000000;

    cout << "\nUnbuffered Writing Start:";
    GetLocalTime(&systime);
    cout << " " << systime.wHour << ":"
         << systime.wMinute << ":"
         << systime.wSecond << ":"
         << systime.wMilliseconds << endl;

    addToStudentUnBuffered(N);

    GetLocalTime(&systime);
    cout << "Unbuffered End: "
         << systime.wHour << ":"
         << systime.wMinute << ":"
         << systime.wSecond << ":"
         << systime.wMilliseconds << endl;


    cout << "\nBuffered Writing Start:";
    GetLocalTime(&systime);
    cout << " " << systime.wHour << ":"
         << systime.wMinute << ":"
         << systime.wSecond << ":"
         << systime.wMilliseconds << endl;

    addToStudentBuffered(N);

    GetLocalTime(&systime);
    cout << "Buffered End: "
         << systime.wHour << ":"
         << systime.wMinute << ":"
         << systime.wSecond << ":"
         << systime.wMilliseconds << endl;

    return 0;
}
