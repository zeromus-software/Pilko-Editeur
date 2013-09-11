zs::Editeur::Editeur()
{
}

void zs::Editeur::run()
{
    int currentObjet = zs::BLOCK;
    string level = "level.lvl";
    if(!m_editorMap.loadMap(level))
    {
        exit(EXIT_FAILURE);
    }
    m_window.create(sf::VideoMode(m_editorMap.getMapMaximumSize().x,m_editorMap.getMapMaximumSize().y,32),"Editeur");

    /**Creation d'un nouveau Map pour appliquer les changements**/

    sf::Sprite tile;
    sf::Texture texture;
    if(!texture.loadFromFile("tileset.bmp"))
    {
        cout << "Failed to load tileset" << endl;
        exit(EXIT_FAILURE);
    }
    tile.setTexture(texture);

    unsigned int a = m_editorMap.getMapSize().x , b = m_editorMap.getMapSize().y;
    int map2apply[b][a];
    for(unsigned int i=0;i < b;i++)
    {
        for(unsigned int j=0;j < a;j++)
        {
            map2apply[i][j] = m_editorMap.getMap()[i][j];
        }
    }

    /**Fin**/

    m_window.setFramerateLimit(60);

    while(m_window.isOpen())
{
        while(m_window.pollEvent(m_even))
        {
            switch(m_even.type)
            {
            case sf::Event::Closed:
                m_window.close();
            break;
            case sf::Event::KeyPressed:
                switch(m_even.key.code)
                {
                case sf::Keyboard::Num1:
                    currentObjet = zs::BLOCK;
                break;
                case sf::Keyboard::Num2:
                    currentObjet = zs::BLOCK1;
                break;
                case sf::Keyboard::Num3:
                    currentObjet = zs::BLOCK2;
                break;
                default:
                break;
                }
            break;
            default:
            break;
            }
        }

    /**Calcule du tile courant **/
    sf::Vector2i posMouse = sf::Mouse::getPosition(m_window);
    system("cls");
    unsigned int x = m_editorMap.getTileSize().x, y = m_editorMap.getTileSize().y;
    unsigned int tileX = posMouse.x/x ,tileY = posMouse.y/y;
    cout << "Map[" << tileY << "]" << "[" << tileX << "]";
    /**Fin**/

    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if(tileY > 10000 || tileX > 10000)
        {
            system("cls");
            cout << "Map size 'Reached' !" << endl;
        }
        else{
            map2apply[tileY][tileX] = zs::VIDE;
        }
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(tileY > 10000 || tileX > 10000)
        {
            system("cls");
            cout << "Map size 'Reached' !" << endl;
        }
        else{
            map2apply[tileY][tileX] = currentObjet;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        ofstream open_file("EditeurMap.txt",ios::out|ios::trunc);

    if(open_file.is_open())
    {
        open_file << m_editorMap.getTileSize().x << " " << m_editorMap.getTileSize().y << endl ;
        open_file << m_editorMap.getMapSize().x << " " << m_editorMap.getMapSize().y << endl;
        open_file << "tileset.bmp" << endl;
        for(int i=0;i < m_editorMap.getMapSize().y;i++)
        {
            for(int j=0;j < m_editorMap.getMapSize().x;j++)
            {
                open_file << map2apply[i][j] << " ";
            }
            open_file << endl;
        }
    open_file.close();
    }
    system("cls");
    cout << "Map Saved !" << endl;
    }

    for(unsigned int i=0;i < b;i++)
    {
        for(unsigned int j=0;j < a;j++)
        {
            tile.setPosition(j*x,i*y);
            tile.setTextureRect(sf::IntRect(map2apply[i][j]*x,map2apply[i][j]*y,x,y));
            m_window.draw(tile);
        }
    }

    m_window.display();
    m_window.clear();
}
}
