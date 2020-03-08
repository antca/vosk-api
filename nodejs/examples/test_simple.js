#!/usr/bin/env node

const fs = require("fs");
const wav = require("wav");

const { Model, KaldiRecognizer } = require("..");

try {
    fs.accessSync("model-en", fs.constants.R_OK);
} catch(err) {
    console.error("Please download the model from https://github.com/alphacep/kaldi-android-demo/releases and unpack as 'model-en' in the current folder.");
    process.exit(1);
}

const wfStream = fs.createReadStream(process.argv[1]);
const wfReader = new wav.Reader();

const model = new Model("model-en");

wfReader.on('format', async ({ audioFormat, sampleRate, channels }) => {
    if (audioFormat != 1 || channels != 1) {
        console.error("Audio file must be WAV format mono PCM.");
        process.exit(1);
    }
    const rec = KaldiRecognizer(model, format.sampleRate);
    for await (const data of wfReader) {
        const result = await rec.AcceptWaveform(data);
        console.log(result);
    }
});

wfStream.pipe(wfReader);
