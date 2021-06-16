/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** SerializeHelper.cpp
*/

#include "SerializeHelper.hpp"
#include "iostream"

void SerializeHelper::beginKey(const std::string& key)
{
    for (int i = 0; i < tabs; i++)
        xmlCode << "\t";
    xmlCode << "<" << key << ">" << std::endl;
    tabs++;
}

void SerializeHelper::endKey(const std::string& key)
{
    tabs--;
    for (int i = 0; i < tabs; i++)
        xmlCode << "\t";
    xmlCode << "</" << key << ">" << std::endl;
}

void SerializeHelper::insertValue(const std::string& value)
{
    for (int i = 0; i < tabs; i++)
        xmlCode << "\t";
    xmlCode << value << std::endl;
}

std::string SerializeHelper::getXML()
{
    return xmlCode.str();
}

void SerializeHelper::addKeyValue(const std::string &key, const std::string &value)
{
    beginKey(key);
    insertValue(value);
    endKey(key);
}

std::string SerializeHelper::FindKeyValue(const std::string& xml, const std::string &key)
{
    std::string search = "<" + key + ">";
    std::stringstream code(xml);
    std::string line = "somethingThatShouldTest";
    std::string found;
    std::string before;
    while (line != search && line != before)
    {
        before  = line;
        code >> line;
    }
    if (before != line)
        code >> found;
    else
        throw std::runtime_error("Key not found");
    return found;
}

std::string SerializeHelper::GetNextKey()
{
    std::stringstream xml;
    std::string key;
    std::string line;
    std::string before;
    std::string check;
    getline(xmlCode, line);
    std::stringstream tmp1(line);
    tmp1 >> key;
    xml << line << std::endl;
    key = key.substr(1, key.length() - 2);
    std::string search = "</" + key + ">";

    while (check != search && getline(xmlCode, line))
    {
        before  = line;
        std::stringstream tmp(line);
        tmp >> check;
        xml << line << std::endl;
    }
    return xml.str();
}

void SerializeHelper::addXML(const std::string& xml)
{
    std::string line;
    std::stringstream ss(xml);
    while (getline(ss, line))
    {
        for (int i = 0; i < tabs; i++)
            xmlCode << "\t";
        xmlCode << line << std::endl;
    }
}
