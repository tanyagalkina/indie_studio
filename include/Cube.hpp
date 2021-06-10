#include "AppContext.hpp"
#include "Floor.hpp"
#include "Error.hpp"

//                     meshPath       texturePath
static const std::pair<irr::io::path, irr::io::path>  assetPath[4] = {
    std::make_pair("media/WoodenBox.3ds", "media/textures/grass.png"), // Empty
    std::make_pair("media/WoodenBox.3ds", "media/WoodPlanks_Albedo.png"), // Box
    std::make_pair("media/WoodenBox.3ds", "media/textures/grass.png"), // Tile
    std::make_pair("media/WoodenBox.3ds", "media/textures/wall_interior_save.png"), // Wall
    // @todo maybe add something for the outside walls ??
};

class Cube
{
public:
    Cube(SAppContext &context, Floor::Type  blockType, Coordinate cord);
    ~Cube();
    void addCollision(irr::scene::IAnimatedMeshSceneNode *body);

private:
    Floor::Type type;
    Coordinate coordinate;
    irr::scene::ISceneManager *smgr;
    irr::scene::IAnimatedMeshSceneNode *body;
    irr::scene::ITriangleSelector *selector;
};
