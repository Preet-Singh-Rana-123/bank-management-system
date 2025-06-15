#include <iostream>
#include <fstream>
#include <istream>
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

    friend void writeInFile(User u);
};

vector<User> users;
int User ::nextAccountNo = 100000;

void writeInFile(User u)
{
    ofstream outfile("accounts.txt", ios::app);
    if (outfile.is_open())
    {
        outfile << u.accountNo << "|" << u.name << "|" << u.address << "|" << u.branchName << "|" << u.pin << "\n";
        cout << "your account has been created.\n";
        outfile.close();
    }
    else
    {
        cout << "Sorry error in opening accounts.txt.\n";
    }
}

void createAccount()
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

    users.emplace_back(name, address, branchName, pin);
    writeInFile(users.back());
}

int main()
{
    cout << "======== Bank Management System ========" << endl;
    cout << "1. Create Account\n";
    cout << "2. See account details\n";
    cout << "3. Deposite amount\n";
    cout << "4. Withdraw amount\n";
    cout << "5. Update account details\n";
    cout << "6. Exit\n";

    int userChoice;

    cin >> userChoice;
    cin.ignore();

    switch (userChoice)
    {
    case 1:
    {
        createAccount();
        break;
    }
    case 2:
    {
        int pin;
        int accountNo;

        cout << "Enter your account no. : ";
        cin >> accountNo;
        cout << "Enter your pin:  ";
        cin >> pin;
    }
    }
    return 0;
}