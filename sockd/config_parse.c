#ifndef lint
/*static char yysccsid[] = "from: @(#)yaccpar	1.9 (Berkeley) 02/21/93";*/
static char yyrcsid[]
#if __GNUC__ == 2
  __attribute__ ((unused))
#endif /* __GNUC__ == 2 */
  = "$OpenBSD: skeleton.c,v 1.15 2000/01/27 21:34:23 deraadt Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#define yyparse socks_yyparse
#define yylex socks_yylex
#define yyerror socks_yyerror
#define yychar socks_yychar
#define yyval socks_yyval
#define yylval socks_yylval
#define yydebug socks_yydebug
#define yynerrs socks_yynerrs
#define yyerrflag socks_yyerrflag
#define yyss socks_yyss
#define yysslim socks_yysslim
#define yyssp socks_yyssp
#define yyvs socks_yyvs
#define yyvsp socks_yyvsp
#define yystacksize socks_yystacksize
#define yylhs socks_yylhs
#define yylen socks_yylen
#define yydefred socks_yydefred
#define yydgoto socks_yydgoto
#define yysindex socks_yysindex
#define yyrindex socks_yyrindex
#define yygindex socks_yygindex
#define yytable socks_yytable
#define yycheck socks_yycheck
#define yyname socks_yyname
#define yyrule socks_yyrule
#define YYPREFIX "socks_yy"
#line 45 "config_parse.y"

#include "common.h"

#include "yacconfig.h"

static const char rcsid[] =
"$Id: config_parse.y,v 1.130 2000/06/09 10:45:18 karls Exp $";

__BEGIN_DECLS

#if HAVE_LIBWRAP && SOCKS_SERVER
	extern jmp_buf tcpd_buf;
#endif /* HAVE_LIBWRAP && SOCKS_SERVER */

static void
addressinit __P((struct ruleaddress_t *address));

__END_DECLS

extern int yylineno;
extern char *yytext;

#if SOCKS_SERVER
static struct rule_t				ruleinit;
static struct rule_t				rule;				/* new rule.							*/
static struct protocol_t		protocolmem;	/* new protocolmem.					*/
struct linkedname_t				**userbase;		/* users rule applies to.			*/
#endif

#if SOCKS_CLIENT
static struct serverstate_t	state;
static struct route_t			route;			/* new route.							*/
static struct ruleaddress_t	gw;				/* new gateway.						*/
#endif


static struct ruleaddress_t	src;				/* new src.								*/
static struct ruleaddress_t	dst;				/* new dst.								*/
static struct ruleaddress_t	*ruleaddress;	/* current ruleaddress				*/
static struct extension_t		*extension;		/* new extensions						*/
static struct proxyprotocol_t	*proxyprotocol;/* proxy protocol.					*/

static char							*atype;			/* atype of new address.			*/
static struct in_addr			*ipaddr;			/* new ipaddress						*/
static struct in_addr			*netmask;		/* new netmask							*/
static char							*domain;			/* new domain.							*/

static in_port_t					*port_tcp;		/* new TCP portnumber.				*/
static in_port_t					*port_udp;		/* new UDP portnumber.				*/
static int							*methodv;		/* new authmethods.					*/
static int							*methodc;		/* number of them.					*/
static struct protocol_t		*protocol;		/* new protocol.						*/
static struct command_t			*command;		/* new command.						*/
static enum operator_t			*operator;		/* new operator.						*/

static const struct {
	const char *name;
	const int value;
} syslogfacility[] = {
#ifdef LOG_AUTH
	{ "auth",	LOG_AUTH		},
#endif /* LOG_AUTH */
#ifdef LOG_AUTHPRIV
	{ "authpriv",	LOG_AUTHPRIV		},
#endif /* LOG_AUTHPRIV */
#ifdef LOG_DAEMON
	{ "daemon",	LOG_DAEMON	},
#endif /* LOG_DAEMON */
#ifdef LOG_USER
	{ "user",	LOG_USER		},
#endif /* LOG_USER */
#ifdef LOG_LOCAL0
	{ "local0",	LOG_LOCAL0	},
#endif /* LOG_LOCAL0 */
#ifdef LOG_LOCAL1
	{ "local1",	LOG_LOCAL1	},
#endif /* LOG_LOCAL1 */
#ifdef LOG_LOCAL2
	{ "local2",	LOG_LOCAL2	},
#endif /* LOG_LOCAL2 */
#ifdef LOG_LOCAL3
	{ "local3",	LOG_LOCAL3	},
#endif /* LOG_LOCAL3 */
#ifdef LOG_LOCAL4
	{ "local4",	LOG_LOCAL4	},
#endif /* LOG_LOCAL4 */
#ifdef LOG_LOCAL5
	{ "local5",	LOG_LOCAL5	},
#endif /* LOG_LOCAL5 */
#ifdef LOG_LOCAL6
	{ "local6",	LOG_LOCAL6	},
#endif /* LOG_LOCAL6 */
#ifdef LOG_LOCAL7
	{ "local7",	LOG_LOCAL7	}
#endif /* LOG_LOCAL7 */
};


#define YYDEBUG 1

#define ADDMETHOD(method) \
	do { \
		if (*methodc >= AUTHMETHOD_MAX)	\
			yyerror("internal error or duplicate methods given");	\
		methodv[(*methodc)++] = method; \
	} while (0)


