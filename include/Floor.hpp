//
// Created by oelman on 5/28/21.
//

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP

#include "../include/my_list.hpp"
#include <map>
#include <ostream>
#include <iostream>
#include "Coordinate.hpp"

class Floor
{
public:
    enum class Type
    {
        EMPTY,
        BOX,
        WALL,
        BOMB,
        POWER_UP
    };
private:
    int width = 13;
    int height = 11;

    std::array<std::array<Type, 11>, 13> _map; //height>, width
    MyList<std::pair<Type, Coordinate>> _new_map;

public:
    //FloorBlock() = default;
    bool can_walk_on();
    bool makes_invincible();
    void draw_floor(int x, int y);
    void create_map();
    void draw_map();
    int get_width() const;
    int get_height() const;
    void generate_template();

private:
    Type _type;
    void *_box;
    void *_bomb;
    void *_power_up;
    void *_wall;
    MyList<std::string> _template; //height
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP
