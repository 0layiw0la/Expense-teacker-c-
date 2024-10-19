#ifndef EXPENSES_H
#define EXPENSES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>

struct Expense {
    std::string date;
    std::string description;
    double amount;
};

// Function declarations
std::string getDate();
int getYear(const std::string& date);
int getMonth(const std::string& date);
bool fileExists(const std::string& filename);
std::vector<Expense> readCSV(const std::string& filename);
void writeCSV(const std::string& filename, const std::vector<Expense>& expenses, bool append = true);
double calculateTotalSpentInYear(const std::vector<Expense>& expenses, int year);
double calculateTotalSpentInMonth(const std::vector<Expense>& expenses, int year, int month);
Expense findHighestExpense(const std::vector<Expense>& expenses);
void addExpense(std::vector<Expense>& expenses);
void clearAllRecords(const std::string& filename, std::vector<Expense>& expenses);
void displaySummary(const std::vector<Expense>& expenses); // Declare the function here

#endif // EXPENSES_H
