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
    friend bool isCorrectAccount(User u, int n);
    friend bool isCorrectPin(User u, int pin);
    friend void showAccountDetails(User u, int n);
};

vector<User> users;
int User ::nextAccountNo = 100000;

void writeInFile(User u)
{
    ofstream outfile("accounts.txt", ios::app);
    if (outfile.is_open())
    {
        outfile << u.accountNo << "|" << u.name << "|" << u.address << "|" << u.branchName << "|" << u.pin << "\n";
        cout << "Account created successfully!! Your account number is " << u.accountNo << endl;
        outfile.close();
    }
    else
    {
        cout << "Sorry error in opening accounts.txt.\n";
    }
}

bool isCorrectAccount(User u, int n)
{
    if (u.accountNo == n)
        return 1;
    return 0;
}

bool isCorrectPin(User u, int pin)
{
    if (u.pin == pin)
        return 1;
    return 0;
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

void showAccountDetails(User u, int n)
{
    int newUserInputPin;
    if (isCorrectPin(u, n))
    {
        cout << "Account Number: " << u.accountNo << endl;
        cout << "Name: " << u.name << endl;
        cout << "Address: " << u.address << endl;
        cout << "Branch Name: " << u.branchName << endl;
    }
    else
    {
        cout << "Pin is incorrect.\n";
        cin>>newUserInputPin;
        showAccountDetails(u,newUserInputPin);
    }
}

void systemHelpList(){
    cout << "\n======== Bank Management System ========" << endl;
    cout << "1. Create Account\n";
    cout << "2. See account details\n";
    cout << "3. Deposite amount\n";
    cout << "4. Withdraw amount\n";
    cout << "5. Update account details\n";
    cout << "6. Exit\n";
}

int main()
{
    systemHelpList();
    while (true)
    {
        int userChoice;

        cin >> userChoice;
        cin.ignore();

        switch (userChoice)
        {
        case 1:
        {
            createAccount();
            systemHelpList();
            break;
        }
        case 2:
        {
            int userInputAccountNo, userInputPin;
            cout << "Enter your account number: ";
            cin >> userInputAccountNo;

            bool found = false;

            for (const auto &user : users)
            {
                if (isCorrectAccount(user, userInputAccountNo))
                {
                    cout << "Enter your pin: ";
                    cin >> userInputPin;
                    showAccountDetails(user, userInputPin);
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"Account not found!!\n";
                cout<<"Try Again\n";
            }
            break;
        }
        }
    }

    return 0;
}