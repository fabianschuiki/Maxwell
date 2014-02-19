PDFGEN = /usr/texbin/pdflatex
CMD = ${PDFGEN} -output-directory=build -interaction=nonstopmode main.tex

all: build
	${CMD}
	${CMD}
	cp build/main.pdf "Maxwell Language Design.pdf"

build:
	mkdir build
