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

    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x, size_y * 5,
                                                begin_x + size_x * 0.02,size_y * 5.4 + size_x * 0.02),
                      GUI_RADIO_PLAYER1, context.muteMusic);
    menu->addLabel(GUI_RADIO_PLAYER1, irr::core::position2d<irr::s32>
        (begin_x * 1.2, size_y * 5));

    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x * 3, size_y * 5,
                                                begin_x * 3 + size_x * 0.02, size_y * 5.4 + size_x * 0.02),
                      GUI_RADIO_PLAYER2, context.muteSound);
    menu->addLabel(GUI_RADIO_PLAYER2, irr::core::position2d<irr::s32>
        (begin_x * 3.2, size_y * 5));

    menu->addLabel(GUI_TEXT_MAP, irr::core::position2d<irr::s32>
        (begin_x * 2.4, size_y * 8));

    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x * 1, size_y * 10,
                                                begin_x * 1 + size_x * 0.02, size_y * 10.4 + size_x * 0.02),
                      GUI_RADIO_SMALL, context.muteSound);
    menu->addLabel(GUI_RADIO_SMALL, irr::core::position2d<irr::s32>
        (begin_x * 1.2, size_y * 10));

    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x * 2.2, size_y * 10,
                                                begin_x * 2.2 + size_x * 0.02, size_y * 10.4 + size_x * 0.02),
                      GUI_RADIO_MEDIUM, context.muteSound);
    menu->addLabel(GUI_RADIO_MEDIUM, irr::core::position2d<irr::s32>
        (begin_x * 2.4, size_y * 10));

    menu->addCheckBox(irr::core::rect<irr::s32>(begin_x * 3.4, size_y * 10,
                                                begin_x * 3.4 + size_x * 0.02, size_y * 10.4 + size_x * 0.02),
                      GUI_RADIO_LARGE, context.muteSound);
    menu->addLabel(GUI_RADIO_LARGE, irr::core::position2d<irr::s32>
        (begin_x * 3.6, size_y * 10));

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 14.5,
                                              begin_x + size_x,size_y * 16.5), GUI_BUTTON_CREATE, L"Create Game");

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 17,
                                              begin_x + size_x,size_y * 19), GUI_BUTTON_BACK, L"Go back");

    return menu;
}

Menu *build_save_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList)
{
    irr::core::dimension2d<irr::u32> dimensions =
        context.device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.6);
    int begin_x = (int)(dimensions.Width * 0.2);

    Menu *menu = new Menu(context, imageList);
    menu->addLabel(GUI_TEXT_SAVEGAME, irr::core::position2d<irr::s32>
        (begin_x * 1.85, size_y));

    menu->addButton(irr::core::rect<irr::s32>(begin_x * 1.2, size_y * 6, begin_x
                                                                         + size_x * 0.93, size_y * 7.5), GUI_BUTTON_SAVE1, L"Save to State No. 1");

    menu->addButton(irr::core::rect<irr::s32>(begin_x * 1.2, size_y * 8.5,
                                              begin_x + size_x * 0.93,size_y * 10),
                    GUI_BUTTON_SAVE2, L"Save to State No. 2");

    menu->addButton(irr::core::rect<irr::s32>(begin_x * 1.2, size_y * 11,
                                              begin_x + size_x * 0.93, size_y * 12.5),
                    GUI_BUTTON_SAVE3,L"Save to State No. 3");

    menu->addButton(irr::core::rect<irr::s32>(begin_x * 1.2, size_y * 13.5,
                                              begin_x + size_x * 0.93,size_y * 15),
                    GUI_BUTTON_SAVE4, L"Save to State No. 4");

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 17,
                                              begin_x + size_x,size_y * 19), GUI_BUTTON_BACK, L"Go back");

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
        (begin_x * 1.85, size_y));

    menu->addButton(irr::core::rect<irr::s32>(begin_x * 1.2, size_y * 6, begin_x
        + size_x * 0.93, size_y * 7.5), GUI_BUTTON_SAVE1, L"Load State No. 1");

    menu->addButton(irr::core::rect<irr::s32>(begin_x * 1.2, size_y * 8.5,
        begin_x + size_x * 0.93,size_y * 10),
        GUI_BUTTON_SAVE2, L"Load State No. 2");

    menu->addButton(irr::core::rect<irr::s32>(begin_x * 1.2, size_y * 11,
        begin_x + size_x * 0.93, size_y * 12.5),
        GUI_BUTTON_SAVE3,L"Load State No. 3");

    menu->addButton(irr::core::rect<irr::s32>(begin_x * 1.2, size_y * 13.5,
        begin_x + size_x * 0.93,size_y * 15),
        GUI_BUTTON_SAVE4, L"Load State No. 4");

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

Menu *build_pause_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList)
{
    irr::core::dimension2d<irr::u32> dimensions =
        context.device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.6);
    int begin_x = (int)(dimensions.Width * 0.2);

    Menu *menu = new Menu(context, imageList);
    menu->addLabel(GUI_TEXT_PAUSED, irr::core::position2d<irr::s32>
        (begin_x * 1.8, size_y));

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 4, begin_x
        + size_x, size_y * 5.5),GUI_BUTTON_CONTINUE, L"Continue the game");

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 7, begin_x
        + size_x, size_y * 8.5),GUI_BUTTON_SAVE, L"Save your Game");

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 9,
        begin_x + size_x,size_y * 10.5), GUI_BUTTON_LOAD, L"Load your Game");

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 11,
    begin_x + size_x, size_y * 12.5),GUI_BUTTON_SETTINGS,L"Open Settings Menu");

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 14,
    begin_x + size_x,size_y * 15.5),GUI_BUTTON_MAINMENU, L"Go to Main Menu");

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 16,
    begin_x + size_x,size_y * 17.5),GUI_BUTTON_QUIT, L"Exit Program");

    return menu;
}

Menu *build_game_over_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList, int winner)
{
    irr::core::dimension2d<irr::u32> dimensions =
        context.device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.6);
    int begin_x = (int)(dimensions.Width * 0.2);

    Menu *menu = new Menu(context, imageList);
    switch (winner) {
        case 1:
            menu->addLabel(GUI_TEXT_PLAYER1, irr::core::position2d<irr::s32>
                (begin_x * 1.25, size_y * 4));
            break;
        case 2:
            menu->addLabel(GUI_TEXT_PLAYER2, irr::core::position2d<irr::s32>
                (begin_x * 1.25, size_y * 4));
            break;
        case 0:
            menu->addLabel(GUI_TEXT_AI, irr::core::position2d<irr::s32>
                (begin_x * 1.6, size_y* 4));
            break;
        default:
            break;
    }

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 11,
                                              begin_x + size_x,size_y * 13),
                    GUI_BUTTON_MAINMENU, L"Go to Main Menu");

    menu->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 14,
                                              begin_x + size_x,size_y * 16),
                    GUI_BUTTON_QUIT, L"Exit Program");

    return menu;
}
