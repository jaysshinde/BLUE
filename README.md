# BLUE
Aligning BLUE implementation with ns3-dev

## Things to be done before running the codes in ns3.29

<p>
<li> download the above files from the repo
<li> add those file in traffic module <br>
* src/traffic-moudle/example/red-vs-blue <br>
* src/traffic-module/model/blue-queue-disc.cc and blue-queue-disc.h in that folder<br>
* src/traffic-module/tests/blue-implementation.cc <br>
<li> add corresponding wscripts in there respective directories as the ns3.29 doesnot have blue inbuilt
<li> now run these commands to check wheather its building properly or not and wheather its running or not
 * ./waf configure<br>
 * ./waf --enable-examples --enable-tests<br>
 * ./waf build
