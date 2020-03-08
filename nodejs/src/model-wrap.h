#include <napi.h>

#include "model.h"

class ModelWrap : public Napi::ObjectWrap<ModelWrap> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  ModelWrap(const Napi::CallbackInfo &info);
  Model* GetInstance();

 private:
  static Napi::FunctionReference constructor;
  Model* _instance;
};
