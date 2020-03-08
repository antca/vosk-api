#include <string>
#include <napi.h>

#include "kaldi_recognizer.h"

class KaldiRecognizerWrap : public Napi::ObjectWrap<KaldiRecognizerWrap> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  KaldiRecognizerWrap(const Napi::CallbackInfo &info);

  Napi::Value AcceptWaveform(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  KaldiRecognizer* kaldiRecognizer_;
};

class AcceptWaveformTask : public Napi::AsyncWorker {
public:
  AcceptWaveformTask(Napi::Env env, KaldiRecognizer* kaldiRecognizer, Napi::Buffer<char>& buffer, Napi::Promise::Deferred& deferred);

  void Execute() override;
  void OnOK() override;
  void OnError(const Napi::Error& e) override;

private:
  KaldiRecognizer* kaldiRecognizer_;
  char* data_;
  size_t len_;
  std::string result_;
  Napi::Promise::Deferred deferred_;
};

