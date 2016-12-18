#!/usr/bin/python2

import OSC
import time

# Init OSC
client = OSC.OSCClient()
msg = OSC.OSCMessage()

msg.setAddress("/pose/position")
    
for i in range(10):
    time.sleep(1)
    msg.append(i)
    try:
        client.sendto(msg, ('127.0.0.1', 8338))
        msg.clearData()
    except:
        print 'Connection refused'
        pass
    
    
