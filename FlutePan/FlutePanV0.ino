#include "settings.h"
#include "FlutePan.h"
#include "midiHandler.h"

FlutePan* flutePan = nullptr;
MidiHandler* midiHandler = nullptr;


void setup() {
  Serial.begin(115200);

  while (!Serial) {
   delay(10); // Attendre que la connexion série soit établie
  }
  Serial.println("setup main FlutePan MIDI USB");
  flutePan = new FlutePan();
  midiHandler = new MidiHandler(*flutePan);
}

void loop() {
  midiHandler->readMidi(); // gestion des messages midi
  flutePan->update(); // gestion extinction electroaiamants / temps maximum actif
}
