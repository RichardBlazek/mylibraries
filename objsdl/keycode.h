#pragma once

enum class Scancode : uint16
{
    Unknown=0,

    A=4,
    B=5,
    C=6,
    D=7,
    E=8,
    F=9,
    G=10,
    H=11,
    I=12,
    J=13,
    K=14,
    L=15,
    M=16,
    N=17,
    O=18,
    P=19,
    Q=20,
    R=21,
    S=22,
    T=23,
    U=24,
    V=25,
    W=26,
    X=27,
    Y=28,
    Z=29,

    n1=30,
    n2=31,
    n3=32,
    n4=33,
    n5=34,
    n6=35,
    n7=36,
    n8=37,
    n9=38,
    n0=39,

    Return=40,
    Escape=41,
    Backspace=42,
    Tab=43,
    Space=44,

    Minus=45,
    Equals=46,
    LeftBracket=47,
    RightBracket=48,
    Backslash=49, /* Located at the lower left of the return key on ISO keyboards and at the right end
								of the QWERTY row on ANSI keyboards. Produces REVERSE SOLIDUS (backslash) and
								VERTICAL LINE in a US layout, REVERSE SOLIDUS and VERTICAL LINE in a UK Mac
								layout, NUMBER SIGN and TILDE in a UK Windows layout, DOLLAR SIGN and POUND SIGN
								in a Swiss German layout, NUMBER SIGN and APOSTROPHE in a German layout, GRAVE
								ACCENT and POUND SIGN in a French Mac layout, and ASTERISK and MICRO SIGN in a
								French Windows layout.
	*/
    NonUsHash=50, /* ISO USB keyboards actually use this code
								instead of 49 for the same key, but all
								OSes I've seen treat the two codes
								identically. So, as an implementor, unless
								your keyboard generates both of those
								codes and your OS treats them differently,
								you should generate BACKSLASH
								instead of this code. As a user, you
								should not rely on this code because SDL
								will never generate it with most (all?)
								keyboards.
	*/
    Semicolon=51,
    Apostrophe=52,
    Grave=53,

    Comma=54,
    Period=55,
    Slash=56,

    CapsLock=57,

    F1=58,
    F2=59,
    F3=60,
    F4=61,
    F5=62,
    F6=63,
    F7=64,
    F8=65,
    F9=66,
    F10=67,
    F11=68,
    F12=69,

    PrintScreen=70,
    ScrollLock=71,
    Pause=72,
    Insert=73, //insert on PC, help on some Mac keyboards (but does send code 73, not 117)
    Home=74,
    PageUp=75,
    Delete=76,
    End=77,
    PageDown=78,
    Right=79,
    Left=80,
    Down=81,
    Up=82,

    NumLockOrClear=83, //num lock on PC, clear on Mac keyboards
	KpDivide=84,
    KpMultiply=85,
    KpMinus=86,
    KpPlus=87,
    KpEnter=88,
    Kp1=89,
    Kp2=90,
    Kp3=91,
    Kp4=92,
    Kp5=93,
    Kp6=94,
    Kp7=95,
    Kp8=96,
    Kp9=97,
    Kp0=98,
    KpPeriod=99,

    NonUsBackslash=100,

    Application=101, /// windows contextual menu, compose
    Power=102,

    KpEquals=103,
    F13=104,
    F14=105,
    F15=106,
    F16=107,
    F17=108,
    F18=109,
    F19=110,
    F20=111,
    F21=112,
    F22=113,
    F23=114,
    F24=115,
    Execute=116,
    Help=117,
    Menu=118,
    Select=119,
    Stop=120,
    Again=121,   /// redo
    Undo=122,
    Cut=123,
    Copy=124,
    Paste=125,
    Find=126,
    Mute=127,
    VolumeUp=128,
    VolumeDown=129,
	LockingCapsLock=130,
	LockingNumLock=131,
	LockingScrollLock=132,
    KpComma=133,
    KpEqualsAs400=134,

