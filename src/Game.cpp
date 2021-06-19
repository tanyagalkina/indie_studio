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
    _map = nullptr;
    _powerUpHandler = nullptr;
    _floor = nullptr;
    _context = createContext();
    _context.state = GameState::Game;
    _driver = _context.device->getVideoDriver();
    _gameReceiver = new GameEventReceiver();
    _context.device->setEventReceiver(_gameReceiver);

    //_powerUpHandler = new PowerUpHandler(_context);
    //Character *p = new Player(_context, *_map);
    //Character *p2 = new AIBot(_context, *_map, 1);
    //_players.push_back(p);
    //_players.push_back(p2);
    //_bombs.clear();
    //_menu = new Menu(_context);

    for (int i = 0; i < TEXTPATHSLENGTH; i += 1) {
        std::pair<Buttons, irr::video::ITexture *> tmp;
        tmp.first = static_cast<Buttons>(i + 100);
        tmp.second = _driver->getTexture(textPaths[i]);
        _imageList.push_back(tmp);
    }
}

void Game::createMap()
{
    try {
        _map = new VisualMap(_context, _mapTemplate, _size);
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
    irr::video::E_DRIVER_TYPE driver_type = irr::video::EDT_OPENGL;
    irr::IrrlichtDevice *device = irr::createDevice(driver_type,
                                                    irr::core::dimension2d<irr::u32>(1920, 1080),
                                                    16, false, false, false, nullptr);
    device->setWindowCaption(L"Best Bomberman");
    device->setResizable(true);

    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.muteMusic = false;
    context.muteSound = false;
    context.isPaused = false;
    context.saveState = 0;
    context.needSave = false;
    context.needLoad = false;
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
        HandleExplosion();
        getExplosions();
        if (_gameReceiver->IsKeyDown(irr::KEY_ESCAPE) ||
        _gameReceiver->IsKeyDown(irr::KEY_KEY_P)) {
            _context.isPaused = true;
            _context.state = GameState::PauseMenu;
            _gameReceiver->setIsKeyDown(irr::KEY_ESCAPE, false);
            _gameReceiver->setIsKeyDown(irr::KEY_KEY_P, false);
        }
        _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        _powerUpHandler->loop(_players);
        _map->display();
        this->updateMenu();
        _driver->endScene();
        checkLevel();
        checkSaveOrLoad();
    }
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
    //_context.device->drop();
    delete _map;
    delete _gameReceiver;
    delete _driver;
    delete _powerUpHandler;
    delete _floor;
    delete _sounds;
}

void Game::safe(int n)
{
    std::ofstream os;
    os.open("./games/save" + std::to_string(n) + ".xml");
    SerializeHelper sh;
    sh.beginKey("save" + std::to_string(n));
    sh.addKeyValue("size", std::to_string(_size));
    sh.addXML(_floor->serialize());
    for (auto & _player : _players)
        sh.addXML(_player->serialize());
    sh.addXML(_map->serialize());
    sh.endKey("save" + std::to_string(n));
    os << R"(<?xml version="1.0" encoding="ISO-8859-1"?>)" << std::endl << sh.getXML();
    os.close();
}

void Game::showMenu(GameState state, Menu *menu)
{
    while (_context.device->run() && _context.state == state)
    {
        _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        menu->_guienv->drawAll();
        _driver->endScene();
    }
}

void Game::updateMenu()
{
    switch (_context.state) {
        case GameState::Menu: {
            Menu *menu = build_main_menu(_context, _imageList);
            auto *reciever = new MainMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::Menu, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
        }
        case GameState::New: {
            Menu *menu = build_new_menu(_context, _imageList);
            auto *reciever = new NewMenuEventReceiver(_context, menu->_elementList);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::New, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
        }
        case GameState::Save: {
            Menu *menu = build_save_menu(_context, _imageList);
            auto *reciever = new SaveMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::Save, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
        }
        case GameState::Load: {
            Menu *menu = build_load_menu(_context, _imageList);
            auto *reciever = new LoadMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::Load, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
        }
        case GameState::Settings: {
            Menu *menu = build_settings_menu(_context, _imageList);
            auto *reciever = new SettingsMenuEventReceiver(_context, _sounds);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::Settings, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
        }
        case GameState::PauseMenu: {
            Menu *menu = build_pause_menu(_context, _imageList);
            auto *reciever = new PauseMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::PauseMenu, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
        }
        default:
            _context.device->setEventReceiver(_gameReceiver);
            break;
    }

}

void Game::createGame(std::string name, int playerNumber, int botNumber, int
size)
{
    _size = size;
    _playerNumber = playerNumber;
    _botNumber = botNumber;
    _name = std::move(name);
    _floor = new Floor(1, playerNumber, size * 5, size * 5);
    _mapTemplate = _floor->getTemplate();
    createMap();
    _powerUpHandler = new PowerUpHandler(_context);
    int i;
    for (i = 0; i < playerNumber; i++)
        _players.push_back(new Player(_context, *_map, i));
    for (int j = i; j < botNumber + i; j++)
        _players.push_back(new AIBot(_context, *_map, j));
    _bombs.clear();
}

