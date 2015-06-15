#include "NodeT.h"
#include "Player.h"
#include "Stone.h"

#ifndef ELEMENT_H
#define ELEMENT_H

class Element
{

    protected:
        int posX;
        int posY;
        char type; //S = Stone| P = Player

    public:
        Player player;
        Stone stone;

    public:
        Element(){

        }

        Element(int xInit,int yInit, char type){
            this->posX = xInit;
            this->posY = yInit;
            this->type = type;
        }

        ~Element(){

        }


        static int getPosition(int x,int y, int widthMap){
            return (y * widthMap + x);
        }

        /*
         * ENCAPSULAMENTOS
         */
        void setX(int x){
            this->posX = x;
        }
        void setY(int y){
            this->posY = y;
        }
        void setType(char type){
            this->type = type;
        }
        void setPlayer(Player p){
            this->type = 'P';
            this->player = p;
        }
        void setStone(Stone s){
            this->type = 'S';
            this->stone = s;
        }



        int getX(){
            return this->posX;
        }
        int getY(){
            return this->posY;
        }

        //retorna uma constante referente a posicao na matriz
        int getPosition(int width){
            return (this->posY * width + this->posX);
        }

        char getType(){
            return this->type;
        }

        Player *getPlayer(){
            return &this->player;
        }
        Stone *getStone(){
            return &this->stone;
        }



};

#endif // ELEMENTO_H
