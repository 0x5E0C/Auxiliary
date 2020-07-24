#include "hotkey.h"

HHOOK g_hook;
hotkey *hotkeymanager=new hotkey();

hotkey::hotkey(){}

/*函数功能:设置键盘钩子*/
void hotkey::setHook()
{
    g_hook=SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
}

/*函数功能:释放键盘钩子*/
void hotkey::ReleaseHook()
{
    UnhookWindowsHookEx(g_hook);
}

/*函数功能:键盘事件回调*/
LRESULT hotkey::keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    LPKBDLLHOOKSTRUCT kbdStruct = (LPKBDLLHOOKSTRUCT)lParam;
    if (nCode>=0 && wParam == WM_KEYDOWN)
    {
        if(kbdStruct->vkCode == 0x51)
        {
            if(GetKeyState(VK_CONTROL)<0)
            {
                hotkeymanager->emitHotkeySignals();
            }
        }
    }
    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

/*函数功能:发送热键事件*/
void hotkey::emitHotkeySignals()
{
    emit hotkeyevent();
}

