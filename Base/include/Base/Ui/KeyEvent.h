#pragma once

typedef enum Key
{
    KEY_Unknown,
    KEY_ArrowUp,
    KEY_ArrowDown,
    KEY_ArrowLeft,
    KEY_ArrowRight,
    KEY_Escape
} Key;

typedef struct KeyEvent
{
    Key key;
    Bool pressed;
} KeyEvent;