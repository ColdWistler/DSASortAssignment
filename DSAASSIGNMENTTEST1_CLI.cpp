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

Node* linearSearch(Node* head, int key) {
    if (head == nullptr) return nullptr;
    Node* temp = head;
    do {
        if (temp->data.id == key) return temp;
        temp = temp->next;
    } while (temp != head);
    return nullptr;
}

void deleteList(Node*& head) {
    if (head == nullptr) return;
    Node* temp = head;
    do {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    } while (temp != head);
    head = nullptr;
}

void generateRandomData(Node*& head, int N) {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        ComplexData data;
        data.id = rand() % 1000;
        data.name = "Item" + to_string(data.id);
        data.value = (double)(rand() % 10000) / 100;
        insert(head, data);
    }
}

long long measureTime(void (*func)(Node*&), Node*& head) {
    auto start = high_resolution_clock::now();
    func(head);
    auto stop = high_resolution_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

void analyzeAlgorithms(Node*& head, int N) {
    cout << "\nAlgorithm Performance Analysis" << endl;
    cout << "--------------------------------------" << endl;
    cout << setw(20) << left << "Algorithm" << setw(15) << "Time (ms)" << endl;
    cout << "--------------------------------------" << endl;
    
    long long selectionSortTime = measureTime(selectionSort, head);
    cout << setw(20) << left << "Selection Sort" << setw(15) << selectionSortTime << endl;
    
    cout << "\nTime Complexity Analysis:" << endl;
    cout << "Selection Sort: Best - O(N^2), Average - O(N^2), Worst - O(N^2)" << endl;
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
    int key;
    cout << "Enter the ID to search: ";
    cin >> key;
    Node* result = linearSearch(head, key);
    if (result != nullptr) {
        cout << "Element found: ID: " << result->data.id << ", Name: " << result->data.name << ", Value: " << result->data.value << endl;
    } else {
        cout << "Element not found" << endl;
    }
    deleteList(head);
    return 0;
}
