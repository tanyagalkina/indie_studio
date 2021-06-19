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
#include "Audio.hpp"

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
    std::vector<irr::gui::IGUIElement *> _elemList;
public:
    NewMenuEventReceiver(SAppContext &context,
                         std::vector<irr::gui::IGUIElement *> elemList) :
                         _context(context), _elemList(elemList) {};

    void updatePlayer(int id);
    void updateMap(int id);
    virtual bool OnEvent(const irr::SEvent &event);
};

class LoadMenuEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &_context;
public:
    LoadMenuEventReceiver(SAppContext &context) : _context(context) {};

    virtual bool OnEvent(const irr::SEvent &event);
};

class SettingsMenuEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &_context;
    Audio *_sounds;
public:
    SettingsMenuEventReceiver(SAppContext &context, Audio *sounds) : _context
    (context), _sounds(sounds){}

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


class SaveMenuEventReceiver : public irr::IEventReceiver
{
private:
    SAppContext &_context;
public:
    SaveMenuEventReceiver(SAppContext &context) : _context(context){}

    virtual bool OnEvent(const irr::SEvent &event);
};



#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EVENTHANDLING_HPP
