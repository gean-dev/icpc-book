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
	cp build/main.pdf main.pdf
book: | build
	$(LATEXCMD) content/main.tex && $(LATEXCMD) content/main.tex
	cp build/main.pdf book.pdf
	$(LATEXCMD) content/main_bw.tex && $(LATEXCMD) content/main_bw.tex
	cp build/main_bw.pdf book_bw.pdf
build:
	mkdir -p build
clean:
	rm -rf build/
