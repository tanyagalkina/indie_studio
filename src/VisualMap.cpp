#include "../include/VisualMap.hpp"
#include "IAnimatedMesh.h"
#include "menu.hpp"

void VisualMap::display()
{
    this->smgr->drawAll();
}

irr::scene::IAnimatedMeshSceneNode *VisualMap::createCube(int i, int j)
{
    irr::scene::IAnimatedMeshSceneNode *cube;
    irr::scene::IAnimatedMesh *mesh;
    irr::video::ITexture *texture;

    if ((mesh = this->smgr->getMesh("media/WoodenBox.3ds")) == NULL) {
        // @todo throw AssetLoadError("Can't load 'media/WoodenBox.3ds'");
    }

    if ((texture = this->driver->getTexture("media/WoodPlanks_Albedo.png")) == NULL) {
        // @todo throw AssetLoadError("Can't load 'media/WoodPlanks_Albedo.png'");
    }

    cube = this->smgr->addAnimatedMeshSceneNode(mesh);

    // @todo change the pos according to i and j
    int size = 50;
    cube->setPosition(irr::core::vector3df(-300 + i * size, 30, 300));
    cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    cube->setScale(irr::core::vector3df(50, 50, 50));
    cube->setMaterialTexture(0, texture);

    /* @todo add collider for the cubes here */
    return cube;
}

void VisualMap::initializeMap(MyList<std::string> &map)
{
    int rows = map.size();
    int cols = map[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            this->blocks.push_back(createCube(i, j));
        }
    }
}

void VisualMap::addCollision(irr::scene::IAnimatedMeshSceneNode *body)
{
    auto *anim = smgr->createCollisionResponseAnimator(metaSelector, body,
            irr::core::vector3df(10, 10, 10),
            irr::core::vector3df(0.f, 0.f, 0.f));
    body->addAnimator(anim);
    anim->drop();
}

VisualMap::VisualMap(SAppContext &ctx, MyList<std::string> &map)
    : context(&ctx)
{
    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();

    if (!this->smgr->loadScene("media/map.irr")) {
        //@todo throw AssetLoadError("Can't load 'media/map.irr'")
    }

    this->smgr->addCameraSceneNode(NULL, irr::core::vector3df(0, 400, -200),
            irr::core::vector3df(0, 0, -50));

    initializeMap(map);

    irr::core::array<irr::scene::ISceneNode *>	walls;
    smgr->getSceneNodesFromType(irr::scene::ESNT_CUBE, walls);
    metaSelector = smgr->createMetaTriangleSelector();

    for (int i = 0; i < walls.size(); i++) {
        auto selector = smgr->createTriangleSelectorFromBoundingBox(walls[i]);
        metaSelector->addTriangleSelector(selector);
        selector->drop();
    }
}
