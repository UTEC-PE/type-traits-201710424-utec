#ifndef SLIST_H
#define SLIST_H

#include "iterator.h"

template <class T>
class SListIterator : public Iterator<T> {
    public:
        SListIterator() : Iterator<T>() {};
        SListIterator(Node<T> *current) : Iterator<T>(current) {};
        SListIterator<T> operator++(){
          if (this->current) {
            this->current = this->current->next;
            return *this;
          }else throw("iterator point nothing");
        };
};

template <typename Tr>
class SList {
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
        typedef SListIterator<T> iterator;

    private:
        Node<T>* head;
        Operation cmp;

    public:
        SList() {
          head = nullptr;
        };

        bool find(T search, Node<T> **&pointer) {
          while (true) {
            if (*pointer==nullptr) {
              return false;
            }else if (search==(*pointer)->data) {
              return true;
            }else if ((*pointer)->next !=nullptr && cmp(search, (*pointer)->data)){
              pointer= &((*pointer)->next);
            }else if (cmp(search, (*pointer)->data)) {
              pointer = &((*pointer)->next);
              return false;
            }else return false;
          }
        };

        void insert(T data) {
          Node<T> **pos = &this->head;
          if (!this->find(data, pos)) {
            Node<T> *temp = new Node<T>(data);
            temp->next = *pos;
            *pos = temp;
            temp = nullptr;
            delete temp;
          }
          pos = nullptr;
          delete pos;
        };

        void remove(T item) {
          Node<T> **pos = &this->head;
          if (!this->find(item, pos)) {
            if (!this->head) {
              throw("empty list");
            }else throw("there isn't that element");
          }else{
            Node<T> *temp = *pos;
            *pos = (*pos)->next;
            delete temp;
          }
          pos = nullptr;
          delete pos;
        };

        iterator begin() {return iterator (this->head);};

        iterator end() {
          Node<T>* pos = this->head;
          while (pos->next!=nullptr) {
            pos = pos->next;
          }
          return iterator(pos);};

        ~SList() {
            if (head) {
                head->killSelf();
            }
        };
};

#endif
