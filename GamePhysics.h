#include "Map.h"
#include "Element.h"
#include "Player.h"
#include "Stone.h"
#include "Stack.h"
#include "Move.h"
#include "List.h"

#ifndef GAMEPHYSICS_H
#define GAMEPHYSICS_H

class GamePhysics{

    public:
        Map map;
        Stack<Move> moves;
        List<Player> players;

    public:
        GamePhysics(){

        }

        GamePhysics(int widthMap, int heightMap){
            this->map.setWidth(widthMap);
            this->map.setHeigh(heightMap);
        }


        void InOrder(){
            this->map.InOrder(this->map.getRoot());
            cout << endl;
        }


        //ler e executa as jogadas
        void run(){

            Player p;
            Element e;
            int aux,points;
            bool terminou = false;
            bool proximo = false;
            Move m;


            cout << "########################################" << endl;
            cout << "####   >>      NOVO JOGO!     <<   ####" << endl;
            cout << "########################################" << endl;


            this->InsertPlayerOnMap();

            this->getMoves(); //ler as jogadas e armazena na pilha de jogadas

            //pegar o primeiro jogador
            this->players.Iterator = this->players.begin();

            //executa as jogadas enquanto houver jogadas na pilha de execucao
            while(!this->moves.isEmpty()){

                //reseta os pontos de jogadas
                points = 5;

                //pega o jogador que deve fazer a jogada
                p = *this->players.getPosition();

                if(p.getHp() > 0){ //so ataca faz jogada se ele ainda estiver vivo
                    //procura o jogador no mapa
                    aux = Element::getPosition(p.getX(),p.getY(),this->map.getWidth());
                    this->map.Search(aux,&e);

                    proximo = false;
                    for(int i=0; i<5 && !terminou && !proximo; i++){

                        if(!this->moves.pop(&m)){
                            terminou = true;
                        }else{
                            //verifica se jogador pode fazer tal jogada
                            if(this->canMakeAction(m.getAction(),points)){

                                this->executeActionPlayer(m.getAction(),m.getDirection(),&e,&p);
                                *this->players.getPosition() = p; //salva as alteracoes do jogador na lista

                            }else{
                                proximo = true; //indica se o jogador acabou as jogadas ou pontos de jogadas
                                cout << "nao executou " << m.getAction() << m.direction << endl;
                                //this->moves.push(m); //retorna a jogada para o topo da pilha de execucao
                            }

                            points -= this->getPointsAction(m.getAction());

                            //cout << "pts: " << points << endl;
                        }

                    }

                    cout << "------------------------------------" << endl;


                }


                this->players.IteratorToNext(); //passa para o proximo jogador
            }

            cout << "########################################" << endl;
            cout << "#### >> TERMINOU CASO DE TESTE!  << ####" << endl;
            cout << "########################################" << endl;

            //mostra como ficou as posicoes no mapa
            cout << "Resultado do mapa final: " << endl;
            this->InOrder();
            cout << "----------------------------------------------" << endl;

            //lista o resultado final dos jogadores
            this->players.Iterator = this->players.begin();
            do{
                p = *this->players.getPosition();
                cout << "Jogador " << p.getId() << ": ";
                if(p.getHp() > 0){
                cout << "(" << p.getX() << "," << p.getY() << ") ";
                cout << "HP:" << p.getHp() << endl;
                }else{
                    cout << "MORTO" << endl;
                }
                this->players.IteratorToNext();
            }while(this->players.Iterator!=this->players.begin());


        }

        /*
         *Ler as jogadas e armazena na pilha de execucao
         */
        void getMoves(){

            Stack<Move> s_aux;
            Move aux;
            char action,direction;


            //ler as jogadas
            cin >> action;
            cin >> direction;
            while(action != 'F' && direction != '0'){
                aux.setAction(action);
                aux.setDirection(direction);

                s_aux.push(aux);

                cin >> action;
                cin >> direction;
            }

            //tira da pilha auxiliar e empilha na pilha de jogadas
            //pra poder colocar as entradas na ordem certa
            while(!s_aux.isEmpty()){
                s_aux.pop(&aux);
                this->moves.push(aux);
            }

        }


