//
// Created by oelman on 5/28/21.
//

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP

#include "../include/my_list.hpp"
#include <map>
#include <ostream>
#include <random>
#include <set>
#include <iostream>
#include <vector>
#include "Coordinate.hpp"

using std::mt19937_64;
using std::random_device;
using std::uniform_int_distribution;

class Floor
{
public:
    enum class Type
    {
        EMPTY,
        BOX,
        TILE,
        WALL,
        WALL_BOSS,
        BOSS,
        PLAYER,
        BOMB,
        MONSTER,
        POWER_UP,
        TELEPORT
    };
public:
    static std::string getStringFromType(Type t);
    Floor(int level, int player_nb, int width, int height);
    MyList<std::pair<Type, Coordinate>> getTemplate(); //only for debugging
    void show_map(); //only for debugging

private:
    void generate_template();
    void set_obstacle_number_for_the_level();
    void set_teleport();
    void set_monster_nb();
    void put_players();
    void put_obstacles(char obstacle_abbrev_letter, int nb_obstacles);
    void create_map();
    void check_and_fit_in_sizes();
    void build_available_square_list();

private:
    MyList<std::pair<Type, Coordinate>> _map;
    int _level = 1;
    int _player_nb = 1;
    int _width = 13;
    int _height = 11;
    int _nb_free_squares;
    Type _type;
    int _nb_boxes = 3; //default
    int _nb_tiles = 3; //default
    int _nb_monsters = 1; //default
    int _nb_of_item_at_start;
    int _nb_of_item_per_level;
    std::vector<Coordinate> _available_squares;
    std::vector<std::string> _template;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP
