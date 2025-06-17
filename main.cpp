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
    int balance;
    vector<string> transactionHistory;

public:
    User(string name, string address, string branchName, int pin)
    {
        this->name = name;
        this->address = address;
        this->branchName = branchName;
        this->pin = pin;
        this->accountNo = ++nextAccountNo;
        this->balance = 0;
    }

    friend void writeInFile(User u);
    friend bool isCorrectAccount(User u, int n);
    friend bool isCorrectPin(User u, int pin);
    friend void displayAccountDetails(User u, int n);
    friend void depositeAomount();
    friend void withdrawAmount();
    friend void writeTransactionHistory(User u);
    friend bool isAccountPresent(int accountNo);
    friend void updateAccount();
    friend void showHistory();
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

bool isAccountPresent(int accountNo)
{
    for (auto &u : users)
    {
        if (accountNo == u.accountNo)
            return 1;
    }
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

void displayAccountDetails(User u, int n)
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
        cout << "Write your pin again: ";
        cin >> newUserInputPin;
        displayAccountDetails(u, newUserInputPin);
    }
}

void showAccountDetail()
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
            displayAccountDetails(user, userInputPin);
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Account not found!!\n";
        cout << "Try Again\n";
        showAccountDetail();
    }
}

User* foundAccount(int accountNo)
{
    for (auto &user : users)
    {
        if (isCorrectAccount(user, accountNo))
        {
            return &user;
        }
    }
    return nullptr;
}

void depositeAomount()
{
    int userInputAccountNo, userInputPin, userInputBalance;
    cout << "Enter your account number: ";
    cin >> userInputAccountNo;
    if (!isAccountPresent(userInputAccountNo))
    {
        cout << "Account not present!!\n";
        cout << "Try Again.\n";
        depositeAomount();
    }
    User *foundedAccount = foundAccount(userInputAccountNo);
    cout << "Enter your pin: ";
    cin >> userInputPin;
    if (!isCorrectPin(*foundedAccount, userInputPin))
    {
        cout << "Pin is incorrect!!\n";
        cout << "Try Again.\n";
        depositeAomount();
    }

    cout << "Enter balance you want to deposite: ";
    cin >> userInputBalance;
    if (userInputBalance <= 0)
    {
        cout << "Invalid amount. Please enter a positive number.\n";
        cout << "Try Again\n";
        depositeAomount();
    }

    foundedAccount->balance += userInputBalance;
    foundedAccount->transactionHistory.push_back("Deposited: " + to_string(userInputBalance));
    cout << "Your amount has been deposited!\n";
}

void withdrawAmount()
{
    int userInputAccountNo, userInputPin, userInputBalance;
    cout << "Enter your account number: ";
    cin >> userInputAccountNo;
    if (!isAccountPresent(userInputAccountNo))
    {
        cout << "Account not present!!\n";
        cout << "Try Again.\n";
        withdrawAmount();
    }
    User *foundedAccount = foundAccount(userInputAccountNo);
    cout << "Enter your pin: ";
    cin >> userInputPin;
    if (!isCorrectPin(*foundedAccount, userInputPin))
    {
        cout << "Pin is incorrect!!\n";
        cout << "Try Again.\n";
        withdrawAmount();
    }

    if (foundedAccount->balance <= 0)
    {
        cout << "Your balance is 0. Amount cannot be withdrawed\n";
        return;
    }

    cout << "Enter balance you want to withdraw: ";
    cin >> userInputBalance;
    if (userInputBalance <= 0)
    {
        cout << "Invalid amount. Please enter a positive number.\n";
        cout << "Try Again\n";
        withdrawAmount();
    }

    foundedAccount->balance -= userInputBalance;
    foundedAccount->transactionHistory.push_back("Withdraw: " + to_string(userInputBalance));
    cout << "Your amount has been withdrawed!\n";
    cout<<"You have "<<foundedAccount->balance<<" amount left in your account.\n";
}

