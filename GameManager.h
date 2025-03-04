#pragma once

#include <cstdint>
#include "Singleton.h"

/**
 * GameState
 */
enum class EGameState : uint8_t
{
    None,      // 기본값
    Init,      // 게임을 처음 실행했을 때
    MainMenu,  // 메인메뉴
    MainGame,  // 게임플레이중
    Result,    // 결과 화면
};


/**
 * 
 */
class GameManager : public Singleton<GameManager>
{
private:
    EGameState CurrentState = EGameState::Init;
    EGameState PrevState = EGameState::None;

public:
    /** 메인루프에서 콜. 스테이트 바뀌면 로직 실행 */
    void HandleState();

    void SetGameState(EGameState inState);
    EGameState GetGameState() const;
};
