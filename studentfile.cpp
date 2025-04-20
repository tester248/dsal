#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 

using namespace std;

struct Student {
    string rollNumber;
    string name;
    string division;
    string address;
};

void addStudent() {
    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    getline(cin >> ws, student.rollNumber);
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    outFile << student.rollNumber << "," << student.name << "," << student.division << "," << student.address << endl;
    outFile.close();
    cout << "Student added successfully." << endl;
}

void searchStudent(const string& roll) {
    ifstream inFile("students.txt");
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string tokens[4];
        for (int i = 0; i < 4; ++i) {
            getline(ss, tokens[i], ',');
        }

        if (tokens[0] == roll) {
            cout << setw(15) << left << "Roll Number" << setw(20) << left << "Name" << setw(15) << left << "Division" << setw(30) << left << "Address" << endl;
            cout << setw(15) << left << tokens[0] << setw(20) << left << tokens[1] << setw(15) << left << tokens[2] << setw(30) << left << tokens[3] << endl;
            found = true;
            break;
        }
    }

    inFile.close();
    if (!found) {
        cout << "Student with roll number " << roll << " not found." << endl;
    }
}

void deleteStudent(const string& roll) {
    ifstream inFile("students.txt");
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Error creating temporary file." << endl;
        inFile.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string tokens[4];
        for (int i = 0; i < 4; ++i) {
            getline(ss, tokens[i], ',');
        }

        if (tokens[0] == roll) {
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Student with roll number " << roll << " deleted successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "Student with roll number " << roll << " not found." << endl;
    }
}

void displayAllStudents() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    string line;
    cout << setw(15) << left << "Roll Number" << setw(20) << left << "Name" << setw(15) << left << "Division" << setw(30) << left << "Address" << endl;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string tokens[4];
        for (int i = 0; i < 4; ++i) {
            getline(ss, tokens[i], ',');
        }
        cout << setw(15) << left << tokens[0] << setw(20) << left << tokens[1] << setw(15) << left << tokens[2] << setw(30) << left << tokens[3] << endl;
    }
    inFile.close();
}

int main() {
    int choice;
    string rollNumber;
    fstream file("students.txt", ios::in | ios::out | ios::trunc);
    file.close();

    do {
        cout << "\nStudent Information System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Display all Students" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {   
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to search: ";
                cin >> rollNumber;
                searchStudent(rollNumber);
                break;
            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            case 4:
                displayAllStudents();
                break;
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}