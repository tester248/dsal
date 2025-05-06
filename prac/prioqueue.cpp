#include<iostream>
using namespace std;

struct Patient
{
    string name;
    int priority;
    Patient *next;
    Patient(string n,int p){
        name = n;
        priority = p;
        next = nullptr;
    }
};

class PriorityQueue{
    private:
        Patient *head;
    public:
        PriorityQueue(){
            head = nullptr;
        }

        void enqueue(string name, int priority)
        {
            Patient *newPatient = new Patient(name,priority);
            if(head == nullptr || priority < head->priority){
                newPatient->next = head;
                head = newPatient;
            } else {
                Patient* current = head;
                while(current->next != nullptr && current->next->priority <= priority)
                    current = current->next;
                newPatient->next = current->next;
                current->next = newPatient;
            }
        }

        void dequeue()
        {
            if(head == nullptr){
                cout << "The queue is empty. No patients to serve."<<endl;
                return;
            }
            Patient *current = head;
            head = head->next;
            cout << "Serving patient: " << current->name << " (Priority: " << current->priority << ")"<<endl;
            delete current;
        }

        void display()
        {
            if(head == nullptr){
                cout << "No patients in the queue."<<endl;
                return;
            }
            Patient *current = head;
            cout << "Patients in the queue" <<endl;
            while(current != nullptr){
                cout << current->name << " (Priority: " << current->priority << ")"<<endl;
                current = current->next;
            }
        }
};

int main()
{
    PriorityQueue pq;
    int choice, priority;
    string name;
    while(true){
        cout << "\n====MENU====" << endl;
        cout << "1. Add patient" << endl;
        cout << "2. Serve patient" << endl;
        cout << "3. Display patients" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter patient name: ";
                cin >> name;
                cout << "Enter priority (lower number = higher priority): ";
                cin >> priority;
                pq.enqueue(name, priority);
                break;
            case 2:
                pq.dequeue();
                break;
            case 3:
                pq.display();
                break;
            case 4:
                cout << "Exiting..."<<endl;
                return 0;
            default:
                cout << "Invalid choice. Try again."<<endl;
        }
    }
}