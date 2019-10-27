/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 7 "parser.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "util.h"
#include "table.h"
#include "symbol.h"

int yylex(void);
void yyerror(char const *s);
void new_param(S_table t, string s);
void new_var(S_table t, string s);
void new_func(S_table t, string s);
int lookup_var(S_table t, string s);
int lookup_func(S_table t, string s);
extern int yylineno;
FILE* cheating_file;
AST *tree = NULL;    //AST
S_table tab;
S_table f_tab;
S_table p_tab;

int scope = 0;
int call_arity = 0;
int func_cnt = 0;
int var_cnt = 0;
int tmp_cnt = 0;
int lab_cnt = 0;
int par_cnt = 0;
int taby = 0;

#line 98 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ELSE = 258,
    IF = 259,
    INPUT = 260,
    INT = 261,
    OUTPUT = 262,
    RETURN = 263,
    VOID = 264,
    WHILE = 265,
    WRITE = 266,
    PLUS = 267,
    MINUS = 268,
    TIMES = 269,
    OVER = 270,
    LT = 271,
    LE = 272,
    GT = 273,
    GE = 274,
    EQ = 275,
    NEQ = 276,
    ASSIGN = 277,
    SEMI = 278,
    COMMA = 279,
    LPAREN = 280,
    RPAREN = 281,
    LBRACK = 282,
    RBRACK = 283,
    LBRACE = 284,
    RBRACE = 285,
    NUM = 286,
    ID = 287,
    STRING = 288,
    MAIN = 289,
    AND = 290,
    OR = 291,
    NEG = 292,
    MOD = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef AST* YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 188 "parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   307

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    54,    54,    58,    59,    60,    61,    62,    63,    64,
      65,    69,    69,    69,    73,    74,    78,    81,    84,    85,
      86,    87,    89,    90,    97,    97,   101,   102,   102,   106,
     107,   111,   112,   113,   117,   118,   122,   123,   124,   124,
     124,   125,   126,   127,   127,   127,   131,   135,   142,   156,
     163,   170,   186,   187,   191,   191,   191,   192,   192,   192,
     196,   200,   204,   208,   209,   210,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   224,   225,   226,   227,   228,
     229,   230,   231,   233,   234
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ELSE", "IF", "INPUT", "INT", "OUTPUT",
  "RETURN", "VOID", "WHILE", "WRITE", "PLUS", "MINUS", "TIMES", "OVER",
  "LT", "LE", "GT", "GE", "EQ", "NEQ", "ASSIGN", "SEMI", "COMMA", "LPAREN",
  "RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "NUM", "ID", "STRING",
  "MAIN", "AND", "OR", "NEG", "MOD", "$accept", "program", "decl_list",
  "main_func", "$@1", "$@2", "var_defn", "func_defn", "func_decl", "stmt",
  "func_header", "$@3", "params", "$@4", "param_list", "param", "block",
  "stmt_list", "$@5", "$@6", "$@7", "$@8", "assign_stmt", "lval", "rval",
  "if_stmt", "block_", "$@9", "$@10", "$@11", "$@12", "while_stmt",
  "return_stmt", "func_call", "arg_list", "arith_expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

