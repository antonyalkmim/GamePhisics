#include <iostream>
#include "NodeQ.h"

using namespace std;

#ifndef STACK_H
#define STACK_H

#include <stdio.h>

template <class T>
class Stack
{
    public:
        Node<T> *top;

    public:
        Stack()
        {
            top = NULL;
        }

        bool push(T A)
        {
            Node<T> *p = Node<T>::montaNo(A);

            if(!p)
                return p;

            p->next = top;
            top=p;

            return true;
        }

        bool pop(T *A)
        {
            if(!top)
                return false;

            Node<T> *p = top->next;
            *A = Node<T>::desmontaNo(top);

            top = p;
            return true;
        }


        bool isEmpty(){
            return (top == NULL);
        }

        void listar(){
            Node<T> *P = this->top;
            while(P){
                printf("%c%c ",P->A.getAction(),P->A.getDirection());
                P = P->next;
            }
        }

        void clear(){
            Node<T> *p;

            while(top){
                p = top->next;
                Node<T>::desmontaNo(top);
                top = p;
            }

            top = NULL;
        }





};

#endif // STACK_H