        /*
         * Encapsulamentos
         */
        void setWidthMap(int width){
            this->map.setWidth(width);
        }
        void setHeightMap(int height){
            this->map.setHeigh(height);
        }


        void InsertPlayer(Player p){
            players.Insert(p);
        }

        bool InsertStone(Stone s,int x, int y){
            return this->map.InsertStone(s,x,y);
        }

        bool InsertElement(Element e){
            return this->map.InsertElement(e);
        }

        bool DeleteElement(int pos,Element *e){
            this->map.Delete(pos,e);
        }

        bool InsertMove(Move a){
            return this->moves.push(a);
        }

        void reload(){
            this->players.clear();
            this->map.clear();
            this->moves.clear();
        }


    private:

        //ele recebe um Element por que as acoes podem influenciar na posicao do jogador
        void executeActionPlayer(char action, char direction,Element *p, Player *_player){

            switch(action){
                case 'M': //anda para a direction
                    this->movePlayer(direction,p,_player);
                    break;
                case 'A': //ataca na direction
                    this->attackPlayer(direction,p);
                    break;
                case 'C': //constroi um bloco na direction
                    this->buildBlockPlayer(direction,p);
                    break;
                case 'D': //destroi um bloco na direction
                    this->destroyBlockPlayer(direction,p);
                    break;

            }

        }

        /*
         * Metodo responsavel por mover o jogador para uma direcao indicada
         */
        void movePlayer(char direction , Element *p, Player *_player){

            int aux;
            Element e_aux;

            cout << p->getPlayer()->getId() << " Tentou mover para " << direction << ": ";

            switch(direction){

            case '6':
                if(p->getX()+1 < map.getWidth()){
                    aux = Element::getPosition(p->getX()+1,p->getY(),map.getWidth());
                    if(!map.Search(aux,&e_aux)){
                        map.Delete(p->getPosition(map.getWidth()),&e_aux); //remove do mapa
                        e_aux.setX(e_aux.getX()+1); //altera a posicao do elemento
                        e_aux.getPlayer()->setX(e_aux.getX()); //altera a posicao do jogador
                        map.InsertElement(e_aux); //insere o elemento na arvore em uma nova posicao

                        *_player = *e_aux.getPlayer(); //altera o jogador na lista de jogadores
                        *p = e_aux; //altera o jogador que esta fazendo as jogadas

                        cout << "MOVEU" << endl;
                    }else{
                        cout << "OBSTRUIDO POR PEDRA" << endl;
                    }
                }else{
                    cout << "OBSTRUIDO POR PAREDE" << endl;
                }
                break;
            case '2':
                if(p->getY()+1 < map.getHeight()){
                    aux = Element::getPosition(p->getX(),p->getY()+1,map.getWidth());
                    if(!map.Search(aux,&e_aux)){
                        map.Delete(p->getPosition(map.getWidth()),&e_aux);
                        e_aux.setY(e_aux.getY()+1);
                        e_aux.getPlayer()->setY(e_aux.getY());
                        map.InsertElement(e_aux);

                        *_player = *e_aux.getPlayer(); //altera o jogador na lista de jogadores
                        *p = e_aux; //altera o jogador que esta fazendo as jogadas

                        cout << "MOVEU" << endl;
                    }else{
                        cout << "OBSTRUIDO POR PEDRA" << endl;
                    }
                }else{
                    cout << "OBSTRUIDO POR PAREDE" << endl;
                }
                break;

            case '4':
                if(p->getX()-1 >= 0){
                    aux = Element::getPosition(p->getX()-1,p->getY(),map.getWidth());
                    if(!map.Search(aux,&e_aux)){
                        map.Delete(p->getPosition(map.getWidth()),&e_aux);
                        e_aux.setX(e_aux.getX()-1);
                        e_aux.getPlayer()->setX(e_aux.getX());
                        map.InsertPlayer(*e_aux.getPlayer(),e_aux.getX(),e_aux.getY());

                        *_player = *e_aux.getPlayer(); //altera o jogador na lista de jogadores
                        *p = e_aux; //altera o jogador que esta fazendo as jogadas

                        cout << "MOVEU" << endl;
                    }else{
                        cout << "OBSTRUIDO POR PEDRA" << endl;
                    }
                }else{
                    cout << "OBSTRUIDO POR PAREDE" << endl;
                }
                break;

            case '8':
                if(p->getY()-1 >= 0){
                    aux = Element::getPosition(p->getX(),p->getY()-1,map.getWidth());
                    if(!map.Search(aux,&e_aux)){
                        map.Delete(p->getPosition(map.getWidth()),&e_aux);
                        e_aux.setY(e_aux.getY()-1);
                        e_aux.getPlayer()->setY(e_aux.getY());
                        map.InsertElement(e_aux);

                        *_player = *e_aux.getPlayer(); //altera o jogador na lista de jogadores
                        *p = e_aux; //altera o jogador que esta fazendo as jogadas

                        cout << "MOVEU" << endl;
                    }else{
                        cout << "OBSTRUIDO POR PEDRA" << endl;
                    }
                }else{
                    cout << "OBSTRUIDO POR PAREDE" << endl;
                }
                break;

            }

        }

