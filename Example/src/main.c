internal void Handler(Pointer data, Window widget, Event * event)
{
    switch (event->type)
    {
    case WND_KeyEvent:
    {
        Rect rect;
        WND_GetRect(&widget, &rect);

        Int32 step = 3;

        switch (event->keyEvent.key)
        {
            case KEY_ArrowLeft:  rect.x -= step; rect.w += step; break;
            case KEY_ArrowUp:    rect.y -= step; rect.h += step; break;
            case KEY_ArrowRight: rect.x += step; rect.w -= step; break;
            case KEY_ArrowDown:  rect.y += step; rect.h -= step; break;
            case KEY_Escape:     WND_Destroy(&widget);           break;
            default: break;
        }

        WND_SetRect(&widget, &rect);
        break;
    }
    case WND_CloseEvent:
    {
        WND_Destroy(&widget);
        break;
    }
    case WND_DestroyEvent:
    {
        // TODO@Daniel:
        //   Find a better way to do this
        extern void PostQuitMessage(int);
        PostQuitMessage(0);
        break;
    }
    default: break;
    }
}

Int32 Main()
{
    Window widget = null;
    WND_Create(&widget, &Handler, null);

    assert(widget != null);

    while (WND_ProcessEvents())
    {

    }

    // TODO@Daniel:
    //   Handle post quit return code somehow

    return 0;
}