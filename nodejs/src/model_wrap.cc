#include "model_wrap.h"

ModelWrap::ModelWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<ModelWrap>(info) {
  const char* model_path = info[0].ToString().Utf8Value().c_str();
  model_ = new Model(model_path);
}

Napi::FunctionReference ModelWrap::constructor;

Model* ModelWrap::GetModel() {
  return model_;
}

Napi::Object ModelWrap::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function modelClass = DefineClass(env, "Model", {});

  constructor = Napi::Persistent(modelClass);
  constructor.SuppressDestruct();
  exports.Set("Model", modelClass);

  return exports;
}
