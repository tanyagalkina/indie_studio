#include <driverChoice.h>
#include <Floor.hpp>
#include "../include/menu.hpp"
#include "AppContext.hpp"
#include "EDriverTypes.h"
#include "IGUISkin.h"
#include "VisualMap.hpp"
#include "Player.hpp"
#include "../include/Error.hpp"
#include "SpeedUp.hpp"

irr::gui::IGUIEnvironment *editGui(irr::gui::IGUIEnvironment *guienv, irr::IrrlichtDevice *device)
{
    irr::core::dimension2d<irr::u32> dimensions = device->getVideoDriver()->getScreenSize();
    int size_y = (int)(dimensions.Height * 0.05);
    int size_x = (int)(dimensions.Width * 0.8);
    int begin_x = (int)(dimensions.Width * 0.1);

    irr::gui::IGUISkin* skin = guienv->getSkin();
    irr::gui::IGUIFont* font = guienv->getFont("media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);
    //font->setKerningHeight(40);
    //font->setKerningWidth(40);

    skin->setFont(guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);


    guienv->addStaticText(L"BOMBERMAN", irr::core::rect<irr::s32>(begin_x,
                     size_y, begin_x + size_x, size_y * 6), true);
    guienv->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 7, begin_x + size_x,
        size_y * 10), 0, GUI_BUTTON_NEW, L"NEW", L"Create New Game");
    guienv->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 11, begin_x + size_x,
        size_y * 14), 0, GUI_BUTTON_LOAD, L"LOAD", L"Load Previous Game");
    guienv->addButton(irr::core::rect<irr::s32>(begin_x, size_y * 15, begin_x + size_x,
        size_y * 18), 0, GUI_BUTTON_QUIT, L"QUIT", L"Exit Program");
//    guienv->addStaticText(L"Logging ListBox:", irr::core::rect<irr::s32>(50,
//                                                                         110, 250, 130), true);
//    guienv->addEditBox(L"Editable Text",
//                       irr::core::rect<irr::s32>(350, 80, 550, 100));
    return guienv;
}

SAppContext createContext()
{
    irr::video::E_DRIVER_TYPE driver_type = irr::driverChoiceConsole();
    irr::IrrlichtDevice *device = irr::createDevice(driver_type,
        irr::core::dimension2d<irr::u32>(640, 480),
            16, false, false, false, nullptr);
    device->setWindowCaption(L"Best Bomberman");
    device->setResizable(true);
    irr::gui::IGUIEnvironment *guienv = device->getGUIEnvironment();
    guienv = editGui(guienv, device);

//    irr::gui::IGUISkin *skin = guienv->getSkin();
//    skin->setFont(guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
//    irr::gui::IGUIListBox *listbox = guienv->addListBox
//        (irr::core::rect<irr::s32>(50, 140, 250, 210));

    SAppContext context;
    context.device = device;
    context.counter = 0;
//    context.listbox = listbox;
    return context;
}

char get_char(Floor::Type teip)
{
    switch (teip)
    {
        case (Floor::Type::WALL):
            return '#';
        case (Floor:: Type::BOX):
            return 'B';
        case (Floor:: Type::EMPTY):
            return ' ';
        case (Floor::Type::TELEPORT):
            return 'X';
        case (Floor::Type::PLAYER):
            return 'P';

        default:
            return '.';

    }
}

void show_template(MyList<std::pair<Floor::Type, Coordinate>> mapTemplate)
{
    for (int j = 0; j < 40; ++j) {
        for (int i = 0; i < 40; ++i) {
            for (int k = 0; k < mapTemplate.size(); k++) {
                if (mapTemplate[k].second.y == j && mapTemplate[k].second.x == i) {
                    char ch = get_char(mapTemplate[k].first);
                    printf("%c", ch);
                }
            }
        }
        printf("\n");
    }
}

int main()
{
//    try {
//        AssetLoadErrorMac("shit");
//    }
//    catch (AssetLoadError &er)
//    {
//        std::cout << er.getMessage();
//        exit(0);
//    }
    SAppContext context = createContext();
    MyEventReceiver receiver(context);

    context.device->setEventReceiver(&receiver);
    context.state = GameState::Menu;
    irr::video::IVideoDriver *driver = context.device->getVideoDriver();
    irr::gui::IGUIEnvironment *guienv = context.device->getGUIEnvironment();

    ///_level, _nb_players, _width, _height
    Floor floor(1, 1, 30, 11);
    MyList<std::pair<Floor::Type, Coordinate>> mapTemplate = floor.getTemplate();
    ///show_template(mapTemplate);

    while (context.device->run() && context.state == GameState::Menu)
    {
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        guienv->drawAll();
        context.device->getSceneManager()->drawAll();
        driver->endScene();
    }

    VisualMap map(context, mapTemplate);
    Player player(context, map);
    SpeedUp speed(context);
    speed.setPosition(55, 55);
    GameEventReceiver gameReceiver;
    context.device->setEventReceiver(&gameReceiver);

    while (context.device->run()) {
        player.update(gameReceiver);
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        map.display();
        if (speed.checkExisting())
            speed.HandleCollision(player);
        else
            break;
        driver->endScene();
    }
    context.device->drop();
    return (0);
}
