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

class MainMenuEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &_context;
public:
    MainMenuEventReceiver(SAppContext &context) : _context(context){}

    virtual bool OnEvent(const irr::SEvent &event);
};

class NewMenuEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &_context;
public:
    NewMenuEventReceiver(SAppContext &context) : _context(context){}

    virtual bool OnEvent(const irr::SEvent &event);
};

class LoadMenuEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &_context;
public:
    LoadMenuEventReceiver(SAppContext &context) : _context(context){}

    virtual bool OnEvent(const irr::SEvent &event);
};

class SettingsMenuEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &_context;
public:
    SettingsMenuEventReceiver(SAppContext &context) : _context(context){}

    virtual bool OnEvent(const irr::SEvent &event);
};

class PauseMenuEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &_context;
public:
    PauseMenuEventReceiver(SAppContext &context) : _context(context){}

    virtual bool OnEvent(const irr::SEvent &event);
};



#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EVENTHANDLING_HPP
