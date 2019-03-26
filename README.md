# BLUE
Aligning BLUE implementation with ns3-dev

## Things to be done before running the codes in ns3.29

<p>
<li> Download the above files from the repository.
<li> Add those file in traffic module <br>
* root/ns3.29/build/ns3blue-queue-disc.h <br>
* src/traffic-moudle/example/red-vs-blue <br>
* src/traffic-module/model/blue-queue-disc.cc and blue-queue-disc.h in that folder <br>
* src/traffic-module/tests/blue-implementation.cc
<li> Add corresponding wscripts in their respective directories as ns3.29 does not have BLUE in-built
<li> Run these commands to check whether it is building and running properly. <br>
 * ./waf configure <br>
 * ./waf --enable-examples --enable-tests <br>
 * ./waf build<br>