#define YYPACT_NINF -56

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define YYTABLE_NINF -55

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,    49,    12,    -4,   -56,   -56,   -56,   -56,    -8,    57,
     -12,   -56,   -56,   -56,   -56,   -56,   -56,    24,   -56,   -56,
      21,     2,    37,    60,    61,   266,    83,   -56,    67,   -56,
     -56,   -56,    90,    47,    86,   -56,    94,   -56,   -56,   -56,
      95,    89,   113,   -56,   266,   266,   266,   -56,    82,   266,
     -56,   -56,    53,   266,   266,   266,   -56,   -56,   -56,    86,
     -56,   266,   -56,   116,   110,   129,    86,    85,     9,   112,
     109,   -56,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   -56,   266,   266,   266,   139,    88,   232,   166,
     -56,   -56,   193,   -56,   -56,   111,   118,   -56,   -56,   115,
     -56,   -56,   205,     9,     9,   -56,   -56,    -7,    -7,    -7,
      -7,   154,   154,   269,   242,   -56,   115,   266,   -56,   -56,
     -56,   -56,   122,   129,   -56,   142,    86,    54,   -56,   -56,
     232,    -6,   -56,   115,   -56,   130,   -56,   -56,   133,   -56,
     -56,    57,   -56,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,    10,     7,     8,     9,     0,    24,
       0,     1,     6,     3,     4,     5,    17,    43,    16,    14,
       0,     0,     0,     0,     0,     0,     0,    35,    47,    23,
      42,    41,     0,    38,     0,    18,     0,    19,    20,    21,
       0,     0,    26,    11,     0,     0,     0,    69,    49,     0,
      67,    68,     0,     0,    65,     0,    34,    37,    36,     0,
      44,     0,    22,     0,     0,     0,     0,     0,    84,     0,
       0,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,     0,     0,     0,     0,     0,    64,     0,
      39,    45,     0,    15,    25,     0,    28,    30,    12,    57,
      66,    50,     0,    70,    71,    72,    73,    75,    76,    77,
      78,    79,    80,    81,    82,    74,    57,     0,    62,    48,
      40,    46,    31,     0,    13,    52,     0,     0,    51,    60,
      63,     0,    29,    57,    55,     0,    58,    32,     0,    53,
      56,     0,    59,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -56,   -56,   -56,   160,   -56,   -56,    87,   161,     0,   -32,
      42,   -56,   -56,   -56,   -56,    65,   -30,   -56,   -56,   -56,
     -56,   -56,   -56,   -56,   -56,   -56,   -55,   -56,   -56,   -56,
     -56,   -56,   -56,   -17,   -56,   -35
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    66,   124,    29,     6,     7,    31,
       8,    21,    64,    65,    96,    97,    18,    33,    59,   120,
      34,    91,    35,    36,    50,    37,   125,   126,   140,   127,
     142,    38,    39,    51,    87,    52
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,    58,     1,    15,    60,    72,    73,    74,    75,    67,
      68,    69,    11,    22,    71,    16,    40,    30,    86,    88,
      89,    17,   137,    74,    75,   138,    92,    42,    23,    90,
      24,    85,    25,    57,    26,   102,    98,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,    85,   113,   114,
     115,    23,    41,    24,    27,    25,    28,    26,    23,    32,
     135,   129,    25,    43,    26,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    32,    82,    56,   139,    28,
      19,     9,   130,    10,    20,    44,    28,     5,    83,    84,
      13,    85,    54,     9,    55,   136,   134,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    54,    53,    70,
      40,    99,   117,    16,   118,    17,    61,    63,    62,   -27,
      83,    84,    45,    85,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    46,    95,    94,   101,   100,    93,
      47,    48,   123,   122,   -54,   133,    49,    83,    84,   131,
      85,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,   143,   141,    12,    14,   116,    72,    73,    74,    75,
      76,    77,    78,    79,    83,    84,     0,    85,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,   132,     0,
       0,     0,    85,     0,   119,     0,     0,     0,     0,     0,
       0,    83,    84,     0,    85,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,     0,   121,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,    83,    84,
       0,    85,     0,   128,     0,     0,     0,     0,     0,     0,
      83,    84,     0,    85,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,     0,     0,     0,    83,    84,     0,
      85,     0,     0,     0,     0,     0,     0,    83,     0,    45,
      85,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    46,     0,     0,     0,     0,     0,    47,    48,     0,
       0,     0,     0,    49,     0,     0,     0,    85
};

