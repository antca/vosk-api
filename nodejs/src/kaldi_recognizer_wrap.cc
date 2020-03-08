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
  AcceptWaveformTask* task = new AcceptWaveformTask(info.Env(), kaldiRecognizer_, buffer, deferred);
  task->Queue();
  return deferred.Promise();
}

AcceptWaveformTask::AcceptWaveformTask(Napi::Env env, KaldiRecognizer* kaldiRecognizer, Napi::Buffer<char>& buffer, Napi::Promise::Deferred& deferred)
  : AsyncWorker(env), kaldiRecognizer_(kaldiRecognizer), deferred_(deferred) {
  data_ = buffer.Data();
  len_ = buffer.Length();
};

void AcceptWaveformTask::Execute() {
  if (kaldiRecognizer_->AcceptWaveform(data_, len_)) {
    result_ = kaldiRecognizer_->Result();
    return;
  }
  result_ = kaldiRecognizer_->PartialResult();
};

void AcceptWaveformTask::OnOK() {
  deferred_.Resolve(Napi::String::New(Env(), result_));
};

void AcceptWaveformTask::OnError(const Napi::Error& e) {
  deferred_.Reject(Napi::String::New(Env(), e.Message()));
};

