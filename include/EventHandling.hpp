/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** EventHandling.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EVENTHANDLING_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EVENTHANDLING_HPP

#include "AppContext.hpp"
#include "button_enum.hpp"

class MyEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &Context;
public:
    MyEventReceiver(SAppContext &context) : Context(context){}

    virtual bool OnEvent(const irr::SEvent &event)
    {
        if (event.EventType == irr::EET_GUI_EVENT)
        {
            irr::s32 id = event.GUIEvent.Caller->getID();
            irr::gui::IGUIEnvironment *env = Context
                .device->getGUIEnvironment();
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

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EVENTHANDLING_HPP
