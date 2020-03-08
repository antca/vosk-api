#include "model-wrap.h"

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