        /*
         *METODO RESPONSAVEL POR ATACAR OS JOGADORES
         */
        bool attackPlayer(char direction, Element *p){

            cout << p->getPlayer()->getId() << " Tentou atacar na " << direction << ": ";

            Element e_aux;
            int aux,position;

            switch(direction){

            case '6':
                position = p->getX() + 1;
                aux = Element::getPosition(position,p->getY(),map.getWidth());
                while(position < map.getWidth()){
                    if(map.Search(aux,&e_aux)){
                        if(e_aux.getType()=='P'){ //achou um elemento player q pode ser atacado

                            cout << "JOGADOR " << p->getPlayer()->getId() << " CAUSOU " << p->getPlayer()->getAtk() << " DE DANO AO ";
                            cout << "JOGADOR " << e_aux.getPlayer()->getId() << endl;

                            //executa as acoes de ataque

                            map.Delete(aux,&e_aux); //tira o jogador do mapa pra fazer as alteracoes nele

                            //tira do jogador encontrado a quantidade de poder do jogador atacante
                            aux = e_aux.getPlayer()->getHp() - p->getPlayer()->getAtk();
                            e_aux.getPlayer()->setHp(aux);



                            //caso o hp dele seja maior que zero ele volta para o mapa
                            //caso contrario ele morre e nao volta para o mapa
                            if(e_aux.getPlayer()->getHp() > 0){
                                map.InsertElement(e_aux);
                            }

                            //altera o jogador na lista de jogadores
                            this->players.Search(e_aux.getPosition(map.getWidth()),map.getWidth())->setHp(aux);

                        }else{
                            cout << "ATK BLOQUEADO POR PEDRA OU PAREDE" << endl;
                        }
                        break; //para a execucao pq achou um elemento bloqueando
                    }
                    position++; //passa para a proxima posicao
                    aux = Element::getPosition(position,p->getY(),map.getWidth()); //calcula proxima posicao no mapa

                }
                break;

            case '4':
                position = p->getX() - 1;
                aux = Element::getPosition(position,p->getY(),map.getWidth());
                while(position >= 0){
                    if(map.Search(aux,&e_aux)){
                        if(e_aux.getType()=='P'){

                            cout << "JOGADOR " << p->getPlayer()->getId() << " CAUSOU " << p->getPlayer()->getAtk() << " DE DANO AO ";
                            cout << "JOGADOR " << e_aux.getPlayer()->getId() << endl;

                            map.Delete(aux,&e_aux);
                            aux = e_aux.getPlayer()->getHp() - p->getPlayer()->getAtk();
                            e_aux.getPlayer()->setHp(aux);
                            if(e_aux.getPlayer()->getHp() > 0){
                                map.InsertElement(e_aux);
                                this->players.Search(e_aux.getPosition(map.getWidth()),map.getWidth())->setHp(aux);
                            }

                        }else{
                            cout << "ATK BLOQUEADO POR PEDRA OU PAREDE" << endl;
                        }
                        break;
                    }
                    position--;
                    aux = Element::getPosition(position,p->getY(),map.getWidth());

                }
                break;

            case '2':
                position = p->getY() + 1;
                aux = Element::getPosition(p->getX(),position,map.getWidth());
                while(position < map.getHeight()){
                    if(map.Search(aux,&e_aux)){
                        if(e_aux.getType()=='P'){

                            cout << "JOGADOR " << p->getPlayer()->getId() << " CAUSOU " << p->getPlayer()->getAtk() << " DE DANO AO ";
                            cout << "JOGADOR " << e_aux.getPlayer()->getId() << endl;

                            map.Delete(aux,&e_aux);
                            aux = e_aux.getPlayer()->getHp() - p->getPlayer()->getAtk();
                            e_aux.getPlayer()->setHp(aux);
                            if(e_aux.getPlayer()->getHp() > 0){
                                map.InsertElement(e_aux);
                                this->players.Search(e_aux.getPosition(map.getWidth()),map.getWidth())->setHp(aux);
                            }

                        }else{
                            cout << "ATK BLOQUEADO POR PEDRA OU PAREDE" << endl;
                        }
                        break;
                    }
                    position++;
                    aux = Element::getPosition(p->getX(),position,map.getWidth());

                }
                break;

            case '8':
                position = p->getY() - 1;
                aux = Element::getPosition(p->getX(),position,map.getWidth());
                while(position >= 0){
                    if(map.Search(aux,&e_aux)){
                        if(e_aux.getType()=='P'){
                            cout << "JOGADOR " << p->getPlayer()->getId() << " CAUSOU " << p->getPlayer()->getAtk() << " DE DANO AO ";
                            cout << "JOGADOR " << e_aux.getPlayer()->getId() << endl;

                            map.Delete(aux,&e_aux);
                            aux = e_aux.getPlayer()->getHp() - p->getPlayer()->getAtk();
                            e_aux.getPlayer()->setHp(aux);
                            if(e_aux.getPlayer()->getHp() > 0){
                                map.InsertElement(e_aux);
                                this->players.Search(e_aux.getPosition(map.getWidth()),map.getWidth())->setHp(aux);
                            }

                        }else{
                            cout << "ATK BLOQUEADO POR PEDRA OU PAREDE" << endl;
                        }
                        break;
                    }
                    position--;
                    aux = Element::getPosition(p->getX(),position,map.getWidth());

                }
                break;

            }

        }

