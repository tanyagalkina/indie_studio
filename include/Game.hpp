/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Game.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP

#include "Floor.hpp"
#include "Menu.hpp"
#include "PowerUpHandler.hpp"
#include "Bomb.hpp"
#include "fstream"
#include "Audio.hpp"
#include "button_enum.hpp"
#include <driverChoice.h>


class Game
{
private:
    std::string _name = "gameOne";
    SAppContext _context;
    irr::video::IVideoDriver *_driver;
    Floor *_floor;
    MyList<std::pair<Floor::Type, Coordinate>> _mapTemplate;
    VisualMap *_map;
    PowerUpHandler *_powerUpHandler;
    MyList<Player> _players;
    MyList<Bomb> _bombs;
    GameEventReceiver *_gameReceiver;
    Menu *_menu;
    Audio *_sounds;


public:
    Game();
    ~Game();
    void play();
    void showMenu(int menu_enum);
    void safe();
private:
    static SAppContext createContext();

    void createMap();
    bool getExplosions();
    bool isDropPossible(Player *player);
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP
