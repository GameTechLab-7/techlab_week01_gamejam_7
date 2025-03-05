#include "GameObject/Bullet/Bullet.h"


Bullet::Bullet(EWorld selectedWorld) : CircleObject(selectedWorld)
{
    Texture->SetPrimitiveType(EObjectType::Bullet);
}
