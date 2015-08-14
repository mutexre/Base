#ifndef header_722238C8_E600_4F4A_889C_7E588DF589A9
#define header_722238C8_E600_4F4A_889C_7E588DF589A9

namespace UI
{
    enum Key {
        space,
        esc,
        enter,
        backspace,
        up, down, left, right,
        pageUp, pageDown,
        home, end,
        f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12
    };

    enum Modifier {
        shift,
        alt,
        ctrl,
        cmd
    };
    
//    void convertKeyCode(Rt::Option<Key>, Rt::Option<std::string>);
}

#endif
