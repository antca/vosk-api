#include <napi.h>

#include "model.h"

class ModelWrap : public Napi::ObjectWrap<ModelWrap> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  ModelWrap(const Napi::CallbackInfo &info);
  Model* GetModel();

 private:
  static Napi::FunctionReference constructor;
  Model* model_;
};
