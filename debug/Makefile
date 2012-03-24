MWC=../php/bin/debug.php
BUILD_DIR=build
EXEC=${BUILD_DIR}/main

all: ${EXEC}

${EXEC}: ${BUILD_DIR} *.mw
	${MWC} -o ${EXEC} main.mw ${BUILD_DIR}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

debug: ${EXEC}
	${EXEC}
