Sorting & Searching Application

Overview

This is a Qt-based C++ application that allows users to perform sorting and searching operations on a list of numbers. It provides a graphical user interface (GUI) for an intuitive user experience.

Features

Generate Random Numbers: Creates a list of random numbers.

Selection Sort: Sorts the list using the selection sort algorithm.

Binary Search: Searches for a user-specified number using the binary search algorithm.

User-Friendly GUI: Built using Qt for an interactive experience.

Requirements

To run this project, you need:

Qt 5 or Qt 6 (Qt Creator recommended)

C++ Compiler (GCC, Clang, or MSVC)

CMake (optional but recommended for builds)

Installation & Setup

1. Clone the Repository
```
git clone https://github.com/yourusername/sorting-searching-app.git
cd sorting-searching-app
```
2. Build the Project

Using Qt Creator:

Open sorting-searching-app.pro in Qt Creator.

Configure the project with an appropriate Qt kit.

Click Build → Run or press Ctrl + R.

Using Terminal (qmake):
```
qmake SortingSearchingApp.pro
make
./SortingSearchingApp
```
Using CMake (optional alternative):
```
mkdir build && cd build
cmake ..
make
./SortingSearchingApp
```
Usage

Enter numbers in the input field (comma-separated).

Click Generate Random Numbers to create a list.

Click Sort (Selection Sort) to sort the numbers.

Enter a number and click Binary Search to search for it.

Results are displayed in the text area.

File Structure
```
├── sortingsearchingapp.h    # Class declaration
├── sortingsearchingapp.cpp  # Class implementation
├── main.cpp                 # Entry point
├── SortingSearchingApp.pro  # Qt project file
├── README.md                # Documentation
└── assets/                  # (Optional) Icons, screenshots
```
Contribution

Feel free to fork and contribute by submitting a pull request.

License

This project is licensed under the MIT License.

