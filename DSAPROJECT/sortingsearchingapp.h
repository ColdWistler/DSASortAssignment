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
