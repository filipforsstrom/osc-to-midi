#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_osc/juce_osc.h>

//==============================================================================
class MainComponent final : public juce::Component,
                            private juce::OSCReceiver,
                            private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    //==============================================================================
    MainComponent();

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    // Declare the Slider object
    juce::Slider rotaryKnob;

    // Override the OSC message received function
    void oscMessageReceived(const juce::OSCMessage &message) override;

    // Error logging function
    void showConnectionErrorMessage(const juce::String &messageText);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};