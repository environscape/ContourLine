
#include <MozziGuts.h>
#include <ReverbTank.h>
#include <Oscil.h>
#include <tables/cos8192_int8.h>
#include <tables/envelop2048_uint8.h>

ReverbTank reverb;

#define CONTROL_RATE 640  // quite fast, keeps modulation smooth

// Synth from PhaseMod_Envelope example
Oscil<COS8192_NUM_CELLS, AUDIO_RATE> aCarrier(COS8192_DATA);
Oscil<COS8192_NUM_CELLS, AUDIO_RATE> aModulator(COS8192_DATA);
Oscil<COS8192_NUM_CELLS, AUDIO_RATE> aModWidth(COS8192_DATA);
Oscil<COS8192_NUM_CELLS, CONTROL_RATE> kModFreq1(COS8192_DATA);
Oscil<COS8192_NUM_CELLS, CONTROL_RATE> kModFreq2(COS8192_DATA);
Oscil<ENVELOP2048_NUM_CELLS, AUDIO_RATE> aEnvelop(ENVELOP2048_DATA);


void setup() {

  startMozzi(CONTROL_RATE);
}


void updateControl() {
  // synth params
  aCarrier.setFreq(mozziAnalogRead(4) >> 2);
  kModFreq1.setFreq(3.98f);
  kModFreq2.setFreq(3.31757f);
  aModWidth.setFreq(2.52434f);
  aEnvelop.setFreq(9.0f);
  // synth control
  aModulator.setFreq(277.0f + 0.4313f * kModFreq1.next() + kModFreq2.next());
}


int updateAudio() {
  int synth = aCarrier.phMod((int)aModulator.next() * (150u + aModWidth.next()));
  synth *= (byte)aEnvelop.next();
  synth >>= 8;
  // here's the reverb
  int arev = reverb.next(synth);
  // add the dry and wet signals
  return synth + (arev >> 3);
}


void loop() {
  audioHook();
}