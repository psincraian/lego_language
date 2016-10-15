#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: lego.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 */
#define zzEOF_TOKEN 1
#define NUM 2
#define GRID 3
#define PLACE 4
#define POP 5
#define AT 6
#define MOVE 7
#define PUSH 8
#define WHILE 9
#define FITS 10
#define LPAR 11
#define RPAR 12
#define OB 13
#define CB 14
#define COMMA 15
#define HEIGHT 16
#define NORTH 17
#define EAST 18
#define SOUTH 19
#define WEST 20
#define DEF 21
#define ENDEF 22
#define CMP_LESS_EQUAL 23
#define CMP_GRATER_EQUAL 24
#define CMP_LESS 25
#define CMP_GREATER 26
#define CMP_EQUAL 27
#define EQUAL 28
#define AND 29
#define OR 30
#define VAR 31
#define TAB 32
#define SPACE 33
#define CMP_GREATER_EQUAL 34

#ifdef __USE_PROTOS
void lego(AST**_root);
#else
extern void lego();
#endif

#ifdef __USE_PROTOS
void grid(AST**_root);
#else
extern void grid();
#endif

#ifdef __USE_PROTOS
void ops(AST**_root);
#else
extern void ops();
#endif

#ifdef __USE_PROTOS
void op_id(AST**_root);
#else
extern void op_id();
#endif

#ifdef __USE_PROTOS
void op_move(AST**_root);
#else
extern void op_move();
#endif

#ifdef __USE_PROTOS
void op_height(AST**_root);
#else
extern void op_height();
#endif

#ifdef __USE_PROTOS
void ops_equal(AST**_root);
#else
extern void ops_equal();
#endif

#ifdef __USE_PROTOS
void ops_equal_start_var(AST**_root);
#else
extern void ops_equal_start_var();
#endif

#ifdef __USE_PROTOS
void ops_equal_start_coord(AST**_root);
#else
extern void ops_equal_start_coord();
#endif

#ifdef __USE_PROTOS
void op_place(AST**_root);
#else
extern void op_place();
#endif

#ifdef __USE_PROTOS
void op_pop(AST**_root);
#else
extern void op_pop();
#endif

#ifdef __USE_PROTOS
void op_push(AST**_root);
#else
extern void op_push();
#endif

#ifdef __USE_PROTOS
void op_while(AST**_root);
#else
extern void op_while();
#endif

#ifdef __USE_PROTOS
void op_condition(AST**_root);
#else
extern void op_condition();
#endif

#ifdef __USE_PROTOS
void op_and(AST**_root);
#else
extern void op_and();
#endif

#ifdef __USE_PROTOS
void op_boolean(AST**_root);
#else
extern void op_boolean();
#endif

#ifdef __USE_PROTOS
void op_fits(AST**_root);
#else
extern void op_fits();
#endif

#ifdef __USE_PROTOS
void defs(AST**_root);
#else
extern void defs();
#endif

#ifdef __USE_PROTOS
void op_def(AST**_root);
#else
extern void op_def();
#endif

#ifdef __USE_PROTOS
void elem(AST**_root);
#else
extern void elem();
#endif

#ifdef __USE_PROTOS
void coord(AST**_root);
#else
extern void coord();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType zzerr2[];
extern SetWordType setwd1[];
extern SetWordType zzerr3[];
extern SetWordType zzerr4[];
extern SetWordType zzerr5[];
extern SetWordType zzerr6[];
extern SetWordType setwd2[];
extern SetWordType zzerr7[];
extern SetWordType zzerr8[];
extern SetWordType zzerr9[];
extern SetWordType zzerr10[];
extern SetWordType zzerr11[];
extern SetWordType zzerr12[];
extern SetWordType zzerr13[];
extern SetWordType setwd3[];
extern SetWordType zzerr14[];
extern SetWordType zzerr15[];
extern SetWordType zzerr16[];
extern SetWordType setwd4[];
