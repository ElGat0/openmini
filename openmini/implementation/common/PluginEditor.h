/// @filename PluginEditor.h
/// @brief OpenMini plugin editor (UI & control)
/// @author gm
/// @copyright gm 2013
///
/// This file is part of OpenMini
///
/// OpenMini is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// OpenMini is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with OpenMini.  If not, see <http://www.gnu.org/licenses/>.


// This file is NOT generated by Juce (at least not after the first time),
// That's why we apply our coding style here


#ifndef OPENMINI_PLUGIN_COMMON_PLUGINEDITOR_H_
#define OPENMINI_PLUGIN_COMMON_PLUGINEDITOR_H_

#include "JuceHeader.h"
#include "openmini/implementation/common/PluginProcessor.h"

static const int kMainWindowSizeX(800);
static const int kMainWindowSizeY(600);

/// @brief Plugin "editor" class
///
/// Contains all UI and user control stuff
class OpenMiniAudioProcessorEditor : public juce::AudioProcessorEditor,
                                     public juce::ChangeListener,
                                     public juce::Slider::Listener,
                                     public juce::Timer {
 public:
  explicit OpenMiniAudioProcessorEditor(OpenMiniAudioProcessor* owner);
  ~OpenMiniAudioProcessorEditor();

  void paint(juce::Graphics& g);

  // Overrides from inherited classes
  void sliderValueChanged(juce::Slider* slider);
  void changeListenerCallback(juce::ChangeBroadcaster *source);
  void timerCallback();

  /// @brief Retrieve an access to the audio processor
  OpenMiniAudioProcessor* getProcessor() const;

 private:
  OpenMiniAudioProcessor* owner_;
  juce::MidiKeyboardComponent keyboard_;
  juce::Slider osc1_waveform_;
  juce::Slider osc2_waveform_;
  juce::Slider osc3_waveform_;
  juce::Slider osc1_volume_;
  juce::Slider osc2_volume_;
  juce::Slider osc3_volume_;
  juce::Slider filter_freq_;
  juce::Slider filter_q_;
  juce::TextEditor debug_infos_;
  static const int kTimerInterval = 100;
};

#endif  // OPENMINI_PLUGIN_COMMON_PLUGINEDITOR_H_
