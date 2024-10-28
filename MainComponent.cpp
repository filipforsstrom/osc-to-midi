// MainComponent.cpp

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Set up the rotary knob
    rotaryKnob.setRange(0.0, 1.0);
    rotaryKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    rotaryKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 150, 25);
    rotaryKnob.setBounds(10, 10, 180, 180);
    rotaryKnob.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(rotaryKnob);

    // Specify the UDP port number to receive incoming OSC messages
    if (!connect(9001)) // [3]
        showConnectionErrorMessage("Error: could not connect to UDP port 9001.");

    // Listen for OSC messages matching this address
    addListener(this, "/juce/rotaryknob"); // [4]

    setSize(600, 400);
}

void MainComponent::oscMessageReceived(const juce::OSCMessage &message)
{
    if (message.size() == 1 && message[0].isFloat32())                          // [5]
        rotaryKnob.setValue(juce::jlimit(0.0f, 1.0f, message[0].getFloat32())); // [6]
    
    // log message
    juce::Logger::writeToLog("Received OSC message: " + message.getAddressPattern().toString());
}

void MainComponent::showConnectionErrorMessage(const juce::String &messageText)
{
    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::WarningIcon,
        "Connection error",
        messageText,
        "OK");
}

void MainComponent::paint(juce::Graphics &g)
{
    // Fill the background with a solid colour
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // Update positions of child components if necessary
}