static const yytype_int16 yycheck[] =
{
      17,    33,     6,     3,    34,    12,    13,    14,    15,    44,
      45,    46,     0,    25,    49,    23,    33,    17,    53,    54,
      55,    29,    28,    14,    15,    31,    61,    25,     4,    59,
       6,    38,     8,    33,    10,    70,    66,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    38,    83,    84,
      85,     4,    31,     6,    30,     8,    32,    10,     4,    17,
       6,   116,     8,    26,    10,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    33,    23,    30,   133,    32,
      23,    32,   117,    34,    27,    25,    32,     0,    35,    36,
       3,    38,    25,    32,    27,   127,   126,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    25,    25,    27,
     127,    26,    24,    23,    26,    29,    22,    28,    23,     6,
      35,    36,    13,    38,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    25,     6,    26,    28,    26,    23,
      31,    32,    24,    32,    29,     3,    37,    35,    36,    27,
      38,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    28,    32,     3,     3,    26,    12,    13,    14,    15,
      16,    17,    18,    19,    35,    36,    -1,    38,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   123,    -1,
      -1,    -1,    38,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    -1,    38,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    23,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    35,    36,
      -1,    38,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    -1,    38,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    35,    36,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    13,
      38,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    40,    41,    42,    45,    46,    47,    49,    32,
      34,     0,    42,    45,    46,    47,    23,    29,    55,    23,
      27,    50,    25,     4,     6,     8,    10,    30,    32,    45,
      47,    48,    49,    56,    59,    61,    62,    64,    70,    71,
      72,    31,    25,    26,    25,    13,    25,    31,    32,    37,
      63,    72,    74,    25,    25,    27,    30,    47,    48,    57,
      55,    22,    23,    28,    51,    52,    43,    74,    74,    74,
      27,    74,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    23,    35,    36,    38,    74,    73,    74,    74,
      55,    60,    74,    23,    26,     6,    53,    54,    55,    26,
      26,    28,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    26,    24,    26,    28,
      58,    23,    32,    24,    44,    65,    66,    68,    28,    65,
      74,    27,    54,     3,    55,     6,    48,    28,    31,    65,
      67,    32,    69,    28
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    41,    41,    41,    41,
      41,    43,    44,    42,    45,    45,    46,    47,    48,    48,
      48,    48,    48,    48,    50,    49,    51,    52,    51,    53,
      53,    54,    54,    54,    55,    55,    56,    56,    57,    58,
      56,    56,    56,    59,    60,    56,    61,    62,    62,    63,
      63,    63,    64,    64,    66,    67,    65,    68,    69,    65,
      70,    71,    72,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     1,     1,     1,
       1,     0,     0,     7,     3,     6,     2,     2,     1,     1,
       1,     1,     2,     1,     0,     6,     0,     0,     2,     3,
       1,     2,     4,     5,     3,     2,     2,     2,     0,     0,
       4,     1,     1,     0,     0,     3,     4,     1,     4,     1,
       3,     4,     5,     7,     0,     0,     3,     0,     0,     3,
       5,     3,     4,     3,     1,     0,     3,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 2:
#line 54 "parser.y" /* yacc.c:1646  */
    {tree = new_subtree(ROOT_NODE, 1, (yyvsp[0]));}
#line 1633 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 58 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 1639 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 59 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 1645 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 60 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 1651 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 61 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 1657 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 62 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(DECL_LIST_NODE, 1, (yyvsp[0]));}
#line 1663 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 63 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(DECL_LIST_NODE, 1, (yyvsp[0]));}
#line 1669 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 64 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(DECL_LIST_NODE, 1, (yyvsp[0]));}
#line 1675 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 65 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(DECL_LIST_NODE, 1, (yyvsp[0]));}
#line 1681 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 69 "parser.y" /* yacc.c:1646  */
    {S_beginScope(tab);}
#line 1687 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 69 "parser.y" /* yacc.c:1646  */
    {S_endScope(tab);}
#line 1693 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 69 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(MAIN_NODE, 1, (yyvsp[-1])); setPos((yyval), 0);}
#line 1699 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 73 "parser.y" /* yacc.c:1646  */
    {new_var(tab, getName((yyvsp[-1]))); setPos((yyvsp[-1]),lookup_var(tab, getName((yyvsp[-1])))); (yyval) = create_node_aux(NEWSVAR_NODE, getPos((yyvsp[-1])));}
#line 1705 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 74 "parser.y" /* yacc.c:1646  */
    {new_var(tab, getName((yyvsp[-4]))); setPos((yyvsp[-4]),lookup_var(tab, getName((yyvsp[-4])))); (yyval) = create_node_aux(NEWCVAR_NODE, getPos((yyvsp[-4]))); add_leaf((yyval), (yyvsp[-2]));}
#line 1711 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 78 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(FUNC_DEFN_NODE, 2, (yyvsp[-1]), (yyvsp[0])); S_endScope(p_tab); S_endScope(tab); }
#line 1717 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 81 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(FUNC_DECL_NODE, 1, (yyvsp[-1])); S_endScope(p_tab); S_endScope(tab);}
#line 1723 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 84 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1729 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 85 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1735 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 86 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1741 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 87 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1747 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 89 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1753 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 90 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1759 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 97 "parser.y" /* yacc.c:1646  */
    {par_cnt = 0;}
#line 1765 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 97 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(FUNC_HEADER_NODE, 2, (yyvsp[-4]), (yyvsp[-1])); new_func(f_tab, getName((yyvsp[-4]))); setPos((yyvsp[-4]), lookup_func(f_tab, getName((yyvsp[-4]))));}
#line 1771 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 101 "parser.y" /* yacc.c:1646  */
    {S_beginScope(p_tab); S_beginScope(tab); (yyval) = new_subtree(PARAM_LIST_NODE,0);}
#line 1777 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 102 "parser.y" /* yacc.c:1646  */
    {S_beginScope(p_tab); S_beginScope(tab);}
#line 1783 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 102 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1789 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 106 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-2]); add_leaf((yyvsp[-2]), (yyvsp[0]));}
#line 1795 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 107 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(PARAM_LIST_NODE, 1, (yyvsp[0]));}
#line 1801 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 111 "parser.y" /* yacc.c:1646  */
    {new_param(p_tab, getName((yyvsp[0]))); setPos((yyvsp[0]),lookup_var(p_tab, getName((yyvsp[0])))); (yyval) = create_node_aux(NEWPSVAR_NODE, getPos((yyvsp[0])));}
#line 1807 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 112 "parser.y" /* yacc.c:1646  */
    {new_param(p_tab, getName((yyvsp[-2]))); setPos((yyvsp[-2]),lookup_var(p_tab, getName((yyvsp[-2])))); (yyval) = create_node_aux(NEWPCVAR_NODE, getPos((yyvsp[-2])));}
#line 1813 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 113 "parser.y" /* yacc.c:1646  */
    {new_param(p_tab, getName((yyvsp[-3]))); setPos((yyvsp[-3]),lookup_var(p_tab, getName((yyvsp[-3])))); (yyval) = create_node_aux(NEWPCVAR_NODE, getPos((yyvsp[-3])));}
#line 1819 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 117 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1825 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 118 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(BLOCK_NODE, 0);}
#line 1831 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 122 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 1837 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 123 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 1843 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 124 "parser.y" /* yacc.c:1646  */
    {S_beginScope(tab);}
#line 1849 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 124 "parser.y" /* yacc.c:1646  */
    {S_endScope(tab);}
#line 1855 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 124 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-3]), add_leaf((yyvsp[-3]), (yyvsp[-1]));}
#line 1861 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 125 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(BLOCK_NODE, 1, (yyvsp[0]));}
#line 1867 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(BLOCK_NODE, 1, (yyvsp[0]));}
#line 1873 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 127 "parser.y" /* yacc.c:1646  */
    {S_beginScope(tab);}
#line 1879 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 127 "parser.y" /* yacc.c:1646  */
    {S_endScope(tab);}
#line 1885 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 127 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(BLOCK_NODE, 1, (yyvsp[-1]));}
#line 1891 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 131 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(ASSIGN_NODE, 2, (yyvsp[-3]), (yyvsp[-1]));}
#line 1897 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 135 "parser.y" /* yacc.c:1646  */
    {if(lookup_var(p_tab, getName((yyvsp[0])))!=-1) {
                                                        (yyval)=new_subtree(PARSVAR_NODE, 0); 
                                                        setPos((yyvsp[0]),lookup_var(p_tab, getName((yyvsp[0]))));
                                                    } else {
                                                        (yyval) = new_subtree(SVAR_NODE, 0); 
                                                        setPos((yyvsp[0]),lookup_var(tab, getName((yyvsp[0]))));
                                                    } setPos((yyval), getPos((yyvsp[0])));}
#line 1909 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 142 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(TMP_NODE, 0); 
                                                    setPos((yyval), tmp_cnt); 
                                                    tmp_cnt++; 
                                                    if(lookup_var(p_tab, getName((yyvsp[-3])))!=-1) {
                                                        (yyval) = new_subtree(LPARCVAR_NODE, 1, (yyval)); 
                                                        setPos((yyvsp[-3]),lookup_var(p_tab, getName((yyvsp[-3]))));
                                                    } else {
                                                        (yyval) = new_subtree(LCVAR_NODE, 1, (yyval)); 
                                                        setPos((yyvsp[-3]),lookup_var(tab, getName((yyvsp[-3]))));
                                                    } 
                                                    setPos((yyval), getPos((yyvsp[-3]))); 
                                                    add_leaf((yyval), (yyvsp[-1]));}
