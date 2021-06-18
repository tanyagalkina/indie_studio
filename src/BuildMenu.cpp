/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include <driverChoice.h>
#include <Floor.hpp>
#include "../include/Menu.hpp"
#include "AppContext.hpp"
#include "EDriverTypes.h"
#include "IGUISkin.h"
#include "VisualMap.hpp"
#include "Player.hpp"
#include "../include/Error.hpp"


Menu *build_main_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList)
{
    irr::core::dimension2d<irr::u32> dimensions =
        context.device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.6);
    int begin_x = (int)(dimensions.Width * 0.2);

    Menu *menu = new Menu(context, imageList);
    menu->addLabel(GUI_TEXT_HEADLINE, irr::core::position2d<irr::s32>
        (begin_x * 1.375, size_y));
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 7, begin_x
+ size_x, size_y * 9), GUI_BUTTON_NEW, L"Create New Game");
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 10,
                                                   begin_x + size_x,size_y *
                                                   12), GUI_BUTTON_LOAD, L"Load Previous Game");
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 13,
                                                   begin_x + size_x, size_y *
                                                   15),GUI_BUTTON_SETTINGS,
                    L"Open Settings Menu");
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 16,
                                                   begin_x + size_x,size_y * 18), GUI_BUTTON_QUIT, L"Exit ""Program");
    return menu;
}

Menu *build_new_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList)
{
    irr::core::dimension2d<irr::u32> dimensions =
        context.device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.6);
    int begin_x = (int)(dimensions.Width * 0.1);

    Menu *menu = new Menu(context, imageList);
    menu->addLabel(GUI_TEXT_HEADLINE, irr::core::position2d<irr::s32>(begin_x,
                                                                size_y));
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 13,
                                                   begin_x + size_x, size_y *
                                                                     14),GUI_BUTTON_SETTINGS, L"Open Settings Menu");
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 16,
                                                   begin_x + size_x,size_y * 18), GUI_BUTTON_QUIT, L"Exit Program");
    return menu;
}