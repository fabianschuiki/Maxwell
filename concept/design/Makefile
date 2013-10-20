PDFGEN = pdflatex

all: build
	${PDFGEN} -output-directory=build -interaction=nonstopmode "Maxwell Language Design.tex"
	cp build/*.pdf ./

build:
	mkdir build
