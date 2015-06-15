#include "NodeT.h"
#include <iostream>

using namespace std;

#ifndef AVL_H
#define AVL_H

template<class myType>
class AVL{
    public:
        NodeT<myType> *Root;

    public:
        AVL(){
            Root = NULL;
        }

        /*
         * Retorna um apontador para a raiz da arvore
         */
        NodeT<myType> *getRoot(){
            return Root;
        }

        /*
         * Metodo para insercao de Nodes na arvore
         * => Chama o Metodo Insert que insere recursivamente na arvore
         * Dado x => Dado para ser inserido na arvore
         */
        bool Insert(myType x){
           return this->Insert(x,&this->Root);
        }

        /*
         *AVL::Height(NodeT *Raiz);
         *NodeT *Raiz : Nó raiz na qual comeca a contagem da altura da arvore
         */
        int Height(NodeT<myType> *Raiz){

             int altE, altD;

             NodeT<myType> *q, *temp;
             if (!(Raiz))
                 return 0;
             else
             {
                 altE = Height((Raiz)->Left);
                 altD = Height((Raiz)->Right);

                 if (altE < altD)
                    return altD + 1;
                 else
                    return altE + 1;
             }

        }


        /*
         *R.D.D. : ROTACAO DUPLA PARA DIREITA
         *AVL::RDD(NodeT **Raiz);
         *NodeT **Raiz: NodeT para se aplicar a Rotacao
         *Efetua a rotacao dupla para Direita em um determinado NodeT **Raiz
         */
        void RDD(NodeT<myType> **Raiz){
            NodeT<myType> *b,*c;

            b = (*Raiz)->Left;
            c = b->Right;

            //rotaciona
            (*Raiz)->Left = c->Right;
            b->Right = c->Left;
            c->Right = (*Raiz);
            c->Left = b;

            //cout << "ROTACAO DUPLA DIREITA" << endl;

            //atualiza o fator de balanceamento
            if(c->FB == 1){
                (*Raiz)->FB = 0;
                b->FB = -1;
            }else{
                if(c->FB == 0){
                    (*Raiz)->FB = 0;
                    b->FB = 0;
                }else{
                    (*Raiz)->FB = 1;
                    b->FB = 0;
                }
            }
            c->FB = 0;
            (*Raiz) = c;

        }

        /*
         *R.D.E. : ROTACAO DUPLA PARA ESQUERDA
         *AVL::RDE(NodeT **Raiz);
         *NodeT **Raiz: NodeT para se aplicar a Rotacao
         *Efetua a rotacao dupla para Esquerda em um determinado NodeT **Raiz
         */
        void RDE(NodeT<myType> **Raiz){
            NodeT<myType> *b,*c;

            b = (*Raiz)->Right;
            c = b->Left;

            //cout << "ROTACAO DUPLA ESQUERDA" << endl;

            //rotaciona
            (*Raiz)->Right = c->Left;
            b->Left = c->Right;
            c->Left = (*Raiz);
            c->Right = b;

            //atualiza o fator de balanceamento
            if(c->FB == 1){
                (*Raiz)->FB = -1;
                b->FB = 0;
            }else{
                if(c->FB == 0){
                    (*Raiz)->FB = 0;
                    b->FB = 0;
                }else{
                    (*Raiz)->FB = 0;
                    b->FB = 1;
                }
            }
            c->FB = 0;
            (*Raiz) = c;
        }

        /*
         *R.S.E. : ROTACAO SIMPLES PARA ESQUERDA
         *AVL::RSE(NodeT **Raiz);
         *NodeT **Raiz: NodeT para se aplicar a Rotacao
         *Efetua a rotacao simples para esquerda em um determinado NodeT **Raiz
         */
        void RSE(NodeT<myType> **Raiz){
            NodeT<myType> *b = (*Raiz)->Right;
            (*Raiz)->Right = b->Left;
            b->Left = (*Raiz);

            //cout << "Entrou na rotacao pra esquerda" << endl;

            //atualiza fator de balanceamento
            if(b->FB == 1){
                b->FB = 0;
                (*Raiz)->FB = 0;
            }else{
                b->FB = -1;
                (*Raiz)->FB = 1;
            }

            (*Raiz) = b;
        }

