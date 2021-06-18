/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** menu.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MENU_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MENU_HPP

#include "EventHandling.hpp"
#include "vector"

class Menu
{
public:
    Menu(SAppContext context);
    ~Menu() = default;
    void addLabel(const wchar_t *text, const irr::core::rect<irr::s32>& pos);
    void addButton(const irr::core::rect<irr::s32>& pos, int btn_enum, const wchar_t
    *text, const wchar_t *tooltip);
    void clearGUI();

    irr::IrrlichtDevice *device;
    irr::gui::IGUIEnvironment *guienv;
    std::vector<irr::gui::IGUIElement *> _elementList;
};

Menu *build_main_menu(SAppContext context);
Menu *build_new_menu(SAppContext context);


#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MENU_HPP
