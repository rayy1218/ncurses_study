#include "Snake.hpp"

template<typename T>
Node<T>::Node(T data): data(data), next_node(nullptr) {}

template<typename T>
LinkedList<T>::LinkedList(): head_node(nullptr), tail_node(nullptr) {}

template<typename T>
Node<T>* LinkedList<T>::begin() {
    return head_node;
}

template<typename T>
Node<T>* LinkedList<T>::end() {
    return tail_node;
}

template<typename T>
void LinkedList<T>::addNode(T data) {
    auto *node_to_add = new Node<T>(data);
    if (head_node == nullptr && tail_node == nullptr) {
        head_node = node_to_add;
        tail_node = head_node;

        return;
    }

    tail_node->next_node = node_to_add;
    tail_node = node_to_add;
}

Position::Position(int x, int y): x(x), y(y) {}

Motion::Motion(int dx, int dy): dx(dx), dy(dy) {}

SnakeEntity::SnakeEntity(): is_ate_last_round(false), last_tail_position(0 ,0), head_motion(0, 0) {
    for (int i = 1; i <= 3; i += 1) {
        snake.addNode(Position(i + 23, 12));
    }

    last_tail_position = snake.end()->data;
}

void SnakeEntity::setMotion(Motion motion) {
    head_motion = motion;
}

bool SnakeEntity::doMove() {
    if (head_motion.dx == 0 && head_motion.dy == 0) {
        return true;
    }

    if (snake.begin()->data.x + head_motion.dx <= 0 ||
        snake.begin()->data.x + head_motion.dx >= 49 ||
        snake.begin()->data.y + head_motion.dy <= 0 ||
        snake.begin()->data.y + head_motion.dy >= 24) {

        return false;
    }

    for (Node<Position> *node = snake.begin()->next_node; node != nullptr; node = node->next_node) {
        if (snake.begin()->data.x + head_motion.dx == node->data.x &&
            snake.begin()->data.y + head_motion.dy == node->data.y) {

            return false;
        }
    }

    Position last_position(snake.begin()->data.x, snake.begin()->data.y);
    snake.begin()->data.x += head_motion.dx;
    snake.begin()->data.y += head_motion.dy;

    if (snake.begin()->next_node == nullptr) {return true;}

    Node<Position> *body_node = snake.begin()->next_node;
    Position node_position(0, 0);
    while (body_node != nullptr) {
        node_position = Position(body_node->data.x, body_node->data.y);
        body_node->data = last_position;
        last_position = node_position;
        body_node = body_node->next_node;
    }

    if (is_ate_last_round) {
        snake.addNode(last_tail_position);
        is_ate_last_round = false;
    }

    last_tail_position = snake.end()->data;
    return true;
}

void SnakeEntity::doEat() {
    is_ate_last_round = true;
}


