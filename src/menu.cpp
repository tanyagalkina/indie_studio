#include <driverChoice.h>
#include "../include/menu.hpp"

irr::gui::IGUIEnvironment *editGui(irr::gui::IGUIEnvironment *guienv)
{
    guienv->addButton(irr::core::rect<irr::s32>(10, 240, 110, 272), 0,
                      GUI_BUTTON1, L"QUIT", L"Exits Program");
    guienv->addStaticText(L"Logging ListBox:", irr::core::rect<irr::s32>(50,
                                                                         110, 250, 130), true);
    guienv->addEditBox(L"Editable Text",
                       irr::core::rect<irr::s32>(350, 80, 550, 100));
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
    guienv = editGui(guienv);

    irr::gui::IGUISkin *skin = guienv->getSkin();
    skin->setFont(guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
    irr::gui::IGUIListBox *listbox = guienv->addListBox
        (irr::core::rect<irr::s32>(50, 140, 250, 210));

    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.listbox = listbox;
    return context;
}

int main()
{
    SAppContext context = createContext();
    MyEventReceiver receiver(context);

    context.device->setEventReceiver(&receiver);
    irr::video::IVideoDriver *driver = context.device->getVideoDriver();
    irr::gui::IGUIEnvironment *guienv = context.device->getGUIEnvironment();
    while (context.device->run())
    {
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        guienv->drawAll();
        driver->endScene();
    }
    context.device->drop();
    return (0);
}