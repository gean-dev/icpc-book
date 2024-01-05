# Adapted from KACTL
LATEXCMD=pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

all:
	echo "Hello World!"
compile-all:
	./scripts/compile-test.sh .
test-all:
	./scripts/run-test.sh .
fast: | build
	$(LATEXCMD) content/main.tex
	cp build/book.pdf book.pdf
book: | build
	$(LATEXCMD) content/main.tex && $(LATEXCMD) content/main.tex
	cp build/book.pdf book.pdf
build:
	mkdir -p build
clean:
	rm -rf build/