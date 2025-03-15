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

void split(Node* head, Node*& firstHalf, Node*& secondHalf) {
    if (!head || head->next == head) return;
    Node* slow = head;
    Node* fast = head->next;
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    firstHalf = head;
    secondHalf = slow->next;
    slow->next = firstHalf;
    firstHalf->prev = slow;
    Node* last = secondHalf;
    while (last->next != head) last = last->next;
    last->next = secondHalf;
    secondHalf->prev = last;
}

Node* merge(Node* first, Node* second) {
    if (!first) return second;
    if (!second) return first;
    if (first->data.id <= second->data.id) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        return first;
    } else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        return second;
    }
}

void mergeSort(Node*& head) {
    if (!head || head->next == head) return;
    Node* firstHalf = nullptr;
    Node* secondHalf = nullptr;
    split(head, firstHalf, secondHalf);
    mergeSort(firstHalf);
    mergeSort(secondHalf);
    head = merge(firstHalf, secondHalf);
}

Node* binarySearch(Node* head, int key) {
    Node* start = head;
    Node* end = head->prev;
    while (start != end) {
        Node* mid = start;
        for (Node* temp = start; temp != end; temp = temp->next) mid = mid->next;
        if (mid->data.id == key) return mid;
        else if (mid->data.id < key) start = mid->next;
        else end = mid->prev;
    }
    return start->data.id == key ? start : nullptr;
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
    long long mergeSortTime = measureTime(mergeSort, tempHead);
    cout << setw(25) << left << "Merge Sort" << setw(15) << mergeSortTime << endl;
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
