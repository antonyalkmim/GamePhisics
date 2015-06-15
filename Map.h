#include "Avl.h"
#include "Element.h"

#ifndef MAP_H
#define MAP_H

class Map : public AVL<Element>
{
    private:
        int width;
        int height;

    public:
        Map(){
            this->Root = NULL;
        }

        Map(int w,int h){
            this->width = w;
            this->height = h;

            this->Root = NULL;
        }


        bool InsertElement(Element x){
            return this->Insert(x,&this->Root);
        }

        bool InsertPlayer(Player p,int x, int y){
            Element e;
            e.setPlayer(p);
            e.setX(x);
            e.setY(y);
            e.setType('P');

            return this->InsertElement(e);
        }
        bool InsertStone(Stone s, int x, int y){
            Element e;
            e.setStone(s);
            e.setX(x);
            e.setY(y);
            e.setType('S');

            return this->InsertElement(e);
        }

        void Delete(int pos, Element *x){
            DeleteAVL(pos,x,&Root);
        }

        bool Search(int pos, Element *x){
            return this->Search(pos,x,&Root);
        }

        /*
         *AVL::InOrder(NodeT *Raiz);
         *(*Raiz) : No raiz de uma arvore para poder percorrer
         *Percorre a Arvore in-order
         */
        void InOrder(NodeT<Element> *Raiz){
            if(Raiz){
                InOrder(Raiz->Left);
                cout << Raiz->A.getPosition(this->width) << Raiz->A.getType() << " ";
                InOrder(Raiz->Right);
            }
        }




        /*
         * Encapsulamentos
         */
        void setWidth(int w){
            this->width = w;
        }
        void setHeigh(int h){
            this->height = h;
        }
        int getWidth(){
            return this->width;
        }
        int getHeight(){
            return this->height;
        }


        static NodeT<Element> *Max(NodeT<Element> *Raiz){

            if(!Raiz->Right){
                return Raiz;
            }

            return Max(Raiz->Right);

        }
        
        void clear(){
            if(this->Root)
                iclear(&this->Root);
        }

    private:

        void iclear(NodeT<Element> **Raiz){

            if((*Raiz)){
                NodeT<Element> *P;

                iclear(&(*Raiz)->Left);
                iclear(&(*Raiz)->Right);

                P = *Raiz;
                *Raiz = NULL;
                NodeT<Element>::desmontaNo(P);
            }
        }

        /*
         *AVL::Insert(Dado x, NodeT **Raiz);
         *Dado x : Objeto do tipo dado que armazenaremos na arvore
         *NodeT **Raiz : Ponteiro que aponta para o Ponteiro Raiz da Arvore ou sub-arvore
         *Metodo para inserir um Dado na Arvore Binaria
         */
        bool Insert(Element x, NodeT<Element> **Raiz){

            if(!(*Raiz)){
                (*Raiz) = NodeT<Element>::montaNo(x);

                if(!(*Raiz))
                    return false;
                return true;
            }

            //verifica se a chave do dado e menor que a chave do NodeT Raiz
            if(x.getPosition(this->width) < (*Raiz)->A.getPosition(this->width)){
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

            if(x.getPosition(this->width) > (*Raiz)->A.getPosition(this->width)){
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


        bool DeleteAVL(int pos, Element *x, NodeT<Element> **Raiz){
            if(!(*Raiz))
                return false; //chave nao encontrada

            //cout << "chave da raiz: " << (*Raiz)->A.id << endl;
            if(pos < (*Raiz)->A.getPosition(this->width)){

                if(DeleteAVL(pos, x, &(*Raiz)->Left)){

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
            if(pos > (*Raiz)->A.getPosition(this->width)){
                if(DeleteAVL(pos, x, &(*Raiz)->Right)){

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

            NodeT<Element> *P = *Raiz;
            if(!(*Raiz)->Left){ //nao tem filho a esquerda
                *Raiz = (*Raiz)->Right;
                *x = NodeT<Element>::desmontaNo(P);
                return true;
            }

            if(!(*Raiz)->Right){ //tem filho somente a esquerda
                *Raiz = (*Raiz)->Left;
                *x = NodeT<Element>::desmontaNo(P);
                return true;
            }

            //tem 2 filhos
            NodeT<Element> *m = Map::Max((*Raiz)->Left);
            Element aux = m->A;
            m->A = (*Raiz)->A;
            (*Raiz)->A = aux;



            if(DeleteAVL(pos,x,&(*Raiz)->Left)){
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


        /*
         *AVL::Search(int key, Dado *x, NodeT **Raiz);
         *Busca um node com chave key na arvore com raiz (*Raiz)
         *e armazena em x
         */
        bool Search(int pos, Element *x, NodeT<Element> **Raiz){

            if(!(*Raiz))
                return false;

            if(pos < (*Raiz)->A.getPosition(this->width))
                return Search(pos, x, &(*Raiz)->Left);
            if(pos > (*Raiz)->A.getPosition(this->width))
                return Search(pos, x, &(*Raiz)->Right);


            //se chegar aqui e pq achou a chave que procura
            *x = (*Raiz)->A;
            return true;
        }


};

#endif // MAP_H
