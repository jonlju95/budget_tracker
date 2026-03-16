# budget_tracker

A command line budget tracker written in C++. Log income and expenses, view summaries, and filter by category. Data is
saved to a local csv-file and persists between sessions.

## Usage

```
budget_tracker.exe
```

Once running, type a command at the `>` prompt.

## Commands

| Command           | Description                                            |
|-------------------|--------------------------------------------------------|
| `add`             | Add a new income or expense entry                      |
| `summary`         | Show total income, total expenses, and current balance |
| `list`            | List all entries                                       |
| `category <name>` | List all entries in a given category                   |
| `help`            | Show available commands                                |
| `quit`            | Exit the program                                       |

## Data storage

Entries are saved to `budget.csv` in the directory the program is run from. The file is created automatically on first
use. Each entry is stored as a comma-delimited line in the format:

```
type,category,description,amount
```

## Building

Requires a C++17 compatible compiler. Built with CMake.

```
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build .
```

> **Note for Windows/MinGW builds:** Add the following to `CMakeLists.txt` to avoid missing DLL errors:
> ```cmake
> target_link_options(budget_tracker PRIVATE -static)
> ```