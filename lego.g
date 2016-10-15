#header
<<
#include <string>
#include <iostream>
#include <map>
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

//global structures
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



int main() {
  root = NULL;
  ANTLR(lego(&root), stdin);
  ASTPrint(root);
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
#token VAR "[A-Z]+([A-Z]|[0-9])*"
#token SPACE "[\ \n]" << zzskip();>>

lego: (grid ops defs) <<#0=createASTlist(_sibling);>>;

grid: GRID^ NUM NUM ;

ops:	(	
			op_while		|
			op_id		 	|
			op_move 		|
			op_height
		)*<<#0=createASTlist(_sibling);>>;


op_id:		VAR {EQUAL^ ops_equal};
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
