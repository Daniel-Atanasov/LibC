#include <Windows.h>
#include <windowsx.h>

typedef struct WindowInfo
{
    Pointer handle;
    WND_EventHandler eventHandler;
    Pointer eventData;
} WindowInfo;

internal void PaintWindow(Pointer handle, WindowInfo * info)
{
    Uint32 colorA = RGB(255, 127, 0);
    Uint32 colorB = RGB(0, 128, 255);

    RECT rect;
    GetClientRect(handle, &rect);

    PAINTSTRUCT painter;
    HDC windowDevice = BeginPaint(handle, &painter);

    HBRUSH brushA = CreateSolidBrush(colorA);
    HBRUSH brushB = CreateSolidBrush(colorB);

    FillRect(windowDevice, &rect, brushB);

    RECT topLeft;
    topLeft.left = rect.left;
    topLeft.top = rect.top;
    topLeft.right = rect.right / 2;
    topLeft.bottom = rect.bottom / 2;

    RECT bottomRight;
    bottomRight.left = rect.right / 2;
    bottomRight.top = rect.bottom / 2;
    bottomRight.right = rect.right;
    bottomRight.bottom = rect.bottom;

    FillRect(windowDevice, &topLeft, brushA);
    FillRect(windowDevice, &bottomRight, brushA);

    DeleteObject(brushA);
    DeleteObject(brushB);

    EndPaint(handle, &painter);
}

internal Pointer WndProc(Pointer handle, Uint32 message, Uint64 w, Uint64 l)
{
    WindowInfo * info = GetWindowLongPtrA(handle, GWLP_USERDATA);

    Event event;
    event.type = WND_NullEvent;

    if (info == null)
    {
        goto end;
    }

    switch (message)
    {
    case WM_NCCALCSIZE:
    {
        if (w) {
            NCCALCSIZE_PARAMS * ncParams = l;
            ncParams->rgrc[0].top -= 1;
            ncParams->rgrc[0].left -= 1;
            ncParams->rgrc[0].bottom += 1;
            ncParams->rgrc[0].right += 1;

            GetWindowRect(handle, &ncParams->rgrc[1]);
            GetWindowRect(handle, &ncParams->rgrc[2]);

            return WVR_VALIDRECTS;
        }
        break;
    }
    case WM_KEYDOWN:
    {
        Key key = KEY_Unknown;
        switch (w)
        {
        case VK_LEFT:   key = KEY_ArrowLeft;  break;
        case VK_UP:     key = KEY_ArrowUp;    break;
        case VK_RIGHT:  key = KEY_ArrowRight; break;
        case VK_DOWN:   key = KEY_ArrowDown;  break;
        case VK_ESCAPE: key = KEY_Escape;     break;
        }
        if (key != KEY_Unknown)
        {
            event.type = WND_KeyEvent;
            event.keyEvent.key = key;
        }
        break;
    }
    case WM_PAINT:
    {
        PaintWindow(handle, info);
        return 0;
    }
    case WM_NCHITTEST:
    {
        POINT point;
        point.x = GET_X_LPARAM(l);
        point.y = GET_Y_LPARAM(l);

        ScreenToClient(handle, &point);

        Rect rect;
        WND_GetRect(&info, &rect);

        Int32 padding = 10;

        Int32 leftResize = padding;
        Int32 topResize = padding;
        Int32 rightResize = rect.w - padding;
        Int32 bottomResize = rect.h - padding;

        Int8 horizontal = HTNOWHERE;
        Int8 vertical = HTNOWHERE;

        if (point.x <= leftResize)
        {
            horizontal = HTLEFT;
        }
        else if (point.x >= rightResize)
        {
            horizontal = HTRIGHT;
        }

        if (point.y <= topResize)
        {
            vertical = HTTOP;
        }
        else if (point.y >= bottomResize)
        {
            vertical = HTBOTTOM;
        }

        // TODO@Daniel:
        //   Either make this a flag or forward this to the callback
        if (horizontal == HTNOWHERE and vertical == HTNOWHERE)
        {
            return HTCAPTION;
        }

        if (horizontal == HTNOWHERE or vertical == HTNOWHERE)
        {
            return horizontal | vertical;
        }

        if (horizontal == HTLEFT and vertical == HTTOP)
        {
            return HTTOPLEFT;
        }

        if (horizontal == HTLEFT and vertical == HTBOTTOM)
        {
            return HTBOTTOMLEFT;
        }

        if (horizontal == HTRIGHT and vertical == HTTOP)
        {
            return HTTOPRIGHT;
        }

        if (horizontal == HTRIGHT and vertical == HTBOTTOM)
        {
            return HTBOTTOMRIGHT;
        }
        break;
    }
    case WM_CLOSE:
    {
        event.type = WND_CloseEvent;
        break;
    }
    case WM_DESTROY:
    {
        event.type = WND_DestroyEvent;
        break;
    }
    }

    if (info != null and info->eventHandler != null and event.type != WND_NullEvent)
    {
        info->eventHandler(info->eventData, info, &event);
    }

end:
    Pointer result = DefWindowProcA(handle, message, w, l);
    if (message == WM_NCDESTROY)
    {
        SYS_FreeMemory(&info);
    }
    return result;
}

