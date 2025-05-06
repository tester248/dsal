#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
using namespace std;

struct Student {
    string rollNum, name, division, address;
};

void addStudent()
{
    ofstream outFile("students.txt", ios::app);
    if(!outFile){
        cerr << "Error opening file for writing." << endl;
        return;
    }
    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.rollNum;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Division: ";
    cin >> s.division;
    cout << "Enter Address: ";
    cin >> s.address;
    outFile << s.rollNum << "," << s.name << "," << s.division << ","
        << s.address << endl;
    outFile.close();
    cout << "Student added successfully." << endl;
}

void deleteStudent(const string &roll)
{
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    if(!inFile || !outFile){
        cerr << "Error opening file." << endl;
        return;
    }
    string line;
    bool found = false;
    while(getline(inFile, line)){
        stringstream ss(line);
        string tokens[4];
        for(int i =0 ; i < 4; i++)
            getline(ss, tokens[i],',');
        if(tokens[0] == roll){
            found = true;
        } else {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();
    if(found){
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Student with roll number " << roll << " deleted successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "Student with roll number " << roll << " not found." << endl;
    }
}

void searchStudent(const string &roll)
{
    ifstream inFile("students.txt");
    if(!inFile){
        cerr << "Error opening file." << endl;
        return;
    }
    string line;
    bool found = false;
    while(getline(inFile, line)){
        stringstream ss(line);
        string tokens[4];
        for(int i =0 ; i < 4; i++)
            getline(ss, tokens[i],',');
        if(tokens[0] == roll){
            cout << "Student found:" << endl;
            cout << setw(15) << left << "Roll Number" << setw(20) << left << "Name" << setw(15) << left << "Division" << setw(30) << left << "Address" << endl;
            cout << setw(15) << left << tokens[0] << setw(20) << left << tokens[1] << setw(15) << left << tokens[2] << setw(30) << left << tokens[3] << endl;
            found = true;
            break;
        }
    }
    inFile.close();
    if(!found){
        cout << "Student with roll number " << roll << " not found." << endl;
    }
}

void displayAllStudents()
{
    ifstream inFile("students.txt");
    if(!inFile){
        cerr << "Error opening file for reading." << endl;
        return;
    }
    string line;
    cout << "Reading file..." << endl;
    cout << setw(15) << left << "Roll Number" << setw(20) << left << "Name" << setw(15) << left << "Division" << setw(30) << left << "Address" << endl;
    while(getline(inFile, line)){
        stringstream ss(line);
        string tokens[4];
        for(int i =0 ; i < 4; i++)
            getline(ss, tokens[i],',');
        cout << setw(15) << left << tokens[0] << setw(20) << left << tokens[1] << setw(15) << left << tokens[2] << setw(30) << left << tokens[3] << endl;
    }
    inFile.close();
}

int main()
{
    int choice;
    string roll;
    while(true){
        cout << "\n====MENU====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 3:
                cout << "Enter Roll Number to search: ";
                cin >> roll;
                searchStudent(roll);
                break;
            case 4:
                displayAllStudents();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}