        /*
         *R.S.D. : ROTACAO SIMPLES PARA DIREITA
         *AVL::RDD(NodeT **Raiz);
         *NodeT **Raiz: NodeT para se aplicar a Rotacao
         *Efetua a rotacao Simples para Direita em um determinado NodeT **Raiz
         */
        void RSD(NodeT<myType> **Raiz){
            NodeT<myType> *b = (*Raiz)->Left;
            (*Raiz)->Left = b->Right;
            b->Right = (*Raiz);


            //atualiza o fator de balanceamento
            if(b->FB == -1){
                b->FB = 0;
                (*Raiz)->FB = 0;
            }else{
                b->FB = 1;
                (*Raiz)->FB = -1;
            }
            (*Raiz) = b;
        }

        /*
         *AVL::Max(NodeT *Raiz);
         *NodeT *Raiz : Informa o NodeT Raiz de uma arvore
         *Busca o NodeT com a maior chave na arvore de Raiz = *Raiz
         */
        static NodeT<myType> *Max(NodeT<myType> *Raiz){

            if(!Raiz->Right){
                return Raiz;
            }

            return Max(Raiz->Right);

        }

        /*
         *AVL::Min(NodeT *Raiz);
         *NodeT *Raiz : Informa o NodeT Raiz de uma arvore
         *Busca o NodeT com a menor chave na arvore de Raiz = *Raiz
         */
        static NodeT<myType> *Min(NodeT<myType> *Raiz){

            if(!Raiz->Left){
                return Raiz;
            }

            return Min(Raiz->Left);

        }

        /*
         *AVL::InOrder(NodeT *Raiz);
         *(*Raiz) : No raiz de uma arvore para poder percorrer
         *Percorre a Arvore in-order
         */
        static void InOrder(NodeT<myType> *Raiz){
            if(Raiz){
                InOrder(Raiz->Left);
                cout << Raiz->A.getX() << " ";
                InOrder(Raiz->Right);
            }
        }

        /*
         *AVL::PreOrder(NodeT *Raiz);
         *(*Raiz) : No raiz de uma arvore para poder percorrer
         *Percorre a Arvore pre-order
         */
        static void PreOrder(NodeT<myType> *Raiz){
            if(Raiz){
                cout << Raiz->A.id << " ";
                PreOrder(Raiz->Left);
                PreOrder(Raiz->Right);
            }
        }

        /*
         *AVL::PosOrder(NodeT *Raiz);
         *(*Raiz) : No raiz de uma arvore para poder percorrer
         *Percorre a Arvore pos-order
         */
        static void PosOrder(NodeT<myType> *Raiz){
            if(Raiz){
                PosOrder(Raiz->Left);
                PosOrder(Raiz->Right);
                cout << Raiz->A.id << " ";
            }
        }


        /*
         *AVL::Search(int key, Dado *x, NodeT **Raiz);
         *Busca um node com chave key na arvore com raiz (*Raiz)
         *e armazena em x
         */
        bool Search(int key, myType *x, NodeT<myType> **Raiz){

            if(!(*Raiz))
                return false;

            if(key < (*Raiz)->A.id)
                return Search(key, x, &(*Raiz)->Left);
            if(key > (*Raiz)->A.id)
                return Search(key, x, &(*Raiz)->Right);


            //se chegar aqui e pq achou a chave que procura
            *x = (*Raiz)->A;
            return true;
        }


        void Delete(int pos,int widthMap, myType *x){
            DeleteAVL(pos,widthMap,x,&Root);
        }





