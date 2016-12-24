/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
#include "gaplessgrid.c"

/* appearance */
static const char font[]            = "Meslo for Powerline:size=9";

#define NUMCOLORS 14
static const char colors[NUMCOLORS][ColLast][8] = {
	// border    foreground background
	{ "#333333", "#999999", "#000000" }, // normal 
	{ "#770000", "#FFFFFF", "#000000" }, // selected
	{ "#770000", "#FFFFFF", "#666666" }, // urgent
	{ "#000000", "#999999", "#000000" }, // wireless
	{ "#000000", "#999999", "#000000" }, // bat
	{ "#000000", "#999999", "#000000" }, // ram
 	{ "#000000", "#999999", "#000000" }, // cpu
 	{ "#000000", "#999999", "#000000" }, // disk 
 	{ "#000000", "#999999", "#000000" }, // net
 	{ "#000000", "#999999", "#000000" }, // none
 	{ "#000000", "#999999", "#000000" }, // time
 	{ "#000000", "#BB0707", "#000000" }, // none
 	{ "#000000", "#AA0000", "#000000" }, // none
 	{ "#000000", "#AA0000", "#000000" }, // none
	
};

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool clicktofocus	    = True;	/* False means ignore clicks */
static const Bool viewontag         = True;	/* Switch view on tag switch */ 

/* layout(s) */
static const float mfact      = 0.55;	/* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;	/* number of clients in master area */
static const Bool resizehints = False;	/* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol   gaps    arrange function */
	{ "[]=",    True,   tile },    /* first entry is default */
	{ "[M]",    False,  monocle },
	{ "><>",    False,  NULL },    /* no layout function means floating behavior */
	{ "[G]",    True,  gaplessgrid}, 
};

/* tagging */
static Tag tags[] = {
	/* name     	layout      mfact   nmaster */
	{ "www",	&layouts[1], -1,    -1 },
	{ "tty",   	&layouts[0], -1,    -1 },
	{ "dev",   	&layouts[0], -1,    -1 },
	{ "doc",    	&layouts[1], -1,    -1 },
	{ "art",   	&layouts[0], -1,    -1 },
	{ "im",   	&layouts[0], -1,    -1 },
	{ "lab",   	&layouts[0], -1,    -1 },
	{ "misc",   	&layouts[0], -1,    -1 },
	{ "null",   	&layouts[0], -1,    -1 },
};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "mpv",	NULL,       NULL,       0,	    True,	 -1 },
	{ "Dwb",	NULL,       NULL,       1 << 0,	    False,	 -1 },
	{ "Zathura",	NULL,       NULL,       1 << 3,	    False,	 -1 },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenu[]	= { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], 
    "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *dbright[]	= {"xbacklight", "-dec", "5", NULL};
static const char *ibright[]	= {"xbacklight", "-inc", "5", NULL};
static const char *etpad[]   	= {"enable_touchpad", NULL};
static const char *dtpad[]   	= {"disable_touchpad", NULL};
static const char *play[]	= { "mpc", "toggle", NULL };
static const char *suspend[]	= { "sudo", "zzz", NULL };
static const char *term[]	= { "urxvtcd", NULL };
static const char *voldown[]	= { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *volmute[]	= { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volup[]	= { "amixer", "-q", "set", "Master", "5%+", NULL };
static Key keys[] = {
	/* modifier                 key     	            function        argument */
	{ MODKEY,		XK_p,			    spawn,          {.v = dmenu } },
	{ MODKEY|ShiftMask,	XK_Return,		    spawn,          {.v = term } },
	{ MODKEY,		XK_b,			    togglebar,      {0} },
	{ MODKEY,		XK_j,			    focusstack,     {.i = +1 } },
	{ MODKEY,		XK_k,			    focusstack,     {.i = -1 } },
	{ MODKEY,		XK_i,			    incnmaster,     {.i = +1 } },
	{ MODKEY,		XK_d,			    incnmaster,     {.i = -1 } },
	{ MODKEY,		XK_h,			    setmfact,       {.f = -0.05} },
	{ MODKEY,		XK_l,			    setmfact,       {.f = +0.05} },
	{ MODKEY,		XK_Return,		    zoom,           {0} },
	{ MODKEY,		XK_Tab,			    view,           {0} },
	{ MODKEY|ShiftMask,	XK_c,			    killclient,     {0} },
	{ MODKEY,		XK_t,			    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,		XK_f,			    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,		XK_m,			    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,		XK_g,			    setlayout,      {.v = &layouts[3]} },
	{ MODKEY,		XK_space,		    setlayout,      {0} },
	{ MODKEY|ShiftMask,	XK_space,		    togglefloating, {0} },
	{ MODKEY,		XK_0,			    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,			    tag,            {.ui = ~0 } },
	{ MODKEY,		XK_comma,		    focusmon,       {.i = -1 } },
	{ MODKEY,		XK_period,		    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_comma,		    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,	XK_period,		    tagmon,         {.i = +1 } },

	{ WINKEY,		XK_n,			spawn,		{.v = dbright } },
	{ WINKEY,		XK_m,			spawn,		{.v = ibright } },
	{ WINKEY,		XK_k, 			spawn,		{.v = etpad } },
	{ WINKEY,		XK_j, 			spawn,		{.v = dtpad } },
	{ WINKEY,		XK_less,		spawn,		{.v = volmute } },
	{ WINKEY,		XK_o,			spawn,		{.v = play } },
	{ WINKEY,		XK_s,			spawn,		{.v = suspend } },
	{ WINKEY,		XK_x,			spawn,		{.v = volup } },
	{ WINKEY,		XK_z,			spawn,		{.v = voldown } },

	TAGKEYS(		XK_1,			    0)
	TAGKEYS(		XK_2,			    1)
	TAGKEYS(		XK_3,			    2)
	TAGKEYS(		XK_4,			    3)
	TAGKEYS(		XK_5,			    4)
	TAGKEYS(		XK_6,			    5)
	TAGKEYS(		XK_7,			    6)
	TAGKEYS(		XK_8,			    7)
	TAGKEYS(		XK_9,			    8)
	TAGKEYS(		XK_0,			    9)

	{ MODKEY|ShiftMask,	XK_q,			    quit,	    {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkClock, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
//	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = term } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
