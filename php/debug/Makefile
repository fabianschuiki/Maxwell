MWC=../bin/mwc
BUILD_DIR=../build
EXEC=${BUILD_DIR}/mwc

compile: ${EXEC}

${EXEC}: ${BUILD_DIR} main.mw
	${MWC} --debug -o ${EXEC} -b ${BUILD_DIR} main.mw

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}
