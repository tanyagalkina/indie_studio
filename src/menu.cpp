#include <driverChoice.h>
#include <Floor.hpp>
#include "../include/menu.hpp"
#include "AppContext.hpp"
#include "EDriverTypes.h"
#include "IGUISkin.h"
#include "VisualMap.hpp"
#include "Player.hpp"
#include "../include/Error.hpp"

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
    guienv->addStaticText(text, pos, true);
}

void Menu::addButton(const irr::core::rect<irr::s32>& pos, int btn_enum, const wchar_t
*text, const wchar_t *tooltip)
{
    guienv->addButton(pos, nullptr, btn_enum, text, tooltip);
}