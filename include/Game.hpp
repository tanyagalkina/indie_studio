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
    int _size;
    irr::video::IVideoDriver *_driver;
    Floor *_floor;
    MyList<std::pair<Floor::Type, Coordinate>> _mapTemplate;
    VisualMap *_map;
    PowerUpHandler *_powerUpHandler;
    MyList<Character *> _players;
    std::vector<Bomb*> _bombs;
    GameEventReceiver *_gameReceiver;
    Audio *_sounds = new Audio;
    int _playerNumber;
    int _botNumber;
    std::vector<std::pair<Buttons, irr::video::ITexture *>> _imageList;

public:
    Game();
    ~Game();
    void play();
    void updateMenu();
    void showMenu(GameState state, Menu *menu);
    void safe(int n);
    void createGame(std::string name, int playerNumber, int botNumber, int
    size);
    void load(int n);
    void unload();
    void checkSaveOrLoad();
private:
    static SAppContext createContext();
    bool HandleExplosion();

    void createMap();
    void getExplosions();
    bool isDropPossible(Character *player);


    void randomPowerUpSpawn(float x, float z);

    void nextLevel();

    void checkLevel();
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP
