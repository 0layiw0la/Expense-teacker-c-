#include <iostream>
#include "expenses.h"

int main() {
    std::string filename = "expenses.csv";

    // Check if the file exists, if not create one with a header
    if (!fileExists(filename)) {
        std::ofstream file(filename);
        // Create the header
        file << "Date,Description,Amount\n";
    }

    // Load existing expenses from CSV
    std::vector<Expense> expenses = readCSV(filename);

    // Display the summary initially if there are expenses
    displaySummary(expenses);

    int choice;

    do {
        std::cout << "\nWhat do you want to do?\n";
        std::cout << "1. Add a new expense\n";
        std::cout << "2. Clear all records\n";  // Option to clear all records
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            addExpense(expenses);
            writeCSV(filename, expenses, true); // Append the new entry to the CSV
            displaySummary(expenses); // Display the summary again
            break;
        }
        case 2: {
            char confirm;
            std::cout << "Are you sure you want to clear all records? (y/n): ";
            std::cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                clearAllRecords(filename, expenses);
                expenses.clear(); // Clear the vector as well
                std::cout << "All records cleared.\n";
            } else {
                std::cout << "Clear action cancelled.\n";
            }
            displaySummary(expenses); // Display the summary again
            break;
        }
        case 3:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
