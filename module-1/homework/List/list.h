#pragma once

#include <cstddef>

#ifndef LIST_H
#define LIST_H

namespace task {

    class list {

    public:

        list();
        list(size_t count, const int &value = int());
        list(const list& other);

        ~list();
        list &operator=(const list &other);
        bool operator==(const list &other);


        int &front();
        const int &front() const;

        int &back();
        const int &back() const;


        bool empty() const;
        size_t size() const;
        void clear();


        void push_back(const int &value);
        void pop_back();
        void push_front(const int &value);
        void pop_front();
        void resize(size_t count);
        void swap(list &other);


        void remove(const int &value);
        void unique();
        void sort();


    private:
        class Node;

        static Node *ListSort(Node *head_, Node *tail);

        class Node {
        public:
            Node *pNext;
            Node *pPrev;
            int data;

            Node(int data = int(), Node *pNext = nullptr, Node *pPrev = nullptr) {
                this->data = data;
                this->pNext = pNext;
                this->pPrev = pPrev;
            }
        };

        int size_;
        Node *head;
        Node *tail;
        void QuickSort(Node*, Node*);
        Node* Partition(Node*, Node*);


    };

}  // namespace task

#endif // LIST_H