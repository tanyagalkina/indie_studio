/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include <driverChoice.h>
#include "../include/Menu.hpp"
#include "EDriverTypes.h"
#include "IGUISkin.h"
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

        default:
            return '.';

    }
}

int main()
{
    Game g;
    g.play();
    return (0);
}