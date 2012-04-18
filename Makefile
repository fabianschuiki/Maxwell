MWC=php/bin/mwc
BUILD_DIR=build
EXEC=${BUILD_DIR}/mwc

compile: ${EXEC}

${EXEC}: ${BUILD_DIR} source/main.mw
	${MWC} --debug -o ${EXEC} -b ${BUILD_DIR} source/main.mw

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

strip:
	rm ${BUILD_DIR}/*.intf
	rm ${BUILD_DIR}/*.let
	rm ${BUILD_DIR}/*.specs
	rm ${BUILD_DIR}/*.html

debug: ${EXEC}
	${EXEC}