Pointer WND_GetWindowClassHandle()
{
    static Pointer windowClassHandle = null;

    if (windowClassHandle == null)
    {
        WNDCLASSEX windowClass = { 0 };
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.lpszClassName = "WND_BASE_WINDOW";
        windowClass.lpfnWndProc = &WndProc;
        windowClass.hbrBackground = GetStockBrush(BLACK_BRUSH);
        windowClass.hCursor = LoadCursor(null, IDC_ARROW);
        windowClass.hInstance = SYS_GetModuleHandle();
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClassHandle = RegisterClassExA(&windowClass);
    }

    return windowClassHandle;
}

Bool WND_ProcessEvents()
{
    MSG msg;
    Bool success = GetMessageA(&msg, NULL, 0, 0) > 0;
    if (not success)
    {
        return false;
    }

    TranslateMessage(&msg);
    DispatchMessageA(&msg);

    return true;
}

Bool WND_Create(Window * window, WND_EventHandler eventHandler, Pointer eventData)
{
    assert(window != null);

    Bool success = false;
    WindowInfo * info = null;

    success = SYS_Alloc(WindowInfo, &info);
    if (not success)
    {
        return false;
    }

    Uint32 windowStyleEx = 0;
    Pointer windowClassHandle = WND_GetWindowClassHandle();
    Pointer windowText = "HELLO";
    Uint32 windowStyle = WS_VISIBLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_BORDER | WS_CLIPCHILDREN | WS_SIZEBOX;
    Int32 windowX = 200;
    Int32 windowY = 200;
    Int32 windowW = 500;
    Int32 windowH = 500;

    Pointer handle = CreateWindowExA(
        windowStyleEx,
        windowClassHandle,
        windowText,
        windowStyle,
        windowX, windowY,
        windowW, windowH,
        null,
        null,
        SYS_GetModuleHandle(),
        null
    );

    if (handle == null)
    {
        SYS_Free(WindowInfo, &info);
        return false;
    }

    info->handle = handle;
    info->eventHandler = eventHandler;
    info->eventData = eventData;

    SetWindowLongPtrA(handle, GWLP_USERDATA, info);

    ShowWindow(handle, SW_SHOW);
    SetWindowPos(handle, null, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    *window = info;

    return true;
}

Bool WND_GetRect(Window * window, Rect * rect)
{
    assert(window != null);
    assert(*window != null);
    assert(rect != null);

    Bool success = false;
    WindowInfo * info = cast(WindowInfo *, *window);

    RECT r;
    success = GetWindowRect(info->handle, &r);
    if (not success)
    {
        return false;
    }

    *rect = (Rect)
    {
        .x = r.left,
        .y = r.top,
        .w = r.right - r.left,
        .h = r.bottom - r.top
    };

    return true;
}

Bool WND_SetRect(Window * window, Rect * rect)
{
    assert(window != null);
    assert(*window != null);
    assert(rect != null);

    WindowInfo * info = cast(WindowInfo *, *window);

    Bool success = SetWindowPos(
        info->handle,
        0,
        rect->x, rect->y,
        rect->w, rect->h,
        SWP_NOACTIVATE
    );

    return success;
}

Bool WND_Destroy(Window * window)
{
    assert(window != null);

    if (*window == null)
    {
        return true;
    }

    WindowInfo * info = cast(WindowInfo *, *window);

    return DestroyWindow(info->handle) != 0;
}