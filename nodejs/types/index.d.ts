export class Model {
  constructor(modelPath: string);
}

export class KaldiRecognizer {
  constructor(model: Model, sampleRate: number);
  AcceptWaveform(data: Buffer): Promise<string>;
}
