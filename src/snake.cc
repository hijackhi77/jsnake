#include <cstdlib> // rand()
#include <iostream>
#include "snake.h"
using namespace std;

Node::Node() {}

Node::Node(const Posn &p, const int dir)
: p{p}, prev{nullptr}, next{nullptr}, dir{dir} {}

Snake::Snake(int w, int h, int x, int y, int dir)
: width{w}, height{h} {
	head = new Node(Posn(x, y), dir);
	tail = head;
}

Snake::~Snake() {
	Node *node = head;
		while(node) {
    	Node *temp = node->next;
    	delete node;
    	node = temp;
	}
}

Node *Snake::getHead() const { return head; }

Node *Snake::getTail() const { return tail; }

int Snake::getLen() const { return len; }

Posn Snake::getLastTail() const { return lastTail; }

bool Snake::isSnakeBody(Posn &p) const {
	Node *node = head->next;
	// TODO: find more efficient algorithm
	// Solution: body nodes have order property,
	//			 employ more advanced algorithm
	while (node) {
		if (p == node->p) return true;
		node = node->next;
	}
	return false;
}

bool Snake::isSnake(Posn &p) const {
	if (p == head->p) return false;
	return isSnakeBody(p);
}

void Snake::grow(const int step) {
	Node *temp = new Node();
	temp->p = tail->p;
	switch(tail->dir) {
		case N:
			temp->p.y += step;
			break;
		case W:
			temp->p.x += step;
			break;
		case E:
			temp->p.x -= step;
			break;
		case S:
			temp->p.y -= step;
			break;
	}
	// TODO: the case that len == height-2 or width-2
	// Solution: try the other two direction
	// Eg: N - try W and E
	if (temp->p.x<1 || temp->p.x>width-1
		|| temp->p.y<1 || temp->p.y>height-1) return;
	temp->prev = tail;
	temp->next = nullptr;
	temp->dir = tail->dir;
	tail->next = temp;
	tail = temp;
	++len;
}

void Snake::changeDir(const int dir) {
	if (dir == head->dir) return;
	// Opposite direction
	if (len > 0 && dir + head->dir == 3) return;
	head->dir = dir; 
}

void Snake::forward(const int step) {
	lastTail = tail->p;
	Node *node = tail;
	while (node->prev) {
		node->p = node->prev->p;
		node->dir = node->prev->dir;
		node = node->prev;
	}

	switch(head->dir) {
		case N:
			head->p.y -= step;
			break;
		case W:
			head->p.x -= step;
			break;
		case E:
			head->p.x += step;
			break;
		case S:
			head->p.y += step;
			break;
	}
}
