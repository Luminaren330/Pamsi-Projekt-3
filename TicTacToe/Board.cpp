#include "Board.hh"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



using namespace std;
using namespace sf;



void Board::Reset_All() // zeruje wszystkie wartości do parametrów początkowych
{
    field_size = 0;
    field_data = 0;
    beat_number = 0;
    beat_data = 0;
    mouse_click = 0;

}

int Board::get_field_size() // zwraca rozmiar pola
{
  return field_size;
}

int Board::get_beat_number() // zwraca ilość bić
{
  return beat_number;
}

void Board::Exit(RenderWindow &Aplication_window) // funckja, która pozwala na wyjście z gry i okna aplikacji
{
  Event event;
  while(Aplication_window.pollEvent(event)) {
      if(event.type == Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)))
      Aplication_window.close(); //  jeśli wciśnięty jest przycisk esc lub ikonka x, wychodzi z aplikacji
    }
}

void Board::Menu(RenderWindow &Aplication_window) // funkcja odpowiadająca za wczyatnie pierwszej aplikacji (menu)
{
    Texture Back;
    Back.loadFromFile("background.jpg"); // wczytuje tło z pliku
    Sprite Background;
    Background.setTexture(Back);
    Aplication_window.draw(Background);

    RectangleShape field_width;

  Font font;
  font.loadFromFile( "arial.ttf" );

  Texture texture;
  Sprite image;

  //Start
  if(field_size > 2 && beat_number > 2) { // jeśli odpowiednie parametry są dobrane
      Text text1("NACISNIJ PRAWY PRZYCISK MYSZY",font,24); // pokazuje napis
      text1.setPosition(100,10);
      text1.setColor(sf::Color::Black);
      Aplication_window.draw(text1);

      texture.loadFromFile("start.png");
      image.setTexture(texture); // wczytuje start z pliku
      image.setPosition(65, 200);
      Aplication_window.draw(image);
  }
  else {
      texture.loadFromFile("tictactoe.png"); //wczytanie ikonki tictactoe
      image.setTexture(texture);
      image.setPosition(170, 50);
      image.setScale(0.5, 0.5);
      Aplication_window.draw(image);

      Text text6("ILOSC POL I BIC MUSI BYC WIEKSZA NIZ 2", font, 24);
      text6.setPosition(80, 520);
      text6.setColor(sf::Color::Black);
      Aplication_window.draw(text6);


      Text text2("PODAJ WIELKOSC PLANSZY", font, 20); // pokolei pokazuje odpowiednie teksty
      text2.setPosition(170, 300);
      text2.setColor(sf::Color::Black);
      Aplication_window.draw(text2);

      Text text3("PODAJ ILOSC BIC", font, 20);
      text3.setPosition(220, 400);
      text3.setColor(sf::Color::Black);
      Aplication_window.draw(text3);

      string text_number = to_string(beat_number); // wczytuje ilość bić i odpowiednio się zmeinia
      Text text4(text_number, font, 50);
      text4.setPosition(285, 425);
      text4.setColor(sf::Color::Black);
      Aplication_window.draw(text4);

      text_number = to_string(field_size); // wczytuje wielkość i odpowiednio się zmeinia
      Text text5(text_number, font, 50);
      text5.setPosition(285, 320);
      text5.setColor(sf::Color::Black);
      Aplication_window.draw(text5);
  }

}

void Board::Beat_Field(RenderWindow &Aplication_window) // funckja odpowiadająca za ilość bić
{
  Mouse mouse;

  if(mouse.getPosition(Aplication_window).x < 330 && mouse.getPosition(Aplication_window).x > 250 && mouse.getPosition(Aplication_window).y < 480 && mouse.getPosition(Aplication_window).y > 430) {
      if (mouse.isButtonPressed(mouse.Left)) { // wciśnięcie myszki w odpowiednie miejsce
          beat_data++;
          mouse_click++;
      }
  }
}

