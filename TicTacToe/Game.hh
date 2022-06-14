#ifndef GAME_HH
#define GAME_HH
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

static unsigned int LENGHT = 600;
static unsigned int WIDTH = 600;



class Game
 {  
 private:
     int field_size;
     int beat_number;
     int array[15][15];
     int player_move = 1;
     int computer_move = 0 ;
     int move_number = 0;
     int player_wins = 0;
     int computer_wins = 0;

 public:
     Game();
     void Reset_All();
     void Exit(RenderWindow &Aplication_window);
     void Board(RenderWindow &Aplication_window, int field, int beat);
     void Assignment(int field, int beat );
     void Line_Render(RenderWindow &Aplication_window);
     void Sign_Insert(RenderWindow &Aplication_window);
     void Computer_Sign_Insert(RenderWindow &Aplication_window);
     int Winner_Check();
     bool Tie();
     void Find_Best_Move(int array[15][15], int &x, int &y);
     int miniMax(int array[15][15], int depth , bool player , int alfa , int beta);
     int maxx(int a,int b);
     int minx(int a, int b);
     void Game_End(RenderWindow &Aplication_window, int &transition);
     int get_player_win();
     int get_computer_win();
     
    
   

    
 };

 #endif


