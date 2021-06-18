#include <cstddef>
#include <driverChoice.h>
#include <Floor.hpp>
#include "../include/Menu.hpp"
#include "AppContext.hpp"
#include "AssetLoadError.hpp"
#include "EDriverTypes.h"
#include "IGUISkin.h"
#include "SceneError.hpp"
#include "VisualMap.hpp"
#include "Player.hpp"
#include "../include/Error.hpp"
#include "PowerUpHandler.hpp"

Menu::Menu(SAppContext context)
{
    device = context.device;
    guienv = context.device->getGUIEnvironment();

    irr::gui::IGUISkin* skin = guienv->getSkin();
    irr::gui::IGUIFont* font = guienv->getFont("media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    skin->setFont(guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
}

void Menu::addLabel(const wchar_t *text, const irr::core::rect<irr::s32>& pos)
{
    irr::gui::IGUIStaticText *elem = guienv->addStaticText(text, pos, true);
    _elementList.push_back(elem);
}

void Menu::addButton(const irr::core::rect<irr::s32>& pos, int btn_enum, const wchar_t
*text, const wchar_t *tooltip)
{
    irr::gui::IGUIButton *elem = guienv->addButton(pos, nullptr, btn_enum,
                                                   text, tooltip);
    _elementList.push_back(elem);
}

void Menu::clearGUI()
{
    for(auto const &elem: _elementList) {
        elem->remove();
    }
}
