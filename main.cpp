#include <iostream>
#include <string>
using namespace std;

struct Node {
    int accountNo;
    string name;
    string password;
    double balance;
    int age;
    Node* prev;
    Node* next;
};

class Bank {
private:
    Node* head;
    Node* tail;

public:
    Bank() : head(nullptr), tail(nullptr) {}

    void createAccount() {
        int accountNo;
        string name, password;
        double balance;
        int age;

        cout << "Enter account number: ";
        cin >> accountNo;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Create password: ";
        cin >> password;
        cout << "Enter initial balance: ";
        cin >> balance;
        cout << "Enter age: ";
        cin >> age;

        if (age < 18) {
            cout << "You must be 18 or older to create a bank account." << endl;
            return;
        }

        Node* newNode = new Node{accountNo, name, password, balance, age, nullptr, nullptr};
        if (head == nullptr) {
            head = tail = newNode;
            head->next = head->prev = head; // Circular initialization
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head; // Circular linking
            head->prev = newNode;
            tail = newNode;
        }

        cout << "Account created successfully." << endl;
    }

    void checkBalance(int accountNo, string password) {
        Node* current = findAccount(accountNo, password);
        if (current != nullptr) {
            cout << "Dear " << current->name << ", your account balance is: " << current->balance << endl;
        } else {
            cout << "Invalid account number or password." << endl;
        }
    }

    void debit(int accountNo, string password, double amount) {
        Node* current = findAccount(accountNo, password);
        if (current != nullptr) {
            if (current->balance >= amount) {
                current->balance -= amount;
                cout << "Dear " << current->name << ", debit successful. \nRemaining balance: " << current->balance << endl;
            } else {
                cout << "Dear " << current->name << ", insufficient balance." << endl;
            }
        } else {
            cout << "Invalid account number or password." << endl;
        }
    }

    void credit(int accountNo, string password, double amount) {
        Node* current = findAccount(accountNo, password);
        if (current != nullptr) {
            current->balance += amount;
            cout << "Dear " << current->name << ", credit successful.\n Updated balance: " << current->balance << endl;
        } else {
            cout << "Invalid account number or password." << endl;
        }
    }

    Node* findAccount(int accountNo, string password) {
        if (head == NULL) {
            cout << "No account available." << endl;
            return nullptr;
        }
        Node* current = head;
        do {
            if (current->accountNo == accountNo && current->password == password) {
                return current;
            }
            current = current->next;
        } while (current != head);
        return nullptr;
    }

    void del(int accountNo, string password) {
        if (head == NULL) {
            cout << "No account available." << endl;
            return;
        }
        Node* current = head;
        do {
            char key1;
            if (current->accountNo == accountNo && current->password == password) {
                cout << "if Delete account enter D or d:";
                cin >> key1;
                if (key1 == 'D' || key1 == 'd') {
                    if (current == head) {
                        current->prev = NULL;
                        current->next = NULL;
                    } else {
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                    }
                    delete current;
                    cout << "Account Deleted successfully." << endl;
                } else {
                    cout << "Deletation is cancel." << endl;
                }
                return;
            }
            current = current->next;
        } while (current != head);
        cout << "Incorrect password or account Number." << endl;
    }

    void displayMenu() {
        int choice;
        do {
            cout << "\nBanking System Menu\n";
            cout << "1. Create Account\n";
            cout << "2. Check Balance\n";
            cout << "3. Debit\n";
            cout << "4. Credit\n";
            cout << "5. Delete Account\n";
            cout << "6. Exit\n";


            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    createAccount();
                    break;
                }
                case 2: {
                    int accountNo;
                    string password;
                    cout << "Enter account number: ";
                    cin >> accountNo;
                    cout << "Enter password: ";
                    cin >> password;
                    checkBalance(accountNo, password);
                    break;
                }
                case 3: {
                    int accountNo;
                    string password;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> accountNo;
                    cout << "Enter password: ";
                    cin >> password;
                    cout << "Enter amount to debit: ";
                    cin >> amount;
                    debit(accountNo, password, amount);
                    break;
                }
                case 4: {
                    int accountNo;
                    string password;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> accountNo;
                    cout << "Enter password: ";
                    cin >> password;
                    cout << "Enter amount to credit: ";
                    cin >> amount;
                    credit(accountNo, password, amount);
                    break;
                }
                case 5: {
                    int accountNo;
                    string password;
                    cout << "Enter accountNo: ";
                    cin >> accountNo;
                    cout << "Enter password: ";
                    cin >> password;
                    del(accountNo, password);
                    break;
                }
                case 6: {
                    cout << "Exiting program...\n";
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            }
        } while (choice != 6);
    }
};

int main() {
    Bank bank;
    bank.displayMenu();

    return 0;
}


