#ifndef EDITEUR_H_INCLUDED
#define EDITEUR_H_INCLUDED

#include "tile.hpp"
#include <iostream>

namespace zs
{
class Editeur
{
public:
    /**Constructeur par defaut **/
    Editeur();
    /** \brief affiche le map (c'est là que tout se passe =) )
     * \return void
     */
    void run();
private:
    zs::TileMap m_editorMap;
    sf::RenderWindow m_window;
    sf::Event m_even;
};
}

#endif // EDITEUR_H_INCLUDED