        /*
         * Metodo responsavel por construir um bloco de pedra em uma direcao indicada
         */
        bool buildBlockPlayer(char direction, Element *p){

            cout << p->getPosition(map.getWidth()) << " Tentou construir pedra na " << direction << ": ";

            Element e_aux;
            int aux;

            switch(direction){
            case '6':
                if(p->getX()+1 < map.getWidth()){ //verifica se nao ultrapassa os limites do mapa
                    aux = Element::getPosition(p->getX()+1,p->getY(),map.getWidth());
                    if(!map.Search(aux,&e_aux)){ //verifica se a posicao indicada esta vazia
                        //insere uma pedra na direction indicada
                        Stone s;
                        this->map.InsertStone(s,p->getX()+1,p->getY());

                        cout << "CONSTRUIU" << endl;
                    }else{
                        cout << "NAO CONSTRIU/POSICAO OCUPADA" << endl;
                    }
                }else{
                    cout << "POSICAO INEXISTENTE" << endl;
                }
                break;
            case '2':
                if(p->getY()+1 < map.getHeight()){
                    aux = Element::getPosition(p->getX(),p->getY()+1,map.getWidth());
                    if(!map.Search(aux,&e_aux)){
                        //insere uma pedra na direction indicada
                        Stone s;
                        this->map.InsertStone(s,p->getX(),p->getY()+1);

                        cout << "CONSTRUIU" << endl;
                    }else{
                        cout << "NAO CONSTRIU/POSICAO OCUPADA" << endl;
                    }
                }else{
                    cout << "POSICAO INEXISTENTE" << endl;
                }
                break;

            case '4':
                if(p->getX()-1 >= 0){
                    aux = Element::getPosition(p->getX()-1,p->getY(),map.getWidth());
                    if(!map.Search(aux,&e_aux)){
                        //insere uma pedra na direction indicada
                        Stone s;
                        this->map.InsertStone(s,p->getX()-1,p->getY());

                        cout << "CONSTRUIU" << endl;
                    }else{
                        cout << "NAO CONSTRIU/POSICAO OCUPADA" << endl;
                    }
                }else{
                    cout << "POSICAO INEXISTENTE" << endl;
                }
                break;

            case '8':
                if(p->getY()-1 >= 0){
                    aux = Element::getPosition(p->getX(),p->getY()-1,map.getWidth());
                    if(!map.Search(aux,&e_aux)){
                        //insere uma pedra na direction indicada
                        Stone s;
                        this->map.InsertStone(s,p->getX(),p->getY()-1);

                        cout << "CONSTRUIU" << endl;
                    }else{
                        cout << "NAO CONSTRIU/POSICAO OCUPADA" << endl;
                    }
                }else{
                    cout << "POSICAO INEXISTENTE" << endl;
                }
                break;


            }

        }

