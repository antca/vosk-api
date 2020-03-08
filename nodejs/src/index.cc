#include <napi.h>
#include <string>

#include "kaldi_recognizer.h"
#include "model.h"
#include "spk_model.h"

class ModelWrap : public Napi::ObjectWrap<ModelWrap> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  ModelWrap(const Napi::CallbackInfo &info);
  Model* GetInstance();

private:
  static Napi::FunctionReference constructor;
  Model* _instance;
};

ModelWrap::ModelWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<ModelWrap>(info) {
  // Napi::Env env = info.Env();
  const char* model_path = info[0].ToString().Utf8Value().c_str();
  _instance = new Model(model_path);
}

Napi::FunctionReference ModelWrap::constructor;

Model* ModelWrap::GetInstance() {
  return _instance;
}

Napi::Object ModelWrap::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function modelClass = DefineClass(env, "Model", {});

  constructor = Napi::Persistent(modelClass);
  constructor.SuppressDestruct();
  exports.Set("Model", modelClass);

  return exports;
}

Napi::Object Init (Napi::Env env, Napi::Object exports) {
  ModelWrap::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
