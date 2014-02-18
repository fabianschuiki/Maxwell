PDFGEN = /usr/texbin/pdflatex

all: build
	${PDFGEN} -output-directory=build -interaction=nonstopmode main.tex
	cp build/main.pdf "Maxwell Language Design.pdf"

build:
	mkdir build
