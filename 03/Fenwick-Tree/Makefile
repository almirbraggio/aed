all:
		make fenwick
		make fibonacci

fenwick:
		rm -f fenwick
		gcc -o fenwick src/fenwick.c src/fenwick-tree.c src/fenwick-tree.h

fibonacci:
		rm -f fibonacci
		gcc -o fibonacci src/fibonacci.c src/fenwick-tree.c src/fenwick-tree.h		

clean:
		rm -f fenwick fibonacci
