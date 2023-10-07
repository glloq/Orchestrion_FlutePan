#ifndef MIDIHANDLER_H
#define MIDIHANDLER_H

#include <MIDIUSB.h>
#include "FlutePan.h"
/***********************************************************************************************
----------------------------    MIDI message handler    ----------------------------------------
************************************************************************************************/
class MidiHandler {
  private:
    FlutePan& _flutePan;
    void processMidiEvent(midiEventPacket_t midiEvent);

  public:
    MidiHandler(FlutePan &flutePan);
    void readMidi();
};

#endif // MIDIHANDLER_H
