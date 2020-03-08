cmake_minimum_required(VERSION 3.2.0)

project (vosk)

set(TOP_SRCDIR "${CMAKE_SOURCE_DIR}/..")
set(KALDI_ROOT "$ENV{KALDI_ROOT}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -DFST_NO_DYNAMIC_LINKING")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{WHEEL_FLAGS}")

include_directories("${CMAKE_JS_INC}" "${TOP_SRCDIR}/src" "${KALDI_ROOT}/src" "${KALDI_ROOT}/tools/openfst/include")

# Declare the location of the source files
file(GLOB SOURCE_FILES "${TOP_SRCDIR}/src/*.cc" "${CMAKE_SOURCE_DIR}/src/*.cc")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)

target_link_libraries(${PROJECT_NAME}
             ${KALDI_ROOT}/src/online2/kaldi-online2.a
             ${KALDI_ROOT}/src/decoder/kaldi-decoder.a
             ${KALDI_ROOT}/src/ivector/kaldi-ivector.a
             ${KALDI_ROOT}/src/gmm/kaldi-gmm.a
             ${KALDI_ROOT}/src/nnet3/kaldi-nnet3.a
             ${KALDI_ROOT}/src/tree/kaldi-tree.a
             ${KALDI_ROOT}/src/feat/kaldi-feat.a
             ${KALDI_ROOT}/src/lat/kaldi-lat.a
             ${KALDI_ROOT}/src/hmm/kaldi-hmm.a
             ${KALDI_ROOT}/src/transform/kaldi-transform.a
             ${KALDI_ROOT}/src/cudamatrix/kaldi-cudamatrix.a
             ${KALDI_ROOT}/src/matrix/kaldi-matrix.a
             ${KALDI_ROOT}/src/fstext/kaldi-fstext.a
             ${KALDI_ROOT}/src/util/kaldi-util.a
             ${KALDI_ROOT}/src/base/kaldi-base.a
             ${KALDI_ROOT}/tools/openfst/lib/libfst.a
             ${KALDI_ROOT}/tools/openfst/lib/libfstngram.a
             ${KALDI_ROOT}/tools/OpenBLAS/libopenblas.a
             -lgfortran)

# Include N-API wrappers
add_definitions(-DNAPI_VERSION=3)
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
