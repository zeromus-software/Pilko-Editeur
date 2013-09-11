#include "tile.hpp"
#include <fstream>
#include <iostream>

using namespace std;

/********** Class Tile ***********/

zs::Tile::Tile() : sf::RectangleShape()
{
    m_id = VIDE;
    this->setSize(sf::Vector2f(32,32));
}

void zs::Tile::setID(zs::Props block)
{
    m_id = block;
}

int zs::Tile::getID()
{
    return m_id;
}

/********* Class TileMap *********/

zs::TileMap::TileMap() : sf::Drawable()
{
    m_tiles_size = sf::Vector2f(32,32);
}

bool zs::TileMap::loadMap(std::string& levelPath)
{
    m_mapPath = levelPath;

    ifstream file_map(m_mapPath);

    if(file_map.is_open())
    {
        file_map >> m_tiles_size.x >> m_tiles_size.y;

        file_map >> m_tiles_count.x >> m_tiles_count.y;

        file_map >> tileset;

        if(!m_texture.loadFromFile(tileset))
        {
            cout << "Failed to load tileset '" << tileset << "'" << endl;
            system("pause");
            return false;
        }

        for(int i=0;i < m_tiles_count.y;i++)
        {
        vector<int> m;
         m_map.push_back(m);
            for(int j=0;j < m_tiles_count.x;j++)
            {
                int a;
                file_map >> a;
                m_map[i].push_back(a);
                if(m_tiles_count.x > 39)
                {
                    cout << "Maximum Map Size(39*21 tiles) 'Reached' : " << m_tiles_count.x << "*" << m_tiles_count.y << " tiles in '" << m_mapPath << "'" << endl;
                    system("pause");
                    return false;
                } else if(m_tiles_count.y > 21) {
                    cout << "Maximum Map Size(39*21 tiles) 'Reached' : " << m_tiles_count.x << "*" << m_tiles_count.y << " tiles in '" << m_mapPath << "'" << endl;
                    system("pause");
                    return false;
                }
            }
        }

    file_map.close();

    } else {
        cout << "Failed to load Map : '" << file_map << "'" << endl;
        system("pause");
        return false;
    }

    m_map_size.x = m_tiles_size.x * m_tiles_count.x;
    m_map_size.y = m_tiles_size.y * m_tiles_count.y;

    fillMap();

    return true;
}

void zs::TileMap::fillMap()
{
    for(int i=0;i < m_tiles_count.y;i++)
        {
            for(int j=0;j < m_tiles_count.x;j++)
            {
                zs::Tile tile;
                tile.setSize(m_tiles_size);
                tile.setPosition(j*m_tiles_size.x,i*m_tiles_size.y);
                if(m_map[i][j] != 2)
                {
                    tile.setID(zs::Props::BLOCK);
                }
                tile.setTexture(&m_texture);
                tile.setTextureRect(sf::IntRect(m_map[i][j]*m_tiles_size.x,m_map[i][j]*m_tiles_size.y,m_tiles_size.x,m_tiles_size.y));
                m_tiles.push_back(tile);
            }
        }
}

bool zs::TileMap::save(const char* filePath)
{
    ofstream data(filePath,ios::out | ios::trunc);

    if(data.is_open())
    {
        data << m_tiles_size.x << " " << m_tiles_size.y << endl;
        data << m_tiles_count.x << " " << m_tiles_count.y << endl;
        data << tileset << endl;
        for(int i=0;i < m_tiles_count.y;i++)
        {
            for(int j=0;j < m_tiles_count.x;j++)
            {
                data << m_map[i][j] << " ";
            }
            data << endl;
        }

    } else {
        cout << "Failed to save '" << filePath << "'" << endl;
        system("pause");
        return false;
    }

    return true;
}

bool zs::TileMap::saveCurMap()
{
    if(save("level.lvl"))
    {
        return true;
    } else {
        return false;
    }

    return true;
}

bool zs::TileMap::saveCurMap(const char* nameLevelToSave)
{
    if(save(nameLevelToSave))
    {
        return true;
    } else {
        return false;
    }

    return true;
}

zs::Matrice zs::TileMap::getMap()
{
    return m_map;
}

sf::Vector2f zs::TileMap::getMapMaximumSize()
{
    return m_map_size;
}

sf::Vector2f zs::TileMap::getMapSize()
{
    return m_tiles_count;
}

sf::Vector2f zs::TileMap::getTileSize()
{
    return m_tiles_size;
}

string zs::TileMap::getMapPath()
{
    return m_mapPath;
}
