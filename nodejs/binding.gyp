{
    "targets": [
        {
            "target_name": "vosk",
            "cflags!": [],
            "cflags_cc!": ["-fno-exceptions", "-fno-rtti"],
            "cflags": [],
            "cflags_cc": ["-shared", "-Wno-unused-local-typedefs", "-Wno-sign-compare", "-Wno-deprecated-copy", "-Wno-ignored-qualifiers", "-Wno-pessimizing-move", "-Wno-extra"],

            "sources": [
                "./src/index.cpp",
                "../src/kaldi_recognizer.cc",
                "../src/kaldi_recognizer.h",
                "../src/model.cc",
                "../src/model.h",
                "../src/spk_model.cc",
                "../src/spk_model.h"
            ],

            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "<(KALDI_ROOT)/src",
                "<(KALDI_ROOT)/tools/openfst/include",
                "../src",
                "./src"
            ],
            "libraries": [
                "<(KALDI_ROOT)/src/online2/kaldi-online2.a",
                "<(KALDI_ROOT)/src/decoder/kaldi-decoder.a",
                "<(KALDI_ROOT)/src/ivector/kaldi-ivector.a",
                "<(KALDI_ROOT)/src/gmm/kaldi-gmm.a",
                "<(KALDI_ROOT)/src/nnet3/kaldi-nnet3.a",
                "<(KALDI_ROOT)/src/tree/kaldi-tree.a",
                "<(KALDI_ROOT)/src/feat/kaldi-feat.a",
                "<(KALDI_ROOT)/src/lat/kaldi-lat.a",
                "<(KALDI_ROOT)/src/hmm/kaldi-hmm.a",
                "<(KALDI_ROOT)/src/transform/kaldi-transform.a",
                "<(KALDI_ROOT)/src/cudamatrix/kaldi-cudamatrix.a",
                "<(KALDI_ROOT)/src/matrix/kaldi-matrix.a",
                "<(KALDI_ROOT)/src/fstext/kaldi-fstext.a",
                "<(KALDI_ROOT)/src/util/kaldi-util.a",
                "<(KALDI_ROOT)/src/base/kaldi-base.a",
                "<(KALDI_ROOT)/tools/openfst/lib/libfst.a",
                "<(KALDI_ROOT)/tools/openfst/lib/libfstngram.a",
                "<(KALDI_ROOT)/tools/OpenBLAS/libopenblas.a",
                "-lgfortran"
            ],
            "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS", "FST_NO_DYNAMIC_LINKING" ]
        }
    ]
}
