#!/usr/bin/python2

import OSC
import threading
from RPi import GPIO

#------OSC Server-------------------------------------#
receive_address = '127.0.0.1', 8338

# OSC Server. there are three different types of server. 
s = OSC.ThreadingOSCServer(receive_address)

# this registers a 'default' handler (for unmatched messages)
s.addDefaultHandlers()

# define a message-handler function for the server to call.
def printing_handler(addr, tags, stuff, source):
	if addr=='/test':
		print "Test", stuff, tags, source
	if addr=='/neutral':
		print "expression neutre"
		GPIO.output(5, GPIO.LOW)
		GPIO.output(6, GPIO.LOW)
	if addr=='/smile':
		print "Sourire detecte ! :"
		GPIO.output(6, GPIO.LOW)
		GPIO.output(5, GPIO.HIGH)
	if addr=='/raisedeyebrows':
		print "Sourcil leve !"
		GPIO.output(5, GPIO.LOW)
		GPIO.output(6, GPIO.HIGH)


	
s.addMsgHandler("/test", printing_handler)
s.addMsgHandler("/found", printing_handler)
s.addMsgHandler("/neutral", printing_handler)
s.addMsgHandler("/smile", printing_handler)
s.addMsgHandler("/raisedeyebrows", printing_handler)


def main():
    # Start OSCServer
    print "Starting OSCServer"
    st = threading.Thread(target=s.serve_forever)
    st.start()

main()
