/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** help_functions.cpp
*/

#include <irrlicht.h>

void setSkinTransparancy(irr::s32 alpha, irr::gui::IGUISkin *skin)
{
    for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT; i++)
    {
        irr::video::SColor col = skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
        col.setAlpha(alpha);
        skin->setColor((irr::gui::EGUI_DEFAULT_COLOR) i, col);
    }
}