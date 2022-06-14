#include "Game.hh"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;


Game::Game() // funkcja wypełniająca tablice 0
{
    for(int i = 0; i < 15; i++) {
        for (int k = 0; k < 15; k++) {
            array[i][k] = 0;
        }
    }
}

int Game::get_player_win() // zwraca wygraną człowieka
{
    return player_wins;
}

int Game::get_computer_win() // zwraca wygraną komputera
{
    return computer_wins;
}


void Game::Reset_All() // zeruje wszystkie wartości do parametrów początkowych
{
    for(int i = 0; i < 15; i++) {
        for (int k = 0; k < 15; k++) {
            array[i][k] = 0;
        }
    }
    player_move = 1;
    computer_move = 0 ;
    move_number = 0;
    player_wins = 0;
    computer_wins = 0;
}


void Game::Exit(RenderWindow &Aplication_window) // funckja, która pozwala na wyjście z gry i okna aplikacji (podczas gry)
{
    Event event;
    while(Aplication_window.pollEvent(event)) {
      if(event.type == Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)))
      Aplication_window.close(); //  jeśli wciśnięty jest przycisk esc lub ikonka x, wychodzi z aplikacji
    }
}

void Game::Assignment(int field, int beat) // przypisuje wielkości
{
    field_size = field;
    beat_number = beat;
}

void Game::Line_Render(RenderWindow &Aplication_window) // funkcja ryusująca linie pola gry // może coś zmienić potem
{
    RectangleShape vertical_line;
    RectangleShape horizontal_line;
    Font font;
    font.loadFromFile( "arial.ttf" );

    vertical_line.setSize(sf::Vector2f(0, 600)); // odpowiednie parametry liń
    vertical_line.setOutlineColor(sf::Color::Black);
    vertical_line.setOutlineThickness(1);

    horizontal_line.setSize(sf::Vector2f(600, 0));
    horizontal_line.setOutlineColor(sf::Color::Black);
    horizontal_line.setOutlineThickness(1);



    for(int i = 1; i <= field_size - 1; i++) // w zależności od ilości gry np. 3x3 lub 5x5
    {
        int variable = LENGHT / field_size;
        vertical_line.setPosition(i * variable, 0);
        Aplication_window.draw(vertical_line);
                                                            // rysuje odpowiednią ilość liń
        horizontal_line.setPosition(0, i * variable);
        Aplication_window.draw(horizontal_line);

    }


}

