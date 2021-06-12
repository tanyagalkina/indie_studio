/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include <driverChoice.h>
#include <Floor.hpp>
#include <PowerUpHandler.hpp>
#include "../include/menu.hpp"
#include "AppContext.hpp"
#include "EDriverTypes.h"
#include "IGUISkin.h"
#include "VisualMap.hpp"
#include "Player.hpp"
#include "../include/Error.hpp"


char get_char(Floor::Type teip)
{
    switch (teip)
    {
        case (Floor::Type::WALL):
            return '#';
        case (Floor:: Type::BOX):
            return 'B';
        case (Floor:: Type::EMPTY):
            return ' ';
        case (Floor::Type::TELEPORT):
            return 'X';
        case (Floor::Type::PLAYER):
            return 'P';

        default:
            return '.';

    }
}

void show_template(MyList<std::pair<Floor::Type, Coordinate>> mapTemplate)
{
    for (int j = 0; j < 40; ++j) {
        for (int i = 0; i < 40; ++i) {
            for (int k = 0; k < mapTemplate.size(); k++) {
                if (mapTemplate[k].second.y == j && mapTemplate[k].second.x == i) {
                    char ch = get_char(mapTemplate[k].first);
                    printf("%c", ch);
                }
            }
        }
        printf("\n");
    }
}


SAppContext createContext()
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


int main()
{
    SAppContext context = createContext();
    MyEventReceiver receiver(context);

    context.device->setEventReceiver(&receiver);
    context.state = GameState::Menu;
    irr::video::IVideoDriver *driver = context.device->getVideoDriver();
    Menu *main_menu = build_main_menu(context);

    Floor floor(1, 1, 10, 10);
    MyList<std::pair<Floor::Type, Coordinate>> mapTemplate = floor.getTemplate();

    while (context.device->run() && context.state == GameState::Menu)
    {
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        main_menu->guienv->drawAll();
        context.device->getSceneManager()->drawAll();
        driver->endScene();
    }

    VisualMap *map = nullptr;

    try {
        map = new VisualMap(context, mapTemplate);
    } catch (AssetLoadError &e) {
        std::cerr << e.getMessage() << std::endl;
        return 84;
    } catch (SceneError &e) {
        std::cerr << e.getMessage() << std::endl;
        return 84;
    }

    Player player(context, *map);
    GameEventReceiver gameReceiver;
    context.device->setEventReceiver(&gameReceiver);
    PowerUpHandler PUHandler(context, player);
    Timer t(1000);
    t.startTimer();
    bool over = false;
    while (context.device->run()) {
        player.update(gameReceiver);
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        if (t.isFinished() && !over)
        {
            PUHandler.addPowerUp(PowerUpType::SpeedUp_t, 50, 50);
            over = true;
        }
        PUHandler.loop(gameReceiver);
        map->display();
        driver->endScene();
    }

    context.device->drop();
    delete map;
    return (0);
}