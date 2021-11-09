/*
 * pedalboard
 * Copyright 2021 Spotify AB
 *
 * Licensed under the GNU Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    https://www.gnu.org/licenses/gpl-3.0.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "JuceHeader.h"

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace Pedalboard {

void addMidiToBuffer (const uint8_t  status,
                      const uint8_t  data1,
                      const uint8_t  data2,
                      const int    timeInSamples,
                      juce::MidiBuffer&  midiBuffer)
{
    switch (status & 0xF0) {
        case (0x80):
        {
            juce::MidiMessage msg = juce::MidiMessage::noteOn (1, data1, data2);
            msg.setTimeStamp(timeInSamples);
            midiBuffer.addEvent (msg, msg.getTimeStamp());
            break;
        }
        case (0x90):
        {
            juce::MidiMessage msg = juce::MidiMessage::noteOff (1, data1, data2);
            msg.setTimeStamp(timeInSamples);
            midiBuffer.addEvent (msg, msg.getTimeStamp());
            break;
        }
        case (0xB0):
        {
            juce::MidiMessage msg = juce::MidiMessage::controllerEvent(1, data1, data2);
            msg.setTimeStamp(timeInSamples);
            midiBuffer.addEvent (msg, msg.getTimeStamp());
            break;
        }
        default:
        	throw std::runtime_error(
    			"Unknown midi message");
            break;
    }
}


} // namespace Pedalboard