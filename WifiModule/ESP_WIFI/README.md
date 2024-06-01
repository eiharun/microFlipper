Notes:

	Before sending each command, check to see if UART is currently IDLE, if not, have a timeout.
	
	Before leaving each command function check to see if UART is currently IDLE, have a timeout as well
	
	Process data in each function. -- OK/r/n/r/n signals the end of all messages
	
	For AT+RST ignore the trailing message
	
	USE ST-LINK TO UPDATE-FLASH ESP01 AT-FIRMWARE