#line 1926 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 156 "parser.y" /* yacc.c:1646  */
    {if(lookup_var(p_tab, getName((yyvsp[0])))!=-1) {
                                                        (yyval)=new_subtree(PARSVAR_NODE, 0); 
                                                        setPos((yyvsp[0]),lookup_var(p_tab, getName((yyvsp[0]))));
                                                    } else {
                                                        (yyval) = new_subtree(SVAR_NODE, 0); 
                                                        setPos((yyvsp[0]),lookup_var(tab, getName((yyvsp[0]))));
                                                    } setPos((yyval), getPos((yyvsp[0])));}
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 163 "parser.y" /* yacc.c:1646  */
    {if(lookup_var(p_tab, getName((yyvsp[-2])))!=-1) {
                                                        (yyval)=new_subtree(PARSVAR_NODE, 0); 
                                                        setPos((yyvsp[-2]),lookup_var(p_tab, getName((yyvsp[-2]))));
                                                    } else {
                                                        (yyval) = new_subtree(SVAR_NODE, 0); 
                                                        setPos((yyvsp[-2]),lookup_var(tab, getName((yyvsp[-2]))));
                                                    } setPos((yyval), getPos((yyvsp[-2])));}
#line 1950 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 170 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(RTMP_NODE, 0); 
                                                    setPos((yyval), tmp_cnt); 
                                                    tmp_cnt+=2; 
                                                    if(lookup_var(p_tab, getName((yyvsp[-3])))!=-1) {
                                                        (yyval) = new_subtree(RPARCVAR_NODE, 1, (yyval)); 
                                                        setPos((yyvsp[-3]),lookup_var(p_tab, getName((yyvsp[-3]))));
                                                    } else {
                                                        (yyval) = new_subtree(RCVAR_NODE, 1, (yyval)); 
                                                        setPos((yyvsp[-3]),lookup_var(tab, getName((yyvsp[-3]))));
                                                    } 
                                                    setPos((yyval), getPos((yyvsp[-3]))); 
                                                    add_leaf((yyval), (yyvsp[-1]));}
