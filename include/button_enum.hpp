/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** button_enum.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BUTTON_ENUM_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BUTTON_ENUM_HPP

#include "irrlicht.h"

enum Buttons {
    GUI_TEXT_HEADLINE = 100,
    GUI_BUTTON_NEW,
    GUI_BUTTON_LOAD,
    GUI_BUTTON_SETTINGS,
    GUI_BUTTON_QUIT,
    GUI_BUTTON_BACK,
    GUI_BUTTON_MAINMENU,
};

#define TEXTPATHSLENGTH 7

const irr::io::path textPaths[7] {
    "./media/menu/Best Bomberman.png",
    "./media/menu/New Game.png",
    "./media/menu/Load Game.png",
    "./media/menu/Settings.png",
    "./media/menu/Quit.png",
    "./media/menu/Back.png",
    "./media/menu/Main Menu.png",
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BUTTON_ENUM_HPP
