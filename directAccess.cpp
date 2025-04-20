#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Person {
    int id;
    char name[50];
    int age;
};

long calculateOffset(int id, long recordSize) {
    return (id - 1) * recordSize; 
}

void insertPerson() {
    fstream outFile("persons.dat", ios::binary | ios::in | ios::out);
    
    if (!outFile) {
        ofstream createFile("persons.dat", ios::binary);
        createFile.close();
        outFile.open("persons.dat", ios::binary | ios::in | ios::out);
    }

    Person person;
    cout << "Enter ID: ";
    cin >> person.id;
    cin.ignore(); 
    cout << "Enter Name: ";
    cin.getline(person.name, 50);
    cout << "Enter Age: ";
    cin >> person.age;

    long recordSize = sizeof(Person);
    long offset = calculateOffset(person.id, recordSize);

    outFile.seekp(0, ios::end);
    long fileSize = outFile.tellp();
    
    if (fileSize < offset + recordSize) {
        Person dummy;
        dummy.id = -1;
        outFile.seekp(0, ios::end);
        while (outFile.tellp() < offset) {
            outFile.write((char*)(&dummy), sizeof(Person));
        }
    }

    outFile.seekp(offset);
    outFile.write((char*)(&person), sizeof(Person));

    outFile.close();
    cout << "Person record inserted successfully." << endl;
}

void searchPerson(int id) {
    ifstream inFile("persons.dat", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    Person person;
    long recordSize = sizeof(Person);
    long offset = calculateOffset(id, recordSize);
    
    inFile.seekg(0, ios::end);
    long fileSize = inFile.tellg();
    
    if (offset >= fileSize) {
        cout << "Person with ID " << id << " not found." << endl;
        inFile.close();
        return;
    }

    inFile.seekg(offset);
    inFile.read((char*)(&person), sizeof(Person));

    if (inFile.gcount() == sizeof(Person) && person.id == id) {
        cout << "ID: " << person.id << endl;
        cout << "Name: " << person.name << endl;
        cout << "Age: " << person.age << endl;
    } else {
        cout << "Person with ID " << id << " not found." << endl;
    }

    inFile.close();
}

void deletePerson(int id) {
    fstream file("persons.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    Person person;
    long recordSize = sizeof(Person);
    long offset = calculateOffset(id, recordSize);

    // Check if this offset is beyond the end of the file
    file.seekg(0, ios::end);
    long fileSize = file.tellg();
    
    if (offset >= fileSize) {
        cout << "Person with ID " << id << " not found." << endl;
        file.close();
        return;
    }

    file.seekg(offset);
    file.read(reinterpret_cast<char*>(&person), sizeof(Person));

    if (file.gcount() == sizeof(Person) && person.id == id) {
        // Logically delete the record by setting ID to -1
        person.id = -1;
        file.seekp(offset);
        file.write(reinterpret_cast<char*>(&person), sizeof(Person));
        cout << "Person with ID " << id << " deleted." << endl;
    } else {
        cout << "Person with ID " << id << " not found." << endl;
    }

    file.close();
}

void displayAllPersons() {
    ifstream inFile("persons.dat", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    Person person;
    cout << left << setw(10) << "ID" << setw(50) << "Name" << setw(10) << "Age" << endl;
    cout << string(70, '-') << endl;

    while (inFile.read(reinterpret_cast<char*>(&person), sizeof(Person))) {
        if (person.id != -1) { // Skip logically deleted records
            cout << left << setw(10) << person.id 
                 << setw(50) << person.name 
                 << setw(10) << person.age << endl;
        }
    }

    inFile.close();
}

void displayAllPersonsWithEmptySlots() {
    ifstream inFile("persons.dat", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    Person person;
    cout << left << setw(10) << "ID" << setw(50) << "Name" << setw(10) << "Age" << endl;
    cout << string(70, '-') << endl;

    int recordNumber = 1;
    while (inFile.read(reinterpret_cast<char*>(&person), sizeof(Person))) {
        cout << left << setw(10) << (person.id == -1 ? "Empty" : to_string(person.id)) 
             << setw(50) << (person.id == -1 ? "Empty Slot" : person.name) 
             << setw(10) << (person.id == -1 ? "-" : to_string(person.age)) << endl;
        recordNumber++;
    }

    inFile.close();
}

int main() {
    int choice, id;
    fstream file("persons.dat", ios::binary | ios::in | ios::out | ios::trunc);
    file.close();

    do {
        cout << "\nDirect Access File - Person Records" << endl;
        cout << "1. Insert Person" << endl;
        cout << "2. Search Person" << endl;
        cout << "3. Delete Person" << endl;
        cout << "4. Display All Persons" << endl;
        cout << "5. Display All Persons (With Empty Slots)" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertPerson();
                break;
            case 2:
                cout << "Enter ID to search: ";
                cin >> id;
                searchPerson(id);
                break;
            case 3:
                cout << "Enter ID to delete: ";
                cin >> id;
                deletePerson(id);
                break;
            case 4:
                displayAllPersons();
                break;
            case 5:
                displayAllPersonsWithEmptySlots();
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