#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// Represents a single financial entry (income or expense)
struct Entry {
    std::string type; // "income" or "expense"
    std::string category; // e.g. "food", "rent", "salary"
    std::string description; // free text description
    double amount = 0.0;
};

const std::string DATA_FILE = "budget.csv";

// Serialize a single Entry to a string for storage
// Called when saving entries to disk
std::string serializeEntry(const Entry &entry) {
    return entry.type + "," + entry.category + "," + entry.description + "," + std::to_string(entry.amount);
}

// Deserialize a single line from the file back into an Entry
// Called when loading entries from disk
Entry deserializeEntry(const std::string &line) {
    Entry entry;
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, entry.type, ',');
    std::getline(ss, entry.category, ',');
    std::getline(ss, entry.description, ',');
    std::getline(ss, token, ',');
    entry.amount = std::stod(token);
    return entry;
}

// Load all entries from the data file
// Returns an empty vector if the file doesn't exist yet
std::vector<Entry> loadEntries() {
    std::vector<Entry> entries;
    std::ifstream file(DATA_FILE);
    if (!file.is_open()) {
        std::cout << "No existing data found, starting fresh." << std::endl;
        return {};
    }
    std::string line;
    std::getline(file, line); // Discard csv header
    while (std::getline(file, line)) {
        entries.push_back(deserializeEntry(line));
    }
    return entries;
}

// Save all entries to the data file, overwriting existing content
void saveEntries(const std::vector<Entry> &entries) {
    if (std::ofstream file(DATA_FILE); !file.is_open()) {
        std::cout << "Could not open file " << DATA_FILE << std::endl;
    } else {
        file << "type,category,description,amount" << std::endl;
        for (const Entry &entry: entries) {
            file << serializeEntry(entry) << std::endl;
        }
    }
}

// Prompt the user to input a new entry and return it
Entry promptEntry() {
    Entry entry;
    std::string line;
    while (entry.type != "income" && entry.type != "expense") {
        std::cout << "Type 'income' or 'expense': ";
        std::getline(std::cin, entry.type);
    }
    std::cout << "Type category: ";
    std::getline(std::cin, entry.category);
    std::cout << "Type description: ";
    std::getline(std::cin, entry.description);
    while (entry.amount < 0 || entry.amount == 0) {
        std::cout << "Type amount: ";
        std::getline(std::cin, line);
        try {
            entry.amount = std::stod(line);
        } catch (std::invalid_argument &e) {
            std::cout << "Invalid amount " << e.what() << std::endl;
        }
    }
    return entry;
}

// Add a new entry to the list and persist to disk
void addEntry(std::vector<Entry> &entries) {
    entries.push_back(promptEntry());
    saveEntries(entries);
    std::cout << "Entry added." << std::endl;
}

// Print a summary of all entries
// Shows total income, total expenses, and current balance
void printSummary(const std::vector<Entry> &entries) {
    double incomeAmount = 0.0;
    double expenseAmount = 0.0;
    for (const Entry &entry: entries) {
        if (entry.type == "income") {
            incomeAmount += entry.amount;
        } else {
            expenseAmount += entry.amount;
        }
    }
    std::cout << "Income: " << std::fixed << std::setprecision(2) << incomeAmount << std::endl;
    std::cout << "Expense: " << std::fixed << std::setprecision(2) << expenseAmount << std::endl;
    std::cout << "Current balance: " << std::fixed << std::setprecision(2) << incomeAmount - expenseAmount << std::endl;
}

// Print all entries filtered by category
// Case insensitive match
void printByCategory(const std::vector<Entry> &entries, const std::string &category) {
    bool found = false;
    for (const Entry &entry: entries) {
        if (entry.category == category) {
            found = true;
            std::cout << "[Type]: " << entry.type << std::endl;
            std::cout << "[Category]: " << entry.category << std::endl;
            std::cout << "[Description]: " << entry.description << std::endl;
            std::cout << "[Amount]: " << std::fixed << std::setprecision(2) << entry.amount << std::endl << std::endl;
        }
    }
    if (!found) std::cout << "No entries in category." << std::endl;
}

// Print all entries in a readable format
void printAll(const std::vector<Entry> &entries) {
    bool found = false;
    for (const Entry &entry: entries) {
        found = true;
        std::cout << "[Type]: " << entry.type << std::endl;
        std::cout << "[Category]: " << entry.category << std::endl;
        std::cout << "[Description]: " << entry.description << std::endl;
        std::cout << "[Amount]: " << std::fixed << std::setprecision(2) << entry.amount << std::endl << std::endl;
    }
    if (!found) std::cout << "No entries yet." << std::endl;
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
        std::cin.ignore();

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
