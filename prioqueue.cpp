#include <iostream>
#include <string>
using namespace std;

struct Patient {
    string name;
    int priority; 
    Patient* next;
};

class PriorityQueue {
private:
    Patient* head;

public:
    PriorityQueue()
    {
        head = nullptr;
    }

    void enqueue(string name, int priority) {
        Patient* newPatient = new Patient{name, priority, nullptr};
        if (!head || priority < head->priority) {
            newPatient->next = head;
            head = newPatient;
        } else {
            Patient* temp = head;
            while (temp->next && temp->next->priority <= priority) {
                temp = temp->next;
            }
            newPatient->next = temp->next;
            temp->next = newPatient;
        }
    }

    void dequeue() {    
        if (!head) {
            cout << "Queue is empty. No patients to serve.\n";
            return;
        }
        Patient* temp = head;
        head = head->next;
        cout << "Serving patient: " << temp->name << " (Priority: " << temp->priority << ")\n";
        delete temp;
    }

    void display() {
        if (!head) {
            cout << "No patients in the queue.\n";
            return;
        }
        Patient* temp = head;
        cout << "Patients in the queue:\n";
        while (temp) {
            cout << temp->name << " (Priority: " << temp->priority << ")\n";
            temp = temp->next;
        }
    }

    ~PriorityQueue() {
        while (head) {
            Patient* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    PriorityQueue pq;
    int choice;
    do {
        cout << "\nHospital Priority Queue System\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Display Patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1: {
                string name;
                int priority;
                cout << "Enter patient name: ";
                getline(cin, name); // Use getline to allow spaces in the name
                cout << "Enter priority (1: Serious, 2: Non-serious, 3: General Check-up): ";
                cin >> priority;
                pq.enqueue(name, priority);
                break;
            }
            case 2:
                pq.dequeue();
                break;
            case 3:
                pq.display();
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
