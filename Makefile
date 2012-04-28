MWC=php/bin/mwc
BUILD_DIR=build
EXEC=${BUILD_DIR}/mwc

compile: strip ${EXEC}

${EXEC}: ${BUILD_DIR} source/main.mw
	${MWC} --debug -o ${EXEC} -b ${BUILD_DIR} source/main.mw

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

strip:
	rm -R ${BUILD_DIR}/*

debug: ${EXEC}
	${EXEC}
