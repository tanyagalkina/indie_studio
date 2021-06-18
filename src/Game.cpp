/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/Game.hpp"

#include <utility>
#include "AIBot.hpp"

Game::Game()
{
    _context = createContext();
    //    Bomb b(_context);
    _context.state = GameState::Menu;
    _driver = _context.device->getVideoDriver();
    _gameReceiver = new GameEventReceiver();
    _context.device->setEventReceiver(_gameReceiver);
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
                                                    irr::core::dimension2d<irr::u32>(1920, 1080),
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
                Bomb *b = new Bomb(_context, _sounds, player);
                b->drop();
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
    auto it = _bombs.begin();

    int i = 0;
    if (!player->getUnlimitedBombs())
    {
        for (; it != _bombs.end(); it++) {
            if ((*it)->getPLayer() == player)
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
        if ((*it)->body->getPosition() == position)
            return false;
    }
    return true;
}

void Game::getExplosions() {
    auto it = _bombs.begin();

    while (it != _bombs.end()) {
        if (!(*it)->_exploded && (*it)->timer.isFinished()) {
            (*it)->initExplosion();
            _sounds->explode();
        } else if ((*it)->_exploded && (*it)->timer.isFinished()) {
            (*it)->stopExplosion();
            delete _bombs[it - _bombs.begin()];
            it = _bombs.erase(it);
            continue;
        }
        it++;
    }
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
    sh.addXML(_floor->serialize());
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

void Game::load(std::string name, int playerNumber, int botNumber, int width, int height)
{
    _name = std::move(name);
    _floor = new Floor(1, playerNumber, width, height);
    _mapTemplate = _floor->getTemplate();
    createMap();
    _powerUpHandler = new PowerUpHandler(_context);
    for (int i = 0; i < playerNumber; i++)
        _players.push_back(new Player(_context, *_map, i));
    for (int i = 0; i < botNumber; i++)
        _players.push_back(new AIBot(_context, *_map, i));
    _bombs.clear();
}

void Game::load(const std::string& gamename)
{
    _name = gamename;
    std::ifstream file("./games/" + gamename + ".xml");
    std::stringstream ss;
    std::string line;
    std::string before;
    if (file.is_open())
    {
        file >> line;
        file >> line;
        file >> line;
        file >> line;
        while (line != before)
        {
            before  = line;
            ss << line << std::endl;
            file >> line;
        }
        file.close();
    }
    else throw std::runtime_error("file for game was not found");
    std::string code = ss.str();
    SerializeHelper sh(code, true);
    std::string sub_node;
    std::string xmlFloor = SerializeHelper::FindKeyValue(code, "Floor");
    std::string xmlVisualMap = SerializeHelper::FindKeyValue(code, "VisualMap");
    _floor = new Floor(xmlFloor, xmlVisualMap);
    _mapTemplate = _floor->getTemplate();
    _map = new VisualMap(_context, _mapTemplate);

    _powerUpHandler = new PowerUpHandler(_context);

    std::string node = sh.GetNextKey();
    while (!node.empty())
    {
        std::string object = SerializeHelper::GetKeyName(node);
        if (object == "Player")
        {
            auto *p = new Player(_context, *_map);
            p->deserialize(node);
            _players.push_back(p);
        }
        else if (object == "AIBot")
        {
            auto aiB = new AIBot(_context, *_map);
            aiB->deserialize(node);
            _players.push_back(aiB);
        }
        else if (object == "Floor" || object == "VisualMap") {
            // here happens nothing
         }
        node = sh.GetNextKey();
    }
}
