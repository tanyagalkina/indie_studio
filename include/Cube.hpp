#include "AppContext.hpp"
#include "Floor.hpp"
#include "Error.hpp"
#include "IXML.hpp"
//                     meshPath       texturePath
static const std::pair<irr::io::path, irr::io::path>  assetPath[7] = {
    std::make_pair("media/WoodenBox.3ds", "media/textures/grass.png"), // Empty
    std::make_pair("media/WoodenBox.3ds", "media/WoodPlanks_Albedo.png"), // Box
    std::make_pair("media/WoodenBox.3ds", "media/textures/grass.png"), // Tile
    std::make_pair("media/WoodenBox.3ds", "media/textures/wall_interior_save.png"), // Wall
    std::make_pair("media/WoodenBox.3ds", "media/textures/wall_interior_save.png"), // Wall_Boss
    std::make_pair("media/WoodenBox.3ds", "media/textures/wall_interior_save.png"), // Boss
    std::make_pair("media/WoodenBox.3ds", "media/WoodPlanks_Normal.png"), // Player starting pos
};

class Cube : IXML
{
public:
    Cube(SAppContext &context, Floor::Type blockType, Coordinate cord);
    ~Cube();
    void addCollision(irr::scene::IAnimatedMeshSceneNode *body);
    std::string serialize() final;
    void deserialize(std::string xmlCode) final;

private:
    Floor::Type type;
    Coordinate coordinate;
    irr::scene::ISceneManager *smgr;
    irr::scene::IAnimatedMeshSceneNode *body;
    irr::scene::ITriangleSelector *selector;
};