#pragma once

class Cursor
{
    ///Hide cursor
    static void Hide()noexcept;
    ///Show cursor
    static void Show()noexcept;
    static bool IsVisible()noexcept;
    static void MoveInWindow(Window&, int, int)noexcept;
};