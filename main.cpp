#include <iostream>
using namespace std;

class User
{
private:
    static int nextAccountNo;
    int accountNo;
    string name;
    int pin;
    string address;
    string branchName;

public:
    User(string name, string address, string branchName, int pin)
    {
        this->name = name;
        this->address = address;
        this->branchName = branchName;
        this->pin = pin;
        this->accountNo = ++nextAccountNo;
    }
};

int User ::nextAccountNo = 100000;

int main()
{

    cout << "======== Bank Management System ========" << endl;
    cout << "1. Create Account\n";
    cout << "2. Enter your Account\n";
    cout << "3. See your account details\n";
    cout << "4. Deposite amount\n";
    cout << "5. Withdraw amount\n";
    cout << "6. Update your account details\n";
    cout << "7. Exit your Account\n";

    int userChoice;
    vector<User> users;

    cin >> userChoice;

    if (userChoice == 1)
    {
        string name;
        string address;
        string branchName;
        int pin;

        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your address: ";
        getline(cin, address);
        cout << "Enter your branchName: ";
        getline(cin, branchName);
        cout << "Enter 6-digit pin for your account: ";
        cin >> pin;
        cin.ignore();
    }

    return 0;
}