void updateAccount()
{
    int userInputAccountNo, userInputPin;
    cout << "Enter your account number: ";
    cin >> userInputAccountNo;
    if (!isAccountPresent(userInputAccountNo))
    {
        cout << "Account not present!!\n";
        cout << "Try Again.\n";
        updateAccount();
    }
    User *foundedAccount = foundAccount(userInputAccountNo);
    cout << "Enter your pin: ";
    cin >> userInputPin;
    cin.ignore();
    if (!isCorrectPin(*foundedAccount, userInputPin))
    {
        cout << "Pin is incorrect!!\n";
        cout << "Try Again.\n";
        updateAccount();
    }

    cout << "a. To update Name.\n";
    cout << "b. To update Address.\n";
    cout << "c. To update Branch Name.\n";
    cout << "d. To update all.\n";

    char userChoice;
    cout << "Enter your choice: ";
    cin >> userChoice;
    cin.ignore();

    switch (userChoice)
    {
    case 'a':
    {
        string newName;
        cout << "Enter your name: ";
        getline(cin, newName);
        foundedAccount->name = newName;
        cout<<"Your name has been updated\n";
        break;
    }
    case 'b':
    {
        string newAddress;
        cout << "Enter your Address: ";
        getline(cin, newAddress);
        foundedAccount->address = newAddress;
        cout<<"Your Address has been updated!!\n";
        break;
    }
    case 'c':
    {
        string newBranchName;
        cout << "Enter your Branch name: ";
        getline(cin, newBranchName);
        foundedAccount->name = newBranchName;
        cout<<"Your Branch Name has been updated!!\n";
        break;
    }
    case 'd':
    {
        string newName, newAddress, newBranchName;
        cout << "Enter your name: ";
        getline(cin, newName);
        cout << "Enter your Address: ";
        getline(cin, newAddress);
        cout << "Enter your Branch name: ";
        getline(cin, newBranchName);
        foundedAccount->name = newName;
        foundedAccount->address = newAddress;
        foundedAccount->name = newBranchName;
        cout<<"Your account has been updated!!\n";
        break;
    }
    default:
    {
        break;
    }
    }
}

void showHistory()
{
    int userInputAccountNo, userInputPin;
    cout << "Enter your account number: ";
    cin >> userInputAccountNo;
    if (!isAccountPresent(userInputAccountNo))
    {
        cout << "Account not present!!\n";
        cout << "Try Again.\n";
        showHistory();
    }
    User *foundedAccount = foundAccount(userInputAccountNo);
    cout << "Enter your pin: ";
    cin >> userInputPin;
    cin.ignore();
    if (!isCorrectPin(*foundedAccount, userInputPin))
    {
        cout << "Pin is incorrect!!\n";
        cout << "Try Again.\n";
        showHistory();
    }

    cout << "Transaction history for Account " << foundedAccount->accountNo << ":\n";
    if (foundedAccount->transactionHistory.empty())
    {
        cout << "No Transactions yet.\n";
    }
    else
    {
        for (auto &record : foundedAccount->transactionHistory)
        {
            cout << "- " << record << endl;
        }
    }
}

void systemHelpList()
{
    cout << "\n======== Bank Management System ========" << endl;
    cout << "1. Create Account\n";
    cout << "2. See account details\n";
    cout << "3. Deposite amount\n";
    cout << "4. Withdraw amount\n";
    cout << "5. Update account details\n";
    cout << "6. See Your transaction history\n";
    cout << "7. Exit\n";
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
            showAccountDetail();
            systemHelpList();
            break;
        }
        case 3:
        {
            depositeAomount();
            systemHelpList();
            break;
        }
        case 4:
        {
            withdrawAmount();
            systemHelpList();
            break;
        }
        case 5:
        {
            updateAccount();
            systemHelpList();
            break;
        }
        case 6:
        {
            showHistory();
            systemHelpList();
            break;
        }
        default:
        {
            break;
        }
        }
    }

    return 0;
}