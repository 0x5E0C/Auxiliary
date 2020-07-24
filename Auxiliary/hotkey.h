#ifndef HOTKEY_H
#define HOTKEY_H

#include <QObject>
#include "config.h"

class hotkey;
extern hotkey *hotkeymanager;

class hotkey : public QObject
{
    Q_OBJECT

signals:
    void hotkeyevent();

public:
    hotkey();
    void setHook();
    void ReleaseHook();
    static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    void emitHotkeySignals();
};

#endif // HOTKEY_H