        /*
         *Metodo resposavel por destruir bloco de pedra na direcao indicada
         */
        bool destroyBlockPlayer(char direction, Element *p){

            cout << p->getPlayer()->getId() << " Tentou destruir pedra na " << direction << ": ";

            Element e_aux;
            int aux;

            switch(direction){
            case '6':
                if(p->getX()+1 < map.getWidth()){ //verifica se nao ultrapassa os limites do mapa
                    aux = Element::getPosition(p->getX()+1,p->getY(),map.getWidth());
                    if(map.Search(aux,&e_aux) && e_aux.getType() == 'S'){ //verifica se a posicao indicada tem uma pedra
                        map.Delete(aux,&e_aux); //remove a pedra do mapa
                        cout << "DESTRUIU" << endl;
                    }else{
                        cout << "PEDRA INEXISTENTE" << endl;
                    }
                }
                break;
            case '2':
                if(p->getY()+1 < map.getHeight()){
                    aux = Element::getPosition(p->getX(),p->getY()+1,map.getWidth());
                    if(map.Search(aux,&e_aux) && e_aux.getType() == 'S'){
                        map.Delete(aux,&e_aux); //remove a pedra do mapa
                        cout << "DESTRUIU" << endl;
                    }else{
                        cout << "PEDRA INEXISTENTE" << endl;
                    }
                }
                break;

            case '4':
                if(p->getX()-1 >= 0){
                    aux = Element::getPosition(p->getX()-1,p->getY(),map.getWidth());
                    if(map.Search(aux,&e_aux) && e_aux.getType() == 'S'){
                        map.Delete(aux,&e_aux); //remove a pedra do mapa
                        cout << "DESTRUIU" << endl;
                    }else{
                        cout << "PEDRA INEXISTENTE" << endl;
                    }
                }
                break;

            case '8':
                if(p->getY()-1 >= 0){
                    aux = Element::getPosition(p->getX(),p->getY()-1,map.getWidth());
                    if(map.Search(aux,&e_aux) && e_aux.getType() == 'S'){
                        map.Delete(aux,&e_aux); //remove a pedra do mapa
                        cout << "DESTRUIU" << endl;
                    }else{
                        cout << "PEDRA INEXISTENTE" << endl;
                    }
                }
                break;


            }

        }


        int getPointsAction(char action){

            switch(action){
                case 'M': return 1; break;
                case 'A' : return 1; break;
                case 'D' : return 3; break;
                case 'C' : return 4; break;
            }

        }


        bool canMakeAction(char action, int points){

            if(points >= this->getPointsAction(action))
                return true;
            return false;

        }

        void InsertPlayerOnMap(){
            Player aux;

            this->players.Iterator = this->players.begin();
            do{
                aux = *this->players.getPosition();
                map.InsertPlayer(aux,aux.getX(),aux.getY());

                this->players.IteratorToNext();
            }while(this->players.Iterator!=this->players.begin());

        }




};


#endif // GAMEPHYSICS_H
