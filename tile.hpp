#ifndef TILE_HPP_INCLUDED
#define TILE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace zs
{

/** \brief enum Props */
enum Props { BLOCK , BLOCK1 , VIDE , BLOCK2};

/**Un typedef pour racourcir le tableau 2D **/
typedef std::vector<std::vector<int> > Matrice;

/**La class Tile (derivant de sf::Rectangle shape: represente un tile sur le map ;) ,il nous faut des ordis robusque :p **/
class Tile : public sf::RectangleShape
{
public:
    /**Constructeur (par defaut)**/
    Tile();
    /**Constructeur (surchargé)**/
    Tile(sf::Vector2f size,sf::Vector2f position);
    /** \brief setID
     * \param Props un enum Props
     * \return void
     */
    void setID(Props block);
    /** \brief getters du Props du tile
     * \return int
     */
    int getID();
private:
    Props m_id;
};

class TileMap : public sf::Drawable
{
public:
    /**Constructeur par defaut **/
    TileMap();
    /** \brief loadMap
     * \param string levelPath : fichier map
     * \return return true (si tout se passe bien) et false (si il y'a une erreur et affiche l'erreur dans la conssole)
     */
    bool loadMap(std::string& levelPath);
    /** \brief draw (fonction virtuelle derivé de drawable) ,celle-ci sera appelleren interne quand tu feras window.draw(
     *  En fait , elle prend rien comme parametre quand vous l'utiliserez
     * \return void
     */
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const
    {
        for(unsigned int b=0;b < m_tiles.size();b++)
        {
            states.texture = &m_texture;
            target.draw(m_tiles[b],states);
        }
    }
    /** \brief getMapSize : getteurs du nombre de tile en X et Y
     * \return sf::Vector2f
     */
    sf::Vector2f getMapSize();
    /** \brief setTileSize : getters de tile Size
     * \param un vector tile_size
     * \return sf::Vector2f
     */
    void setTileSize(sf::Vector2f tile_size);
     /** \brief getter tileSize
     * \return sf::Vector2f
     */
    sf::Vector2f getTileSize();
     /** \brief getMapPath : retourne la location du fichier Map
     * \return string
     */
    std::string getMapPath();
     /** \brief saveCurMap --> abrege par save current map : cree un fichier level.lvl du Map courant
     * \return true (si tout se passe bien) sinon false
     */
    bool saveCurMap();
     /** \brief saveCurMap (surchargé) : cree un fichier level.lvl du Map courant mais cet fois-ci tu donne le nom et l'extention
     * \param const char* nameLevelToSave : nom et extension du fichier
     * \return true (si tout se passe bien) sinon false
     */
    bool saveCurMap(const char* nameLevelToSave);
    /** \brief getMapMaximumSize : retourne la longueur et largeur map dans un vecteur
     * \return sf::Vector2f
     */
    sf::Vector2f getMapMaximumSize();
    /** \brief getMap : retourne un Matrice (si vous savez pas ce que regarde plus haut :p
     * \return Matrice
     */
    Matrice getMap();
private:
    bool save(const char* filePath);
    void fillMap();
    std::vector<zs::Tile> m_tiles;
    Matrice m_map;
    sf::Vector2f m_tiles_size;
    sf::Vector2f m_tiles_count;
    sf::Vector2f m_map_size;
    std::string m_mapPath;
    std::string tileset;
    sf::Texture m_texture;
};

}

#endif // TILE_HPP_INCLUDED
