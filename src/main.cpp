/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include <driverChoice.h>
#include <Floor.hpp>
#include "../include/menu.hpp"
#include "AppContext.hpp"
#include "EDriverTypes.h"
#include "IGUISkin.h"
#include "VisualMap.hpp"
#include "Player.hpp"
#include "../include/Error.hpp"


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

    Floor floor;
    floor.generate_template();

    while (context.device->run() && context.state == GameState::Menu)
    {
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        main_menu->guienv->drawAll();
        context.device->getSceneManager()->drawAll();
        driver->endScene();
    }

    VisualMap map(context, floor.getTemplate());
    Player player(context, map);

    GameEventReceiver gameReceiver;
    context.device->setEventReceiver(&gameReceiver);

    while (context.device->run()) {
        player.update(gameReceiver);
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        map.display();
        driver->endScene();
    }
    context.device->drop();
    return (0);
}