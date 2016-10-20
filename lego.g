#header
<<
#include <string>
#include <iostream>
#include <map>
#include "Board.hpp"
using namespace std;

// struct to store information about tokens
typedef struct {
  string kind;
  string text;
} Attrib;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr, int type, char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text;
#include "ast.h"

// macro to create a new AST node (and function predeclaration)
#define zzcr_ast(as,attr,ttype,textt) as=createASTnode(attr,ttype,textt)
AST* createASTnode(Attrib* attr,int ttype, char *textt);
>>

<<
#include <cstdlib>
#include <cmath>

AST *root;


// function to fill token information
void zzcr_attr(Attrib *attr, int type, char *text) {
/*  if (type == ID) {
    attr->kind = "id";
    attr->text = text;
  }
  else {*/
    attr->kind = text;
    attr->text = "";
//  }
}

// function to create a new AST node
AST* createASTnode(Attrib* attr, int type, char* text) {
  AST* as = new AST;
  as->kind = attr->kind;
  as->text = attr->text;
  as->right = NULL;
  as->down = NULL;
  return as;
}


/// create a new "list" AST node with one element
AST* createASTlist(AST *child) {
 AST *as=new AST;
 as->kind="list";
 as->right=NULL;
 as->down=child;
 return as;
}

/// get nth child of a tree. Count starts at 0.
/// if no such child, returns NULL
AST* child(AST *a,int n) {
AST *c=a->down;
for (int i=0; c!=NULL && i<n; i++) c=c->right;
return c;
}



/// print AST, recursively, with indentation
void ASTPrintIndent(AST *a,string s)
{
  if (a==NULL) return;

  cout<<a->kind;
  if (a->text!="") cout<<"("<<a->text<<")";
  cout<<endl;

  AST *i = a->down;
  while (i!=NULL && i->right!=NULL) {
    cout<<s+"  \\__";
    ASTPrintIndent(i,s+"  |"+string(i->kind.size()+i->text.size(),' '));
    i=i->right;
  }

  if (i!=NULL) {
      cout<<s+"  \\__";
      ASTPrintIndent(i,s+"   "+string(i->kind.size()+i->text.size(),' '));
      i=i->right;
  }
}

/// print AST
void ASTPrint(AST *a)
{
  while (a!=NULL) {
    cout<<" ";
    ASTPrintIndent(a,"");
    a=a->right;
  }
}

Board board;

void createGrid(AST *a)
{
    int rows = stoi(a->down->kind);
    int columns = stoi(a->down->right->kind);
    board = Board(rows, columns);
}

Block* getBlock(AST *a);

Block* push(AST *a)
{
    Block *over = getBlock(a->down);
    Block *base = getBlock(a->down->right);
    return board.push(base, over);
}

Block* place(AST *a)
{
    int width = stoi(a->down->down->kind);
    int height = stoi(a->down->down->right->kind);
    int column = stoi(a->down->right->down->kind);
    int row = stoi(a->down->right->down->right->kind);

    return board.place(row - 1, column - 1, width, height);
}

Block *getBasicBlock(AST *a)
{
    int width = stoi(a->down->kind);
    int height = stoi(a->down->right->kind);

    return new Block(width, height);
}

Block* getBlock(AST *a)
{
    if (a == NULL)
        return NULL;
    else if (a->kind == "PUSH")
        return push(a);
    else if (a->kind == "PLACE")
        return place(a);
    else if (a->kind == "list")
        return getBasicBlock(a);
    else
        return board.find(a->kind);
}

void equal(AST *a)
{
    string id = a->down->kind;
    Block *block = getBlock(a->down->right);
    board.equal(id, block);
}

void move(AST *a)
{
    string id = a->down->kind;
    string direction = a->down->right->kind;
    int units = stoi(a->down->right->right->kind);
    board.move(id, direction, units);
}

void print(AST *a)
{
    cout << board << endl;
}

void printblock(AST *a)
{
    Block *b = board.find(a->down->kind);
    cout << *b << endl;
}