#line 155 "config_parse.y"
typedef union {
	char	*string;
	uid_t	uid;
} YYSTYPE;
#line 160 "y.tab.c"
#define SERVERCONFIG 257
#define CLIENTCONFIG 258
#define DEPRECATED 259
#define CLIENTRULE 260
#define INTERNAL 261
#define EXTERNAL 262
#define DEBUGING 263
#define RESOLVEPROTOCOL 264
#define SRCHOST 265
#define NOMISMATCH 266
#define NOUNKNOWN 267
#define EXTENSION 268
#define BIND 269
#define PRIVILEGED 270
#define IOTIMEOUT 271
#define CONNECTTIMEOUT 272
#define METHOD 273
#define NONE 274
#define GSSAPI 275
#define UNAME 276
#define RFC931 277
#define COMPATIBILITY 278
#define REUSEADDR 279
#define SAMEPORT 280
#define USERNAME 281
#define USER_PRIVILEGED 282
#define USER_UNPRIVILEGED 283
#define USER_LIBWRAP 284
#define LOGOUTPUT 285
#define LOGFILE 286
#define ROUTE 287
#define VIA 288
#define VERDICT_BLOCK 289
#define VERDICT_PASS 290
#define PROTOCOL 291
#define PROTOCOL_TCP 292
#define PROTOCOL_UDP 293
#define PROTOCOL_FAKE 294
#define PROXYPROTOCOL 295
#define PROXYPROTOCOL_SOCKS_V4 296
#define PROXYPROTOCOL_SOCKS_V5 297
#define PROXYPROTOCOL_MSPROXY_V2 298
#define USER 299
#define COMMAND 300
#define COMMAND_BIND 301
#define COMMAND_CONNECT 302
#define COMMAND_UDPASSOCIATE 303
#define COMMAND_BINDREPLY 304
#define COMMAND_UDPREPLY 305
#define ACTION 306
#define LINE 307
#define LIBWRAPSTART 308
#define OPERATOR 309
#define LOG 310
#define LOG_CONNECT 311
#define LOG_DATA 312
#define LOG_DISCONNECT 313
#define LOG_ERROR 314
#define LOG_IOOPERATION 315
#define IPADDRESS 316
#define DOMAIN 317
#define DIRECT 318
#define PORT 319
#define PORTNUMBER 320
#define SERVICENAME 321
#define NUMBER 322
#define FROM 323
#define TO 324
#define YYERRCODE 256
short socks_yylhs[] = {                                        -1,
    0,    0,   45,    1,    1,    1,    1,    1,    2,    2,
    2,    2,   22,   23,   23,   46,   46,   46,   46,   46,
   46,   46,   44,   44,   44,   44,   44,   44,    3,   52,
   21,    7,    8,    8,    8,    9,    9,   10,   11,   12,
   12,   28,   29,   30,   30,   31,   32,   33,   34,   24,
   24,   24,   35,   36,   37,   37,   47,   47,   47,   48,
   49,   50,   51,   26,   27,   25,   38,   39,   39,   40,
   40,   13,   14,   14,   14,   15,   16,   16,   17,   17,
   85,   41,   43,   43,   43,   43,   42,   42,   60,   61,
   61,   61,   61,   62,   62,   57,   58,   58,   58,   58,
   58,   58,   58,   59,   59,   63,   63,   18,   20,   20,
   20,   20,   20,   19,   19,    4,    6,    6,    5,    5,
   64,   65,   67,   67,   67,   67,   67,   66,   66,   68,
   69,   70,   54,   55,   55,   55,   55,   55,   56,   56,
   76,   77,   53,   71,   71,   73,   73,   73,   72,   78,
   78,   74,   75,   79,   79,   79,   83,   83,   80,   81,
   86,   84,   82,
};
short socks_yylen[] = {                                         2,
    2,    2,    1,    0,    2,    2,    2,    2,    0,    2,
    2,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    8,
    0,    3,    1,    1,    1,    1,    2,    3,    1,    1,
    2,    3,    1,    1,    2,    5,    0,    4,    0,    1,
    1,    1,    3,    1,    1,    2,    1,    1,    1,    3,
    3,    3,    1,    3,    3,    3,    3,    1,    1,    1,
    2,    3,    1,    1,    1,    3,    1,    1,    1,    2,
    0,    4,    1,    1,    1,    1,    1,    2,    7,    1,
    1,    1,    1,    0,    2,    6,    1,    1,    1,    1,
    1,    1,    1,    0,    2,    1,    1,    3,    1,    1,
    1,    1,    1,    1,    2,    3,    1,    1,    1,    2,
    2,    3,    1,    1,    1,    1,    1,    1,    2,    3,
    3,    3,    3,    1,    1,    1,    1,    1,    0,    2,
    1,    1,    1,    4,    2,    2,    2,    1,    1,    1,
    1,    1,    1,    0,    3,    2,    1,    1,    3,    1,
    1,    1,    1,
};
short socks_yydefred[] = {                                      0,
    3,   13,    0,    9,    4,    0,    0,   29,    0,    0,
    0,   31,   10,   15,   52,   11,   14,   51,   50,   12,
    0,   47,   49,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  106,  107,    5,   17,   27,   28,   26,   24,
   25,   18,   19,   20,   23,   16,   21,    6,   22,   57,
   58,   59,    8,    7,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   81,    0,    0,    0,
    0,    0,   66,   74,   75,   73,   72,   54,    0,   53,
    0,    0,    0,    0,   77,   78,    0,   76,   43,    0,
   42,   64,   65,    0,   68,   69,    0,   67,   63,   60,
   61,   62,    0,    0,    0,    0,    0,    0,  101,  102,
  103,   98,   97,    0,    0,  100,   99,   56,  136,  137,
  134,  135,  138,    0,    0,   93,   90,    0,    0,   92,
   91,  149,    0,   48,   80,   45,   83,   84,   85,   86,
   82,    0,   71,    0,    0,    0,    0,    0,    0,  105,
  141,    0,    0,    0,  140,    0,   95,    0,    0,   46,
   88,  117,  118,  116,    0,   33,   34,   35,    0,   32,
   39,    0,   38,  109,  110,  111,  112,  113,  108,    0,
  130,  123,  124,  125,  126,  127,  122,    0,    0,  142,
  121,    0,    0,  143,    0,    0,    0,  163,  160,  156,
    0,    0,  120,   37,   41,  115,  129,   96,    0,  152,
  131,    0,    0,    0,    0,   89,    0,  162,  158,  155,
  157,  132,    0,  145,  153,    0,  133,    0,  148,   30,
  161,  159,  151,  150,    0,  146,  147,  144,
};
short socks_yydgoto[] = {                                       3,
    7,    6,   14,  109,  164,  165,  110,  169,  170,  111,
  172,  173,   15,   77,   38,   87,   88,  112,  179,  180,
   59,    4,   16,   17,   18,   39,   40,  122,   90,   91,
   42,   61,   43,   62,   19,   79,   80,   45,   97,   98,
  113,  141,  142,   47,    5,   48,   49,   50,   51,   52,
  100,   20,  195,  196,  124,  125,   53,  114,  115,   54,
  128,  129,   55,  152,  116,  187,  188,  117,  153,  191,
  211,  212,  227,  213,  229,  154,  192,  235,  160,  200,
  201,  202,  220,  221,   94,  232,
};
short socks_yysindex[] = {                                   -233,
    0,    0,    0,    0,    0,  -10,  224,    0,  -25,    2,
    4,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -262,    0,    0,    8,   15,   36,   45,   57,   58,   59,
   60,   61,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -65, -202, -224, -165,   -1,    6,
   72,   73, -231, -137, -189, -186,    0, -234, -144, -144,
 -144, -251,    0,    0,    0,    0,    0,    0, -165,    0,
 -193, -236, -176, -176,    0,    0, -231,    0,    0, -137,
    0,    0,    0, -198,    0,    0, -234,    0,    0,    0,
    0,    0,   83,   84,   85,   86,   87,   88,    0,    0,
    0,    0,    0, -251, -175,    0,    0,    0,    0,    0,
    0,    0,    0, -193, -175,    0,    0, -236, -175,    0,
    0,    0, -172,    0,    0,    0,    0,    0,    0,    0,
    0, -198,    0, -206, -255, -132, -220, -155, -203,    0,
    0, -251, -171,   97,    0, -134,    0, -236, -289,    0,
    0,    0,    0,    0, -206,    0,    0,    0, -255,    0,
    0, -132,    0,    0,    0,    0,    0,    0,    0, -220,
    0,    0,    0,    0,    0,    0,    0, -203,   33,    0,
    0,  101, -227,    0,  103, -193,   38,    0,    0,    0,
  119, -216,    0,    0,    0,    0,    0,    0, -227,    0,
    0,  120, -172, -217,   41,    0, -149,    0,    0,    0,
    0,    0, -293,    0,    0, -172,    0, -172,    0,    0,
    0,    0,    0,    0, -172,    0,    0,    0,
};
short socks_yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,  173,  175,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -142,    0,    0,    0,    0,    0,    0,   96,    0,
 -129, -127,    0,    0,    0,    0,  128,    0,    0,   54,
    0,    0,    0,    0,    0,    0,  160,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -120,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -119,    0,    0,    0, -118,    0,    0,
    0,    0,  192,    0,    0,    0,    0,    0,    0,    0,
    0,    1,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   75,    0,    0,    0,    0,    0,   90,    0,    0,
    0,    0,    0,    0, -117,    0,    0,    0, -111,    0,
    0,  -75,    0,    0,    0,    0,    0,    0,    0,  -78,
    0,    0,    0,    0,    0,    0,    0,   -2,    0,    0,
    0,    0,    0,    0,    0,   93,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -123,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -54,    0,  -54,    0,    0,
    0,    0,    0,    0, -123,    0,    0,    0,
};
short socks_yygindex[] = {                                      0,
    0,    0,  179,  -72,   44,    0,  -71,    0,   39,  -67,
    0,   51,  203,    0,    0,    0,  124,  -69,   46,    0,
    0,    0,    0,    0,    0,    0,    0,  220,    0,  138,
    0,    0,    0,    0,  222,    0,  152,    0,    0,  139,
   11,   98,    0,    0,    0,    0,    0,    0,    0,    0,
   43,    0,    0,    0,    0, -108,    0,    0, -101,    0,
    0, -102,  217,  -91,  -63,   55,    0,  -61,    0,    0,
   30,  -80,    0,   28,    0,    0,    0,    0, -196,    0,
   42,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 514
short socks_yytable[] = {                                      13,
   87,  154,  133,  134,  104,  139,   94,  119,  119,  120,
   87,  121,  150,   36,  126,  155,  224,   46,  130,  198,
  131,   28,  233,    1,    2,  157,   33,   34,  234,  236,
  199,  237,   56,  156,   85,   86,   28,  158,  238,  103,
  166,  167,  168,  104,   95,   96,  114,  105,  106,   40,
  189,  119,  120,   44,  121,  197,  107,   72,  108,   57,
  126,   58,  105,   44,  130,   63,  131,   74,   75,   76,
  154,  107,   64,  108,   25,  137,  138,  139,  140,   28,
  174,  175,  176,  177,  178,  162,  163,  215,  132,  210,
  126,  123,  127,   65,  130,   55,  131,  103,  132,  210,
  225,  104,   66,  199,  218,   55,  106,  182,  183,  184,
  185,  186,  101,  102,   67,   68,   69,   70,   71,   73,
   78,   81,  128,  119,  120,   87,  121,   79,   82,   83,
   84,   89,   92,  226,  123,   93,   99,   79,  127,  132,
  144,  145,  146,  147,  148,  149,  159,  151,  171,  154,
  119,  181,  190,  194,  193,  119,   36,  208,  209,   70,
  214,   36,  216,  217,  154,  230,  223,  154,  127,   70,
  231,  154,    2,  119,    1,  154,  154,  119,   44,   36,
  104,  119,  119,   36,  154,   36,  154,   36,   36,  114,
  119,  154,  119,  139,  114,   94,   36,   40,   36,  104,
  154,  154,  104,  139,   94,  119,  123,  204,  203,   37,
  135,   36,  114,  154,   94,   40,  114,  139,  154,   40,
  114,  114,  205,   40,   40,  206,   41,  136,   44,  114,
  118,  114,   40,   35,   40,  143,  154,   60,  222,  161,
  154,  228,  207,  219,  114,  154,    0,   40,    8,    0,
    0,    0,    9,   10,    0,    0,    0,    0,    0,   87,
   87,   87,   87,    0,   87,   87,    0,    0,   87,    0,
  128,   87,   87,   87,   11,    0,   12,    0,   87,    0,
    0,    0,   87,   87,   87,   87,    0,    0,  128,   87,
   87,   87,  128,    0,    0,   87,  128,  128,    0,   87,
   87,    0,    0,    0,    0,  128,    0,  128,   87,    0,
   87,    0,   44,   44,   44,   44,    0,   44,   44,    0,
  128,   44,    0,   87,   44,   44,   44,    0,    0,    0,
    0,   44,    0,    0,    0,   44,   44,   44,   44,    0,
    0,    0,   44,   44,   44,    0,    0,    0,   44,    0,
    0,    0,    0,   44,   55,   55,   55,   55,   55,   55,
   55,    0,    0,   55,    0,    0,   55,   55,   55,    0,
    0,    0,    0,   55,    0,    0,   44,   55,   55,   55,
   55,    0,   55,    0,   55,   55,   79,   79,   79,   79,
    0,   79,   79,    0,    0,   79,    0,    0,   79,   79,
   79,    0,    0,    0,    0,   79,    0,    0,    0,   79,
   79,   79,   79,    0,    0,    0,   79,   79,   70,   70,
   70,   70,    0,   70,   70,    0,    0,   70,    0,    0,
   70,   70,   70,    0,    0,    0,    0,   70,    0,    0,
    0,   70,   70,   70,   70,    0,    0,    0,   70,   70,
  154,  154,  154,  154,    0,  154,  154,    0,    0,  154,
    0,    0,  154,  154,  154,    0,    0,    0,    0,  154,
    0,    0,    0,  154,  154,  154,  154,    0,    0,    0,
  154,  154,    8,   21,   22,   23,    0,   10,   24,    0,
    0,   25,    0,    0,   26,   27,   28,    0,    0,    0,
    0,   29,    0,    0,    0,   30,   31,   32,   11,    0,
    0,    0,   33,   34,
};
short socks_yycheck[] = {                                      10,
    0,  125,   83,   84,  125,  125,  125,  125,   81,   81,
   10,   81,  114,  125,   82,  124,  213,    7,   82,  309,
   82,  273,  316,  257,  258,  128,  289,  290,  322,  226,
  320,  228,   58,  125,  266,  267,  273,  129,  235,  291,
  296,  297,  298,  295,  279,  280,  125,  299,  300,  125,
  152,  124,  124,    0,  124,  158,  308,  123,  310,   58,
  128,   58,  299,   10,  128,   58,  128,  292,  293,  294,
  125,  308,   58,  310,  268,  274,  275,  276,  277,  273,
  301,  302,  303,  304,  305,  292,  293,  196,  316,  317,
  158,   81,   82,   58,  158,    0,  158,  291,  316,  317,
  318,  295,   58,  320,  321,   10,  300,  311,  312,  313,
  314,  315,   70,   71,   58,   58,   58,   58,   58,  322,
  286,  123,  125,  196,  196,  125,  196,    0,  123,   58,
   58,  269,  322,  214,  124,  322,  281,   10,  128,  316,
   58,   58,   58,   58,   58,   58,  319,  323,  281,  273,
  268,  307,  324,  288,   58,  273,  268,  125,   58,    0,
   58,  273,  125,   45,  288,  125,   47,  291,  158,   10,
  320,  295,    0,  291,    0,  299,  300,  295,  125,  291,
  323,  299,  300,  295,  308,    7,  310,  299,  300,  268,
  308,    0,  310,  323,  273,  323,  308,  273,  310,  125,
  324,   10,  323,  323,  323,  323,  196,  169,  165,    7,
   87,  323,  291,  268,  125,  291,  295,  125,  273,  295,
  299,  300,  172,  299,  300,  180,    7,   90,    7,  308,
   79,  310,  308,   10,  310,   97,  291,   21,  209,  142,
  295,  214,  188,  202,  323,  300,   -1,  323,  259,   -1,
   -1,   -1,  263,  264,   -1,   -1,   -1,   -1,   -1,  259,
  260,  261,  262,   -1,  264,  265,   -1,   -1,  268,   -1,
  273,  271,  272,  273,  285,   -1,  287,   -1,  278,   -1,
   -1,   -1,  282,  283,  284,  285,   -1,   -1,  291,  289,
  290,  291,  295,   -1,   -1,  295,  299,  300,   -1,  299,
  300,   -1,   -1,   -1,   -1,  308,   -1,  310,  308,   -1,
  310,   -1,  259,  260,  261,  262,   -1,  264,  265,   -1,
  323,  268,   -1,  323,  271,  272,  273,   -1,   -1,   -1,
   -1,  278,   -1,   -1,   -1,  282,  283,  284,  285,   -1,
   -1,   -1,  289,  290,  291,   -1,   -1,   -1,  295,   -1,
   -1,   -1,   -1,  300,  259,  260,  261,  262,  263,  264,
  265,   -1,   -1,  268,   -1,   -1,  271,  272,  273,   -1,
   -1,   -1,   -1,  278,   -1,   -1,  323,  282,  283,  284,
  285,   -1,  287,   -1,  289,  290,  259,  260,  261,  262,
   -1,  264,  265,   -1,   -1,  268,   -1,   -1,  271,  272,
  273,   -1,   -1,   -1,   -1,  278,   -1,   -1,   -1,  282,
  283,  284,  285,   -1,   -1,   -1,  289,  290,  259,  260,
  261,  262,   -1,  264,  265,   -1,   -1,  268,   -1,   -1,
  271,  272,  273,   -1,   -1,   -1,   -1,  278,   -1,   -1,
   -1,  282,  283,  284,  285,   -1,   -1,   -1,  289,  290,
  259,  260,  261,  262,   -1,  264,  265,   -1,   -1,  268,
   -1,   -1,  271,  272,  273,   -1,   -1,   -1,   -1,  278,
   -1,   -1,   -1,  282,  283,  284,  285,   -1,   -1,   -1,
  289,  290,  259,  260,  261,  262,   -1,  264,  265,   -1,
   -1,  268,   -1,   -1,  271,  272,  273,   -1,   -1,   -1,
   -1,  278,   -1,   -1,   -1,  282,  283,  284,  285,   -1,
   -1,   -1,  289,  290,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 324
#if YYDEBUG
char *socks_yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,"':'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"SERVERCONFIG","CLIENTCONFIG","DEPRECATED","CLIENTRULE","INTERNAL","EXTERNAL",
"DEBUGING","RESOLVEPROTOCOL","SRCHOST","NOMISMATCH","NOUNKNOWN","EXTENSION",
"BIND","PRIVILEGED","IOTIMEOUT","CONNECTTIMEOUT","METHOD","NONE","GSSAPI",
"UNAME","RFC931","COMPATIBILITY","REUSEADDR","SAMEPORT","USERNAME",
"USER_PRIVILEGED","USER_UNPRIVILEGED","USER_LIBWRAP","LOGOUTPUT","LOGFILE",
"ROUTE","VIA","VERDICT_BLOCK","VERDICT_PASS","PROTOCOL","PROTOCOL_TCP",
"PROTOCOL_UDP","PROTOCOL_FAKE","PROXYPROTOCOL","PROXYPROTOCOL_SOCKS_V4",
"PROXYPROTOCOL_SOCKS_V5","PROXYPROTOCOL_MSPROXY_V2","USER","COMMAND",
"COMMAND_BIND","COMMAND_CONNECT","COMMAND_UDPASSOCIATE","COMMAND_BINDREPLY",
"COMMAND_UDPREPLY","ACTION","LINE","LIBWRAPSTART","OPERATOR","LOG",
"LOG_CONNECT","LOG_DATA","LOG_DISCONNECT","LOG_ERROR","LOG_IOOPERATION",
"IPADDRESS","DOMAIN","DIRECT","PORT","PORTNUMBER","SERVICENAME","NUMBER","FROM",
"TO",
};
char *socks_yyrule[] = {
"$accept : configtype",
"configtype : serverinit serverline",
"configtype : clientinit clientline",
"serverinit : SERVERCONFIG",
"serverline :",
"serverline : serverline '\\n'",
"serverline : serverline serverconfig",
"serverline : serverline clientrule",
"serverline : serverline rule",
"clientline :",
"clientline : clientline '\\n'",
"clientline : clientline clientconfig",
"clientline : clientline route",
"clientinit : CLIENTCONFIG",
"clientconfig : clientoption",
"clientconfig : deprecated",
"serverconfig : authmethod",
"serverconfig : deprecated",
"serverconfig : internal",
"serverconfig : external",
"serverconfig : logoutput",
"serverconfig : serveroption",
"serverconfig : userids",
"serveroption : compatibility",
"serveroption : connecttimeout",
"serveroption : extension",
"serveroption : iotimeout",
"serveroption : resolveprotocol",
"serveroption : srchost",
"deprecated : DEPRECATED",
"route : ROUTE routeinit '{' routeoptions fromto gateway routeoptions '}'",
"routeinit :",
"proxyprotocol : PROXYPROTOCOL ':' proxyprotocols",
"proxyprotocolname : PROXYPROTOCOL_SOCKS_V4",
"proxyprotocolname : PROXYPROTOCOL_SOCKS_V5",
"proxyprotocolname : PROXYPROTOCOL_MSPROXY_V2",
"proxyprotocols : proxyprotocolname",
"proxyprotocols : proxyprotocolname proxyprotocols",
"user : USER ':' usernames",
"username : USERNAME",
"usernames : username",
"usernames : username usernames",
"extension : EXTENSION ':' extensions",
"extensionname : BIND",
"extensions : extensionname",
"extensions : extensionname extensions",
"internal : INTERNAL internalinit ':' ipaddress port",
"internalinit :",
"external : EXTERNAL externalinit ':' ipaddress",
"externalinit :",
"clientoption : logoutput",
"clientoption : debuging",
"clientoption : resolveprotocol",
"logoutput : LOGOUTPUT ':' logoutputdevices",
"logoutputdevice : LOGFILE",
"logoutputdevices : logoutputdevice",
"logoutputdevices : logoutputdevice logoutputdevices",
"userids : user_privileged",
"userids : user_unprivileged",
"userids : user_libwrap",
"user_privileged : USER_PRIVILEGED ':' userid",
"user_unprivileged : USER_UNPRIVILEGED ':' userid",
"user_libwrap : USER_LIBWRAP ':' userid",
"userid : USERNAME",
"iotimeout : IOTIMEOUT ':' NUMBER",
"connecttimeout : CONNECTTIMEOUT ':' NUMBER",
"debuging : DEBUGING ':' NUMBER",
"compatibility : COMPATIBILITY ':' compatibilitys",
"compatibilityname : REUSEADDR",
"compatibilityname : SAMEPORT",
"compatibilitys : compatibilityname",
"compatibilitys : compatibilityname compatibilitys",
"resolveprotocol : RESOLVEPROTOCOL ':' resolveprotocolname",
"resolveprotocolname : PROTOCOL_FAKE",
"resolveprotocolname : PROTOCOL_TCP",
"resolveprotocolname : PROTOCOL_UDP",
"srchost : SRCHOST ':' srchostoptions",
"srchostoption : NOMISMATCH",
"srchostoption : NOUNKNOWN",
"srchostoptions : srchostoption",
"srchostoptions : srchostoption srchostoptions",
"$$1 :",
"authmethod : METHOD ':' $$1 authmethods",
"authmethodname : NONE",
"authmethodname : GSSAPI",
"authmethodname : UNAME",
"authmethodname : RFC931",
"authmethods : authmethodname",
"authmethods : authmethodname authmethods",
"clientrule : CLIENTRULE verdict '{' clientruleoptions fromto clientruleoptions '}'",
"clientruleoption : authmethod",
"clientruleoption : libwrap",
"clientruleoption : log",
"clientruleoption : user",
"clientruleoptions :",
"clientruleoptions : clientruleoption clientruleoptions",
"rule : verdict '{' ruleoptions fromto ruleoptions '}'",
"ruleoption : authmethod",
"ruleoption : command",
"ruleoption : libwrap",
"ruleoption : log",
"ruleoption : protocol",
"ruleoption : proxyprotocol",
"ruleoption : user",
"ruleoptions :",
"ruleoptions : ruleoption ruleoptions",
"verdict : VERDICT_BLOCK",
"verdict : VERDICT_PASS",
"command : COMMAND ':' commands",
"commandname : COMMAND_BIND",
"commandname : COMMAND_CONNECT",
"commandname : COMMAND_UDPASSOCIATE",
"commandname : COMMAND_BINDREPLY",
"commandname : COMMAND_UDPREPLY",
"commands : commandname",
"commands : commandname commands",
"protocol : PROTOCOL ':' protocols",
"protocolname : PROTOCOL_TCP",
"protocolname : PROTOCOL_UDP",
"protocols : protocolname",
"protocols : protocolname protocols",
"fromto : srcaddress dstaddress",
"log : LOG ':' logs",
"logname : LOG_CONNECT",
"logname : LOG_DATA",
"logname : LOG_DISCONNECT",
"logname : LOG_ERROR",
"logname : LOG_IOOPERATION",
"logs : logname",
"logs : logname logs",
"libwrap : LIBWRAPSTART ':' LINE",
"srcaddress : from ':' address",
"dstaddress : to ':' address",
"gateway : via ':' gwaddress",
"routeoption : command",
"routeoption : extension",
"routeoption : protocol",
"routeoption : proxyprotocol",
"routeoption : authmethod",
"routeoptions :",
"routeoptions : routeoption routeoptions",
"from : FROM",
"to : TO",
"via : VIA",
"address : ipaddress '/' netmask port",
"address : domain port",
"gwaddress : ipaddress port",
"gwaddress : domain port",
"gwaddress : direct",
"ipaddress : IPADDRESS",
"netmask : NUMBER",
"netmask : IPADDRESS",
"domain : DOMAIN",
"direct : DIRECT",
"port :",
"port : PORT portoperator portnumber",
"port : PORT portrange",
"portnumber : portservice",
"portnumber : portstart",
"portrange : portstart '-' portend",
"portstart : PORTNUMBER",
"portend : PORTNUMBER",
"portservice : SERVICENAME",
"portoperator : OPERATOR",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 1044 "config_parse.y"

#define INTERACTIVE		0

#if SOCKS_SERVER
#define ELECTRICFENCE	0
#else
#define ELECTRICFENCE	0
#endif


#if ELECTRICFENCE
	extern int EF_PROTECT_FREE;
	extern int EF_ALLOW_MALLOC_0;
	extern int EF_ALIGNMENT;
	extern int EF_PROTECT_BELOW;
#endif /* ELECTRICFENCE */

extern FILE *yyin;

int parseinit;

int
readconfig(filename)
	const char *filename;
{
	const char *function = "readconfig()";

#if ELECTRICFENCE
	EF_PROTECT_FREE         = 1;
	EF_ALLOW_MALLOC_0       = 1;
	EF_ALIGNMENT            = 0;
	EF_PROTECT_BELOW			= 0;
#endif /* ELECTRICFENCE */

/*	yydebug		= 0; */
	yylineno		= 1;
	parseinit	= 0;

	if ((yyin = fopen(filename, "r")) == NULL) {
		swarn("%s: %s", function, filename);
		return -1;
	}

	yyparse();
	fclose(yyin);

	errno = 0; /* yacc for some reason alters errno sometimes. */

	return 0;
}


void
yyerror(s)
	const char *s;
{

	serrx(EXIT_FAILURE, "%s: error on line %d, near '%.10s': %s",
	config.option.configfile, yylineno,
	(yytext == NULL || *yytext == NUL) ? "'start of line'" : yytext, s);
}


void
yywarn(s)
	const char *s;
{
	swarnx("%s: warning on line %d, near '%.10s': %s",
	config.option.configfile, yylineno,
	(yytext == NULL || *yytext == NUL) ? "'start of line'" : yytext, s);
}

static void
addressinit(address)
	struct ruleaddress_t *address;
{
		ruleaddress	= address;

		atype			= &ruleaddress->atype;
		ipaddr		= &ruleaddress->addr.ipv4.ip;
		netmask		= &ruleaddress->addr.ipv4.mask;
		domain		= ruleaddress->addr.domain;
		port_tcp		= &ruleaddress->port.tcp;
		port_udp		= &ruleaddress->port.udp;
		operator		= &ruleaddress->operator;
}
#line 783 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
#if defined(__cplusplus) || __STDC__
static int yygrowstack(void)
#else
static int yygrowstack()
#endif
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        goto bail;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        goto bail;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
bail:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return -1;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
#if defined(__cplusplus) || __STDC__
yyparse(void)
#else
yyparse()
#endif
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 3:
#line 250 "config_parse.y"
{
#if SOCKS_SERVER
		protocol			= &protocolmem;
		extension		= &config.extension;
		methodv			= config.methodv;
		methodc			= &config.methodc;
#endif
	}
break;
case 4:
#line 261 "config_parse.y"
{ yyval.string = NULL; }
break;
case 9:
#line 268 "config_parse.y"
{ yyval.string = NULL; }
break;
case 13:
#line 275 "config_parse.y"
{
	}
break;
case 29:
#line 301 "config_parse.y"
{
		yyerror("given keyword is deprecated");
	}
break;
case 30:
#line 305 "config_parse.y"
{
#if SOCKS_CLIENT
		route.src		= src;
		route.dst		= dst;
		ruleaddress2sockshost(&gw, &route.gw.host, SOCKS_TCP);
		route.gw.state	= state;

		addroute(&route);
#endif
	}
break;
case 31:
#line 317 "config_parse.y"
{
#if SOCKS_CLIENT
		command			= &state.command;
		extension		= &state.extension;
		methodv			= state.methodv;
		methodc			= &state.methodc;
		protocol			= &state.protocol;
		proxyprotocol	= &state.proxyprotocol;

		bzero(&state, sizeof(state));
		bzero(&route, sizeof(route));
		bzero(&gw, sizeof(gw));
		bzero(&src, sizeof(src));
		bzero(&dst, sizeof(dst));
		src.atype		= SOCKS_ADDR_IPV4;
		dst.atype		= SOCKS_ADDR_IPV4;
#endif
	}
break;
case 33:
#line 341 "config_parse.y"
{
			proxyprotocol->socks_v4 = 1;
	}
break;
case 34:
#line 344 "config_parse.y"
{
			proxyprotocol->socks_v5 = 1;
	}
break;
case 35:
#line 347 "config_parse.y"
{
			proxyprotocol->msproxy_v2 = 1;
	}
break;
case 39:
#line 359 "config_parse.y"
{
#if SOCKS_SERVER
#if !HAVE_LIBWRAP
		if (strcmp(yyvsp[0].string, method2string(AUTHMETHOD_RFC931)) == 0)
			yyerror("method rfc931 requires libwrap");
#endif /* !HAVE_LIBWRAP */
		if (adduser(userbase, yyvsp[0].string) == NULL)
			yyerror(NOMEM);
#endif /* SOCKS_SERVER */
	}
break;
case 43:
#line 378 "config_parse.y"
{
			extension->bind = 1;
	}
break;
case 46:
#line 388 "config_parse.y"
{
#if SOCKS_SERVER
		if (config.state.init) {
			int i;

			for (i = 0; i < config.internalc; ++i)
				if (config.internalv[i].addr.sin_addr.s_addr == ipaddr->s_addr
				&&	 config.internalv[i].addr.sin_port == *port_tcp)
					break;

			if (i == config.internalc)
				swarnx("can not change internal addresses once running");
		}
#endif /* SOCKS_SERVER */
	}
break;
case 47:
#line 405 "config_parse.y"
{
#if SOCKS_SERVER
	static struct ruleaddress_t mem;
	struct servent	*service;

	addressinit(&mem);

	if (!config.state.init) {
		if ((config.internalv = (struct listenaddress_t *)
		realloc(config.internalv, sizeof(*config.internalv) * ++config.internalc))
		== NULL)
			yyerror(NOMEM);

		bzero(&config.internalv[config.internalc - 1].addr,
		sizeof((*config.internalv).addr));
		config.internalv[config.internalc - 1].addr.sin_family = AF_INET;

		ipaddr		= &config.internalv[config.internalc - 1].addr.sin_addr;
		port_tcp		= &config.internalv[config.internalc - 1].addr.sin_port;
	}
	else { /* can only set internal addresses once. */
		static struct in_addr inaddrmem;
		static in_port_t portmem;

		ipaddr		= &inaddrmem;
		port_tcp		= &portmem;
	}

	/* set default port. */
	if ((service = getservbyname("socks", "tcp")) == NULL)
		*port_tcp = htons(SOCKD_PORT);
	else
		*port_tcp = (in_port_t)service->s_port;
#endif
	}
break;
case 48:
#line 442 "config_parse.y"
{
#if SOCKS_SERVER
		if (config.externalv[config.externalc - 1].sin_addr.s_addr
		== htonl(INADDR_ANY))
			yyerror("external address can't be a wildcard address");
#endif
		}
break;
case 49:
#line 451 "config_parse.y"
{
#if SOCKS_SERVER
		static struct ruleaddress_t mem;

		if ((config.externalv = (struct sockaddr_in *)realloc(config.externalv,
		sizeof(*config.externalv) * ++config.externalc)) == NULL)
			yyerror(NOMEM);

		bzero(&config.externalv[config.externalc - 1], sizeof(*config.externalv));
		config.externalv[config.externalc - 1].sin_family = AF_INET;

		addressinit(&mem);

		ipaddr = &config.externalv[config.externalc - 1].sin_addr;
#endif
	}
break;
case 54:
#line 477 "config_parse.y"
{
		if (!config.state.init) {
			const char *syslogname = "syslog";

			if (strncmp(yyvsp[0].string, syslogname, strlen(syslogname)) == 0
			&& (yyvsp[0].string[strlen(syslogname)] == NUL || yyvsp[0].string[strlen(syslogname)] == '/')) {
				char *sl;

				config.log.type |= LOGTYPE_SYSLOG;

				if (*(sl = &(yyvsp[0].string[strlen(syslogname)])) == '/') { /* facility. */
					size_t i;

					for (i = 0, ++sl; i < ELEMENTS(syslogfacility); ++i)
						if (strcmp(sl, syslogfacility[i].name) == 0)
							break;

					if (i == ELEMENTS(syslogfacility))
						serrx(EXIT_FAILURE, "unknown syslog facility \"%s\"", sl);
					config.log.facility = syslogfacility[i].value;
				}
				else
					config.log.facility = LOG_DAEMON; /* default. */
			}
			else {
				config.log.type |= LOGTYPE_FILE;

				if ((config.log.fpv = (FILE **)realloc(config.log.fpv,
				sizeof(*config.log.fpv) * (config.log.fpc + 1))) == NULL
				|| (config.log.fplockv = (int *)realloc(config.log.fplockv,
				sizeof(*config.log.fplockv) * (config.log.fpc + 1))) == NULL)
					serrx(EXIT_FAILURE, NOMEM);

				if ((config.log.fplockv[config.log.fpc]
				= socks_mklock(SOCKS_LOCKFILE)) == -1)
					serr(EXIT_FAILURE, "socks_mklock()");

				if (strcmp(yyvsp[0].string, "stdout") == 0)
					config.log.fpv[config.log.fpc] = stdout;
				else if (strcmp(yyvsp[0].string, "stderr") == 0)
					config.log.fpv[config.log.fpc] = stderr;
				else {
					int flag;

					if ((config.log.fpv[config.log.fpc] = fopen(yyvsp[0].string, "a"))
					== NULL)
						serr(EXIT_FAILURE, "fopen(%s)", yyvsp[0].string);

					if ((flag = fcntl(fileno(config.log.fpv[config.log.fpc]),
					F_GETFD, 0)) == -1
					||  fcntl(fileno(config.log.fpv[config.log.fpc]), F_SETFD,
					flag | FD_CLOEXEC) == -1)
						serr(EXIT_FAILURE, "fcntl(F_GETFD/F_SETFD)");
				}
				++config.log.fpc;
			}
		}
		else
			;	/* XXX warn/exit if output changed. */
	}
break;
case 60:
#line 548 "config_parse.y"
{
#if SOCKS_SERVER
		config.uid.privileged			= yyvsp[0].uid;
		config.uid.privileged_isset	= 1;
#endif
	}
break;
case 61:
#line 556 "config_parse.y"
{
#if SOCKS_SERVER
		config.uid.unprivileged			= yyvsp[0].uid;
		config.uid.unprivileged_isset	= 1;
#endif
	}
break;
case 62:
#line 564 "config_parse.y"
{
#if HAVE_LIBWRAP && SOCKS_SERVER
		config.uid.libwrap			= yyvsp[0].uid;
		config.uid.libwrap_isset	= 1;
#else  /* HAVE_LIBWRAP */
		yyerror("libwrap support not compiled in");
#endif /* !HAVE_LIBWRAP */
	}
break;
case 63:
#line 575 "config_parse.y"
{
		struct passwd *pw;

		if ((pw = getpwnam(yyvsp[0].string)) == NULL)
			serrx(EXIT_FAILURE, "no such user \"%s\"", yyvsp[0].string);
		else
			yyval.uid = pw->pw_uid;
	}
break;
case 64:
#line 585 "config_parse.y"
{
#if SOCKS_SERVER
		config.timeout.io = (time_t)atol(yyvsp[0].string);
#endif
	}
break;
case 65:
#line 592 "config_parse.y"
{
#if SOCKS_SERVER
		config.timeout.negotiate = (time_t)atol(yyvsp[0].string);
#endif
	}
break;
case 66:
#line 599 "config_parse.y"
{
		config.option.debug = atoi(yyvsp[0].string);
	}
break;
case 68:
#line 607 "config_parse.y"
{
#if SOCKS_SERVER
		config.compat.reuseaddr = 1;
	}
break;
case 69:
#line 611 "config_parse.y"
{
		config.compat.sameport = 1;
#endif
	}
break;
case 73:
#line 624 "config_parse.y"
{
			config.resolveprotocol = RESOLVEPROTOCOL_FAKE;
	}
break;
case 74:
#line 627 "config_parse.y"
{
#if HAVE_NO_RESOLVESTUFF
			yyerror("resolveprotocol keyword not supported on this installation");
#else /* HAVE_NO_RESOLVESTUFF */
			config.resolveprotocol = RESOLVEPROTOCOL_TCP;
#endif /* !HAVE_NO_RESOLVESTUFF */
	}
break;
case 75:
#line 634 "config_parse.y"
{
			config.resolveprotocol = RESOLVEPROTOCOL_UDP;
	}
break;
case 77:
#line 642 "config_parse.y"
{
#if HAVE_LIBWRAP && SOCKS_SERVER
			config.srchost.nomismatch = 1;
	}
break;
case 78:
#line 646 "config_parse.y"
{
			config.srchost.nounknown = 1;
#else
		yyerror("srchostoption requires libwrap");
#endif
	}
break;
case 81:
#line 659 "config_parse.y"
{ *methodc = 0; /* reset. */ }
break;
case 83:
#line 662 "config_parse.y"
{
		ADDMETHOD(AUTHMETHOD_NONE);
	}
break;
case 84:
#line 665 "config_parse.y"
{
		yyerror("GSSAPI not supported");
	}
break;
case 85:
#line 668 "config_parse.y"
{
		ADDMETHOD(AUTHMETHOD_UNAME);
	}
break;
case 86:
#line 671 "config_parse.y"
{
#if HAVE_LIBWRAP && SOCKS_SERVER
		ADDMETHOD(AUTHMETHOD_RFC931);
#else /* !HAVE_LIBWRAP */
		yyerror("method rfc931 requires libwrap");
#endif /* !HAVE_LIBWRAP */
	}
break;
case 89:
#line 687 "config_parse.y"
{
#if SOCKS_SERVER
		rule.src = src;
		rule.dst = dst;

		addclientrule(&rule);

		bzero(&src, sizeof(src));
		bzero(&dst, sizeof(dst));
		rule = ruleinit;

		src.atype = SOCKS_ADDR_IPV4;
		dst.atype = SOCKS_ADDR_IPV4;
#endif
	}
break;
case 94:
#line 710 "config_parse.y"
{ yyval.string = NULL; }
break;
case 96:
#line 714 "config_parse.y"
{
#if SOCKS_SERVER
		rule.src = src;
		rule.dst = dst;

		addsocksrule(&rule);

		bzero(&src, sizeof(src));
		bzero(&dst, sizeof(dst));
		rule = ruleinit;

		src.atype	= SOCKS_ADDR_IPV4;
		dst.atype	= SOCKS_ADDR_IPV4;
#endif
	}
break;
case 104:
#line 741 "config_parse.y"
{ yyval.string = NULL; }
break;
case 106:
#line 745 "config_parse.y"
{
#if SOCKS_SERVER
		rule.verdict	= VERDICT_BLOCK;
		command			= &rule.state.command;
		methodv			= rule.state.methodv;
		methodc			= &rule.state.methodc;
		protocol			= &rule.state.protocol;
		proxyprotocol	= &rule.state.proxyprotocol;
		userbase			= &rule.user;
	}
break;
case 107:
#line 755 "config_parse.y"
{
		rule.verdict	= VERDICT_PASS;
		command			= &rule.state.command;
		methodv			= rule.state.methodv;
		methodc			= &rule.state.methodc;
		protocol			= &rule.state.protocol;
		proxyprotocol	= &rule.state.proxyprotocol;
		userbase			= &rule.user;
#endif
	}
break;
case 109:
#line 770 "config_parse.y"
{
			command->bind = 1;
	}
break;
case 110:
#line 773 "config_parse.y"
{
			command->connect = 1;
	}
break;
case 111:
#line 776 "config_parse.y"
{
			command->udpassociate = 1;
	}
break;
case 112:
#line 782 "config_parse.y"
{
			command->bindreply = 1;
	}
break;
case 113:
#line 786 "config_parse.y"
{
			command->udpreply = 1;
	}
break;
case 117:
#line 798 "config_parse.y"
{
		protocol->tcp = 1;
	}
break;
case 118:
#line 801 "config_parse.y"
{
		protocol->udp = 1;
	}
break;
case 123:
#line 817 "config_parse.y"
{
#if SOCKS_SERVER
	rule.log.connect = 1;
	}
break;
case 124:
#line 821 "config_parse.y"
{
			rule.log.data = 1;
	}
break;
case 125:
#line 824 "config_parse.y"
{
			rule.log.disconnect = 1;
	}
break;
case 126:
#line 827 "config_parse.y"
{
			rule.log.error = 1;
	}
break;
case 127:
#line 830 "config_parse.y"
{
			rule.log.iooperation = 1;
#endif
	}
break;
case 130:
#line 841 "config_parse.y"
{
#if HAVE_LIBWRAP && SOCKS_SERVER
		struct request_info request;
		char libwrap[LIBWRAPBUF];

		if (strlen(yyvsp[0].string) >= sizeof(rule.libwrap))
			yyerror("libwrap line too long, make LIBWRAPBUF bigger");
		strcpy(rule.libwrap, yyvsp[0].string);

		/* libwrap modifies the passed buffer. */
		SASSERTX(strlen(rule.libwrap) < sizeof(libwrap));
		strcpy(libwrap, rule.libwrap);

		++dry_run;
		request_init(&request, RQ_FILE, -1, RQ_DAEMON, __progname, 0);
		if (setjmp(tcpd_buf) != 0)
			yyerror("bad libwrap line");
		process_options(libwrap, &request);
		--dry_run;

#else /* !HAVE_LIBWRAP */
		yyerror("libwrap support not compiled in");
#endif
	}
break;
case 139:
#line 886 "config_parse.y"
{ yyval.string = NULL; }
break;
case 141:
#line 890 "config_parse.y"
{
		addressinit(&src);
	}
break;
case 142:
#line 896 "config_parse.y"
{
		addressinit(&dst);
	}
break;
case 143:
#line 902 "config_parse.y"
{
#if SOCKS_CLIENT
		addressinit(&gw);
#endif
	}
break;
case 149:
#line 921 "config_parse.y"
{
		*atype = SOCKS_ADDR_IPV4;

		if (inet_aton(yyvsp[0].string, ipaddr) != 1)
			yyerror("bad address");
	}
break;
case 150:
#line 930 "config_parse.y"
{
		if (atoi(yyvsp[0].string) < 0 || atoi(yyvsp[0].string) > 32)
			yyerror("bad netmask");

		netmask->s_addr
		= atoi(yyvsp[0].string) == 0 ? 0 : htonl(0xffffffff << (32 - atoi(yyvsp[0].string)));
	}
break;
case 151:
#line 937 "config_parse.y"
{
			if (!inet_aton(yyvsp[0].string, netmask))
				yyerror("bad netmask");
	}
break;
case 152:
#line 943 "config_parse.y"
{
		*atype = SOCKS_ADDR_DOMAIN;

		if (strlen(yyvsp[0].string) >= MAXHOSTNAMELEN)
			yyerror("domain too long");
		strcpy(domain, yyvsp[0].string);
	}
break;
case 153:
#line 952 "config_parse.y"
{
		*atype = SOCKS_ADDR_DOMAIN;

		if (strlen(yyvsp[0].string) >= MAXHOSTNAMELEN)
			yyerror("domain too long");
		strcpy(domain, yyvsp[0].string);

#if SOCKS_CLIENT
		route.state.direct = 1;
#endif
	}
break;
case 154:
#line 965 "config_parse.y"
{ yyval.string = NULL; }
break;
case 160:
#line 978 "config_parse.y"
{
		*port_tcp	= htons((in_port_t)atoi(yyvsp[0].string));
		*port_udp	= htons((in_port_t)atoi(yyvsp[0].string));
	}
break;
case 161:
#line 984 "config_parse.y"
{
		ruleaddress->portend		= htons((in_port_t)atoi(yyvsp[0].string));
		ruleaddress->operator	= range;
	}
break;
case 162:
#line 990 "config_parse.y"
{
		struct servent	*service;
		struct protocol_t	protocolunset;
		int set;

		bzero(&protocolunset, sizeof(protocolunset));

		/* set all protocols if none set, default. */
		if (memcmp(protocol, &protocolunset, sizeof(*protocol)) == 0) {
			memset(protocol, UCHAR_MAX, sizeof(*protocol));
			set = 0;
		}
		else
			set = 1;

		if (protocol->tcp) {
			if ((service = getservbyname(yyvsp[0].string, "tcp")) == NULL) {
				if (set)
					yyerror("bad servicename for tcp");
				else
					*port_tcp = htons(0);
			}
			else
				*port_tcp = (in_port_t)service->s_port;
		}

		if (protocol->udp) {
			if ((service = getservbyname(yyvsp[0].string, "udp")) == NULL) {
				if (set)
					yyerror("bad servicename for udp");
				else
					*port_udp = htons(0);
			}
			else
				*port_udp = (in_port_t)service->s_port;
		}

		/* check we got both protocol ports set right. */
		if (*port_tcp == htons(0) && *port_udp == htons(0))
			yyerror("bad service name for tcp/udp");
		if (*port_tcp == htons(0))
			*port_tcp = *port_udp;
		else if (*port_udp == htons(0))
			*port_udp = *port_tcp;
	}
break;
case 163:
#line 1038 "config_parse.y"
{
		*operator = string2operator(yyvsp[0].string);
	}
break;
#line 1684 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
