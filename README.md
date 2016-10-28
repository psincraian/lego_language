# LEGO LANGUAGE #
Lego Language is an interpreter for a block language. It is a short practice of the [LP](http://www.fib.upc.edu/en/estudiar-enginyeria-informatica/assignatures.html?assig=LP) subject that is taught at [FIB](http://www.fib.upc.edu/en.html).

*IMPORTANT: the code is not tested and it's not documented due to the limited amount of time*

## Block language ##
The block language is a programming language to imitate the bricks from Lego, these bricks can be pushed over a grid, another brick, moved, etc.

Also, the language has a small portion of the things you can have in another languages, like vars, loops, functions and so on.

A basic example is the following:

```
Grid 10 20
B1 = PLACE (2,2) AT (1,1)
B2 = PLACE (2,4) AT (3,1)
MOVE B2 EAST 5
B2 = B1 PUSH B2;

WHILE(FITS(B2,2,1,2)) [
	B2 = (2,1) PUSH B2
]

B4 = PLACE (2,2) AT (5,5)
TOWER10
PRINT

DEF TOWER10
	WHILE(HEIGHT(B4) > 0 AND HEIGHT(B4) < 9) [
		B4 = (2,2) PUSH B4
	]
ENDEF
```

## Compilation ##
To compile the program only need to have installed [pccts](http://packages.ubuntu.com/xenial/pccts) and do:

```
git clone https://github.com/psincraian/lego_language.git
cd lego_language
make
```

## Operations ##
* Grid N M: define a Grid of N cols and M rows.
* PLACE (w,h) AT (x,y): push a block of x columns and h rows in x, y.
* MOVE ID (EAST | NORTH | WEST | SOUTH) N: move the block with the specified ID in the given direction
* ID1 = ID2 PUSH ID1: push block with ID1 over ID2.
* ID1 = ID2 POP ID1: pop the ID1 block from ID2. Then ID1 is not specified.
* FITS(ID, BLOCK, LEVEL): return true if BLOCK can be pushed to ID at the specified level.
* WHILE: a while loop.
* PRINT: print the level 1 of the grid.
* PRINTBLOCK ID: print the level 1 of the given block.
* PRINTHEIGHT: print the height of the bases blocks that are in the grid