#line 1967 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 186 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(IF_NODE, 2, (yyvsp[-2]), (yyvsp[0])); setPos((yyval), lab_cnt); lab_cnt++;}
#line 1973 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 187 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(IF_NODE, 3, (yyvsp[-4]), (yyvsp[-2]), (yyvsp[0])); setPos((yyval), lab_cnt); lab_cnt+=2;}
#line 1979 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 191 "parser.y" /* yacc.c:1646  */
    {S_beginScope(tab);}
#line 1985 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 191 "parser.y" /* yacc.c:1646  */
    {S_endScope(tab);}
#line 1991 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 191 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(BLOCK_NODE, 1, (yyvsp[-1]));}
#line 1997 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 192 "parser.y" /* yacc.c:1646  */
    {S_beginScope(tab);}
#line 2003 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 192 "parser.y" /* yacc.c:1646  */
    {S_endScope(tab);}
#line 2009 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 192 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(BLOCK_NODE, 1, (yyvsp[-1]));}
#line 2015 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 196 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(WHILE_NODE, 2, (yyvsp[-2]), (yyvsp[0])); setPos((yyval), lab_cnt); lab_cnt+=2;}
#line 2021 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 200 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(RETURN_NODE, 1, (yyvsp[-1]));}
#line 2027 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(FUNC_CALL_NODE, 2, (yyvsp[-3]), (yyvsp[-1])); setPos((yyval), tmp_cnt); tmp_cnt++;}
#line 2033 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 208 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-2]); add_leaf((yyvsp[-2]), (yyvsp[0])); call_arity++;}
#line 2039 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 209 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(ARG_LIST_NODE, 1, (yyvsp[0])); call_arity++;}
#line 2045 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 210 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(ARG_LIST_NODE, 0);}
#line 2051 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 214 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 2057 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2063 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 216 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2069 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2075 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 218 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2081 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 219 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2087 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2093 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2099 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2105 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 224 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2111 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 225 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2117 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 226 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2123 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2129 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2135 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2141 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 230 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2147 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 231 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyvsp[-1]), (yyvsp[-2])); add_leaf((yyvsp[-1]), (yyvsp[0]));}
#line 2153 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 233 "parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyval), (yyvsp[0]));}
#line 2159 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 234 "parser.y" /* yacc.c:1646  */
    {(yyval) = new_subtree(UMINUS_NODE, 1, (yyvsp[-1])); setPos((yyval), tmp_cnt); tmp_cnt++; add_leaf((yyval), (yyvsp[0]));}