    protected:
        /*
         *AVL::Insert(Dado x, NodeT **Raiz);
         *Dado x : Objeto do tipo dado que armazenaremos na arvore
         *NodeT **Raiz : Ponteiro que aponta para o Ponteiro Raiz da Arvore ou sub-arvore
         *Metodo para inserir um Dado na Arvore Binaria
         */
        bool Insert(myType x, NodeT<myType> **Raiz){

            if(!(*Raiz)){
                (*Raiz) = NodeT<myType>::montaNo(x);

                if(!(*Raiz))
                    return false;
                return true;
            }

            //verifica se a chave do dado e menor que a chave do NodeT Raiz
            if(x.id < (*Raiz)->A.id){
                 if(Insert(x, &(*Raiz)->Left)){

                     if((*Raiz)->FB == 1){
                        (*Raiz)->FB = 0;
                         return false;
                     }

                     if((*Raiz)->FB == 0){
                         (*Raiz)->FB = -1;
                         return true;
                     }


                     if((*Raiz)->Left->FB != 1){
                         RSD(Raiz);
                     }else{
                         RDD(Raiz);
                     }

                     return false;
                }
                return false;
            }

            if(x.id > (*Raiz)->A.id){
                 if(Insert(x, &(*Raiz)->Right)){

                     if((*Raiz)->FB == -1){
                        (*Raiz)->FB = 0;
                         return false;
                     }

                     if((*Raiz)->FB == 0){
                         (*Raiz)->FB = 1;
                         return true;
                     }


                     if((*Raiz)->Right->FB != -1){
                         RSE(Raiz);
                     }else{
                         RDE(Raiz);
                     }

                     return false;
                }
                return false;
            }


            return false; //deu erro na insercao
        }



        bool DeleteAVL(int key, myType *x, NodeT<myType> **Raiz){
            if(!(*Raiz))
                return false; //chave nao encontrada

            //cout << "chave da raiz: " << (*Raiz)->A.id << endl;
            if(key < (*Raiz)->A.id){

                if(DeleteAVL(key, x, &(*Raiz)->Left)){

                    if((*Raiz)->FB == -1){
                        (*Raiz)->FB = 0;
                        return true;
                    }
                    if((*Raiz)->FB == 0){
                        (*Raiz)->FB = 1;
                        return false;
                    }

                    //so pode ser +1
                    if((*Raiz)->Right->FB != 1){
                        RDE(Raiz);
                        (*Raiz)->FB = 0;
                    }else{
                        RSE(Raiz);
                    }
                    return true;
                }
                return false;
            }
            if(key > (*Raiz)->A.id){
                if(DeleteAVL(key, x, &(*Raiz)->Right)){

                    if((*Raiz)->FB == 1){
                        (*Raiz)->FB = 0;
                        return true;
                    }

                    if((*Raiz)->FB == 0){
                        (*Raiz)->FB = -1;
                        return false;
                    }

                    //so pode ser -1
                    if((*Raiz)->Left->FB != -1){
                        RDD(Raiz);
                    }else{
                        RSD(Raiz);
                    }
                    return true;

                }
                return false;
            }

            NodeT<myType> *P = *Raiz;
            if(!(*Raiz)->Left){ //nao tem filho a esquerda
                *Raiz = (*Raiz)->Right;
                *x = NodeT<myType>::desmontaNo(P);
                return true;
            }

            if(!(*Raiz)->Right){ //tem filho somente a esquerda
                *Raiz = (*Raiz)->Left;
                *x = NodeT<myType>::desmontaNo(P);
                return true;
            }

            //tem 2 filhos
            NodeT<myType> *m = AVL<myType>::Max((*Raiz)->Left);
            myType aux = m->A;
            m->A = (*Raiz)->A;
            (*Raiz)->A = aux;



            if(DeleteAVL(key,x,&(*Raiz)->Left)){
                if((*Raiz)->FB == -1){
                    (*Raiz)->FB = 0;
                    return true;
                }
                if((*Raiz)->FB == 0){
                    (*Raiz)->FB = 1;
                    return false;
                }
                //so pode ser +1
                if((*Raiz)->Right->FB != 1){
                    RDE(Raiz);
                }else{
                    RSE(Raiz);
                }
                return true;
            }


        }


};

#endif // AVL_H
