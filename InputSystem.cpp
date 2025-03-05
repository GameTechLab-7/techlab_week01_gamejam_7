#include "InputSystem.h"


InputSystem::InputSystem()
{
    for (bool& key : _keys)
    {
        key = false;
    }
}

bool InputSystem::IsPressedKey(EKeyCode key) const
{
    return _keys[static_cast<uint8_t>(key)];
}

void InputSystem::KeyDown(EKeyCode key)
{
    _keys[static_cast<uint8_t>(key)] = true;
}

void InputSystem::KeyUp(EKeyCode key)
{
    _keys[static_cast<uint8_t>(key)] = false;
}

std::vector<EKeyCode> InputSystem::GetPressedKeys() {
    std::vector<EKeyCode> ret;

    for (int i = 0; i < 256; i++) {
        if (_keys[ i ]) {
            ret.push_back(static_cast< EKeyCode >( i ));
        }
    }

    return ret;
}
void InputSystem::MouseKeyDown(FVector3 MouseDownPoint, FVector3 WindowSize){
    mouse = true; 
    MouseKeyDownPos = MouseDownPoint;
    MouseKeyDownRatioPos = FVector3(( MouseKeyDownPos.x / ( WindowSize.x / 2 ) ) - 1 , ( MouseKeyDownPos.y / ( WindowSize.y / 2 ) ) - 1 , 0);
} //MouseKeyDownPos 설정

void InputSystem::MouseKeyUp(FVector3 MouseUpPoint, FVector3 WindowSize){
    mouse = false; 
    MouseKeyUpPos = MouseUpPoint;
    MouseKeyUpRatioPos = FVector3(( MouseKeyUpPos.x / ( WindowSize.x / 2 ))-1 , ( MouseKeyUpPos.y / ( WindowSize.y / 2 ) )-1 , 0);
}

#include <unordered_map>
#include <utility>
#include <cmath>

#include "Math/FVector3.h"
#include "Enum.h"
#include "GameObject/Player.h"
#include "Manager/ObjectManager.h"
#include "Manager/GameManager.h"
#include "Scene/MainGameScene.h"

struct pair_hash {
    template <class T1 , class T2>
    std::size_t operator () (std::pair<T1 , T2> const& v) const {
        auto h1 = std::hash<T1>{}( v.first );
        auto h2 = std::hash<T2>{}( v.second );
        return h1 ^ h2;
    }
};

std::unordered_map<Direction , FVector3> DicKeyAddVector //speed는 곱해서 쓰자
{
    {Direction::Left, FVector3(-1, 0, 0)},
    {Direction::Right, FVector3(1, 0, 0)},
    {Direction::Top, FVector3(0, 1, 0)},
    {Direction::Bottom, FVector3(0, -1, 0)},
};

std::unordered_map<std::pair<EWorld , Direction> , EKeyCode, pair_hash> DicDirectionCodeByPlayer{
    {std::make_pair( EWorld::First, Direction::Left ), EKeyCode::A},
    {std::make_pair( EWorld::First, Direction::Right ), EKeyCode::D},
    {std::make_pair( EWorld::First, Direction::Top ), EKeyCode::W},
    {std::make_pair( EWorld::First, Direction::Bottom ), EKeyCode::S},
    
    {std::make_pair( EWorld::Second, Direction::Left ), EKeyCode::J},
    {std::make_pair( EWorld::Second, Direction::Right ), EKeyCode::L},
    {std::make_pair( EWorld::Second, Direction::Top ), EKeyCode::I},
    {std::make_pair( EWorld::Second, Direction::Bottom ), EKeyCode::K},
};

InputHandler::InputHandler() {

}

void InputHandler::HandlePlayerInputByWorld(EWorld World) {
    Player* player = static_cast< MainGameScene* >( GameManager::GetInstance().GetCurrentScene() )->GetPlayer(World);
    
    FVector3 NewPlayerVelocity(0 , 0 , 0);

    if (InputSystem::GetInstance().IsPressedKey(DicDirectionCodeByPlayer[std::make_pair(World, Direction::Left)])) {
        NewPlayerVelocity += DicKeyAddVector[ Direction::Left ];
    }
    if (InputSystem::GetInstance().IsPressedKey(DicDirectionCodeByPlayer[ std::make_pair(World , Direction::Right) ])) {
        NewPlayerVelocity += DicKeyAddVector[ Direction::Right ];
    }
    if (InputSystem::GetInstance().IsPressedKey(DicDirectionCodeByPlayer[ std::make_pair(World , Direction::Top) ])) {
        NewPlayerVelocity += DicKeyAddVector[ Direction::Top ];
    }
    if (InputSystem::GetInstance().IsPressedKey(DicDirectionCodeByPlayer[ std::make_pair(World , Direction::Bottom) ])) {
        NewPlayerVelocity += DicKeyAddVector[ Direction::Bottom ];
    }
    NewPlayerVelocity = NewPlayerVelocity.Normalize();

    //회전이랑 마우스클릭 구현
    if (NewPlayerVelocity.Length() > 0.001f) {
        player->SetAngle(std::atan2(NewPlayerVelocity.y , NewPlayerVelocity.x));
    }

    player->SetVelocity(NewPlayerVelocity);
}

void InputHandler::InputUpdate() {

    HandlePlayerInputByWorld(EWorld::First);
    HandlePlayerInputByWorld(EWorld::Second);

}