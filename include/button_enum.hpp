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
    // Main Menu
    GUI_TEXT_HEADLINE = 100,
    GUI_BUTTON_NEW,
    GUI_BUTTON_LOAD,
    GUI_BUTTON_SETTINGS,
    GUI_BUTTON_QUIT,
    GUI_BUTTON_BACK,
    GUI_BUTTON_MAINMENU,
    // Settings
    GUI_TEXT_SETTINGS,
    GUI_CHECK_MUSIC,
    GUI_CHECK_SOUND,
    // New Game
    GUI_TEXT_NEWGAME,
    GUI_RADIO_PLAYER1,
    GUI_RADIO_PLAYER2,
    GUI_TEXT_MAP,
    GUI_RADIO_SMALL,
    GUI_RADIO_MEDIUM,
    GUI_RADIO_LARGE,
    GUI_BUTTON_CREATE,
    // Load Game
    GUI_TEXT_LOADGAME,
    GUI_BUTTON_SAVE1,
    GUI_BUTTON_SAVE2,
    GUI_BUTTON_SAVE3,
    GUI_BUTTON_SAVE4,
    // Pause Game
    GUI_TEXT_PAUSED,
    GUI_BUTTON_CONTINUE,
    GUI_BUTTON_SAVE,
    //Save Game
    GUI_TEXT_SAVEGAME,
};

#define TEXTPATHSLENGTH 27

const irr::io::path textPaths[27] {
    "./media/menu/BestBomberman.png",
    "./media/menu/NewGame.png",
    "./media/menu/LoadGame.png",
    "./media/menu/Settings.png",
    "./media/menu/Quit.png",
    "./media/menu/Back.png",
    "./media/menu/MainMenu.png",
    "./media/menu/SettingsHeadline.png",
    "./media/menu/MuteMusic.png",
    "./media/menu/MuteSounds.png",
    "./media/menu/NewGameHeadline.png",
    "./media/menu/1Player.png",
    "./media/menu/2Players.png",
    "./media/menu/MapHeadline.png",
    "./media/menu/Small.png",
    "./media/menu/Medium.png",
    "./media/menu/Large.png",
    "./media/menu/CreateGame.png",
    "./media/menu/LoadGameHeadline.png",
    "./media/menu/SaveState1.png",
    "./media/menu/SaveState2.png",
    "./media/menu/SaveState3.png",
    "./media/menu/SaveState4.png",
    "./media/menu/GamePaused.png",
    "./media/menu/Continue.png",
    "./media/menu/SaveGame.png",
    "./media/menu/SaveGameHeadline.png",
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BUTTON_ENUM_HPP
