#include<iostream>

using namespace std;

struct Patient
{
    string name;
    int priority;
    Patient* next;
    Patient(string n, int p)
    {
        name = n;
        priority = p;
        next = nullptr; 
    }
};

class PriorityQueue
{
    private:
        Patient* head;
    public:
        PriorityQueue()
        {
            head = nullptr;
        }
        
        void enqueue(string name, int priority)
        {
            Patient* newPatient = new Patient(name,priority);
            if (head == nullptr || priority < head->priority){
                newPatient->next = head;
                head = newPatient;
            } else {
                Patient* temp = head;
                while (temp->next != nullptr && temp->next->priority <= priority)
                {
                    temp = temp->next;
                }
                newPatient->next = temp->next;
                temp->next = newPatient;
            }
        }
        
        void dequeue()
        {
            if(head == nullptr) {
                cout << "Queue is empty. No patients to serve.\n";
                return;
            }
            Patient* temp = head;
            head = head->next;
            cout << "Serving patient: " << temp->name << " (Priority: " << temp->priority << ")\n";
            delete temp;
        }

        void display()
        {
            if(head == nullptr) {
                cout << "No patients in the queue.\n";
                return;
            }
            Patient* temp = head;
            cout << "Patients in the queue:"<<endl;
            while(temp != nullptr){
                cout << temp->name << " (Priority: " << temp->priority <<")"<<endl;
                temp = temp->next;
            }
        }

        ~PriorityQueue()
        {
            while(head != nullptr) {
                Patient* temp = head;
                head = head->next;
                delete temp;
            }
        }      
};

int main()
{
    PriorityQueue pq;
    int choice, priority;
    string name;
    
    do {
        cout << "\n====Hospital Priority Queue Menu====";
        cout << "\n1. Add Patient";
        cout << "\n2. Serve Patient";
        cout << "\n3. Display Patients";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter patient name: ";
                cin >> name;
                cout << "Enter patient priority (lower number = higher priority): ";
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
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 4);
    
    return 0;
}