void interpret(AST *a)
{
    if (a == NULL)
        return;
    else if (a->kind == "list")
        interpret(a->down);
    else if (a->kind == "Grid") {
        createGrid(a);
        interpret(a->right);
    } else if (a->kind == "=") {
        equal(a);
        interpret(a->right);
    } else if (a->kind == "MOVE") {
        move(a);
        interpret(a->right);
    } else if (a->kind == "PRINT") {
        print(a);
        interpret(a->right);
    } else if (a->kind == "PRINTBLOCK") {
        printblock(a);
        interpret(a->right);
    }
}

int main() {
  root = NULL;
  ANTLR(lego(&root), stdin);
  ASTPrint(root);
  try {
      interpret(root);
  } catch (string msg) {
      cout << msg << endl;
  }
}
>>

#lexclass START
//...
#token NUM "[0-9]+"
#token GRID "Grid"
#token PLACE "PLACE"
#token POP "POP"
#token AT "AT"
#token MOVE "MOVE"
#token PUSH "PUSH"
#token WHILE "WHILE"
#token FITS "FITS"
#token LPAR "\("
#token RPAR "\)"
#token OB "\["
#token CB "\]"
#token COMMA ","
#token HEIGHT "HEIGHT"
#token NORTH "NORTH"
#token EAST "EAST"
#token SOUTH "SOUTH"
#token WEST "WEST"
#token DEF "DEF"
#token ENDEF "ENDEF"
#token CMP_LESS_EQUAL "<="
#token CMP_GRATER_EQUAL ">="
#token CMP_LESS "<"
#token CMP_GREATER ">"
#token CMP_EQUAL "=="
#token EQUAL "="
#token AND "AND"
#token OR "OR"
#token PRINTBLOCK "PRINTBLOCK"
#token PRINT "PRINT"
#token VAR "[A-Z]+([A-Z]|[0-9])*"
#token TAB "[\t]" << zzskip();>>
#token SPACE "[\ \n]" << zzskip();>>

lego: (grid ops defs) <<#0=createASTlist(_sibling);>>;

grid: GRID^ NUM NUM ;

ops:	(
            op_print_b      |
            op_print        |
			op_while		|
			op_id		 	|
			op_move 		|
			op_height
		)*<<#0=createASTlist(_sibling);>>;


op_id:		VAR {EQUAL^ ops_equal};
op_print_b: PRINTBLOCK^ VAR;
op_print:   PRINT^;
op_move: 	MOVE^ VAR (NORTH | EAST | SOUTH | WEST) NUM;
op_height:	HEIGHT^ LPAR! VAR RPAR!;

ops_equal:	op_place | ops_equal_start_var | ops_equal_start_coord;
ops_equal_start_var:	VAR (POP^ op_pop | PUSH^ op_push);
ops_equal_start_coord:	coord PUSH^ op_push;

op_place: 	PLACE^ elem AT! coord;
op_pop:		VAR {POP^ op_pop};
op_push:	elem {(PUSH^ op_push| POP^ op_pop)};

op_while: 	WHILE^ LPAR! op_condition RPAR! OB! ops CB!;
op_condition:	op_and (OR^ (op_fits | op_boolean))* ;
op_and:		(op_fits | op_boolean) {AND^ op_and};
op_boolean:	(op_height | NUM) (CMP_LESS^ | CMP_LESS_EQUAL^ | CMP_GREATER^ | CMP_GREATER_EQUAL^ | CMP_EQUAL^) (op_height | NUM);
op_fits:	FITS^ LPAR! VAR COMMA! elem COMMA! NUM RPAR!;

defs:		(op_def) *<<#0=createASTlist(_sibling);>>;
op_def:		DEF^ VAR ops ENDEF!;

elem:
		coord   |
		VAR;

coord: {LPAR!} NUM COMMA! NUM {RPAR!} <<#0=createASTlist(_sibling);>>;
//....
