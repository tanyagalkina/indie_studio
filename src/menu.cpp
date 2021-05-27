#include "../include/menu.hpp"
#include <irrlicht.h>
#include <cstdlib>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_SOFTWARE,
        irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false,
                                               nullptr);
    device->setWindowCaption(L"Best Bomberman");
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager *sm = device->getSceneManager();
    irr::gui::IGUIEnvironment *guienv = device->getGUIEnvironment();
    guienv->addStaticText(L"added this static", irr::core::rect<irr::s32>(10,
        10, 260, 22), true);
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