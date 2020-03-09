#include "kaldi_recognizer_wrap.h"
#include "model_wrap.h"

KaldiRecognizerWrap::KaldiRecognizerWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<KaldiRecognizerWrap>(info) {
  Model* model = Napi::ObjectWrap<ModelWrap>::Unwrap(info[0].As<Napi::Object>())->GetModel();
  float sample_frequency = info[1].ToNumber().FloatValue();
  kaldiRecognizer_ = new KaldiRecognizer(*model, sample_frequency);
}

Napi::FunctionReference KaldiRecognizerWrap::constructor;

Napi::Object KaldiRecognizerWrap::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function modelClass = DefineClass(env, "KaldiRecognizer", {
    InstanceMethod("AcceptWaveform", &KaldiRecognizerWrap::AcceptWaveform)
  });

  constructor = Napi::Persistent(modelClass);
  constructor.SuppressDestruct();
  exports.Set("KaldiRecognizer", modelClass);

  return exports;
}

Napi::Value KaldiRecognizerWrap::AcceptWaveform(const Napi::CallbackInfo& info) {
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
  AcceptWaveformTask* task = new AcceptWaveformTask(info.Env(), this, buffer, deferred);
  task->Queue();
  return deferred.Promise();
}

std::string KaldiRecognizerWrap::ExecAcceptWaveform(char* data, size_t len) {
  mutex_.lock();
  std::string result;
  if (kaldiRecognizer_->AcceptWaveform(data, len)) {
    result = kaldiRecognizer_->Result();
  } else {
    result = kaldiRecognizer_->PartialResult();
  }
  mutex_.unlock();
  return result;
}

AcceptWaveformTask::AcceptWaveformTask(Napi::Env env, KaldiRecognizerWrap* kaldiRecognizerWarp, Napi::Buffer<char>& buffer, Napi::Promise::Deferred& deferred)
  : AsyncWorker(env), kaldiRecognizerWarp_(kaldiRecognizerWarp), data_(buffer.Data()), len_(buffer.Length()), deferred_(deferred) {
};

void AcceptWaveformTask::Execute() {
  result_ = kaldiRecognizerWarp_->ExecAcceptWaveform(data_, len_);
};

void AcceptWaveformTask::OnOK() {
  deferred_.Resolve(Napi::String::New(Env(), result_));
};

void AcceptWaveformTask::OnError(const Napi::Error& e) {
  deferred_.Reject(Napi::String::New(Env(), e.Message()));
};

