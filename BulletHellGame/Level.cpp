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
    {
        if (!spawner->isActive)
            continue;
        
        spawner->Update(_deltaTime);

        // Check bullet collisions
        for (const auto bullet : spawner->bullets) // spawner -> player
        {
            if(bullet->CheckCollision(m_player))
                m_player->lives--;
        }

        for (const auto bullet : m_player->bullets) // player -> spawner
        {
            if (bullet->CheckCollision(spawner))
                spawner->health--;
        }
    }

    if (m_player->isActive)
        m_player->Update(_deltaTime);
}

void Level::Draw()
{
    for (int i = 0; i < (int)m_spawners.size(); i++)
    {
        if (!m_spawners[i]->isActive)
        {
            delete m_spawners[i];
            
            m_spawners.erase(m_spawners.begin() + i);
            
            continue;
        }
        
        m_spawners[i]->Draw();
    }

    if (m_player->isActive)
        m_player->Draw();
}

void Level::LoadLevel(const int _levelNumber)
{
    m_sequences.clear();
    
    std::fstream levelFile;

    std::string filePath = "./Levels";

    _mkdir(filePath.c_str());

    filePath += "/" + std::to_string(_levelNumber) + ".txt";
    
    levelFile.open(filePath, std::ios::in);
    
    if (levelFile.is_open())
    {
        std::string sequence;
        
        while(getline(levelFile, sequence))
        {
            if (sequence.front() == '#')
                continue;
            
            std::string::iterator unusedReturnType = std::remove(sequence.begin(), sequence.end(), ' ');
            m_sequences.push_back(sequence);
        }

        levelFile.close();
    }
}

void Level::InitSpawners()
{
    for (const auto spawner : m_spawners)
        delete spawner;

    m_spawners.clear();

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
        
        m_spawners.push_back(new Spawner(renderer2D, *application));
        m_spawners.back()->SetSequence(splitSequence);
    }
}