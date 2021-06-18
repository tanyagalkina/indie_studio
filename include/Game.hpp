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
    MyList<Character *> _players;
    std::vector<Bomb*> _bombs;
    GameEventReceiver *_gameReceiver;
    Audio *_sounds = new Audio;


public:
    Game();
    ~Game();
    void play();
    void updateMenu();
    void showMenu(GameState state, Menu *menu);
    void safe();
    void load(std::string name, int playerNumber, int botNumber, int width, int height);
    void load(const std::string& game_name);
private:
    static SAppContext createContext();

    void createMap();
    void getExplosions();
    bool isDropPossible(Character *player);
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP
