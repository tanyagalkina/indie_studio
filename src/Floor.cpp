//
// Created by oelman on 5/28/21.
//

#include <ctime>
#include "../include/Floor.hpp"

void Floor::set_monster_nb()
{
    if (_level >= 5 && _level <= 9)
        _nb_monsters = 2;
    if (_level >= 11 && _level <= 14)
        _nb_monsters = 3;
    if (_level >= 15 && _level <= 19)
        _nb_monsters = 4;
}

void Floor::set_obstacle_number_for_the_level()
{
    _nb_of_item_at_start = ((_height * _width) / 10);
    _nb_of_item_per_level = _nb_of_item_at_start / 10;
    _nb_tiles = (_nb_of_item_at_start * (1.5/3)) + (_nb_of_item_per_level * _level);
    _nb_boxes = (_nb_of_item_at_start * (1/3)) + (_nb_of_item_per_level * _level);
    set_monster_nb();
}

void Floor::build_available_square_list()
{
    Coordinate cor;
    _available_squares.clear();
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            if (_template[y][x] == ' ' && x != 1 && x != _width - 2 && y != 1 && y != _height - 2) {
                cor.x = x;
                cor.y = y;
                _available_squares.push_back(cor);
            }
        }
    }
    _nb_free_squares = _available_squares.size();
}

void Floor::show_map()
{
    for (std::vector<std::string>::const_iterator i = _template.begin(); i != _template.end(); ++i)
        std::cout << *i << std::endl;
}

void Floor::set_teleport()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 4);
    int my_random = distr(gen);
    switch (my_random)
    {
        case (1):
            _template[_height / 2][1] = 'X';
            break;
        case (2):
            _template[(_height) / 2][_width - 2] =  'X';
            break;
        case (3):
            _template[1][(_width) / 2] = 'X';
            break;
        case (4):
            _template[_height - 2][_width / 2] = 'X';
            break;
    }

    build_available_square_list();
}

void Floor::put_players()
{
    switch (_player_nb)
    {
        case (1):
            _template[1][1] = 'P';
            break;
        case (2):
            _template[1][1] = 'P';
            _template[1][_width - 2] = 'P';

            break;
        case (3):
            _template[1][1] = 'P';
            _template[1][_width - 2] = 'P';
            _template[_height - 2][1] = 'P';
            break;
        case (4):
            _template[1][1] = 'P';
            _template[1][_width - 2] = 'P';
            _template[_height - 2][1] = 'P';
            _template[_height -2] [_width -2] = 'P';
            break;
    }

}

///return _map will return a List of pairs <Coordinate, Type>
///MyList<std::string> Floor::getTemplate()
MyList<std::pair<Floor::Type, Coordinate>> Floor::getTemplate()
{
    /*MyList<std::string> output;
    for (std::vector<std::string>::const_iterator i = _template.begin(); i != _template.end(); ++i)
        output.push_back(*i);
    return output;*/

    ///_map is a list of pairs<Coordinate, Floor::Type>
    return _map;
}

void Floor::generate_template()
{
    std::string wall;
    std::string interior;
    std::string empty;
    empty.append(_width, ' ');
    wall.append(_width, '#');
    _template.push_back(wall);
    for (int i = 0; i < _height - 2; i++) {
        _template.push_back(empty);
    }
    _template.push_back(wall);
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            if ((y % 2 == 0) && (x % 2 == 0))
                _template[y][x] = '#';
            if (x == 0 || x == _width - 1)
                _template[y][x] = '#';
        }
    }
    set_teleport();
    build_available_square_list();
    if (_level == 10)
        put_obstacles('B', 1);
    else if (_level == 20)
        put_obstacles('B', 2);
    else {
        put_obstacles('+', _nb_boxes);
        put_obstacles('M', _nb_monsters);
        put_obstacles('*', _nb_tiles);
    }
    put_players();
    create_map();
}

void Floor::create_map() {
    int i = 0;
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            Coordinate cord;
            Floor::Type type = Floor::Type::EMPTY;
            char c = _template[y][x];
            if (c == '#') {
                if (_level == 10 || _level == 20)
                    type = Floor::Type::WALL_BOSS;
                else
                    type = Floor::Type::WALL;
            }
            if (c == 'B') {
                type = Floor::Type::BOSS;
            }
            if (c == '+') {
                type = Floor::Type::BOX;
            }
            if (c == '*') {
                type = Floor::Type::TILE;
            }
            if (c == 'B') {
                type = Floor::Type::BOMB;
            }
            if (c == 'U') {
                type = Floor::Type::POWER_UP;
            }
            if (c == 'M') {
                type = Floor::Type::MONSTER;
            }
            if (c == 'P') {
                type = Floor::Type::PLAYER;
            }
            if (c == 'X')
                type = Floor::Type::TELEPORT;

            cord.x = x;
            cord.y = y;
            _map.push_back(std::make_pair(type, cord));
            i++;
        }
    }
}

void Floor::check_and_fit_in_sizes() {
    if (_height % 2 == 0)
        _height++;
    if (_width % 2 == 0)
        _width++;
    if (_player_nb > 4)
        _player_nb = 4;
    if (_width <= 13 || _width > 100)
        _width = 13;
    if (_height <= 11 || _height > 100)
        _height = 11;
    _height += 2;
    _width += 2;
}

std::set<unsigned int> get_random_number_set(int min, int max, int amount)
{
    std::set<unsigned int> results;
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<unsigned int> dist{(unsigned)min, (unsigned)max};
    while(results.size() != amount)
    {
        results.insert(dist(generator));
    }

    return results;
}


void Floor::put_obstacles(char ch, int nb_items)
{
    std::set<unsigned int> random_set = get_random_number_set(0, _nb_free_squares - 1, nb_items);
    Coordinate cord;

    for (auto it = random_set.begin(); it !=
                                  random_set.end(); ++it)
    {
        cord = _available_squares[*it];
       _template[cord.y][cord.x] = ch;

    }
    build_available_square_list();

}

Floor::Floor(int level, int player_nb ,int width, int height)
{
    _level = level;
    _player_nb = player_nb;
    _width = width;
    _height = height;
    check_and_fit_in_sizes();
    set_obstacle_number_for_the_level();
    generate_template();
}

std::string Floor::getStringFromType(Floor::Type t)
{
    const std::map<Type, std::string> TypeStrings {
        {Type::EMPTY, "EMPTY"},
        {Type::BOX, "BOX"},
        {Type::TILE, "TILE"},
        {Type::WALL, "WALL"},
        {Type::WALL_BOSS, "WALL_BOSS"},
        {Type::BOSS, "BOSS"},
        {Type::PLAYER, "PLAYER"},
        {Type::BOMB, "BOMB"},
        {Type::MONSTER, "MONSTER"},
        {Type::POWER_UP, "POWER_UP"},
        {Type::TELEPORT, "TELEPORT"},
    };
    auto it = TypeStrings.find(t);
    return it == TypeStrings.end() ? "Out of range" : it->second;
}
