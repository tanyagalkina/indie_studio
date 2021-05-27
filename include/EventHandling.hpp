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

    virtual bool OnEvent(const irr::SEvent &event);
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EVENTHANDLING_HPP
