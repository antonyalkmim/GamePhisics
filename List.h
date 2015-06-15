#include <stdio.h>
#include "NodeQ.h"
#include <iostream>

using namespace std;

#ifndef LIST_H
#define LIST_H

template <class T>
class List{

    public:
        Node<T> *head;
        Node<T> *tail;
        Node<T> *Iterator;

        List(){
            head = NULL;
            Iterator = NULL;
        }


        bool Insert(T x){

            Node<T> *P = Node<T>::montaNo(x);
            if(!P) return false;

            //caso a lista estiver vazia ele insere no head
            if(!head)
            {
                head = P;
                head->next = head;
                head->prev = head;

                tail = head; //inicia o head e o tail na mesma posicao
                return true;
            }

            //insere sempre no tail
            P->prev = this->tail;
            P->next = this->head;
            this->head->prev = P;
            this->tail->next = P;
            tail = P;
            return true;

        }


        bool Delete(int pos, T *x,int widthMap)
        {
            Node<T> *P; //ponteiro para armazenar o endereco onde vamos remover
            //Node<T> *aux; //ponteiro para auxiliar na remocao do elemento no meio da lista

            //nao deleta nada caso a lista estiver vazia
            if(!head) return false;

            P = this->SearchI(pos,widthMap); //procura jogador

            //se a busca nos retornar null quer dizer que o elemento nao existe na lista
            if(!P) return false;

            if(P==head){

                if(P==tail){
                    tail = NULL;
                    head = NULL;
                }else{
                    head = head->next;
                    tail->next = head;
                }
            }else{
                if(P==tail){
                    tail = tail->prev;
                    head->prev = tail;
                }
            }

            if(P==Iterator)
                Iterator = Iterator->prev;

            P->next->prev = P->prev;
            P->prev->next = P->next;


            //tem que saber o porque isso daki esta fazendo travar o PC
            *x = Node<T>::desmontaNo(P);

            return true;
        }




        bool Search(int pos, T *x,int widthMap)
        {
            for(Node<T> *P = head; P != NULL; P = P->next){
                if(P->A.getPosition(widthMap) == pos){
                    *x = P->A;
                    return true;
                }
            }
            return false; //nao achou o elemento
        }


        void mostrar(){
            Node<T> *P = head;

            do{
                printf("%i\n",P->A.getIdPlayer());
                P = P->next;
            }while(P!=head);

        }

        void mostrar(bool DIREITA){
            Node<T> *P = head;
            if(P)
            {
                printf("%i\n", P->A.getIdPlayer()); //mostra o que esta no head
                if(DIREITA)
                {//imprima a lista andando para a esquerda
                    while(P->prev != head)
                    {
                        P = P->prev;
                        printf("%i\n", P->A.getIdPlayer());
                    }
                }
                else
                {
                    //imprime a lista andando para a direita
                    while(P->next != head)
                    {
                        P = P->next;
                        printf("%i\n", P->A.getIdPlayer());
                    }
                }
            }
        }

        //verifica se a lista esta vazia
        bool isEmpty(){
            return (head==NULL);
        }

        //retorna o dado contido na posicao em que o Iterator se encontra
        T *getPosition(){
            return &(Iterator->A);
        }

        //inicio da lista
        Node<T>* begin(){
            return head;
        }

        //final da lista
        Node<T>* end(){
            return tail;
        }

        //iterator vai para a proxima posicao
        bool IteratorToNext(){
            if(Iterator)
                Iterator = Iterator->next;
            return Iterator;
        }

        //iterator vai para a posicao anterior
        bool IteratorToBack(){
            if(Iterator)
                Iterator = Iterator->prev;
            return Iterator;
        }

        //consertar metodo
        void clear(){
            Node<T> *P = head;
            Node<T> *Q;


            this->Iterator = this->begin();
            do{
                this->DeleteIterator(new T);

                this->IteratorToNext();
            }while(head);

        }

        void listar(){

            this->Iterator = this->begin();
            do{
                cout << this->Iterator->A.getX() << "|" << Iterator->A.getY() << "|";
                cout << Iterator->A.getHp() << "|" << Iterator->A.getAtk() << endl;
                this->IteratorToNext();
            }while(this->Iterator!=this->begin());

            cout << endl;

        }

        T* Search(int pos,int widthMap){
            //procura o jogador na lista e retorna um ponteiro para player
            Node<T> *P = head;


            if(P->A.getPosition(widthMap) == pos)
                return &P->A;

            P = P->next;
            while(P->A.getPosition(widthMap) != pos && P->next != head)
                P = P->next;

            return  &P->A;

        }

    private:

        bool DeleteIterator(T *x){

            Node<T>* P = Iterator;

            if(!P)
                return false;

            if(P==head){
                if(P==tail){
                    tail = NULL;
                    head = NULL;
                }else{
                    head = head->next;
                    tail->next = head;
                }
            }else{
                if(P==tail){
                    tail = tail->prev;
                    head->prev = tail;
                }
            }

            P->next->prev = P->prev;
            P->prev->next = P->next;

            *x = Node<T>::desmontaNo(P);
            return true;

        }


        Node<T>* SearchI(int pos, int widthMap)
        {
            Node<T> *P = head;

            if(P->A.getPosition(widthMap) == pos)
                return P;

            P = P->next;
            while(P->A.getPosition(widthMap) != pos && P->next != head)
                P = P->next;

            return P;
        }


};

#endif // LIST_H