    International1=135, /// used on Asian keyboards, see footnotes in USB doc
    International2=136,
    International3=137, /// Yen
    International4=138,
    International5=139,
    International6=140,
    International7=141,
    International8=142,
    International9=143,
    Lang1=144, /// Hangul/English toggle
    Lang2=145, /// Hanja conversion
    Lang3=146, /// Katakana
    Lang4=147, /// Hiragana
    Lang5=148, /// Zenkaku/Hankaku
    Lang6=149, /// reserved
    Lang7=150, /// reserved
    Lang8=151, /// reserved
    Lang9=152, /// reserved

    AltErase=153, /// Erase-Eaze
    SysReq=154,
    Cancel=155,
    Clear=156,
    Prior=157,
    Return2=158,
    Separator=159,
    Out=160,
    Oper=161,
    ClearAgain=162,
    CrSel=163,
    ExSel=164,

    Kp00=176,
    Kp000=177,
    ThousandsSeparator=178,
    DecimalSeparator=179,
    CurrencyUnit=180,
    CurrencySubunit=181,
    KpLeftParen=182,
    KpRightParen=183,
    KpLeftBrace=184,
    KpRightBrace=185,
    KpTab=186,
    KpBackspace=187,
    KpA=188,
    KpB=189,
    KpC=190,
    KpD=191,
    KpE=192,
    KpF=193,
    KpXor=194,
    KpPower=195,
    KpPercent=196,
    KpLess=197,
    KpGreater=198,
    KpAmpersand=199,
    KpDblAmpersand=200,
    KpVerticalBar=201,
    KpDblVerticalBar=202,
    KpColon=203,
    KpHash=204,
    KpSpace=205,
    KpAt=206,
    KpExclam=207,
    KpMemStore=208,
    KpMemRecall=209,
    KpMemClear=210,
    KpMemAdd=211,
    KpMemSubstract=212,
    KpMemMultiply=213,
    KpMemDivide=214,
    KpPlusMinus=215,
    KpClear=216,
    KpClearEntry=217,
    KpBinary=218,
    KpOctal=219,
    KpDecimal=220,
    KpHexadecimal=221,

    LCtrl=224,
    LShift=225,
    LAlt=226, /// alt, option
    LGUI=227, /// windows, command (apple), meta
    RCtrl=228,
    RShift=229,
    RAlt=230, /// alt gr, option
    RGUI=231, /// windows, command (apple), meta

    Mode=257,

    AudioNext=258,
    AudioPrev=259,
    AudioStop=260,
    AudioPlay=261,
    AudioMute=262,
    MediaSelect=263,
    Www=264,
    Mail=265,
    Calculator=266,
    Computer=267,
    AcSearch=268,
    AcHome=269,
    AcBack=270,
    AcForward=271,
    AcStop=272,
    AcRefresh=273,
    AcBookmarks=274,

    BrightnessDown=275,
    BrightnessUp=276,
    DisplaySwitch=277, ///display mirroring/dual display switch, video mode switch
    KbDillumToggle=278,
    KbDillumDown=279,
    KbDillumUp=280,
    Eject=281,
    Sleep=282,

    App1=283,
    App2=284,

    // Add any other keys here.

    NumScancodes=512 ///not a key, just marks the number of scancodes for array bounds
};
#define KEYCODE_FROM_SCANCODE(X) SDL_SCANCODE_TO_KEYCODE(int32((X)))
enum class Keycode: int32
{
    Unknown=0,

    Return='\r',
    Escape='\033',
    Backspace='\b',
    Tab='\t',
    Space=' ',
    Exclaim='!',
    Quotedbl='"',
    Hash='#',
    Percent='%',
    Dollar='$',
    Ampersand='&',
    Quote='\'',
    Leftparen='(',
    Rightparen=')',
    Asterisk='*',
    Plus='+',
    Comma=',',
    Minus='-',
    Period='.',
    Slash='/',
    N0='0',
    N1='1',
    N2='2',
    N3='3',
    N4='4',
    N5='5',
    N6='6',
    N7='7',
    N8='8',
    N9='9',
    Colon=':',
    Semicolon=';',
    Less='<',
    Equals='=',
    Greater='>',
    Question='?',
    At='@',
		//Skip Uppercase Letters
    Leftbracket='[',
    Backslash='\\',
    Rightbracket=']',
    Caret='^',
    Underscore='_',
    Backquote='`',
    A='a',
    B='b',
    C='c',
    D='d',
    E='e',
    F='f',
    G='g',
    H='h',
    I='i',
    J='j',
    K='k',
    L='l',
    M='m',
    N='n',
    O='o',
    P='p',
    Q='q',
    R='r',
    S='s',
    T='t',
    U='u',
    V='v',
    W='w',
    X='x',
    Y='y',
    Z='z',

    Capslock=KEYCODE_FROM_SCANCODE(Scancode::CapsLock),
    F1=KEYCODE_FROM_SCANCODE(Scancode::F1),
    F2=KEYCODE_FROM_SCANCODE(Scancode::F2),
    F3=KEYCODE_FROM_SCANCODE(Scancode::F3),
    F4=KEYCODE_FROM_SCANCODE(Scancode::F4),
    F5=KEYCODE_FROM_SCANCODE(Scancode::F5),
    F6=KEYCODE_FROM_SCANCODE(Scancode::F6),
    F7=KEYCODE_FROM_SCANCODE(Scancode::F7),
    F8=KEYCODE_FROM_SCANCODE(Scancode::F8),
    F9=KEYCODE_FROM_SCANCODE(Scancode::F9),
    F10=KEYCODE_FROM_SCANCODE(Scancode::F10),
    F11=KEYCODE_FROM_SCANCODE(Scancode::F11),
    F12=KEYCODE_FROM_SCANCODE(Scancode::F12),

    Printscreen=KEYCODE_FROM_SCANCODE(Scancode::PrintScreen),
    Scrolllock=KEYCODE_FROM_SCANCODE(Scancode::ScrollLock),
    Pause=KEYCODE_FROM_SCANCODE(Scancode::Pause),
    Insert=KEYCODE_FROM_SCANCODE(Scancode::Insert),
    Home=KEYCODE_FROM_SCANCODE(Scancode::Home),
    Pageup=KEYCODE_FROM_SCANCODE(Scancode::PageUp),
    Delete='\177',
    End=KEYCODE_FROM_SCANCODE(Scancode::End),
    Pagedown=KEYCODE_FROM_SCANCODE(Scancode::PageDown),
    Right=KEYCODE_FROM_SCANCODE(Scancode::Right),
    Left=KEYCODE_FROM_SCANCODE(Scancode::Left),
    Down=KEYCODE_FROM_SCANCODE(Scancode::Down),
    Up=KEYCODE_FROM_SCANCODE(Scancode::Up),

    NumLockOrClear=KEYCODE_FROM_SCANCODE(Scancode::NumLockOrClear),
    KpDivide=KEYCODE_FROM_SCANCODE(Scancode::KpDivide),
    KpMultiply=KEYCODE_FROM_SCANCODE(Scancode::KpMultiply),
    KpMinus=KEYCODE_FROM_SCANCODE(Scancode::KpMinus),
    KpPlus=KEYCODE_FROM_SCANCODE(Scancode::KpPlus),
    KpEnter=KEYCODE_FROM_SCANCODE(Scancode::KpEnter),
    Kp1=KEYCODE_FROM_SCANCODE(Scancode::Kp1),
    Kp2=KEYCODE_FROM_SCANCODE(Scancode::Kp2),
    Kp3=KEYCODE_FROM_SCANCODE(Scancode::Kp3),
    Kp4=KEYCODE_FROM_SCANCODE(Scancode::Kp4),
    Kp5=KEYCODE_FROM_SCANCODE(Scancode::Kp5),
    Kp6=KEYCODE_FROM_SCANCODE(Scancode::Kp6),
    Kp7=KEYCODE_FROM_SCANCODE(Scancode::Kp7),
    Kp8=KEYCODE_FROM_SCANCODE(Scancode::Kp8),
    Kp9=KEYCODE_FROM_SCANCODE(Scancode::Kp9),
    Kp0=KEYCODE_FROM_SCANCODE(Scancode::Kp0),
    KpPeriod=KEYCODE_FROM_SCANCODE(Scancode::KpPeriod),

    Application=KEYCODE_FROM_SCANCODE(Scancode::Application),
    Power=KEYCODE_FROM_SCANCODE(Scancode::Power),
    KpEquals=KEYCODE_FROM_SCANCODE(Scancode::KpEquals),
    F13=KEYCODE_FROM_SCANCODE(Scancode::F13),
    F14=KEYCODE_FROM_SCANCODE(Scancode::F14),
    F15=KEYCODE_FROM_SCANCODE(Scancode::F15),
    F16=KEYCODE_FROM_SCANCODE(Scancode::F16),
    F17=KEYCODE_FROM_SCANCODE(Scancode::F17),
    F18=KEYCODE_FROM_SCANCODE(Scancode::F18),
    F19=KEYCODE_FROM_SCANCODE(Scancode::F19),
    F20=KEYCODE_FROM_SCANCODE(Scancode::F20),
    F21=KEYCODE_FROM_SCANCODE(Scancode::F21),
    F22=KEYCODE_FROM_SCANCODE(Scancode::F22),
    F23=KEYCODE_FROM_SCANCODE(Scancode::F23),
    F24=KEYCODE_FROM_SCANCODE(Scancode::F24),
    Execute=KEYCODE_FROM_SCANCODE(Scancode::Execute),
    Help=KEYCODE_FROM_SCANCODE(Scancode::Help),
    Menu=KEYCODE_FROM_SCANCODE(Scancode::Menu),
    Select=KEYCODE_FROM_SCANCODE(Scancode::Select),
    Stop=KEYCODE_FROM_SCANCODE(Scancode::Stop),
    Again=KEYCODE_FROM_SCANCODE(Scancode::Again),
    Undo=KEYCODE_FROM_SCANCODE(Scancode::Undo),
    Cut=KEYCODE_FROM_SCANCODE(Scancode::Cut),
    Copy=KEYCODE_FROM_SCANCODE(Scancode::Copy),
    Paste=KEYCODE_FROM_SCANCODE(Scancode::Paste),
    Find=KEYCODE_FROM_SCANCODE(Scancode::Find),
    Mute=KEYCODE_FROM_SCANCODE(Scancode::Mute),
    VolumeUp=KEYCODE_FROM_SCANCODE(Scancode::VolumeUp),
    VolumeDown=KEYCODE_FROM_SCANCODE(Scancode::VolumeDown),
    KpComma=KEYCODE_FROM_SCANCODE(Scancode::KpComma),
    KpEqualsAs400=KEYCODE_FROM_SCANCODE(Scancode::KpEqualsAs400),

    AltErase=KEYCODE_FROM_SCANCODE(Scancode::AltErase),
    SysReq=KEYCODE_FROM_SCANCODE(Scancode::SysReq),
    Cancel=KEYCODE_FROM_SCANCODE(Scancode::Cancel),
    Clear=KEYCODE_FROM_SCANCODE(Scancode::Clear),
    Prior=KEYCODE_FROM_SCANCODE(Scancode::Prior),
    Return2=KEYCODE_FROM_SCANCODE(Scancode::Return2),
    Separator=KEYCODE_FROM_SCANCODE(Scancode::Separator),
    Out=KEYCODE_FROM_SCANCODE(Scancode::Out),
    Oper=KEYCODE_FROM_SCANCODE(Scancode::Oper),
    ClearAgain=KEYCODE_FROM_SCANCODE(Scancode::ClearAgain),
    CrSel=KEYCODE_FROM_SCANCODE(Scancode::CrSel),
    ExSel=KEYCODE_FROM_SCANCODE(Scancode::ExSel),

    Kp00=KEYCODE_FROM_SCANCODE(Scancode::Kp00),
    Kp000=KEYCODE_FROM_SCANCODE(Scancode::Kp000),
    ThousandsSeparator=KEYCODE_FROM_SCANCODE(Scancode::ThousandsSeparator),
    DecimalSeparator=KEYCODE_FROM_SCANCODE(Scancode::DecimalSeparator),
    CurrencyUnit=KEYCODE_FROM_SCANCODE(Scancode::CurrencyUnit),
    CurrencySubunit=KEYCODE_FROM_SCANCODE(Scancode::CurrencySubunit),

    KpLeftparen=KEYCODE_FROM_SCANCODE(Scancode::KpLeftParen),
    KpRightparen=KEYCODE_FROM_SCANCODE(Scancode::KpRightParen),
    KpLeftbrace=KEYCODE_FROM_SCANCODE(Scancode::KpLeftBrace),
    KpRightbrace=KEYCODE_FROM_SCANCODE(Scancode::KpRightBrace),
    KpTab=KEYCODE_FROM_SCANCODE(Scancode::KpTab),
    KpBackspace=KEYCODE_FROM_SCANCODE(Scancode::KpBackspace),
    KpA=KEYCODE_FROM_SCANCODE(Scancode::KpA),
    KpB=KEYCODE_FROM_SCANCODE(Scancode::KpB),
    KpC=KEYCODE_FROM_SCANCODE(Scancode::KpC),
    KpD=KEYCODE_FROM_SCANCODE(Scancode::KpD),
    KpE=KEYCODE_FROM_SCANCODE(Scancode::KpE),
    KpF=KEYCODE_FROM_SCANCODE(Scancode::KpF),
    KpXor=KEYCODE_FROM_SCANCODE(Scancode::KpXor),
    KpPower=KEYCODE_FROM_SCANCODE(Scancode::KpPower),
    KpPercent=KEYCODE_FROM_SCANCODE(Scancode::KpPercent),
    KpLess=KEYCODE_FROM_SCANCODE(Scancode::KpLess),
    KpGreater=KEYCODE_FROM_SCANCODE(Scancode::KpGreater),
    KpAmpersand=KEYCODE_FROM_SCANCODE(Scancode::KpAmpersand),

    KpBblAmpersand=KEYCODE_FROM_SCANCODE(Scancode::KpDblAmpersand),
    KpVerticalBar=KEYCODE_FROM_SCANCODE(Scancode::KpVerticalBar),
    KpDblVerticalBar=KEYCODE_FROM_SCANCODE(Scancode::KpDblVerticalBar),

    KpColon=KEYCODE_FROM_SCANCODE(Scancode::KpColon),
    KpHash=KEYCODE_FROM_SCANCODE(Scancode::KpHash),
    KpSpace=KEYCODE_FROM_SCANCODE(Scancode::KpSpace),
    KpAt=KEYCODE_FROM_SCANCODE(Scancode::KpAt),
    KpExclam=KEYCODE_FROM_SCANCODE(Scancode::KpExclam),
    KpMemStore=KEYCODE_FROM_SCANCODE(Scancode::KpMemStore),
    KpMemRecall=KEYCODE_FROM_SCANCODE(Scancode::KpMemRecall),
    KpMemClear=KEYCODE_FROM_SCANCODE(Scancode::KpMemClear),
    KpMemAdd=KEYCODE_FROM_SCANCODE(Scancode::KpMemAdd),

    KpMemSubstract=KEYCODE_FROM_SCANCODE(Scancode::KpMemSubstract),
    KpMemMultiply=KEYCODE_FROM_SCANCODE(Scancode::KpMemMultiply),

    KpMemDivide=KEYCODE_FROM_SCANCODE(Scancode::KpMemDivide),
    KpPlusMinus=KEYCODE_FROM_SCANCODE(Scancode::KpPlusMinus),
    KpClear=KEYCODE_FROM_SCANCODE(Scancode::KpClear),
    KpClearEntry=KEYCODE_FROM_SCANCODE(Scancode::KpClearEntry),
    KpBinary=KEYCODE_FROM_SCANCODE(Scancode::KpBinary),
    KpOctal=KEYCODE_FROM_SCANCODE(Scancode::KpOctal),
    KpDecimal=KEYCODE_FROM_SCANCODE(Scancode::KpDecimal),
    KpHexadecimal=KEYCODE_FROM_SCANCODE(Scancode::KpHexadecimal),

    LCtrl=KEYCODE_FROM_SCANCODE(Scancode::LCtrl),
    LShift=KEYCODE_FROM_SCANCODE(Scancode::LShift),
    LAlt=KEYCODE_FROM_SCANCODE(Scancode::LAlt),
    LGUI=KEYCODE_FROM_SCANCODE(Scancode::LGUI),
    RCtrl=KEYCODE_FROM_SCANCODE(Scancode::RCtrl),
    RShift=KEYCODE_FROM_SCANCODE(Scancode::RShift),
    RAlt=KEYCODE_FROM_SCANCODE(Scancode::RAlt),
    RGUI=KEYCODE_FROM_SCANCODE(Scancode::RGUI),

    Mode=KEYCODE_FROM_SCANCODE(Scancode::Mode),

    AudioNext=KEYCODE_FROM_SCANCODE(Scancode::AudioNext),
    AudioPrev=KEYCODE_FROM_SCANCODE(Scancode::AudioPrev),
    AudioStop=KEYCODE_FROM_SCANCODE(Scancode::AudioStop),
    AudioPlay=KEYCODE_FROM_SCANCODE(Scancode::AudioPlay),
    AudioMute=KEYCODE_FROM_SCANCODE(Scancode::AudioMute),
    MediaSelect=KEYCODE_FROM_SCANCODE(Scancode::MediaSelect),
    Www=KEYCODE_FROM_SCANCODE(Scancode::Www),
    Mail=KEYCODE_FROM_SCANCODE(Scancode::Mail),
    Calculator=KEYCODE_FROM_SCANCODE(Scancode::Calculator),
    Computer=KEYCODE_FROM_SCANCODE(Scancode::Computer),
    AcSearch=KEYCODE_FROM_SCANCODE(Scancode::AcSearch),
    AcHome=KEYCODE_FROM_SCANCODE(Scancode::AcHome),
    AcBack=KEYCODE_FROM_SCANCODE(Scancode::AcBack),
    AcForward=KEYCODE_FROM_SCANCODE(Scancode::AcForward),
    AcStop=KEYCODE_FROM_SCANCODE(Scancode::AcStop),
    AcRefresh=KEYCODE_FROM_SCANCODE(Scancode::AcRefresh),
    AcBookmarks=KEYCODE_FROM_SCANCODE(Scancode::AcBookmarks),

    BrightnessDown=KEYCODE_FROM_SCANCODE(Scancode::BrightnessDown),
    BrightnessUp=KEYCODE_FROM_SCANCODE(Scancode::BrightnessUp),
    DisplaySwitch=KEYCODE_FROM_SCANCODE(Scancode::DisplaySwitch),
    KbDillumToggle=KEYCODE_FROM_SCANCODE(Scancode::KbDillumToggle),
    KbDillumDown=KEYCODE_FROM_SCANCODE(Scancode::KbDillumDown),
    KbDillumUp=KEYCODE_FROM_SCANCODE(Scancode::KbDillumUp),
    Eject=KEYCODE_FROM_SCANCODE(Scancode::Eject),
    Sleep=KEYCODE_FROM_SCANCODE(Scancode::Sleep)
};
#undef KEYCODE_FROM_SCANCODE
#undef SDL_SCANCODE_TO_KEYCODE
enum class Keymod:uint16
{
	None=0,
	LShift=KMOD_LSHIFT,
	RShift=KMOD_RSHIFT,
	Shift=KMOD_SHIFT,
	LCtrl=KMOD_LCTRL,
	RCtrl=KMOD_RCTRL,
	Ctrl=KMOD_CTRL,
	LAlt=KMOD_LALT,
	RAlt=KMOD_RALT,
	Alt=KMOD_ALT,
	LGUI=KMOD_LGUI,
	RGUI=KMOD_RGUI,
	GUI=KMOD_GUI,
	NumLock=KMOD_NUM,
	CapsLock=KMOD_CAPS,
	Mode=KMOD_MODE,
	Reserved=KMOD_RESERVED,
};
#undef KMOD_ALT
#undef KMOD_GUI
#undef KMOD_CTRL
#undef KMOD_SHIFT
Keymod operator|(Keymod first, Keymod second)noexcept
{
	return Keymod(uint32(first)|uint32(second));
}
Keymod operator&(Keymod first, Keymod second)noexcept
{
	return Keymod(uint32(first)&uint32(second));
}
Keymod operator^(Keymod first, Keymod second)noexcept
{
	return Keymod(uint32(first)^uint32(second));
}
Keymod operator|=(Keymod& first, Keymod second)noexcept
{
	return first=(first|second);
}
Keymod operator&=(Keymod& first, Keymod second)noexcept
{
	return first=(first&second);
}
Keymod operator^=(Keymod& first, Keymod second)noexcept
{
	return first=(first^second);
}
Keymod operator~(Keymod param)noexcept
{
	return Keymod(~uint32(param));
}