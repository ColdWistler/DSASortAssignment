#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Node structure for Doubly Linked List
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// Doubly Linked List class
class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Insert a new node at the end
    void insert(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Display the list
    void display(const string& message) {
        cout << "\n==================================\n";
        cout << message << "\n";
        cout << "==================================\n";
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    // Selection Sort
    void selectionSort() {
        for (Node* i = head; i && i->next; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j; j = j->next) {
                if (j->data < minNode->data)
                    minNode = j;
            }
            swap(i->data, minNode->data);
        }
    }

    // Merge Sort Helper
    Node* merge(Node* first, Node* second) {
        if (!first) return second;
        if (!second) return first;

        if (first->data < second->data) {
            first->next = merge(first->next, second);
            first->next->prev = first;
            first->prev = nullptr;
            return first;
        } else {
            second->next = merge(first, second->next);
            second->next->prev = second;
            second->prev = nullptr;
            return second;
        }
    }

    // Split linked list into two halves
    Node* split(Node* head) {
        Node* fast = head, * slow = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* temp = slow->next;
        slow->next = nullptr;
        return temp;
    }

    // Merge Sort
    Node* mergeSort(Node* node) {
        if (!node || !node->next) return node;
        Node* second = split(node);
        return merge(mergeSort(node), mergeSort(second));
    }

    void sortWithMergeSort() {
        head = mergeSort(head);
        Node* temp = head;
        while (temp->next) temp = temp->next;
        tail = temp;
    }

    // Search for a key
    bool search(int key) {
        Node* temp = head;
        while (temp) {
            if (temp->data == key) return true;
            temp = temp->next;
        }
        return false;
    }
};

// Function to generate random numbers
void generateRandomNumbers(DoublyLinkedList& list, int N) {
    for (int i = 0; i < N; i++) {
        list.insert(rand() % 1000);
    }
}

// Function to measure execution time
void measureExecutionTime() {
    int N;
    cout << "Enter the number of elements: ";
    cin >> N;
    DoublyLinkedList list;
    generateRandomNumbers(list, N);
    list.display("Generated Numbers");

    cout << "\n=========== SORTING RESULTS ===========\n";
    auto start = high_resolution_clock::now();
    list.selectionSort();
    auto stop = high_resolution_clock::now();
    list.display("Selection Sorted Numbers");
    cout << "Selection Sort Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    generateRandomNumbers(list, N);
    start = high_resolution_clock::now();
    list.sortWithMergeSort();
    stop = high_resolution_clock::now();
    list.display("Merge Sorted Numbers");
    cout << "Merge Sort Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    cout << "\n=========== SEARCH RESULTS ===========\n";
    int searchKey;
    cout << "Enter number to search: ";
    cin >> searchKey;
    start = high_resolution_clock::now();
    bool found = list.search(searchKey);
    stop = high_resolution_clock::now();
    cout << "Search Time: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";
    cout << "Search Result: " << (found ? "Found" : "Not Found") << "\n";
}

int main() {
    measureExecutionTime();
    return 0;
}
