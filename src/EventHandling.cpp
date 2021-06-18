/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** EventHandling.cpp
*/

#include "../include/EventHandling.hpp"

bool MainMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_QUIT:
                        _context.device->closeDevice();
                        return true;
                    case GUI_BUTTON_NEW:
                        _context.state = GameState::New;
                        return true;
                    case GUI_BUTTON_LOAD:
                        _context.state = GameState::Load;
                        return true;
                    case GUI_BUTTON_SETTINGS:
                        _context.state = GameState::Settings;
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

bool NewMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_BACK:
                        _context.state = GameState::Menu;
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

bool LoadMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_BACK:
                        _context.state = GameState::Menu;
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

bool SettingsMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_BACK:
                        _context.state = GameState::Menu;
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

bool PauseMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_BACK:
                        _context.state = GameState::Menu;
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
