//
// Created by oelman on 5/28/21.
//

#include "../include/Floor.hpp"

bool Floor::can_walk_on() {
    return _type != Type::WALL; //or brick
}

bool Floor::makes_invincible() {
    return _type == Type::POWER_UP;
}

/*
void Floor::draw_floor(int x, int y) {
    void *gameObject = nullptr;
    if (_type == Type::BOX)
        gameObject = _box;
    if (_type == Type::WALL)
        gameObject = _wall;
    if (_type == Type::BOMB)
        gameObject = _bomb;
    if (_type == Type::POWER_UP)
        gameObject = _power_up;
    //if (gameObject)
        //print using the x and y cordinate normally
}*/

void Floor::generate_template()
{
    _template = { //height
            "#############",
            "# B         #",
            "#           #",
            "#           #",
            "#           #",
            "#           #",
            "#           #",
            "#           #",
            "#           #",
            "#           #",
            "#############",
    };
}

void Floor::create_map() {
    int i = 0;
    for (int x = 0; x < 13; x++) { //widtht
        for (int y = 0; y < 11; y++) { //height
            Coordinate cord;
            char c = _template[y][x];
            Floor::Type type = Floor::Type::EMPTY;
            if (c == '#') {
                type = Floor::Type::WALL;
                //std::cout << '#';
            }
            if (c == 'B') {
                type = Floor::Type::BOX;
                //std::cout << 'B';
            }
            if (c == '.') {
                type = Floor::Type::BOMB;
                //std::cout << '.';
            }
            if (c == 'U') {
                type = Floor::Type::POWER_UP;
                //std::cout << 'U';
            }
            /*if (c == ' ') {
                std::cout << " ";
            }*/
            cord.x = x;
            cord.y = y;
            _new_map[i] = std::make_pair(type, cord);
            _map[x][y] = type;
            i++;
        }
    }
    /*for (int i = 0; i < (13 * 11) ; i++)
    {
        std::cout << _new_map[i].second.x << " " << _new_map[i].second.y << std::endl;
    }*/
}

int Floor::get_width() const {
    return width;
}

int Floor::get_height() const {
    return height;
}
