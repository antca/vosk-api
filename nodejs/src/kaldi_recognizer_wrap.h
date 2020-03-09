#include <mutex>
#include <string>
#include <napi.h>

#include "kaldi_recognizer.h"

class KaldiRecognizerWrap : public Napi::ObjectWrap<KaldiRecognizerWrap> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  KaldiRecognizerWrap(const Napi::CallbackInfo &info);

  Napi::Value AcceptWaveform(const Napi::CallbackInfo& info);
  std::string ExecAcceptWaveform(char* data, size_t len);

 private:
  static Napi::FunctionReference constructor;
  KaldiRecognizer* kaldiRecognizer_;
  std::mutex mutex_;
};

class AcceptWaveformTask : public Napi::AsyncWorker {
public:
  AcceptWaveformTask(Napi::Env env, KaldiRecognizerWrap* kaldiRecognizerWarp, Napi::Buffer<char>& buffer, Napi::Promise::Deferred& deferred);

  void Execute() override;
  void OnOK() override;
  void OnError(const Napi::Error& e) override;

private:
  KaldiRecognizerWrap* kaldiRecognizerWarp_;
  std::string result_;
  char* data_;
  size_t len_;
  Napi::Promise::Deferred deferred_;
};
