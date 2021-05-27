/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** EventHandling.cpp
*/

#include "../include/EventHandling.hpp"

bool MyEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();
        irr::gui::IGUIEnvironment *env = Context.device->getGUIEnvironment();
        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_QUIT:
                        Context.device->closeDevice();
                        return true;
                    case GUI_BUTTON_NEW:
                        // create new game here
                        return true;
                    case GUI_BUTTON_LOAD:
                        // load file with old game information here
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