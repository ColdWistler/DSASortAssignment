#ifndef SORTINGSEARCHINGAPP_H
#define SORTINGSEARCHINGAPP_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>

class SortingSearchingApp : public QWidget {
    Q_OBJECT

public:
    explicit SortingSearchingApp(QWidget *parent = nullptr);

private slots:
    void generateRandomNumbers();
    void selectionSort();
    void binarySearch();
    void displayNumbers(const QString &message);

private:
    QLineEdit *inputField;
    QTextEdit *outputField;
    std::vector<int> numbers;
};

#endif // SORTINGSEARCHINGAPP_H

#include "sortingsearchingapp.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

SortingSearchingApp::SortingSearchingApp(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Enter numbers (comma separated):", this);
    layout->addWidget(label);

    inputField = new QLineEdit(this);
    layout->addWidget(inputField);

    QPushButton *generateBtn = new QPushButton("Generate Random Numbers", this);
    layout->addWidget(generateBtn);
    connect(generateBtn, &QPushButton::clicked, this, &SortingSearchingApp::generateRandomNumbers);

    QPushButton *sortBtn = new QPushButton("Sort (Selection Sort)", this);
    layout->addWidget(sortBtn);
    connect(sortBtn, &QPushButton::clicked, this, &SortingSearchingApp::selectionSort);

    QPushButton *searchBtn = new QPushButton("Binary Search", this);
    layout->addWidget(searchBtn);
    connect(searchBtn, &QPushButton::clicked, this, &SortingSearchingApp::binarySearch);

    outputField = new QTextEdit(this);
    outputField->setReadOnly(true);
    layout->addWidget(outputField);
}

void SortingSearchingApp::generateRandomNumbers() {
    numbers.clear();
    srand(time(nullptr));
    for (int i = 0; i < 10; ++i) {
        numbers.push_back(rand() % 100);
    }
    displayNumbers("Generated Numbers: ");
}

void SortingSearchingApp::selectionSort() {
    for (size_t i = 0; i < numbers.size(); ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < numbers.size(); ++j) {
            if (numbers[j] < numbers[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(numbers[i], numbers[minIndex]);
    }
    displayNumbers("Sorted Numbers: ");
}

void SortingSearchingApp::binarySearch() {
    bool ok;
    int key = inputField->text().toInt(&ok);
    if (!ok) {
        outputField->setText("Invalid input for search.");
        return;
    }

    int left = 0, right = numbers.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (numbers[mid] == key) {
            outputField->setText("Found at index: " + QString::number(mid));
            return;
        }
        if (numbers[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    outputField->setText("Not found.");
}

void SortingSearchingApp::displayNumbers(const QString &message) {
    QString result = message;
    for (int num : numbers) {
        result += QString::number(num) + " ";
    }
    outputField->setText(result);
}

#include "sortingsearchingapp.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SortingSearchingApp window;
    window.setWindowTitle("Sorting & Searching App");
    window.resize(400, 300);
    window.show();
    return app.exec();
}
