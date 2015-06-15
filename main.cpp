#include <iostream>
#include "GamePhysics.h"
#include "Element.h"
#include "Stone.h"
#include "Player.h"
#include "Move.h"

using namespace std;

int main()
{
    GamePhysics game;
    int nr_player;
    Player p_aux;
    Stone s_aux;

    cin >> nr_player; //le o numero de jogadores
    while(nr_player>0){

        int aux,aux2;

        //RESETA O JOGO
        game.reload();

        //le as informacoes dos jogadores
        for(int i=0,aux=0; i<nr_player; i++){

            cin >> aux; //posX
            p_aux.setX(aux);

            cin >> aux; //posY
            p_aux.setY(aux);

            cin >> aux; //HP
            p_aux.setHp(aux); //seta o HP

            cin >> aux;//atk
            p_aux.setAtk(aux);//seta o poder de atk


            p_aux.setId(i+1);
            game.InsertPlayer(p_aux);
        }


        //le as dimensoes do mapa
        cin >> aux; //xMap
        game.setWidthMap(aux); //verificar pq no arquivo diz q tem q ser coluna-1
        cin >> aux; //yMap
        game.setHeightMap(aux);//verificar pq no arquivo diz que tem q ser linha-1


        //le as pedras do mapa
        cin >> aux; //x da pedra
        cin >> aux2; //y da pedra

        while(aux >= 0 && aux2 >= 0){
            game.InsertStone(s_aux,aux,aux2);
            cin >> aux; //x da pedra
            cin >> aux2; //y da pedra

        }



        //ler e fazer as jogadas
        game.run(); //ler e executar as jogadas
        cout << "----------------------------------------------" << endl << endl << endl;


        //######################################################################
        cin >> nr_player; //le o numero de jogadores da proxima partida
    }


}

