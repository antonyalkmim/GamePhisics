#ifndef MOVE_H
#define MOVE_H

class Move{

    public:
        char action;
        char direction;


    public:
        Move(){}

        Move(char a, char d){
            this->action = a;
            this->direction = d;
        }



        /*
         *Encapsulamentos
         */
        void setAction(char a){
            this->action = a;
        }
        void setDirection(char d){
            this->direction = d;
        }


        char getAction(){
            return this->action;
        }
        char getDirection(){
            return this->direction;
        }



};

#endif // MOVE_H
