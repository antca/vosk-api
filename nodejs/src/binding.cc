#include <napi.h>

// #include "kaldi_recognizer.h"
// #include "spk_model.h"

#include "model-wrap.h"

Napi::Object Init (Napi::Env env, Napi::Object exports) {
  ModelWrap::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
