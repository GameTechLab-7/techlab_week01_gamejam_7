﻿#pragma once
#include <cstdint>
#include "AbstractClass/Singleton.h"
#include <vector>
#include "Enum.h"
#include "Math/FVector3.h"

/**
 * 윈도우 키 코드 열거형
 * @note https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */
enum class EKeyCode : uint8_t
{
    Backspace = 0x08,
    Tab = 0x09,
    Enter = 0x0D,
    Shift = 0x10,
    Ctrl = 0x11,
    Control = 0x11,
    Alt = 0x12,
    Pause = 0x13,
    CapsLock = 0x14,
    Esc = 0x1B,
    Escape = 0x1B,
    Space = 0x20,
    PageUp = 0x21,
    PageDown = 0x22,
    End = 0x23,
    Home = 0x24,
    Left = 0x25,
    Up = 0x26,
    Right = 0x27,
    Down = 0x28,
    SnapShot = 0x2C,
    PrintScreen = 0x2C,
    Insert = 0x2D,
    Delete = 0x2E,
    _0 = 0x30,
    _1 = 0x31,
    _2 = 0x32,
    _3 = 0x33,
    _4 = 0x34,
    _5 = 0x35,
    _6 = 0x36,
    _7 = 0x37,
    _8 = 0x38,
    _9 = 0x39,
    A = 0x41,
    B = 0x42,
    C = 0x43,
    D = 0x44,
    E = 0x45,
    F = 0x46,
    G = 0x47,
    H = 0x48,
    I = 0x49,
    J = 0x4A,
    K = 0x4B,
    L = 0x4C,
    M = 0x4D,
    N = 0x4E,
    O = 0x4F,
    P = 0x50,
    Q = 0x51,
    R = 0x52,
    S = 0x53,
    T = 0x54,
    U = 0x55,
    V = 0x56,
    W = 0x57,
    X = 0x58,
    Y = 0x59,
    Z = 0x5A,
    Num0 = 0x60,
    Num1 = 0x61,
    Num2 = 0x62,
    Num3 = 0x63,
    Num4 = 0x64,
    Num5 = 0x65,
    Num6 = 0x66,
    Num7 = 0x67,
    Num8 = 0x68,
    Num9 = 0x69,
    NumMul = 0x6A,
    NumAdd = 0x6B,
    NumSub = 0x6D,
    NumDot = 0x6E,
    NumDiv = 0x6F,
    F1 = 0x70,
    F2 = 0x71,
    F3 = 0x72,
    F4 = 0x73,
    F5 = 0x74,
    F6 = 0x75,
    F7 = 0x76,
    F8 = 0x77,
    F9 = 0x78,
    F10 = 0x79,
    F11 = 0x7A,
    F12 = 0x7B,
    F13 = 0x7C,
    F14 = 0x7D,
    F15 = 0x7E,
    F16 = 0x7F,
    F17 = 0x80,
    F18 = 0x81,
    F19 = 0x82,
    F20 = 0x83,
    F21 = 0x84,
    F22 = 0x85,
    F23 = 0x86,
    F24 = 0x87,
    NumLock = 0x90,
    ScrollLock = 0x91,
    LShift = 0xA0,
    RShift = 0xA1,
    LControl = 0xA2,
    RControl = 0xA3,
    LAlt = 0xA4,
    RAlt = 0xA5,
};

class InputSystem : public Singleton<InputSystem>
{
public:
    InputSystem();
    ~InputSystem() = default;

    // 복사 & 이동 생성자 삭제
    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;
    InputSystem(InputSystem&&) = delete;
    InputSystem& operator=(InputSystem&&) = delete;


    /**
     * 키를 눌림 상태로 전환합니다. 
     */
    void KeyDown(EKeyCode key);

    /**
     * 키를 눌리지 않은 상태로 전환합니다.
     */
    void KeyUp(EKeyCode key);


    std::vector<EKeyCode> GetPressedKeys();

    /**
     * 키가 눌려있는지 확인합니다.
     * @param key 감지 할 키
     * @return key의 눌림 여부
     */
    [[nodiscard]] bool IsPressedKey(EKeyCode key) const;

    void MouseKeyDown(FVector3 MouseDownPoint, FVector3 WindowSize);

    void MouseKeyUp(FVector3 MouseUpPoint, FVector3 WindowSize);

    void ExpireOnceMouse() { onceMouse = false; }

    bool IsPressedMouse() { return mouse; }

    bool GetMouseDown() { return onceMouse; }

    FVector3 GetMouseDownPos() { return MouseKeyDownPos; }
    FVector3 GetMouseUpPos() { return MouseKeyUpPos; }

    FVector3 GetMouseDownRatioPos() { return MouseKeyDownRatioPos; }
    FVector3 GetMouseUpRatioPos() { return MouseKeyUpRatioPos; }


private:
    bool mouse;
    bool onceMouse;
    bool _keys[256];
    bool bIsBlockInput = false;
    FVector3 MouseKeyDownPos;
    FVector3 MouseKeyUpPos;
    FVector3 MouseKeyDownRatioPos;
    FVector3 MouseKeyUpRatioPos;
};

class InputHandler {
public :
    InputHandler();

    void HandlePlayerInputByWorld(EWorld World);
    void InputUpdate();

private:

};