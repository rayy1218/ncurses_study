#ifndef SNAKE
#define SNAKE

template <typename T>
struct Node {
    T data;
    Node *next_node;

    Node(T data);
};

template <typename T>
class LinkedList {
private:
    Node<T>* head_node;
    Node<T>* tail_node;
public:
    LinkedList();
    void addNode(T data);

    Node<T>* begin();
    Node<T>* end();
};

struct Position {
    int x, y;

    Position(int x, int y);
};

struct Motion {
    int dx, dy;

    Motion(int dx, int dy);
};

class SnakeEntity {
private:
    bool is_ate_last_round;
    Position last_tail_position;
    Motion head_motion;
public:
    LinkedList<Position> snake;

    SnakeEntity();

    void setMotion(Motion motion);
    bool doMove();
    void doEat();
};


#endif //SNAKE
