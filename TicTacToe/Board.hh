#ifndef BOARD_HH
#define BOARD_HH
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class Board
 {
 private:
    int field_size = 0; //zmienna ktora przyjmuje wartosc wielkosci pola
    int field_data = 0;   // zmienna pomocnica w obliczeniu wielkosci pola
    int beat_number = 0;     // zmienna ktora przyjmuje ilosc figur w rzedzie do zbicia
    int beat_data = 0;    // pomocnicza to wyznaczenia ilosci bic
    int mouse_click = 0;   //pomocnica zwiazana z myszka
    
    public:
    void Reset_All();
    void Exit(RenderWindow &Aplication_window);
    void Start_Menu(RenderWindow &Aplication_window);
    void Beat_Field(RenderWindow &Aplication_window);
    void Menu(RenderWindow &Aplication_window);
    void Field_Field(RenderWindow &Aplication_window);
    void Game_Begin(RenderWindow &Aplication_window, int &transition);
    int get_field_size();
    int get_beat_number();
    void End_Menu(RenderWindow &Aplication_window, int player, int computer);
    bool Rematch(RenderWindow &Alication_window);
    bool Game_Exit(RenderWindow &Aplication_window);


    
 };

 #endif
