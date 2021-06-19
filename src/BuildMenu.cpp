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
        begin_x + size_x,size_y * 12), GUI_BUTTON_LOAD, L"Load Previous Game");
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 13,
        begin_x + size_x, size_y * 15),GUI_BUTTON_SETTINGS,L"Open Settings Menu");
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 16,
        begin_x + size_x,size_y * 18), GUI_BUTTON_QUIT, L"Exit Program");
    return menu;
}

Menu *build_load_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList)
{
    irr::core::dimension2d<irr::u32> dimensions =
        context.device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.6);
    int begin_x = (int)(dimensions.Width * 0.2);

    Menu *menu = new Menu(context, imageList);
    menu->addLabel(GUI_TEXT_LOADGAME, irr::core::position2d<irr::s32>
        (begin_x * 1.9, size_y));
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 17,
    begin_x + size_x,size_y * 19), GUI_BUTTON_BACK, L"Go back");
    return menu;
}

Menu *build_settings_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList)
{
    irr::core::dimension2d<irr::u32> dimensions =
        context.device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.6);
    int begin_x = (int)(dimensions.Width * 0.2);

    Menu *menu = new Menu(context, imageList);
    menu->addLabel(GUI_TEXT_SETTINGS, irr::core::position2d<irr::s32>
        (begin_x * 1.9, size_y));
    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x * 1.25, size_y * 7,
        begin_x * 1.25 + size_x * 0.02,size_y * 7.4 + size_x * 0.02),
        GUI_CHECK_MUSIC, context.muteMusic);
    menu->addLabel(GUI_CHECK_MUSIC, irr::core::position2d<irr::s32>
        (begin_x * 1.5, size_y * 7));
    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x * 1.25, size_y * 9,
        begin_x * 1.25 + size_x * 0.02, size_y * 9.4 + size_x * 0.02),
        GUI_CHECK_SOUND, context.muteSound);
    menu->addLabel(GUI_CHECK_SOUND, irr::core::position2d<irr::s32>
        (begin_x * 1.5, size_y * 9));
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 17,
        begin_x + size_x,size_y * 19), GUI_BUTTON_BACK, L"Go back");
    return menu;
}

Menu *build_new_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList)
{
    irr::core::dimension2d<irr::u32> dimensions =
        context.device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.6);
    int begin_x = (int)(dimensions.Width * 0.2);

    Menu *menu = new Menu(context, imageList);
    menu->addLabel(GUI_TEXT_NEWGAME, irr::core::position2d<irr::s32>
        (begin_x * 1.9, size_y));
    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x * 1.25, size_y * 7,
        begin_x * 1.25 + size_x * 0.02,size_y * 7.4 + size_x * 0.02),
        GUI_RADIO_PLAYER1, context.muteMusic);
    menu->addLabel(GUI_CHECK_MUSIC, irr::core::position2d<irr::s32>
        (begin_x * 1.5, size_y * 7));
    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x * 1.25, size_y * 9,
        begin_x * 1.25 + size_x * 0.02, size_y * 9.4 + size_x * 0.02),
        GUI_RADIO_PLAYER2, context.muteSound);
    menu->addLabel(GUI_CHECK_SOUND, irr::core::position2d<irr::s32>
        (begin_x * 1.5, size_y * 9));
    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 17,
        begin_x + size_x,size_y * 19), GUI_BUTTON_BACK, L"Go back");
    return menu;
}