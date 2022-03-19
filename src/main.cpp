#include <ncurses.h>
#include "Enums.hpp"
#include "Snake.hpp"
#include "GameManager.hpp"

int main() {
    //screen initialization
    initscr();
    noecho();
    curs_set(0);

    while (true) {
        //game initialization
        GameManager game;
        int input;
        //game loop
        while (true) {
            input = game.checkKeyboardEvent();
            if (input == keys::escape) {break;}
            game.respondEvent(input);
            if (!game.doUpdate()) {break;}
            game.doRender();
        }
        if (input == keys::escape) {break;}
    }

    endwin();
}
