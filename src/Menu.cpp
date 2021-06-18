#include <cstddef>
#include <driverChoice.h>
#include <Floor.hpp>
#include <utility>
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

Menu::Menu(SAppContext context, const std::vector<std::pair<Buttons,
           irr::video::ITexture *>> &imageList)
{
    _device = context.device;
    _guienv = context.device->getGUIEnvironment();

    irr::gui::IGUISkin* skin = _guienv->getSkin();
    irr::gui::IGUIFont* font = _guienv->getFont("media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);
    skin->setFont(_guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
    _imageList = imageList;
}

void Menu::addLabel(int i, const irr::core::position2d<irr::s32>& pos)
{
    irr::gui::IGUIImage *elem = _guienv->addImage(_imageList[i - 100].second,
                                                  pos);
    _elementList.push_back(elem);
}

void Menu::addButton(const irr::core::rect<irr::s32>& pos, int btn_enum, const wchar_t *tooltip)
{
    irr::gui::IGUIButton *elem = _guienv->addButton(pos, nullptr, btn_enum,
                                                   nullptr, tooltip);
    elem->setImage(_imageList[btn_enum - 100].second);
    elem->setUseAlphaChannel();
    elem->setIsPushButton();
    _elementList.push_back(elem);
}

void Menu::clearGUI()
{
    for(auto const &elem: _elementList) {
        elem->remove();
    }
}
