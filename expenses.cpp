// expenses.cpp

#include "expenses.h"

// Function to get the current date in "YYYY-MM-DD" format
std::string getDate() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    std::ostringstream oss;
    oss << 1900 + ltm.tm_year << "-"
        << 1 + ltm.tm_mon << "-"
        << ltm.tm_mday;

    return oss.str();
}

// Function to extract year from a date string (YYYY-MM-DD)
int getYear(const std::string& date) {
    return std::stoi(date.substr(0, 4));
}

// Function to extract month from a date string (YYYY-MM-DD)
int getMonth(const std::string& date) {
    return std::stoi(date.substr(5, 2));
}

// Function to check if file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Function to read the CSV file and load expenses into a vector
std::vector<Expense> readCSV(const std::string& filename) {
    std::vector<Expense> expenses;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "File not found, starting with a new file.\n";
        return expenses;
    }

    std::string line;
    // Skip the header line if the file is not empty
    std::getline(file, line);

    // Read the CSV content into a vector
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Expense expense;

        std::getline(ss, expense.date, ',');
        std::getline(ss, expense.description, ',');
        ss >> expense.amount;

        expenses.push_back(expense);
    }
    return expenses;
}

// Function to write expenses back to the CSV file (append mode)
void writeCSV(const std::string& filename, const std::vector<Expense>& expenses, bool append) {
    std::ofstream file;

    if (append) {
        file.open(filename, std::ios::app); // Append to file
    } else {
        file.open(filename); // Overwrite file (when saving all)
        // Write the header
        file << "Date,Description,Amount\n";
    }

    // Write the expenses to the CSV file
    for (const auto& expense : expenses) {
        file << expense.date << "," << expense.description << "," << expense.amount << "\n";
    }
}

// Function to clear all expense records from the file
void clearAllRecords(const std::string& filename, std::vector<Expense>& expenses) {
    // Clear the expense list
    expenses.clear();

    // Overwrite the file with only the header
    writeCSV(filename, expenses, false);

    std::cout << "All expense records have been cleared!\n";
}

// Function to calculate total spent in the current year
double calculateTotalSpentInYear(const std::vector<Expense>& expenses, int year) {
    double total = 0;
    for (const auto& expense : expenses) {
        if (getYear(expense.date) == year) {
            total += expense.amount;
        }
    }
    return total;
}

// Function to calculate total spent in the current month
double calculateTotalSpentInMonth(const std::vector<Expense>& expenses, int year, int month) {
    double total = 0;
    for (const auto& expense : expenses) {
        if (getYear(expense.date) == year && getMonth(expense.date) == month) {
            total += expense.amount;
        }
    }
    return total;
}

// Function to find the item with the highest spend
Expense findHighestExpense(const std::vector<Expense>& expenses) {
    return *std::max_element(expenses.begin(), expenses.end(), [](const Expense& a, const Expense& b) {
        return a.amount < b.amount;
    });
}

// Function to add a new expense entry
void addExpense(std::vector<Expense>& expenses) {
    Expense newExpense;
    newExpense.date = getDate(); // Automatically add the current date

    std::string confirmation;
    do {
        std::cout << "Enter description: ";
        std::cin.ignore();
        std::getline(std::cin, newExpense.description);

        std::cout << "You entered: " << newExpense.description << "\n";
        std::cout << "Is this correct? (y/n): ";
        std::getline(std::cin, confirmation);

        if (confirmation != "y" && confirmation != "Y") {
            std::cout << "Let's correct the description.\n";
        }
    } while (confirmation != "y" && confirmation != "Y");

    std::cout << "Enter amount spent: ";
    std::cin >> newExpense.amount;

    expenses.push_back(newExpense);
    std::cout << "Expense added successfully!\n";
}


// Function to display the spending summary
void displaySummary(const std::vector<Expense>& expenses) {
    if (expenses.empty()) {
        std::cout << "No expenses to display.\n";
        return;
    }

    std::cout << "\n                                SPENDINGS SUMMARY:                                \n";

    // Get the current year and month
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    int currentYear = 1900 + ltm.tm_year;
    int currentMonth = 1 + ltm.tm_mon;

    // Display total spent in the current year
    double totalYear = calculateTotalSpentInYear(expenses, currentYear);
    std::cout << "                          Total spent this year: #" << totalYear << std::endl;

    std::cout << "\n";

    // Display total spent in the current month
    double totalMonth = calculateTotalSpentInMonth(expenses, currentYear, currentMonth);
    std::cout << "                          Total spent this month: #" << totalMonth << std::endl;

    std::cout << "\n";

    // Display the item with the highest spend
    Expense highest = findHighestExpense(expenses);
    std::cout << "                          Largest Expense: " << highest.description << " (#" << highest.amount << ")                                \n";
}