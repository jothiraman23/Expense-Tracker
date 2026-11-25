
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

// Structure to store expense details
struct Expense
{
    string name;
    string category;
    double amount;
};

// Convert category to lowercase for comparison
string normalizeCategory(string category)
{
    transform(category.begin(), category.end(),
              category.begin(),
              [](unsigned char c) {
                  return static_cast<char>(tolower(c));
              });

    return category;
}

// Read and validate a menu choice
int readMenuChoice()
{
    string input;
    int choice;
    char extra;

    while (true)
    {
        cout << "Enter your choice: ";
        getline(cin, input);

        stringstream ss(input);

        if (ss >> choice && !(ss >> extra))
        {
            return choice;
        }

        cout << "Invalid input! Please enter a whole number.\n";
    }
}

// Read non-empty text
string readText(string message)
{
    string value;

    while (true)
    {
        cout << message;
        getline(cin, value);

        if (value.find_first_not_of(" \t") != string::npos)
        {
            return value;
        }

        cout << "Input cannot be empty. Try again.\n";
    }
}

// Read and validate a positive expense amount
double readAmount()
{
    string input;
    double amount;
    char extra;

    while (true)
    {
        cout << "Enter amount (Rs.): ";
        getline(cin, input);

        stringstream ss(input);

        if (ss >> amount &&
            !(ss >> extra) &&
            isfinite(amount) &&
            amount > 0)
        {
            return amount;
        }

        cout << "Invalid amount! Enter a positive number.\n";
    }
}

// Add a new expense
void addExpense(vector<Expense>& expenses)
{
    Expense e;

    cout << "\n========== ADD EXPENSE ==========\n";

    e.name = readText("Enter expense name: ");
    e.category = readText("Enter category: ");
    e.amount = readAmount();

    expenses.push_back(e);

    cout << "\nExpense added successfully!\n";
}

// Display all recorded expenses
void viewExpenses(const vector<Expense>& expenses)
{
    cout << "\n========== ALL EXPENSES ==========\n";

    if (expenses.empty())
    {
        cout << "No expenses recorded yet.\n";
        return;
    }

    cout << left
         << setw(6) << "No."
         << setw(22) << "Name"
         << setw(18) << "Category"
         << "Amount (Rs.)\n";

    cout << string(65, '-') << "\n";

    for (size_t i = 0; i < expenses.size(); i++)
    {
        cout << left
             << setw(6) << i + 1
             << setw(22) << expenses[i].name
             << setw(18) << expenses[i].category
             << fixed << setprecision(2)
             << expenses[i].amount << "\n";
    }
}

// Calculate overall expenditure
void calculateTotal(const vector<Expense>& expenses)
{
    double total = 0;

    for (const Expense& e : expenses)
    {
        total += e.amount;
    }

    cout << "\n========== OVERALL TOTAL ==========\n";

    cout << fixed << setprecision(2);
    cout << "Total Expenses: Rs." << total << "\n";
}

// Calculate category-wise expenditure
void categoryTotal(const vector<Expense>& expenses)
{
    if (expenses.empty())
    {
        cout << "\nNo expenses available for calculation.\n";
        return;
    }

    // Store category names and their totals
    map<string, pair<string, double>> totals;

    for (const Expense& e : expenses)
    {
        string key = normalizeCategory(e.category);

        totals[key].first = e.category;
        totals[key].second += e.amount;
    }

    cout << "\n======= CATEGORY-WISE SUMMARY =======\n";

    cout << left
         << setw(25) << "Category"
         << "Total (Rs.)\n";

    cout << string(42, '-') << "\n";

    for (const auto& item : totals)
    {
        cout << left
             << setw(25) << item.second.first
             << fixed << setprecision(2)
             << item.second.second << "\n";
    }
}

// Display application menu
void displayMenu()
{
    cout << "\n====================================\n";
    cout << "          EXPENSE TRACKER           \n";
    cout << "====================================\n";

    cout << "1. Add Expense\n";
    cout << "2. View All Expenses\n";
    cout << "3. View Category-wise Total\n";
    cout << "4. View Overall Total\n";
    cout << "5. Exit\n";

    cout << "====================================\n";
}

// Main function
int main()
{
    vector<Expense> expenses;

    int choice;

    cout << "\nWelcome to the Expense Tracker!\n";

    do
    {
        displayMenu();

        choice = readMenuChoice();

        switch (choice)
        {
            case 1:
                addExpense(expenses);
                break;

            case 2:
                viewExpenses(expenses);
                break;

            case 3:
                categoryTotal(expenses);
                break;

            case 4:
                calculateTotal(expenses);
                break;

            case 5:
                cout << "\nThank you for using Expense Tracker!\n";
                cout << "Have a great day!\n";
                break;

            default:
                cout << "\nInvalid choice! Select between 1 and 5.\n";
        }

    } while (choice != 5);

    return 0;
}
