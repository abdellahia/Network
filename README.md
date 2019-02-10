-------------
Installation:
-------------
	The command "make" to install the sniffer
	The executable will be created in the same directory named projet0

------------
Execution:
------------
	The program is executed with command:
											./projet0

------------
Options:
------------
	The sniffr can be started with 4 different options : i,o,f,v
	The use is as following:
			./ (-i <device> | -o <file>) [-f <BPF filter>] [-v <1|2|3>(verbosity)>]

	*** o : choice of the device where packet will be analyzed
	*** f : filter a packet
	*** o : file trace for offline sniffing
	*** v : level of verbosity :
		<1> low verbosity
		<2> medium verbosity
		<3> high verbosity

----------------------
Example of use
----------------------
./analyseur -o "http.cap"
