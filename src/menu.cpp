#include "../include/menu.hpp"
#include <irrlicht.h>
#include <cstdlib>
#include <iostream>
#include <driverChoice.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

typedef struct
{
    IrrlichtDevice *device;
    s32 counter;
    IGUIListBox *listbox;
} SAppContext;

enum {
    GUI_BUTTON1 = 101
};

void setSkinTransparancy(s32 alpha, irr::gui::IGUISkin *skin)
{
    for (s32 i = 0; i < irr::gui::EGDC_COUNT; i++)
    {
        irr::video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR) i);
        col.setAlpha(alpha);
        skin->setColor((EGUI_DEFAULT_COLOR) i, col);
    }
}

class MyEventReceiver : public IEventReceiver
{
private:
    SAppContext &Context;
public:
    MyEventReceiver(SAppContext &context) : Context(context){}

    virtual bool OnEvent(const SEvent &event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment *env = Context.device->getGUIEnvironment();
            switch (event.GUIEvent.EventType)
            {
                case irr::gui::EGET_SCROLL_BAR_CHANGED:
                    break;
                case irr::gui::EGET_BUTTON_CLICKED:
                    switch (id)
                    {
                        case GUI_BUTTON1:
                            Context.device->closeDevice();
                            return true;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        return false;
    }
};

int main()
{
    video::E_DRIVER_TYPE driver_type = driverChoiceConsole();
    irr::IrrlichtDevice *device = irr::createDevice(driver_type,
        irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false,
                                               nullptr);
    device->setWindowCaption(L"Best Bomberman");
    device->setResizable(true);
    irr::video::IVideoDriver *driver = device->getVideoDriver();
//    irr::scene::ISceneManager *sm = device->getSceneManager();
    irr::gui::IGUIEnvironment *guienv = device->getGUIEnvironment();

    IGUISkin *skin = guienv->getSkin();
    skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);
    guienv->addButton(irr::core::rect<s32>(10, 240, 110, 272), 0,
        GUI_BUTTON1, L"QUIT", L"Exits Program");

    guienv->addStaticText(L"Logging ListBox:", irr::core::rect<irr::s32>(50,
        110, 250, 130), true);
    IGUIListBox *listbox = guienv->addListBox(irr::core::rect<irr::s32>(50,
        140, 250, 210));
    guienv->addEditBox(L"Editable Text", irr::core::rect<irr::s32>(350, 80,
        550, 100));

    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.listbox = listbox;

    MyEventReceiver receiver(context);

    device->setEventReceiver(&receiver);
//    IAnimatedMesh *mesh = sm->getMesh("")
    while (device->run())
    {
        driver->beginScene(true, true, SColor(255, 100, 101, 140));
//        sm->drawAll();
        guienv->drawAll();
        driver->endScene();
    }
    device->drop();
    return (0);
}