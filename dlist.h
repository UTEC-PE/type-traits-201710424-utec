#ifndef DLIST_H
#define DLIST_H

#include "iterator.h"

template <typename T>
class DListIterator : public Iterator<T> {
    public:
        DListIterator() : Iterator<T>() {};
        DListIterator(Node<T> *current) : Iterator<T>(current) {};
        DListIterator<T> operator++(){
          if (this->current) {
            this->current = this->current->next;
            return *this;
          }else throw("iterator point nothing");
        };
        DListIterator<T> operator--(){
          if (this->current) {
            this->current = this->current->prev;
            return *this;
          }else throw("iterator point nothing");
        };
};

template <typename Tr>
class DList {
    public:
        typedef typename Tr::T T;
        typedef DListIterator<T> iterator;

    private:
        Node<T>* head;
        Node<T>* tail;

    public:
        DList() {
            head = tail = nullptr;
        };

        void push_front(T data) {
          Node<T> *temp = new Node<T>{data};
          temp->prev = nullptr;
          temp->next = this->head;
          if(this->head==nullptr){
            this->tail = temp;
          }else{
            this->head->prev = temp;
          }
          this->head = temp;
          temp = nullptr;
          delete temp;
        };

        void push_back(T data) {
          Node<T> *temp = new Node<T>{data};
          temp->next = nullptr;
          temp->prev = this->tail;
          this->tail = temp;
          if (head==nullptr) {
            this->head = temp;
          }else{
            this->tail->prev->next = temp;
          }
          temp = nullptr;
          delete temp;
        };

        void pop_front() {
          if (!this->head) {
            throw("empty list");
          }else if(this->head==this->tail){
            delete this->head;
            this->head=nullptr;
            this->tail=nullptr;
          }else{
            this->head=this->head->next;
            delete this->head->prev;
            this->head->prev=nullptr;
          }
        };

        void pop_back() {
          if (this->head==nullptr) {
            throw("empty list");
          }else if (this->head==this->tail) {
            delete this->head;
            this->head=nullptr;
            this->tail=nullptr;
          }else{
            this->tail=this->tail->prev;
            delete this->tail->next;
            this->tail->next=nullptr;
          }
        }

        iterator begin() {return DListIterator<T> (this->head);};

        iterator end() {return DListIterator<T> (this->tail);};

        ~DList() {
            if (head) {
                head->killSelf();
            }
        }
};

#endif
