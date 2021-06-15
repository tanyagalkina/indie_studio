#include "Cube.hpp"
#include "Floor.hpp"
#include <sys/select.h>

Cube::Cube(SAppContext &context, Floor::Type  blockType, Coordinate cord)
    : type(blockType), coordinate(cord)
{
    irr::scene::IAnimatedMesh *mesh;
    irr::video::IVideoDriver *driver = context.device->getVideoDriver();

    this->smgr = context.device->getSceneManager();

    if (static_cast<int>(type) > 6)
        type = Floor::Type::WALL;

    auto [meshPath, texturePath] = assetPath[static_cast<int>(type)];
    auto [x, y] = cord;

    if ((mesh = smgr->getMesh(meshPath)) == NULL)
        AssetLoadErrorMac("Can't get mesh for block creation");
    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL)
        SceneErrorMac("Could not add AnimatedMeshSceneNode");

    int cubeSize = 50;
    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->body->setMaterialTexture(0, driver->getTexture(texturePath));
    this->body->setScale(irr::core::vector3df(cubeSize));

    bool isGroundLevel = type == Floor::Type::TILE || type == Floor::Type::EMPTY || type == Floor::Type::PLAYER;
    if (isGroundLevel)
        this->body->setPosition(irr::core::vector3df(-300 + x * cubeSize, -10, 300 - y * cubeSize));
    else
        this->body->setPosition(irr::core::vector3df(-300 + x * cubeSize, 30, 300 - y * cubeSize));

    selector = smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body);
    this->body->setTriangleSelector(selector);
}

void Cube::addCollision(irr::scene::IAnimatedMeshSceneNode *_body)
{
    auto anim = smgr->createCollisionResponseAnimator(selector, _body,
            irr::core::vector3df(10),
            irr::core::vector3df(0));
    _body->addAnimator(anim);
    anim->drop();
}

Cube::~Cube()
{
    selector->drop();
}
