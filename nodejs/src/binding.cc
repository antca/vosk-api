#include <napi.h>

// #include "spk_model.h"

#include "model_wrap.h"
#include "kaldi_recognizer_wrap.h"

Napi::Object Init (Napi::Env env, Napi::Object exports) {
  ModelWrap::Init(env, exports);
  KaldiRecognizerWrap::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
