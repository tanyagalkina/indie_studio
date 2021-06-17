#include "Character.hpp"

static const int positions[4][2] = {
    {0, 0},
    {1, 0},
    {0, 1},
    {1, 1}
};

Character::Character(SAppContext &ctx, VisualMap &vmap, const int &idx)
    : context(&ctx), map(&vmap), playerIndex(idx)
{
    MOVEMENT_SPEED = 100.0f;
    currentMovementState = irr::scene::EMAT_STAND;
    extraSpeedFactor = 1.f;

    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();
    then = context->device->getTimer()->getTime();

    auto [x, z] = map->getMaxCoordinates();
    auto [multX, multZ] = positions[idx];
    int blockSize = 50;
    x = (x - 2) * blockSize * multX;
    z = (z - 2) * blockSize * multZ;

    irr::core::vector3df pos = { static_cast<float>(-250 + x), 0, static_cast<float>(250 + z)};

    initCharacter(pos);
    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body);
    this->body->setTriangleSelector(this->selector);

    map->addCollision(body);
}

Character::~Character()
{
    this->selector->drop();
}

void Character::initCharacter(irr::core::vector3df _pos)
{
    irr::scene::IAnimatedMesh *mesh;

    if ((mesh = smgr->getMesh("media/sydney.md2")) == NULL) {
        AssetLoadErrorMac("Can't load 'media/sydney.md2'");
    }
    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL) {
        SceneErrorMac("Could not add AnimatedMeshSceneNode");
    }

    this->body->setMD2Animation(currentMovementState);
    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->body->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));

    auto pos = this->body->getPosition();
    pos.X = _pos.X;
    pos.Y += 45;
    pos.Z = _pos.Z;

    this->body->setPosition(pos);
}

irr::scene::IAnimatedMeshSceneNode *Character::getBody()
{
    return this->body;
}


/* use this function to create Collision between multiple Players or monsters */
void Character::addCollision(irr::scene::IAnimatedMeshSceneNode *_body)
{
    auto *anim = smgr->createCollisionResponseAnimator(selector, _body,
            irr::core::vector3df(10, 10, 10),
            irr::core::vector3df(0, 0, 0));
    _body->addAnimator(anim);
    anim->drop();
}

bool Character::checkCollision(const irr::scene::IAnimatedMeshSceneNode *object) const
{
    return object->getTransformedBoundingBox().intersectsWithBox(this->body->getTransformedBoundingBox());
}

void Character::setExtraSpeed(irr::f32 newExtraSpeed)
{
    this->extraSpeedFactor = newExtraSpeed;
}

bool Character::isAlive() const
{
    return alive;
}

void Character::kill()
{
    alive = false;
}

void Character::revive()
{
    alive = true;
}

void Character::setFire(bool enable)
{
    fireUp = enable;
}

void Character::setUnlimitedBombs(bool enabled)
{
    unlimitedBombs = enabled;
}

void Character::changeMovementState()
{
    if (currentMovementState == irr::scene::EMAT_STAND) {
        currentMovementState = irr::scene::EMAT_RUN;
        this->body->setMD2Animation(currentMovementState);
    }
}

void Character::moveUp(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 270, 0));
    pos.Z += (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveDown(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 90, 0));
    pos.Z -= (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveRight(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 0, 0));
    pos.X += (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveLeft(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 180, 0));
    pos.X -= (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}
