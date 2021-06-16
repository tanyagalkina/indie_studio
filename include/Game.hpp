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


public:
    Game();
    ~Game();
    void play();
    void safe();
private:
    static SAppContext createContext();

    void createMap();
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
                irr::core::dimension2d<irr::u32>(640, 480),
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
    while (_context.device->run()) {
        for (auto & player : _players)
        {
            if (player.update(*_gameReceiver))
            {
                Bomb b(_context);
                b.drop(player.getBody()->getPosition());
                _bombs.push_back(b);
            }
        }
        _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        _powerUpHandler->loop(_players);
        _map->display();
        _driver->endScene();
    }
    safe();
}

Game::~Game()
{
//    _context.device->drop();
    delete _map;
    delete _gameReceiver;
    delete _driver;
    delete _powerUpHandler;
    delete _floor;
}

void Game::safe()
{
    std::ofstream os;
    os.open("./games/" + _name + ".txt");
    SerializeHelper sh;
    sh.beginKey(_name);
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        sh.addXML(it->serialize());
    }
    sh.endKey(_name);
    os << sh.getXML();
    os.close();
}

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_GAME_HPP
