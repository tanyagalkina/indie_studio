/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/Game.hpp"
#include "AIBot.hpp"

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
    Character *p = new Player(_context, *_map);
    Character *p2 = new AIBot(_context, *_map, 1);
    _players.push_back(p);
    _players.push_back(p2);
    _bombs.clear();
    _menu = new Menu(_context);
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
    _sounds->backMusic();
    while (_context.device->run()) {
        for (auto & player : _players)
        {
            if (player->update(*_gameReceiver) && isDropPossible(player))
            {
                Bomb b(_context, _sounds, player);
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
///this is a hack the real check to come
bool Game::isDropPossible(Character *player)
{
    MyList<Bomb>::iterator it = _bombs.begin();

    int i = 0;
    if (!player->getUnlimitedBombs())
    {
        for (; it != _bombs.end(); it++) {
            if (it->getPLayer() == player)
                ++i;
        }
        if (i >= player->getBombsMax())
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
        _sounds->explode();
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
    delete _menu;
    delete _sounds;
}

void Game::safe()
{
    std::ofstream os;
    os.open("./games/" + _name + ".xml");
    SerializeHelper sh;
    sh.beginKey(_name);
    for (auto & _player : _players)
        sh.addXML(_player->serialize());
    sh.addXML(_map->serialize());
    sh.endKey(_name);
    os << R"(<?xml version="1.0" encoding="ISO-8859-1"?>)" << std::endl << sh.getXML();
    os.close();
}

void Game::showMenu(int menu_enum)
{
    switch (menu_enum) {
        case MAIN_MENU:
            build_main_menu(_context);
            break;
        case NEW_MENU:
            build_main_menu(_context);
            break;
        case LOAD_MENU:
            build_main_menu(_context);
            break;
        case SETTINGS_MENU:
            build_main_menu(_context);
            break;
        case PAUSE_MENU:
            build_main_menu(_context);
            break;
        default:
            break;
    }
}
