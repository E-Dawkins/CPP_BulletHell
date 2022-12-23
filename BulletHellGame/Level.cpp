#include "Level.h"

#include <fstream>
#include <direct.h>
#include <iostream>

#include "Spawner.h"

void Level::Start()
{
    m_player = new Player(renderer2D, *application);

    LoadLevel(1);
    InitSpawners();
}

void Level::Update(const float _deltaTime)
{
    for (const auto spawner : m_spawners)
        spawner->Update(_deltaTime);

    m_player->Update(_deltaTime);
}

void Level::Draw()
{
    for (const auto spawner : m_spawners)
        spawner->Draw();

    m_player->Draw();
}

void Level::LoadLevel(const int _levelNumber)
{
    std::fstream levelFile;

    std::string filePath = "./Levels";

    _mkdir(filePath.c_str());

    filePath += "/" + std::to_string(_levelNumber) + ".txt";
    
    levelFile.open(filePath, std::ios::in);
    
    if (levelFile.is_open())
    {
        std::string sequence;
        
        while(getline(levelFile, sequence))
            m_sequences.push_back(sequence);

        levelFile.close();
    }
}

void Level::InitSpawners()
{
    for (std::string sequence : m_sequences)
    {
        std::vector<std::string> splitSequence;
        std::string command;

        for (std::string::iterator iter = sequence.begin(); iter != sequence.end(); ++iter)
        {
            if (*iter != ',' && *iter != ' ')
                command += *iter;

            if (*iter == ',' || iter == sequence.end() - 1)
            {
                if (!command.empty())
                    splitSequence.push_back(command);
                
                command = "";
            }
        }
        
        m_spawners.push_back(new Spawner(renderer2D, *application, m_player));
        m_spawners.back()->SetSequence(splitSequence);
    }
}