void Game::Sign_Insert(RenderWindow &Aplication_window) // funkcja, która wczytuje wstawiane znaki przez gracza
{
    float Mx = Mouse::getPosition(Aplication_window).x;
    float My = Mouse::getPosition(Aplication_window).y;
    Font font;
    font.loadFromFile( "arial.ttf" );



    if(player_move == 1) { // jeśli w opdowiednie miejsce klikniemy
        for (int i = 0; i < field_size; i++) {
            if ((Mx > i * (LENGHT / field_size) && Mx < i * (LENGHT / field_size) + LENGHT / field_size)) {
                for (int k = 0; k < field_size; k++) {
                    if ((My > k * (WIDTH / field_size) && My < k * (WIDTH / field_size) + WIDTH / field_size)) {
                        if (Mouse::isButtonPressed(Mouse::Left)) {
                            if (array[i][k] == 0) {
                                array[i][k] = -1;
                                player_move = 0; // koniec tury gracza
                                computer_move = 1; // początek tury komputera
                                move_number++;
                            }

                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < field_size; i++) { // to wstawi w to miejsce znak
        for (int k = 0; k < field_size; k++) {
            if (array[i][k] == -1) {
                Text symbol("X", font, LENGHT / field_size);
                symbol.setPosition(i * (LENGHT / field_size)+20, k * (WIDTH / field_size));  // wstawianie w odpowiednim rozmieszczeniu
                symbol.setColor(sf::Color::Blue);
                Aplication_window.draw(symbol);
            }
        }
    }
}

void Game::Find_Best_Move(int array[15][15], int &x, int &y) // funkcja odpowiadająca za znalezienie najlepszego ruchu
{
	int best = -1000;
	int alpha = -1000;
	int beta = 1000;
    for(int i = 0; i < field_size; i++) {
        for (int k = 0; k < field_size; k++) {
            if (array[i][k] == 0) {
                array[i][k] = 1;
                int move = miniMax(array, 0, false, alpha, beta); // wywołanie algorytmu minimax
                array[i][k] = 0;
                if (move > best) { // jeśli ruch jest większy niż best to przyjmuje odpowiednie współrzędne
                    x = i;
                    y = k;
                    best = move;
                }

            }
        }
    }
}

int Game::miniMax(int array[15][15], int depth, bool player, int alpha, int beta) // algorytm minimax
{

    int score = Winner_Check(); // sprawdzanie kto wygrał i zwrócenie wartości

    if(score == 10) {
		return score - depth;
	}
	if(score == -10) {
		return score + depth;
	}
	if(Tie() || depth==8) { // jeśli głębokość przekroczy daną wartośc to zwraca 0 - skrócenie czasu działania algorytmu
		return 0;
	}

    	if(player) { // jeśli tura gracza
		int best = -1000;
		for(int i = 0; i < field_size; i++){
			for(int j = 0; j < field_size; j++) {
				if(array[i][j] == 0) {
                    array[i][j] = 1;
					int val = miniMax(array, depth + 1 , false, alpha, beta); // funckja rekurencyjna
                    best = maxx(best, val);
					alpha = maxx(best, alpha);
                    array[i][j] = 0;
					if(beta <= alpha) {
                        break;
                    }
				}
				if(beta <= alpha) {
                    break;
                }
			}
		}
		return best; // zwraca najlepszy ruch
	}if(!player){ // jeśli tura komputera
		int best = 1000;
		for(int i = 0; i < field_size; i++) {
			for(int j = 0; j < field_size; j++) {
				if(array[i][j] == 0) {
                    array[i][j] = -1;
					int val = miniMax(array, depth + 1 , true, alpha, beta);  // funckja rekurencyjna
                    best = minx(best, val);
					beta = minx(best, beta);
                    array[i][j] = 0;
					if(beta <= alpha) {
                        break;
                    }
				}
				if(beta <= alpha)
					break;
			}
		}
		return best; // zwraca najlepszy ruch
	}
}


void Game::Computer_Sign_Insert(RenderWindow &Aplication_window) // funkcja, która pozwala na wstawianie znaków przez komputer
{

    Font font;
    font.loadFromFile( "arial.ttf");
    int x,y;

    if(computer_move == 1) {
        
        cout<<"Tura Komputera" <<endl; // pokazuje odpowiednie komunikaty w terminalu

        Find_Best_Move(array, x, y);

        cout<<"Twoja kolej" <<endl;

        array[x][y] = 1;
        player_move = 1;
        computer_move = 0;
        move_number++;

    }
        for(int i = 0; i < field_size; i++) {
            for (int k = 0; k < field_size; k++) {
                if (array[i][k] == 1) {
                    Text text1("O", font, LENGHT / field_size); // wstawianie znaku 0 przez komputer
                    text1.setPosition(i * (LENGHT / field_size) + 10, k * (WIDTH / field_size));
                    text1.setColor(sf::Color::Red);
                    Aplication_window.draw(text1);
                }
            }
        }
}

bool Game::Tie() // funkcja, która sprawdza czy jest remis
{
    for(int i = 0; i < field_size; i++) {
        for (int k = 0; k < field_size; k++) {
            if (array[i][k] == 0)
                return false;
        }
    }
    return true;

}

int Game::Winner_Check() // funkcja, która sprawdza kto wygrał
{

    for (int i = 0; i < field_size; i++) {
                                                // dla gracza
        for (int k = 0; k < field_size; k++) { // sprawdza czy w poziomie jest wygrana

            for (int l = 0; l < beat_number; l++) {

                if (array[i + l][k] == -1) {

                    if (l == beat_number - 1) {
                        return -10;
                    }
            }
                else {
                    break;
                }

        }

        for (int l = 0; l < beat_number; l++) {
            if (array[i][k + l] == -1) { // sprawdza czy w pionie jest wygrana
                if (l == beat_number - 1) {
                    return -10;
                    }
            }
            else {
                break;
            }


        }

        for (int l = 0; l < beat_number; l++) {
            if (array[i + l][k + l] == -1) { // sprawdza czy na jednym skosie jest wygrana
                if (l == beat_number - 1) {
                    return -10;
                }
            }
            else {
                break;
            }
        }


        for (int l = 0; l < beat_number; l++) {
            if (array[i + l][k - l] == -1) { //sprawdza czy na drugim skosie jest wygrana
                if (l == beat_number - 1) {
                    return -10;
                }
            }
            else {
                break;
            }
        }
                                        // dla komputera
        for (int l = 0; l < beat_number; l++) {
            if (array[i + l][k] == 1) { // sprawdza czy w poziomie jest wygrana

                if (l == beat_number - 1) {
                    return 10;
                }
            }
            else {
                break;
            }

        }

        for (int l = 0; l < beat_number; l++) {
            if (array[i][k + l] == 1) { // sprawdza czy w pionie jest wygrana
                if (l == beat_number - 1) {
                    return 10;
                }
            }
            else {
                break;
            }


        }

        for (int l = 0; l < beat_number; l++) { // sprawdza czy na jednym skosie jest wygrana
            if (array[i + l][k + l] == 1) {
                if (l == beat_number - 1)
                    return 10;
            } else {
                break;
            }
        }

        for (int l = 0; l < beat_number; l++) { // sprawdza czy na drugim skosie jest wygrana
            if (array[i + l][k - l] == 1) {
                if (l == beat_number - 1)
                    return 10;
            } else {
                break;
            }
        }
    }

}
return 0;
}


int Game::maxx(int a, int b)
{
	if(a > b){
		return a;
	}
	return b;
}



int Game::minx(int a, int b)
{
	if(a < b){
		return a;
	}
	return b;
}





void Game::Board(RenderWindow &Aplication_window, int field, int beat) // funkcja, która w całości rysuje planszę
{                                                                      // wykorzystując wszystkie pozostałe funkcje
    Assignment(field, beat);
    Aplication_window.clear(Color::White);
    Line_Render(Aplication_window);
    Sign_Insert(Aplication_window);
    Computer_Sign_Insert(Aplication_window);
    Aplication_window.display();
}



void Game::Game_End(RenderWindow &Aplication_window, int &transition) // funckja, która odpowiada za odpowiednie przejście konca gry
{
    if(Winner_Check() == -10 && Tie() == false) { // gracz wygrywa
        transition = 2;
        player_wins = 1;
        computer_wins = 0;
    }

    if(Winner_Check() == 10 && Tie() == false ) { // komputer wygrywa
        transition = 2;
        computer_wins = 1;
        player_wins = 0;
 
    }

    if(Tie() == true) { // remis
        transition = 2;
    }
}
