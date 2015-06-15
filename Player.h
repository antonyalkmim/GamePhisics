

#ifndef PLAYER_H
#define PLAYER_H

class Player
{

    public:
        int HP; //Hp do jogador
        int Atk; //poder de ataque do jogador
        int x;
        int y;
        int id;

    public:
        Player(){}

        Player(int hp, int atk){
            //informacoes referentes ao jogador
            this->HP = hp;
            this->Atk = atk;
        }

        ~Player(){}


        /*
         * ENCAPSULAMENTOS
         */
        int getHp(){
            return this->HP;
        }
        int getAtk(){
            return this->Atk;
        }
        int getX(){
            return this->x;
        }
        int getY(){
            return this->y;
        }
        int getPosition(int widthMap){
            return (this->y * widthMap + this->x);
        }
        int getId(){
            return this->id;
        }

        void setHp(int hp){
            this->HP = hp;
        }
        void setAtk(int atk){
            this->Atk = atk;
        }
        void setX(int x){
            this->x = x;
        }
        void setY(int y){
            this->y = y;
        }
        void setId(int id){
            this->id = id;
        }



};

#endif // PLAYER_H
