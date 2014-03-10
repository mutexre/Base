.PHONY: pull clean build all analyze
.DEFAULT_GOAL=all

CONF=Release
TARGET="OSX Static Library"
SDK=macosx10.9
ARCH=x86_64

BOOST=../../boost_1_55_0
RAPIDXML=../../rapidxml-1.13
OUTDIR=build/${CONF}

clean:
	xcodebuild -project Runtime.xcodeproj -target ${TARGET} -configuration ${CONF} clean
	xcodebuild -project Math.xcodeproj -target ${TARGET} -configuration ${CONF} clean
	xcodebuild -project React.xcodeproj -target ${TARGET} -configuration ${CONF} clean
	xcodebuild -project Color.xcodeproj -target ${TARGET} -configuration ${CONF} clean
	xcodebuild -project GLCPP.xcodeproj -target ${TARGET} -configuration ${CONF} clean

build:
	xcodebuild -project Runtime.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} build ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML}
	xcodebuild -project Math.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} build ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML} RUNTIME=${RUNTIME}
	xcodebuild -project React.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} build ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML} RUNTIME=${RUNTIME}
	xcodebuild -project Color.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} build ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML} RUNTIME=${RUNTIME}
	xcodebuild -project GLCPP.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} build ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML} RUNTIME=${RUNTIME}
	mkdir -p ${OUTDIR}; libtool -static -o ${OUTDIR}/libBase.a ${OUTDIR}/libRuntime.a ${OUTDIR}/libMath.a ${OUTDIR}/libReact.a ${OUTDIR}/libColor.a ${OUTDIR}/libGLCPP.a

analyze:
	xcodebuild -project Runtime.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} analyze ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML}
	xcodebuild -project Math.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} analyze ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML} RUNTIME=${RUNTIME}
	xcodebuild -project React.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} analyze ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML} RUNTIME=${RUNTIME}
	xcodebuild -project Color.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} analyze ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML} RUNTIME=${RUNTIME}
	xcodebuild -project GLCPP.xcodeproj -target ${TARGET} -configuration ${CONF} -sdk ${SDK} analyze ARCHS="${ARCH}" BOOST=${BOOST} RAPIDXML=${RAPIDXML} RUNTIME=${RUNTIME}

check:

stats:
	find .. \( -name "*.h" -or -name "*.hpp" -or -name "*.scala" -or -name "*.cpp" -or -name "*.mm" -or -name "*.c" -or -name "*.s" -or -name "*.m" -or -name "*.vs" -or -name "*.fs" \)  \! -name "._*"  -exec wc -l {} \; | awk 'BEGIN { n=0 } { n+=$1 } END { print n }'

all: clean build