void Board::Field_Field(RenderWindow &Aplication_window) // funckja odpowiadająca za ilość pól
{
  Mouse mouse;


  if(mouse.getPosition(Aplication_window).x < 350 && mouse.getPosition(Aplication_window).x > 200 && mouse.getPosition(Aplication_window).y < 384 && mouse.getPosition(Aplication_window).y > 326) {
      if (mouse.isButtonPressed(mouse.Left)) // wciśnięcie myszki w odpowiednie miejsce
      {
          field_data++;
          mouse_click++;
      }
  }
}
void Board::Game_Begin(RenderWindow &Aplication_window, int &transition) // funkcja przechodząca do gry
{
    Mouse mouse;
    if(beat_number > 2 && field_size > 2)
     if(mouse.getPosition(Aplication_window).x < 520 && mouse.getPosition(Aplication_window).x > 90 && mouse.getPosition(Aplication_window).y < 400 && mouse.getPosition(Aplication_window).y > 200)
        if(mouse.isButtonPressed(mouse.Right)) // prawy przycisk bo inaczej samo wstawia pierwszy znak
        {
            transition = 1;
        }


}

void Board::Start_Menu(RenderWindow &Aplication_window) // funkcja która zczytuje wpisanie z klawiatury cyfry
{
    Event load;
    Menu(Aplication_window);
    Beat_Field(Aplication_window);
    Field_Field(Aplication_window);

  if(mouse_click > 0) {
      if (load.type == Event::TextEntered) {
          if (load.text.unicode < 128) {
              char variable = static_cast<char>(load.text.unicode);

              if (field_data > 0) {
                  field_size = atoi(&variable);
              }

              if (beat_data > 0) {
                  beat_number = atoi(&variable);
              }

              if (field_data || beat_data > 0) {
                  mouse_click = 0;
                  field_data = 0;
                  beat_data = 0;
              }
          }
      }
  }
  Aplication_window.display();

}

void Board::End_Menu(RenderWindow &Aplication_window, int player, int computer) // funkcja wczytująca i rysująca okno końcowe
{

    Texture Back;
    Back.loadFromFile("background.jpg"); // tło
    Sprite Background;
    Background.setTexture(Back);
    Aplication_window.draw(Background);
    Font font;
    font.loadFromFile( "arial.ttf" );
    RectangleShape field_width;

    if(computer == 1 || player == 1) {
        Text text1("ZWYCIEZCA:", font, 60); // napis zwycięzca
        text1.setPosition(100, 100);
        text1.setColor(sf::Color::Black);
        Aplication_window.draw(text1);

    if(computer == 1) {  // jeśli komputer wygrał
        Text text2("KOMPUTER", font, 60); // napis komputer
        text2.setPosition(100, 200);
        text2.setColor(sf::Color::Black);
        Aplication_window.draw(text2);
    }

    if(player == 1) { // jeśli gracz wygrał
        Text text2("GRACZ", font, 60); // napis gracz
        text2.setPosition(100, 200);
        text2.setColor(sf::Color::Black);
        Aplication_window.draw(text2);
    }
  }

  if(computer == 0 && player == 0)  { // jeśli nikt nie wygrał
      Text text2("REMIS", font, 60); // napis remis
      text2.setPosition(200, 200);
      text2.setColor(sf::Color::Black);
      Aplication_window.draw(text2);

  }

     Text text3("REWANZ", font, 30); // opcja rewanżu
     text3.setPosition(90, 500);
     text3.setColor(sf::Color::Black);
     Aplication_window.draw(text3);

    Text text4("WYJSCIE", font, 30); // wyjście
    text4.setPosition(390, 500);
    text4.setColor(sf::Color::Black);
    Aplication_window.draw(text4);

  Aplication_window.display();

}


bool Board::Rematch(RenderWindow &Alication_window) // kliknięcie napisu rewanż
{
  Mouse mouse;

  if(mouse.getPosition(Alication_window).x < 230 && mouse.getPosition(Alication_window).x > 80 && mouse.getPosition(Alication_window).y < 540 && mouse.getPosition(Alication_window).y > 500) {
    if(mouse.isButtonPressed(mouse.Left)) {  // powoduje powrót do pierwszego okna
        return true;
    }
  }
  return false;
}

bool Board::Game_Exit(RenderWindow &Aplication_window) // kliknięcie napisu wyjście
{
  Mouse myszka;
  if(myszka.getPosition(Aplication_window).x < 530 && myszka.getPosition(Aplication_window).x > 380 && myszka.getPosition(Aplication_window).y < 540 && myszka.getPosition(Aplication_window).y > 500) {
      if(myszka.isButtonPressed(myszka.Left)) { // wychodzi z gry
          return true;
      }
    }
    return false;
}


