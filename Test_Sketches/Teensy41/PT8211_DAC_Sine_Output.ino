// PT8211 I2S DAC Test
//
// Teensy 4.1 is used to generate sine waves on the left/right
// channels of a PT8211 DAC so the analog outputs can be
// observed on a scope.
//
// Pins from PT8211 to Teensy 4.1:    
//      BCK  21
//       WS  20
//     Data  7
//
// More details about Teensy and PT8211  https://www.pjrc.com/store/pt8211_kit.html
//
// Gadget Reboot 

#include <Audio.h>

AudioSynthWaveform       waveform1;
AudioSynthWaveform       waveform2;

AudioOutputPT8211        audioOutput;   // PT8211 DAC is the I2S audio output device

AudioMixer4              mixer1;        // separate mixers for left and right audio outputs
AudioMixer4              mixer2;        // mixers allow setting the gain of an audio source

AudioConnection          patchCord1(waveform1, 0, mixer1, 0);   // send waveform data into mixer inputs
AudioConnection          patchCord2(waveform2, 0, mixer2, 0);

AudioConnection          patchCord3(mixer1, 0, audioOutput, 0); // send mixer outputs to DAC left/right 
AudioConnection          patchCord4(mixer2, 0, audioOutput, 1);


void setup() {

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  mixer1.gain(0, 0.4);         // set sine wave volumes at 40% on left/right mixers
  mixer2.gain(0, 0.4);

  waveform1.frequency(440);    // 440 Hz sine
  waveform1.amplitude(1.0);

  waveform2.frequency(440);  
  waveform2.amplitude(1.0);

  waveform1.begin(WAVEFORM_SINE);
  waveform2.begin(WAVEFORM_SINE);
  
  AudioInterrupts();
}

void loop() {

}
