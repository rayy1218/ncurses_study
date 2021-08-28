#include <ncurses/ncurses.h>
#include "Snake.hpp"
#include "Enums.hpp"
#include "Utilities.hpp"
#include "GameManager.hpp"

GameManager::GameManager(): score(0), food_position(0, 0), map(nullptr) {
    doRender();
    setNewFood();
}

int GameManager::checkKeyboardEvent() {
    timeout(100);
    return getch();
}

bool GameManager::respondEvent(int input) {
    switch (input) { //movement
        case keys::char_a:
            player.setMotion(Motion(-1, 0));
            break;

        case keys::char_d:
            player.setMotion(Motion(1, 0));
            break;

        case keys::char_s:
            player.setMotion(Motion(0, 1));
            break;

        case keys::char_w:
            player.setMotion(Motion(0, -1));
            break;

        default: return false;
    }

    return true;
}

bool GameManager::doUpdate() {
    if (!player.doMove()) {
        return false;
    }

    if (food_position.x == player.snake.begin()->data.x && food_position.y == player.snake.begin()->data.y) {
        player.doEat();
        setScore(getScore() + 1);
        setNewFood();
    }

    return true;
}

void GameManager::doRender() {
    //render game screen
    map = newwin(25, 50, 0, 0);
    refresh();

    //render map
    for (int y = 1; y < 24; y++) {
        for (int x = 1; x < 49; x++) {
            mvwprintw(map, y, x, "_");
        }
    }
    box(map, 0, 0);
    //Render whole snake
    for (Node<Position> *node = player.snake.begin(); node != nullptr; node = node->next_node) {
        mvwprintw(map, node->data.y, node->data.x, "o");
    }
    mvwprintw(map, player.snake.begin()->data.y, player.snake.begin()->data.x, "@");
    //Render food
    mvwprintw(map, food_position.y, food_position.x, "*");

    //Print score
    mvwprintw(map, 0, 2, " Score: %i", getScore());
    wrefresh(map);

    //clear the screen buffer
    delwin(map);
}

void GameManager::setNewFood() {
    bool valid_food_position = true;
    do {
        food_position.y = getRandNumber(1, 23);
        food_position.x = getRandNumber(1, 48);

        for (Node<Position> *node = player.snake.begin(); node != nullptr; node = node->next_node) {
            if (node->data.x == food_position.x && node->data.y == food_position.y) {
                valid_food_position = false;
                break;
            }
        }
    }
    while (!valid_food_position);
}

int GameManager::getScore() {
    return score;
}

void GameManager::setScore(int set_to) {
    score = set_to;
}