#line 2165 "parser.c" /* yacc.c:1646  */
    break;


#line 2169 "parser.c" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 237 "parser.y" /* yacc.c:1906  */



// /////////////////////////////////////// PARSER ERROR ///////////////////////////////////
void yyerror (char const *s)
{
	printf("PARSE ERROR (%d): %s\n", yylineno, s);
}

// ////////////////////////////////////// SEMANTIC ERROR //////////////////////////////////
void new_param(S_table t, string s) {
    S_enter(t, S_Symbol(s), par_cnt);
    par_cnt ++;
}
void new_var(S_table t, string s) {
    int temp = var_cnt;         // global variable
    S_enter(t, S_Symbol(s), temp);
    var_cnt ++;
}

int lookup_var(S_table t, string s) {
    int num = S_look(t, S_Symbol(s));
    //printf("#############%s, %d\n",s, num);
    return num;
}

void new_func(S_table t, string s) {
    int temp = func_cnt;
    S_enter(t, S_Symbol(s), temp);
    func_cnt ++;
}

int lookup_func(S_table t, string s) {
    int num = S_look(t, S_Symbol(s));
    return num;
}

int main()
{
    cheating_file = fopen("null.txt", "w");
    tab = S_empty();
    p_tab = S_empty();
    f_tab = S_empty();
    //yydebug = 1; // Enter debug mode.
    if(!yyparse())
        printf("");
        //printf("PARSE SUCESSFUL!\n");
    //for(int i=0; i<tmp_cnt; ++i) printf("var t%d\n", i);
    //print_AST(tree);
    gen_code(tree, 0);
   
    free_tree(tree);
    return 0;
}
