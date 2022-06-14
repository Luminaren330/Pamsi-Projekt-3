#include "Board.hh"
#include "Game.hh"

using namespace std;
using namespace sf;


 int main()
 {

    Board board;
    Game game;
    int transition = 0;

    RenderWindow Aplication_window(VideoMode(WIDTH, LENGHT ), "Kolko i  Krzyzyk" );
    
    while(Aplication_window.isOpen()) {
        if(transition == 0) {
            board.Exit(Aplication_window);
            board.Start_Menu(Aplication_window);
            board.Game_Begin(Aplication_window, transition);
        }
        else if(transition == 1) {
            game.Exit(Aplication_window);
            game.Board(Aplication_window, board.get_field_size(), board.get_beat_number());
            game.Game_End(Aplication_window, transition);
        }
        else if (transition == 2) {
            board.Exit(Aplication_window);
            board.End_Menu(Aplication_window, game.get_player_win(), game.get_computer_win());
            if(board.Rematch(Aplication_window)) {
                game.Reset_All();
                board.Reset_All();
                transition = 0;
            }
            if(board.Game_Exit(Aplication_window)) {
                break;
            }
        }
    }
 }
 
 
