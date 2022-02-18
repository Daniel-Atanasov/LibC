#pragma once

// TODO@Daniel:
//   - Track keyboard changes more thoroughly

typedef Pointer Window;

typedef void(*WND_EventHandler)(Pointer, Window, Event *);

Bool WND_ProcessEvents();

Bool WND_Create(Window * window, WND_EventHandler eventHandler, Pointer eventData);
Bool WND_Destroy(Window * window);

Bool WND_GetRect(Window * window, Rect * rect);
Bool WND_SetRect(Window * window, Rect * rect);