void Game::load(int n)
{
    std::ifstream file("./games/save" + std::to_string(n) + ".xml");
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
    } else {
        std::cerr << "Could not open File from save state " << n << std::endl;
        return;
    }
    unload();
    std::string code = ss.str();
    SerializeHelper sh(code, true);

    std::string size = SerializeHelper::FindKeyValue(code, "size");
    _size = stoi(size);

    std::string sub_node;
    std::string xmlFloor = SerializeHelper::FindKeyValue(code, "Floor");
    std::string xmlVisualMap = SerializeHelper::FindKeyValue(code, "VisualMap");
    _floor = new Floor(xmlFloor, xmlVisualMap);
    _mapTemplate = _floor->getTemplate();
    _map = new VisualMap(_context, _mapTemplate, _size);

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

void Game::randomPowerUpSpawn(float x, float z)
{
    srand(time(NULL));
    int i = rand() % 3;
    if (i == 0)
    {
        _powerUpHandler->addPowerUp(SpeedUp_t, x, z);
    }
    if (i == 1)
    {
        _powerUpHandler->addPowerUp(FireUp_t, x, z);
    }
    if (i == 2)
    {
        _powerUpHandler->addPowerUp(BombUp_t, x, z);
    }
}


bool Game::HandleExplosion()
{

    for (auto &bomb : _bombs)
    {
        auto expos = bomb->getExplosions();
        for (auto &expo : expos)
        {
            for (auto &player : _players)
            {
                if (player->checkCollision(
                    expo->_particleSystemSceneNode->getTransformedBoundingBox()))
                {
                    if (bomb->beShureCollision(player, player->getBody()->getPosition()))
                        player->kill();
                }
            }
            auto blocks = _map->getBlocks();
            for (auto &box : blocks)
            {
                if (box->getbody()->isVisible())
                {
                    if (box->HandleCollision(
                        expo->_particleSystemSceneNode->getTransformedBoundingBox()))
                    {
                        if (bomb->beShureCollision(_players[0], box->getbody()->getPosition()))
                        {
                            randomPowerUpSpawn(box->getbody()->getPosition().X,
                                               box->getbody()->getPosition().Z);
                            box->getbody()->setPosition(irr::core::vector3df(-5000));
//                            box->getbody()->setVisible(false);
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Game::nextLevel()
{
    _context.device->closeDevice();
    _context.device->run();
    _context.device->drop();
    irr::video::E_DRIVER_TYPE driver_type = irr::video::EDT_OPENGL;
    irr::IrrlichtDevice *device = irr::createDevice(driver_type,
                                                    irr::core::dimension2d<irr::u32>(1920, 1080),
                                                    16, false, false, false, nullptr);
    device->setWindowCaption(L"Best Bomberman");
    device->setResizable(true);
    _context.device = device;
    _context.state = GameState::Game;
    _context.counter = 0;
    _driver = _context.device->getVideoDriver();

    _imageList.clear();
    for (int i = 0; i < TEXTPATHSLENGTH; i += 1) {
        std::pair<Buttons, irr::video::ITexture *> tmp;
        tmp.first = static_cast<Buttons>(i + 100);
        tmp.second = _driver->getTexture(textPaths[i]);
        _imageList.push_back(tmp);
    }

    _players.clear();
    _bombs.clear();
    delete _map;
    _mapTemplate.clear();
    delete _powerUpHandler;
    _floor->nextLevel();
    _mapTemplate = _floor->getTemplate();
    _map = new VisualMap(_context, _mapTemplate, _size);
    _powerUpHandler = new PowerUpHandler(_context);
    for (int i = 0; i < _playerNumber; i++)
        _players.push_back(new Player(_context, *_map, i));
    for (int i = 0; i < _botNumber; i++)
        _players.push_back(new AIBot(_context, *_map, i));
}

void Game::checkLevel()
{
    int i = 0;
    for (auto &player : _players)
    {
        if (player->isAlive())
            i++;
    }
    if (i < 2)
        nextLevel();
}

void Game::checkSaveOrLoad()
{
    if (_context.needSave) {
        safe(_context.saveState);
        _context.needSave = false;
    }
    if (_context.needLoad) {
        load(_context.saveState);
        _context.needLoad = false;
    }
}

void Game::unload()
{
    _context.device->closeDevice();
    _context.device->run();
    _context.device->drop();
    irr::video::E_DRIVER_TYPE driver_type = irr::video::EDT_OPENGL;
    irr::IrrlichtDevice *device = irr::createDevice(driver_type,
                                                    irr::core::dimension2d<irr::u32>(1920, 1080),
                                                    16, false, false, false, nullptr);
    device->setWindowCaption(L"Best Bomberman");
    device->setResizable(true);
    _context.device = device;
    _driver = _context.device->getVideoDriver();

    _imageList.clear();
    for (int i = 0; i < TEXTPATHSLENGTH; i += 1) {
        std::pair<Buttons, irr::video::ITexture *> tmp;
        tmp.first = static_cast<Buttons>(i + 100);
        tmp.second = _driver->getTexture(textPaths[i]);
        _imageList.push_back(tmp);
    }

    _context.counter = 0;
    _players.clear();
    _bombs.clear();
    delete _map;
    _mapTemplate.clear();
    delete _powerUpHandler;
    _mapTemplate = _floor->getTemplate();
    //_map = new VisualMap(_context, _mapTemplate, _size);
    _powerUpHandler = new PowerUpHandler(_context);
    /*for (int i = 0; i < _playerNumber; i++)
        _players[i].push_back(new Player(_context, *_map, i));
    for (int i = 0; i < _botNumber; i++)
        _players.push_back(new AIBot(_context, *_map, i));*/
}
