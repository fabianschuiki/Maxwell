MWC=php/bin/debug.php
BUILD_DIR=build
EXEC=${BUILD_DIR}/mwc

all: ${EXEC}

${BUILD_DIR}/mwc: ${BUILD_DIR}
	${MWC} -o ${EXEC} source/main.mw ${BUILD_DIR}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

debug: ${EXEC}
	${EXEC}
