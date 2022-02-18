#pragma once

typedef enum EventType
{
    WND_NullEvent,
    WND_MoveEvent,
    WND_ResizeEvent,
    WND_KeyEvent,
    WND_CloseEvent,
    WND_DestroyEvent
} EventType;

typedef struct Event
{
    EventType type;
    union
    {
        MoveEvent moveEvent;
        ResizeEvent resizeEvent;
        KeyEvent keyEvent;
    };
} Event;