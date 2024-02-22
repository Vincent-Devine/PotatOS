#pragma once

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	Math::Vector3 position;
	Math::Vector3 normal;
	Math::Vector2 uv;
    Math::Vector3 tangent;
    Math::Vector3 bitangent;
    int boneIDs[MAX_BONE_INFLUENCE];
    float weights[MAX_BONE_INFLUENCE];
};

struct Inputs
{
    float deltaX = 0.f;
    float deltaY = 0.f;
    bool moveForward = true;
    bool moveBackward = true;
    bool moveRight = true;
    bool moveLeft = true;
    bool moveUp = true;
    bool moveDown = true;
    bool pauseAnimation = true;
    bool attack = true;
    bool jump = false;
    bool showmenu = true;
    float joystickLeftX = 0.0f;
    float joystickLeftY = 0.0f;
    float joystickRightX = 0.0f;
    float joystickRightY = 0.0f;
    float joystickLeftTrigger = 0.0f;
    float joystickRightTrigger = 0.0f;
    bool gamepadA = true;
    bool gamepadB = true;
    bool gamepadX = true;
    bool gamepadY = true;
    bool gamepadLeftButton = true;
    bool gamepadRightButton = true;
    bool displayButton = true;
    bool menuButton = true;
    bool joystickLeftButton = true;
    bool joystickRightButton = true;
    // MDB = Multi Directional Button
    bool MDBDown = true;
    bool MDBRight = true;
    bool MDBUp = true;
    bool MDBLeft = true;
    bool restart = true;
    float sensitivity = 0.2f;
};

enum class KEY_TYPE
{
    /* The unknown key */
    KEY_UNKNOWN            ,

    /* Printable keys */
    KEY_SPACE              ,
    KEY_APOSTROPHE         ,/* ' */
    KEY_COMMA              ,/* , */
    KEY_MINUS              ,/* - */
    KEY_PERIOD             ,/* . */
    KEY_SLASH              ,/* / */
    KEY_0                  ,
    KEY_1                  ,
    KEY_2                  ,
    KEY_3                  ,
    KEY_4                  ,
    KEY_5                  ,
    KEY_6                  ,
    KEY_7                  ,
    KEY_8                  ,
    KEY_9                  ,
    KEY_SEMICOLON          ,/* ; */
    KEY_EQUAL              ,/* = */
    KEY_A                  ,
    KEY_B                  ,
    KEY_C                  ,
    KEY_D                  ,
    KEY_E                  ,
    KEY_F                  ,
    KEY_G                  ,
    KEY_H                  ,
    KEY_I                  ,
    KEY_J                  ,
    KEY_K                  ,
    KEY_L                  ,
    KEY_M                  ,
    KEY_N                  ,
    KEY_O                  ,
    KEY_P                  ,
    KEY_Q                  ,
    KEY_R                  ,
    KEY_S                  ,
    KEY_T                  ,
    KEY_U                  ,
    KEY_V                  ,
    KEY_W                  ,
    KEY_X                  ,
    KEY_Y                  ,
    KEY_Z                  ,
    KEY_LEFT_BRACKET       ,/* [ */
    KEY_BACKSLASH          ,/* \ */
    KEY_RIGHT_BRACKET      ,/* ] */
    KEY_GRAVE_ACCENT       ,/* ` */
    KEY_WORLD_1            ,/* non-US #1 */
    KEY_WORLD_2            ,/* non-US #2 */

    /* Function keys */
    KEY_ESCAPE             ,
    KEY_ENTER              ,
    KEY_TAB                ,
    KEY_BACKSPACE          ,
    KEY_INSERT             ,
    KEY_DELETE             ,
    KEY_RIGHT              ,
    KEY_LEFT               ,
    KEY_DOWN               ,
    KEY_UP                 ,
    KEY_PAGE_UP            ,
    KEY_PAGE_DOWN          ,
    KEY_HOME               ,
    KEY_END                ,
    KEY_CAPS_LOCK          ,
    KEY_SCROLL_LOCK        ,
    KEY_NUM_LOCK           ,
    KEY_PRINT_SCREEN       ,
    KEY_PAUSE              ,
    KEY_F1                 ,
    KEY_F2                 ,
    KEY_F3                 ,
    KEY_F4                 ,
    KEY_F5                 ,
    KEY_F6                 ,
    KEY_F7                 ,
    KEY_F8                 ,
    KEY_F9                 ,
    KEY_F10                ,
    KEY_F11                ,
    KEY_F12                ,
    KEY_F13                ,
    KEY_F14                ,
    KEY_F15                ,
    KEY_F16                ,
    KEY_F17                ,
    KEY_F18                ,
    KEY_F19                ,
    KEY_F20                ,
    KEY_F21                ,
    KEY_F22                ,
    KEY_F23                ,
    KEY_F24                ,
    KEY_F25                ,
    KEY_KP_0               ,
    KEY_KP_1               ,
    KEY_KP_2               ,
    KEY_KP_3               ,
    KEY_KP_4               ,
    KEY_KP_5               ,
    KEY_KP_6               ,
    KEY_KP_7               ,
    KEY_KP_8               ,
    KEY_KP_9               ,
    KEY_KP_DECIMAL         ,
    KEY_KP_DIVIDE          ,
    KEY_KP_MULTIPLY        ,
    KEY_KP_SUBTRACT        ,
    KEY_KP_ADD             ,
    KEY_KP_ENTER           ,
    KEY_KP_EQUAL           ,
    KEY_LEFT_SHIFT         ,
    KEY_LEFT_CONTROL       ,
    KEY_LEFT_ALT           ,
    KEY_LEFT_SUPER         ,
    KEY_RIGHT_SHIFT        ,
    KEY_RIGHT_CONTROL      ,
    KEY_RIGHT_ALT          ,
    KEY_RIGHT_SUPER        ,
    KEY_MENU               ,
    KEY_MOUSE_BUTTON_RIGHT ,
    KEY_MOUSE_BUTTON_LEFT
};

enum class MOUSE_TYPE
{
    KEY_MOUSE_BUTTON_RIGHT,
    KEY_MOUSE_BUTTON_LEFT
};

enum class JOYSTICK_STICK_TYPE
{
    KEY_LEFT_STICK_X,
    KEY_LEFT_STICK_Y,
    KEY_RIGHT_STICK_X,
    KEY_RIGHT_STICK_Y,
    KEY_LEFT_TRIGGER,
    KEY_RIGHT_TRIGGER,
};

enum class JOYSTICK_BUTTON_TYPE
{
    X,
    Y,
    A,
    B,
    LEFT_BUTTON,
    RIGHT_BUTTON,
    DISPLAY_BUTTON,
    MENU_BUTTON,
    JOYSTICK_LEFT_BUTTON,
    JOYSTICK_RIGHT_BUTTON,
    // MDB = Multi Directional Button
    MDB_DOWN,
    MDB_RIGHT,
    MDB_UP,
    MDB_LEFT,
};

enum class KEY_INTERACTION_TYPE : int
{
    RELEASE,
    PRESS,
    REPEAT,
};

enum class GAMESTATE
{
    EDIT,
    PLAY,
};
