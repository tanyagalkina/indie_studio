/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Game.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP

#include "Floor.hpp"
#include "menu.hpp"
#include "PowerUpHandler.hpp"
#include "Bomb.hpp"
#include "fstream"
#include "Audio.hpp"

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
    Audio *sounds = new Audio;


public:
    Game();
    ~Game();
    void play();
    void safe();
private:
    static SAppContext createContext();

    void createMap();
    bool getExplosions();
    bool isDropPossible(Player *player);
};

Game::Game()
{
    _context = createContext();
//    Bomb b(_context);
    _context.state = GameState::Menu;
    _driver = _context.device->getVideoDriver();
    _floor = new Floor(1, 1, 10, 10);
    _mapTemplate = _floor->getTemplate();
    createMap();
    _gameReceiver = new GameEventReceiver();
    _context.device->setEventReceiver(_gameReceiver);
    _powerUpHandler = new PowerUpHandler(_context);
    Player p(_context, *_map);
    _players.push_back(p);
    _bombs.clear();
}

void Game::createMap()
{
    _map = nullptr;
    try {
        _map = new VisualMap(_context, _mapTemplate);
    } catch (AssetLoadError &e) {
        std::cerr << e.getMessage() << std::endl;
        exit(84);
    } catch (SceneError &e) {
        std::cerr << e.getMessage() << std::endl;
        exit(84);
    }
}

SAppContext Game::createContext()
{
    irr::video::E_DRIVER_TYPE driver_type = irr::driverChoiceConsole();
    irr::IrrlichtDevice *device = irr::createDevice(driver_type,
                irr::core::dimension2d<irr::u32>(1280, 720),
                16, false, false, false, nullptr);
    device->setWindowCaption(L"Best Bomberman");
    device->setResizable(true);

    SAppContext context;
    context.device = device;
    context.counter = 0;
    return context;
}

void Game::play()
{
    sounds->backMusic();
    while (_context.device->run()) {
        for (auto & player : _players)
        {
            if (player.update(*_gameReceiver) && isDropPossible(&player))
            {
                Bomb b(_context, sounds, &player);
                b.drop();
                _bombs.push_back(b);
            }
        }
        getExplosions();
        _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        _powerUpHandler->loop(_players);
        _map->display();
        _driver->endScene();
    }
    safe();
}

///func should check if there is already a Bomb at the same position
///returns true if the position is free
///do we need a some radius as well?
bool Game::isDropPossible(Player *player)
{
    MyList<Bomb>::iterator it = _bombs.begin();

    int i = 0;
    if (!player->getUnlimitedBombs())
    {
        for (; it != _bombs.end(); it++) {
            if (it->getPLayer() == player)
                ++i;
        }
        if (i >= player->bombsMax)
            return false;
    }

    auto position = player->getBody()->getPosition();
    position.X = player->calcMiddle(position.X);
    position.Z = player->calcMiddle(position.Z);
    position.Y = 10;

    for (it = _bombs.begin(); it != _bombs.end(); it++)
    {
        if (it->body->getPosition() == position)
            return false;
    }


    return true;
}

bool Game::getExplosions() {
    //MyList<Bomb>::iterator it = _bombs.begin();
    ///how many bombs are there in the list
    //std::cout << _bombs.size() << std::endl;
    if (_bombs.size() > 0 && _bombs[0].timer.isFinished())
    {
        _bombs[0].explosion();
        _bombs.erase(_bombs.begin());
        sounds->explode();
    }
    return true;
}

Game::~Game()
{
//    _context.device->drop();
    delete _map;
    delete _gameReceiver;
    delete _driver;
    delete _powerUpHandler;
    delete _floor;
    delete sounds;
}

void Game::safe()
{
    std::ofstream os;
    os.open("./games/" + _name + ".xml");
    SerializeHelper sh;
    sh.beginKey(_name);
    for (auto & _player : _players)
        sh.addXML(_player.serialize());
    sh.addXML(_map->serialize());
    sh.endKey(_name);
    os << R"(<?xml version="1.0" encoding="ISO-8859-1"?>)" << std::endl << sh.getXML();
    os.close();
}

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP
