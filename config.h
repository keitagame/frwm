/* config.h - cwm 設定ファイル
 * ここを編集してWMをカスタマイズしてください
 */

/* ─────────────────────── 外観 ─────────────────────── */
static const char *font        = "-*-terminus-medium-r-*-*-14-*-*-*-*-*-*-*";
static const char *col_norm_fg = "#bbbbbb";   /* 通常 前景色 */
static const char *col_norm_bg = "#222222";   /* 通常 背景色 */
static const char *col_sel_fg  = "#eeeeee";   /* 選択 前景色 */
static const char *col_sel_bg  = "#005577";   /* 選択 背景色 (アクセント) */
static const char *col_urgent_fg = "#ffffff"; /* 緊急 前景色 */
static const char *col_urgent_bg = "#cc0000"; /* 緊急 背景色 */
static const unsigned int borderpx = 2;       /* ウィンドウ枠幅 (px) */
static const unsigned int snap     = 32;      /* スナップ距離 (px) */
static const int showbar           = 1;       /* バー表示: 1=表示, 0=非表示 */
static const int topbar            = 1;       /* バー位置: 1=上, 0=下 */

/* ─────────────────────── タグ ─────────────────────── */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* ─────────────────────── レイアウト ─────────────────────── */
static const float mfact    = 0.55; /* マスター領域の割合 [0.05..0.95] */
static const int   nmaster  = 1;    /* マスター領域のウィンドウ数 */
static const int   resizehints = 1; /* クライアントのリサイズヒントを尊重する */
static const int   lockfullscreen = 1; /* フルスクリーン中はフォーカス変更を拒否 */

static const Layout layouts[] = {
    /* シンボル  配置関数  */
    { "[T]",  tile    }, /* 最初のレイアウトがデフォルト */
    { "[M]",  monocle }, /* モノクル: 1枚だけ表示 */
    { "[F]",  NULL    }, /* フローティング: 自由配置 */
};

/* ─────────────────────── ウィンドウルール ─────────────────────── */
/* WM_CLASS と WM_NAME でルールを適用する */
static const char broken[] = "broken";
typedef struct {
    const char *class;
    const char *instance;
    const char *title;
    unsigned int tags;     /* 0 = 現在のタグ */
    int isfloating;        /* 1 = フローティング */
    int monitor;           /* -1 = 現在のモニター */
} Rule;

static const Rule rules[] = {
    /* class         instance  title    tags  float monitor */
    { "Gimp",        NULL,     NULL,    0,    1,    -1 },
    { "Firefox",     NULL,     NULL,    1<<1, 0,    -1 }, /* タグ2へ */
    { "mpv",         NULL,     NULL,    0,    1,    -1 },
    { "feh",         NULL,     NULL,    0,    1,    -1 },
    { "Xmessage",    NULL,     NULL,    0,    1,    -1 },
};

/* ─────────────────────── キーバインド ─────────────────────── */
#define MODKEY Mod1Mask   /* Alt キー (Mod4Mask で Super/Win キーに変更可) */
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY, view,        {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY, toggleview,  {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY, tag,         {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY, toggletag,   {.ui = 1 << TAG} },

/* ターミナルコマンド */
static const char *termcmd[]  = { "kitty", NULL };
static const char *termcmd2[] = { "kitty", NULL };
static const char *dmenucmd[] = { "dmenu_run", NULL };

static Key keys[] = {
    /* 修飾キー              キーシム        関数           引数 */
    /* ── アプリ起動 ─────────────────────── */
    { MODKEY,             XK_Return,  spawn,         {.v = termcmd} },
    { MODKEY|ShiftMask,   XK_Return,  spawn,         {.v = termcmd2} },
    { MODKEY,             XK_d,       spawn,         {.v = dmenucmd} },

    /* ── バー ──────────────────────────── */
    { MODKEY,             XK_b,       togglebar,     {0} },

    /* ── フォーカス移動 ─────────────────── */
    { MODKEY,             XK_j,       focusstack,    {.i = +1} },
    { MODKEY,             XK_k,       focusstack,    {.i = -1} },
    { MODKEY,             XK_Tab,     focusstack,    {.i = +1} },

    /* ── マスター調整 ─────────────────── */
    { MODKEY,             XK_i,       incnmaster,    {.i = +1} },
    { MODKEY,             XK_minus,   incnmaster,    {.i = -1} },
    { MODKEY,             XK_h,       setmfact,      {.f = -0.05} },
    { MODKEY,             XK_l,       setmfact,      {.f = +0.05} },

    /* ── ズーム (マスターへ昇格) ────────── */
    { MODKEY,             XK_space,   zoom,          {0} },

    /* ── レイアウト切替 ─────────────────── */
    { MODKEY,             XK_t,       setlayout,     {.v = &layouts[0]} }, /* タイル */
    { MODKEY,             XK_m,       setlayout,     {.v = &layouts[1]} }, /* モノクル */
    { MODKEY,             XK_f,       setlayout,     {.v = &layouts[2]} }, /* フローティング */
    { MODKEY,             XK_comma,   setlayout,     {0} },                /* 前のレイアウト */

    /* ── ウィンドウ操作 ─────────────────── */
    { MODKEY,             XK_q,       killclient,    {0} },
    { MODKEY|ShiftMask,   XK_space,   togglefloating,{0} },
    { MODKEY,             XK_F11,     togglefullscr, {0} },

    /* ── タグ切替 ─────────────────────── */
    { MODKEY,             XK_0,       view,          {.ui = ~0} },     /* 全タグ */
    { MODKEY|ShiftMask,   XK_0,       tag,           {.ui = ~0} },
    TAGKEYS(              XK_1,                      0)
    TAGKEYS(              XK_2,                      1)
    TAGKEYS(              XK_3,                      2)
    TAGKEYS(              XK_4,                      3)
    TAGKEYS(              XK_5,                      4)
    TAGKEYS(              XK_6,                      5)
    TAGKEYS(              XK_7,                      6)
    TAGKEYS(              XK_8,                      7)
    TAGKEYS(              XK_9,                      8)

    /* ── マルチモニター ─────────────────── */
    { MODKEY,             XK_comma,   focusmon,      {.i = -1} },
    { MODKEY,             XK_period,  focusmon,      {.i = +1} },
    { MODKEY|ShiftMask,   XK_comma,   tagmon,        {.i = -1} },
    { MODKEY|ShiftMask,   XK_period,  tagmon,        {.i = +1} },

    /* ── WM 終了 ──────────────────────── */
    { MODKEY|ShiftMask,   XK_q,       quit,          {0} },
};

/* ─────────────────────── マウスバインド ─────────────────────── */
static Button buttons[] = {
    /* クリック位置        マスク     ボタン   関数           引数 */
    { ClkLtSymbol,        0,         Button1, setlayout,     {0} },
    { ClkLtSymbol,        0,         Button3, setlayout,     {.v = &layouts[2]} },
    { ClkWinTitle,        0,         Button2, zoom,          {0} },
    { ClkStatusText,      0,         Button2, spawn,         {.v = termcmd} },
    /* クライアントウィンドウ */
    { ClkClientWin,       MODKEY,    Button1, movemouse,     {0} },
    { ClkClientWin,       MODKEY,    Button2, togglefloating,{0} },
    { ClkClientWin,       MODKEY,    Button3, resizemouse,   {0} },
    /* タグバー */
    { ClkTagBar,          0,         Button1, view,          {0} },
    { ClkTagBar,          0,         Button3, toggleview,    {0} },
    { ClkTagBar,          MODKEY,    Button1, tag,           {0} },
    { ClkTagBar,          MODKEY,    Button3, toggletag,     {0} },
};
