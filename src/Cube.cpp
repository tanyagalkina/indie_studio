
#include "Cube.hpp"

Cube::Cube(SAppContext &context, Floor::Type  blockType, Coordinate cord)
    : type(blockType), coordinate(cord)
{
    irr::scene::IAnimatedMesh *mesh;
    irr::video::IVideoDriver *driver = context.device->getVideoDriver();

    this->smgr = context.device->getSceneManager();

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
    this->body->setPosition(irr::core::vector3df(-300 + x * cubeSize, 30, 300 + y * cubeSize));
}

void Cube::addCollision(irr::scene::IAnimatedMeshSceneNode *body)
{
    auto *anim = smgr->createCollisionResponseAnimator(metaSelector, body,
            irr::core::vector3df(10, 10, 10),
            irr::core::vector3df(0.f, 0.f, 0.f));
    body->addAnimator(anim);
    anim->drop();
}
