//////////////////////////
//  Protean modulator   //
//    for ATtiny 85     //
// Kinetik Laboratories //
//    Pangrus 2015      //    
//////////////////////////

int delayTime;
int waveform;
int sampleholdWave = 128;
int triangleWave = 0;
int smoothRndOld = 127;
int smoothRndNew = 128;
int smoothRndOut = 128;
int maxOutput = 255;

void setup() {
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  TCCR0A = 2 << COM0A0 | 2 << COM0B0 | 3 << WGM00;
  TCCR0B = 0 << WGM02 | 1 << CS00;
}

void loop() {
  for (int x = 0; x <= 255; x++) {
    waveform = analogRead(2);
    if (analogRead (3) < 5) waveform = -1;
    delayTime = map(analogRead (3), 0, 1023, 32000, 1);
    if (waveform == -1) analogWrite(1, maxOutput);
    if (waveform >= 0  && waveform <=  100 ) analogWrite(1, SmoothRnd());
    if (waveform > 100  && waveform <=  280 ) analogWrite(1, Triangle(x));
    if (waveform > 280  && waveform <= 512 ) analogWrite(1, x);
    if (waveform > 512 && waveform <= 743 ) analogWrite(1, 255 - x);
    if (waveform > 742 && waveform <= 923 ) analogWrite(1, Square(x));
    if (waveform > 923 ) analogWrite(1, Samplehold(x));
    delayMicroseconds (delayTime);
  }
}

int Triangle(int x) {
  if (x == 0) triangleWave = 0;
  if (x > 0 and x <= 126) triangleWave = triangleWave + 2;
  if (x > 127 and x <= 253) triangleWave = triangleWave - 2;
  return triangleWave;
}

int Square (int x) {
  if (x <= 127) return maxOutput;
  if (x > 127) return 0;
}

int Samplehold(int x) {
  if (x == sampleholdWave) sampleholdWave = random(maxOutput);
  return sampleholdWave;
}

int SmoothRnd() {
  if (smoothRndOld == smoothRndNew) smoothRndOld = random(255);
  if (smoothRndOld  > smoothRndNew) smoothRndNew++;
  if (smoothRndOld  < smoothRndNew) smoothRndNew--;
  return smoothRndNew;
}
