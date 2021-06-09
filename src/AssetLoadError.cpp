/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Error.cpp
*/

#include "../include/Error.hpp"

AssetLoadError::AssetLoadError(std::string errorMessage) : _errorMessage(errorMessage){}

std::string AssetLoadError::getMessage()
{
    return _errorMessage;
}
