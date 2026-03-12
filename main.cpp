#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Represents a single financial entry (income or expense)
struct Entry {
    std::string type;        // "income" or "expense"
    std::string category;    // e.g. "food", "rent", "salary"
    std::string description; // free text description
    double amount;
};

const std::string DATA_FILE = "budget.txt";

// Serialize a single Entry to a string for storage
// Called when saving entries to disk
std::string serializeEntry(const Entry &entry) {
    // TODO: convert entry fields to a single line string
    // e.g. "income|salary|monthly pay|3000.00"
    return {};
}

// Deserialize a single line from the file back into an Entry
// Called when loading entries from disk
Entry deserializeEntry(const std::string &line) {
    // TODO: split the line by delimiter and populate an Entry struct

    return {};
}

// Load all entries from the data file
// Returns an empty vector if the file doesn't exist yet
std::vector<Entry> loadEntries() {
    // TODO: open DATA_FILE, read line by line, deserialize each line into an Entry
    return {};
}

// Save all entries to the data file, overwriting existing content
void saveEntries(const std::vector<Entry> &entries) {
    // TODO: open DATA_FILE for writing, serialize and write each entry as a line
}

// Prompt the user to input a new entry and return it
Entry promptEntry() {
    // TODO: ask the user for type, category, description, and amount
    // validate that type is either "income" or "expense"
    // validate that amount is a positive number
    return {};
}

// Add a new entry to the list and persist to disk
void addEntry(std::vector<Entry> &entries) {
    // TODO: call promptEntry(), push the result into entries, call saveEntries()
}

// Print a summary of all entries
// Shows total income, total expenses, and current balance
void printSummary(const std::vector<Entry> &entries) {
    // TODO: loop over entries, sum income and expenses separately
    // print totals and balance (income - expenses)
}

// Print all entries filtered by category
// Case insensitive match
void printByCategory(const std::vector<Entry> &entries, const std::string &category) {
    // TODO: loop over entries, print only those matching the given category
}

// Print all entries in a readable format
void printAll(const std::vector<Entry> &entries) {
    // TODO: print each entry with its type, category, description, and amount
}

// Print available commands to the user
void printHelp() {
    std::cout << "Commands:\n";
    std::cout << "  add              - Add a new entry\n";
    std::cout << "  summary          - Show income, expenses, and balance\n";
    std::cout << "  list             - List all entries\n";
    std::cout << "  category <name>  - List entries by category\n";
    std::cout << "  help             - Show this message\n";
    std::cout << "  quit             - Exit\n";
}

int main() {
    std::vector<Entry> entries = loadEntries();

    std::cout << "Budget Tracker\n";
    printHelp();

    std::string command;
    while (true) {
        std::cout << "\n> ";
        std::cin >> command;

        if (command == "add") {
            addEntry(entries);
        } else if (command == "summary") {
            printSummary(entries);
        } else if (command == "list") {
            printAll(entries);
        } else if (command == "category") {
            std::string category;
            std::cin >> category;
            printByCategory(entries, category);
        } else if (command == "help") {
            printHelp();
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Unknown command. Type 'help' for available commands.\n";
        }
    }

    return 0;
}
