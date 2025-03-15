#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct ComplexData {
    int id;
    string name;
    double value;
};

struct Node {
    ComplexData data;
    Node* next;
    Node* prev;
};

void insert(Node*& head, ComplexData value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (head == nullptr) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        Node* last = head->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = head;
        head->prev = newNode;
    }
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    Node* temp = head;
    do {
        cout << "ID: " << temp->data.id << ", Name: " << temp->data.name << ", Value: " << temp->data.value << endl;
        temp = temp->next;
    } while (temp != head);
}

void selectionSort(Node*& head) {
    if (head == nullptr) return;
    Node* temp = head;
    do {
        Node* minNode = temp;
        Node* r = temp->next;
        while (r != head) {
            if (minNode->data.id > r->data.id) {
                minNode = r;
            }
            r = r->next;
        }
        swap(temp->data, minNode->data);
        temp = temp->next;
    } while (temp != head);
}

long long measureTime(void (*func)(Node*&), Node*& head) {
    auto start = high_resolution_clock::now();
    func(head);
    auto stop = high_resolution_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

void analyzeAlgorithms(Node*& head, int N) {
    cout << "\nAlgorithm Performance Analysis" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << setw(25) << left << "Algorithm" << setw(15) << "Time (ms)" << endl;
    cout << "----------------------------------------------------" << endl;
    
    Node* tempHead = head;
    long long selectionSortTime = measureTime(selectionSort, tempHead);
    cout << setw(25) << left << "Selection Sort" << setw(15) << selectionSortTime << endl;
    
    cout << "\nTime Complexity Analysis:" << endl;
    cout << "Selection Sort: Best - O(N^2), Average - O(N^2), Worst - O(N^2)" << endl;
    cout << "Merge Sort: Best - O(N log N), Average - O(N log N), Worst - O(N log N)" << endl;
    cout << "Binary Search: Best - O(1), Average - O(log N), Worst - O(log N)" << endl;
    cout << "Interpolation Search: Best - O(1), Average - O(log log N), Worst - O(N)" << endl;
}

int main() {
    Node* head = nullptr;
    int N;
    cout << "Enter the number of random data items (N): ";
    cin >> N;
    generateRandomData(head, N);
    cout << "Generated List: " << endl;
    printList(head);
    analyzeAlgorithms(head, N);
    deleteList(head);
    return 0;
}
