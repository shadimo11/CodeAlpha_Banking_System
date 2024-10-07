#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class to represent a Transaction
class Transaction {
    string type;
    double amount;
    string date;

public:
    Transaction(string type, double amount, string date)
        : type(type), amount(amount), date(date) {}

    void displayTransaction() const {
        cout << "Transaction Type: " << type << ", Amount: $" << amount << ", Date: " << date << "\n";
    }
};

// Class to represent a Bank Account
class Account {
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accountNumber, double initialBalance)
        : accountNumber(accountNumber), balance(initialBalance) {}

    int getAccountNumber() const { return accountNumber; }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount, __DATE__ " " __TIME__);
        cout << "Deposit successful. New balance: $" << balance << "\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            transactions.emplace_back("Withdrawal", amount, __DATE__ " " __TIME__);
            cout << "Withdrawal successful. New balance: $" << balance << "\n";
        }
    }

    void transfer(Account& toAccount, double amount) {
        if (amount > balance) {
            cout << "Insufficient balance for transfer!\n";
        } else {
            withdraw(amount);
            toAccount.deposit(amount);
            cout << "Transfer successful. Transferred $" << amount << " to Account Number: " << toAccount.getAccountNumber() << "\n";
        }
    }

    void displayTransactionHistory() {
        if (transactions.empty()) {
            cout << "No transactions found for this account.\n";
        } else {
            for (const auto& transaction : transactions) {
                transaction.displayTransaction();
            }
        }
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << ", Balance: $" << balance << "\n";
    }
};

// Class to represent a Customer
class Customer {
    string name;
    int customerID;
    vector<Account> accounts;

public:
    Customer(string name, int customerID)
        : name(name), customerID(customerID) {}

    int getCustomerID() const { return customerID; }

    void createAccount(int accountNumber, double initialBalance) {
        accounts.emplace_back(accountNumber, initialBalance);
        cout << "Account created successfully for " << name << " with Account Number: " << accountNumber << "\n";
    }

    Account* getAccount(int accountNumber) {
        for (Account& acc : accounts) {
            if (acc.getAccountNumber() == accountNumber) {
                return &acc;
            }
        }
        return nullptr;
    }

    void displayCustomerInfo() const {
        cout << "Customer Name: " << name << ", Customer ID: " << customerID << "\n";
        cout << "Accounts:\n";
        for (const auto& account : accounts) {
            account.displayAccountInfo();
        }
    }
};

// Class to represent a Bank
class Bank {
    vector<Customer> customers;

public:
    void createCustomer(string name, int customerID) {
        customers.emplace_back(name, customerID);
        cout << "Customer created successfully with Customer ID: " << customerID << "\n";
    }

    Customer* getCustomer(int customerID) {
        for (Customer& cust : customers) {
            if (cust.getCustomerID() == customerID) {
                return &cust;
            }
        }
        return nullptr;
    }
};

// Main function to run the Bank Management System
int main() {
    Bank bank;
    int choice;

    while (true) {
        cout << "\n=== Bank Management System ===\n";
        cout << "1. Create Customer\n2. Create Account\n3. Deposit\n4. Withdraw\n5. Transfer\n6. Display Account Information\n7. Display Transaction History\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int customerID;
            cout << "Enter Customer Name: ";
            cin >> name;
            cout << "Enter Customer ID: ";
            cin >> customerID;
            bank.createCustomer(name, customerID);
        } else if (choice == 2) {
            int customerID, accountNumber;
            double initialBalance;
            cout << "Enter Customer ID: ";
            cin >> customerID;
            Customer* customer = bank.getCustomer(customerID);
            if (customer) {
                cout << "Enter New Account Number: ";
                cin >> accountNumber;
                cout << "Enter Initial Balance: ";
                cin >> initialBalance;
                customer->createAccount(accountNumber, initialBalance);
            } else {
                cout << "Customer not found!\n";
            }
        } else if (choice == 3) {  // Deposit
            int customerID, accountNumber;
            double amount;
            cout << "Enter Customer ID: ";
            cin >> customerID;
            Customer* customer = bank.getCustomer(customerID);
            if (customer) {
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                Account* account = customer->getAccount(accountNumber);
                if (account) {
                    cout << "Enter Amount to Deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                } else {
                    cout << "Account not found!\n";
                }
            } else {
                cout << "Customer not found!\n";
            }
        } else if (choice == 4) {  // Withdraw
            int customerID, accountNumber;
            double amount;
            cout << "Enter Customer ID: ";
            cin >> customerID;
            Customer* customer = bank.getCustomer(customerID);
            if (customer) {
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                Account* account = customer->getAccount(accountNumber);
                if (account) {
                    cout << "Enter Amount to Withdraw: ";
                    cin >> amount;
                    account->withdraw(amount);
                } else {
                    cout << "Account not found!\n";
                }
            } else {
                cout << "Customer not found!\n";
            }
        } else if (choice == 5) {  // Transfer
            int fromCustomerID, fromAccountNumber, toCustomerID, toAccountNumber;
            double amount;
            cout << "Enter Source Customer ID: ";
            cin >> fromCustomerID;
            cout << "Enter Source Account Number: ";
            cin >> fromAccountNumber;
            cout << "Enter Destination Customer ID: ";
            cin >> toCustomerID;
            cout << "Enter Destination Account Number: ";
            cin >> toAccountNumber;

            Customer* fromCustomer = bank.getCustomer(fromCustomerID);
            Customer* toCustomer = bank.getCustomer(toCustomerID);

            if (fromCustomer && toCustomer) {
                Account* fromAccount = fromCustomer->getAccount(fromAccountNumber);
                Account* toAccount = toCustomer->getAccount(toAccountNumber);

                if (fromAccount && toAccount) {
                    cout << "Enter Amount to Transfer: ";
                    cin >> amount;
                    fromAccount->transfer(*toAccount, amount);
                } else {
                    cout << "One of the accounts was not found!\n";
                }
            } else {
                cout << "One of the customers was not found!\n";
            }
        } else if (choice == 6) {  // Display Account Information
            int customerID;
            cout << "Enter Customer ID: ";
            cin >> customerID;
            Customer* customer = bank.getCustomer(customerID);
            if (customer) {
                customer->displayCustomerInfo();
            } else {
                cout << "Customer not found!\n";
            }
        } else if (choice == 7) {  // Display Transaction History
            int customerID, accountNumber;
            cout << "Enter Customer ID: ";
            cin >> customerID;
            Customer* customer = bank.getCustomer(customerID);
            if (customer) {
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                Account* account = customer->getAccount(accountNumber);
                if (account) {
                    account->displayTransactionHistory();
                } else {
                    cout << "Account not found!\n";
                }
            } else {
                cout << "Customer not found!\n";
            }
        } else if (choice == 8) {  // Exit
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
