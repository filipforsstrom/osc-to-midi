from oscpy.client import OSCClient

address = "127.0.0.1"
port = 9001

osc = OSCClient(address, port)
for i in range(10):
    osc.send_message(b'/juce/rotaryknob', [i])