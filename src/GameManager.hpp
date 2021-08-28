#ifndef GAMEMANAGER
#define GAMEMANAGER

class GameManager {
private:
    int score;
    SnakeEntity player;
    WINDOW *map;
    Position food_position;
public:
    GameManager();
    int checkKeyboardEvent();
    bool respondEvent(int input);
    bool doUpdate();
    void doRender();
    void setNewFood();

    int getScore();
    void setScore(int set_to);
};

#endif //GAMEMANAGER
