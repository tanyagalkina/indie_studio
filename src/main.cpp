/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include <driverChoice.h>
#include "../include/menu.hpp"
#include "EDriverTypes.h"
#include "IGUISkin.h"
#include "../include/Error.hpp"
#include "Game.hpp"


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
    Game g;
    g.play();
    return (0);
}