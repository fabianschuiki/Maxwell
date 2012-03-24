MWC=php/bin/debug.php
BUILD_DIR=build
EXEC=${BUILD_DIR}/mwc

all: ${EXEC}

${EXEC}: ${BUILD_DIR} source/main.mw
	${MWC} -o ${EXEC} source/main.mw ${BUILD_DIR}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

debug: ${EXEC}
	${EXEC}
