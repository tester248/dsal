#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;
const char FILENAME[] = "persons.dat";
const int MAX_RECORDS = 10;
struct Person{
    int id;
    char name[50];
    int age;
    Person(){
        id = -1;
        age = 0;
        name[0] = '\0';
    }
};

void initializeFile(){
    fstream file(FILENAME, ios::in | ios::binary);
    if (!file){
        file.open(FILENAME, ios::out | ios::binary);
        Person p;
        for (int i = 0; i < MAX_RECORDS; ++i)
            file.write((char*)&p, sizeof(Person));
            //or file.write(reinterpret_case<char*>(&p), sizeof(Person));
        file.close();
    }
}

void insertRecord(const Person& p){
    if(p.id < 0 || p.id >= MAX_RECORDS){
        cout << "Invalid ID. Must be between 0 and " << MAX_RECORDS-1 << endl;
        return;
    }
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    file.seekg(p.id * sizeof(Person));
    Person temp;
    file.read((char*)&temp, sizeof(Person));
    if(temp.id != -1){
        cerr << "Slot already filled. Delete first to insert.\n";
        file.close();
        return;
    }
    file.seekp(p.id * sizeof(Person));
    file.write((char*)&p, sizeof(Person));
    file.close();
    cout << "Record inserted at slot " << p.id << endl;
}

void deleteRecord(int id){
    if(id < 0 || id >= MAX_RECORDS){
        cout << "Invalid ID. Must be between 0 and " << MAX_RECORDS-1 << endl;
        return;
    }
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    file.seekg(id * sizeof(Person));
    Person temp;
    file.read((char*)&temp, sizeof(Person));
    if(temp.id == -1){
        cout << "Slot already empty.\n";
        file.close();
        return;
    }
    Person empty;
    file.seekp(id * sizeof(Person));
    file.write((char*)&empty, sizeof(Person));
    file.close();
    cout << "Record deleted from slot " << id << endl;
}

void displayFile(){
    ifstream file(FILENAME, ios::in | ios::binary);
    if(!file){
        cerr << "Error opening file." << endl;
        return;
    }
    cout << left << setw(8) << "Sr. No" << setw(8) << "Status" << setw(8) << "ID" << setw(20) << "Name" << setw(8) << "Age" << endl;
    cout << "---------------------------------------------------------" << endl;
    Person p;
    for(int i = 0; i < MAX_RECORDS; ++i){
        file.read((char*)&p, sizeof(Person));
        if(p.id == -1){
            cout << left << setw(8) << i << setw(8) << "Empty" << setw(8) << "-" << setw(20) << '-' << setw(8) << "-" << endl;
        } else {
            cout << left << setw(8) << i << setw(8) << "Filled" << setw(8) << p.id << setw(20) << p.name << setw(8) << p.age << endl;
        }
    }
    file.close();
}

int main()
{
    initializeFile();
    Person p;
    int choice;
    while(true){
        cout << "\n====MENU====" << endl;
        cout << "1. Insert record" << endl;
        cout << "2. Delete record" << endl;
        cout << "3. Display records" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter ID (0-" << MAX_RECORDS-1 << "): ";
                cin >> p.id;
                cout << "Enter name: ";
                cin.ignore();
                cin.getline(p.name, 50);
                cout << "Enter age: ";
                cin >> p.age;
                insertRecord(p);
                break;
            case 2:
                int id;
                cout << "Enter ID to delete (0-" << MAX_RECORDS-1 << "): ";
                cin >> id;
                deleteRecord(id);
                break;
            case 3:
                displayFile();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Try again."<<endl;
        }
    }
}