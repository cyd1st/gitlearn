all: bst bst2

bst: bst.dot
	dot -Tpng $< -o out/$@.png

bst2: bst2.dot
	dot -Tpng $< -o out/$@.png

clean:
	rm out/*.png