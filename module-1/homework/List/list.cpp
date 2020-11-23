#include <iostream>
#include "list.h"

namespace task {

    list::list() : size_(0), head(nullptr), tail(nullptr) {}

    list::list(const list& other){
        size_ = 0;
        head = nullptr;
        tail = nullptr;
        Node* current = other.head;
        while(current != nullptr){
            push_back(current->data);
            current = current->pNext;
        }
    }

    list::~list() {
        clear();
    }

    list::list(size_t count, const int &value) : list::list() {
        for (size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    list &list::operator=(const list& other) {
        if(this == &other)
            return *this;
        while (!empty())
            pop_back();
        Node *current = other.head;
        while (current) {
            push_back(current->data);
            current = current->pNext;
        }
        return *this;
    }
    bool list::operator==(const list& other){
        if(size_ != other.size())
            return false;
        if(size_ == 0)
            return true;
        Node* current = head;
        Node* current_other = other.head;
        while(current != nullptr){
            if(current->data != current_other->data)
                return false;
            current = current->pNext;
            current_other = current_other->pNext;
        }
        return true;
    }

    int &list::front() {
        return head->data;
    }
    const int &list::front() const {
        return head->data;
    }
    int &list::back() {
        return tail->data;
    }
    const int &list::back() const {
        return tail->data;
    }

    bool list::empty() const {
        return (head == nullptr);
    }
    size_t list::size() const {
        return size_;
    }
    void list::clear() {
        while(!empty())
            pop_back();
        head = nullptr;
        tail = nullptr;
        size_ = 0;

    }

    void list::push_back(const int &value) {
        Node *newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            newNode->pPrev = tail;
            tail->pNext = newNode;
        }
        tail = newNode;
        size_++;
    }
    void list::pop_back() {
        Node *newTail = tail->pPrev;
        if (newTail)
            newTail->pNext = nullptr;
        delete tail;
        tail = newTail;
        size_--;
        if (!size_)
            head = nullptr;
    }
    void list::push_front(const int &value) {
        Node *newNode = new Node(value);
        if (!head) {
            tail = newNode;
        } else {
            head->pPrev = newNode;
            newNode->pNext = head;
        }
        head = newNode;
        size_++;
    }
    void list::pop_front() {
        Node *newHead = head->pNext;
        delete head;
        if (newHead)
            newHead->pPrev = nullptr;
        head = newHead;
        size_--;
        if (!size_)
            tail = nullptr;
    }

    void list::resize(size_t count) {
        if (count == size())
            return;
        while (count < size())
            pop_back();
        while (count > size())
            push_back(int());
        size_ = count;
    }
    void list::swap(list &other) {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size_, other.size_);
    }
    void list::remove(const int &value_) {
        Node *current = head;
        int value = value_;
        while(current != nullptr){
            if(current == head && current->data == value){
                current = current->pNext;
                pop_front();
                continue;
            }
            if(current->data != value) {
                current = current->pNext;
                continue;
            }
            if(current->pNext != nullptr){
                if(current->pPrev != nullptr) {
                    current->pPrev->pNext = current->pNext;
                    current->pNext->pPrev = current->pPrev;
                }
                current->pNext->pPrev = current->pPrev;
            }
            else{
                tail = current->pPrev;
                if(current->pPrev != nullptr)
                    current->pPrev->pNext = nullptr;
            }
            size_--;
            current = current ->pNext;
        }
    }
    void list::unique(){
        if(head == nullptr || head->pNext == nullptr)
            return;
        Node* current = head;
        while(current != nullptr){
            while(current->pNext != nullptr && current->pNext->data == current->data){
                if(current->pNext->pNext != nullptr) {
                    Node* next = current->pNext;
                    current->pNext = current->pNext->pNext;
                    current->pNext->pPrev = current;
                    delete next;
                }
                else
                    current->pNext = nullptr;
                size_--;
            }
            current = current->pNext;
        }
    }
    void list::sort() {
        task::list::QuickSort(head,tail);
    }
    list::Node* list::Partition(Node* left, Node* right){
        int data_ = right->data;
        Node* pivot = left->pPrev;
        for(Node* j = left; j != right; j = j->pNext){
            if(j->data <= data_){
                pivot = (pivot == nullptr ? left : pivot->pNext);
                int temp = pivot->data;
                pivot->data = j->data;
                j->data = temp;

            }
        }
        pivot = (pivot == nullptr) ? left : pivot->pNext;
        int temp = pivot->data;
        pivot->data = right->data;
        right->data = temp;
        return pivot;
    }
    void list::QuickSort(Node* left, Node* right){
        if(right != nullptr && left != right && left != right->pNext){
            Node* p = Partition(left,right);
            QuickSort(left, p->pPrev);
            QuickSort(p->pNext, right);
        }
    }


}
