# BLUE Algorithm in ns-3.29

* The increasing packet loss rates caused by an exponential increase in network traffic 
  The IETF has been considering the deployment of active queue management techniques such as RED. 
  While active queue management can potentially reduce packet loss rates in the Internet, 
  we show that current techniques are ineffective in preventing high loss rates.

* The inherent problem with these queue management algorithms is that they use queue lengths 
  as the indicator of the severity of congestion. In light of this observation, a fundamentally different 
  active queue management algorithm, called BLUE, is proposed, implemented, and evaluated. 

* BLUE uses packet loss and link idle events to manage congestion. Using both simulation and controlled 
  experiments, BLUE is shown to perform significantly better than RED, both in terms of packet loss rates
  and buffer size requirements in the network. 

* As an extension to BLUE, a novel technique based on Bloom filters is described for enforcing fairness among 
  a large number of flows. In particular, we propose and evaluate Stochastic Fair BLUE (SFB), a queue management
  algorithm which can identify and rate-limit nonresponsive flows using a very small amount of state information.
  
* Blue Algorithm Pseudocode  <br>
 ```
    Upon packet loss (or Qlen > l) event:
        if ((now - last_update) > freze_time):
            Pm = Pm + d1
            last_update = now
    Upon link idle event
        if((now - last_update) > freeze_time):
            Pm = Pm -d2
            last_update = now
    
    
    d1 & d2 are constants 
    Pm = Probability of drop packet or mark 
    freeze_time = minimum time inyerval between two successful updates of Pm
```
### Model Description
  The source code for the BLUE model is located in the directory ``src/traffic-control/model``
  and consists of 2 files `blue-queue-disc.h` and `blue-queue-disc.cc` defining a BlueQueueDisc
  class. The code was ported to |ns3| by Mohit P. Tahiliani, Vivek Jain and Sandeep Singh
  based on ns-1.1 code implemented by Wu-chang Feng and the Linux kernel code of Stochastic Fair
  BLUE.  

* class :cpp:class:`BlueQueueDisc`: This class implements the main BLUE algorithm:

  * ``BlueQueueDisc::DoEnqueue ()``: This method checks whether the queue is full, and if so, drops the packets and records the number of drops due to queue overflow and calls method ``BlueQueueDisc::IncrementPmark()``. If queue is not full, this method calls ``BlueQueueDisc::DropEarly()``, and depending on the value returned, the incoming packet is either enqueued or dropped.

  * ``BlueQueueDisc::DropEarly ()``: The decision to enqueue or drop the packet is taken by invoking this method, which returns a boolean value; false indicates enqueue and true indicates drop.

  * ``BlueQueueDisc::IncrementPmark ()``: This method increases the drop probability when there is heavy congestion in queue.

  * ``BlueQueueDisc::DecrementPmark ()``: This method decrements the drop probability when link is idle for certain time.

  * ``BlueQueueDisc::DoDequeue ()``: This method dequeues the packet from queue and if queue is idle, this initializes idleStartTime.  
### Attributes
The key attributes that the BlueQueueDisc class holds include the following: 
  * ``MaxSize:`` BLUE operating mode (BYTES or PACKETS). The default mode is PACKETS and maximum number of bytes or packets the queue                    can hold. The default value is 25 bytes / packets.
  * ``MeanPktSize:`` Mean packet size in bytes. The default value is 1000 bytes.
  * ``Increment:`` Decrement value for marking probability. The default value is 0.0025.
  * ``Decrement:`` Increment value for marking probability. The default value is 0.00025.
  * ``FreezeTime:`` Time interval during which Pmark cannot be updated. The default value is 100 ms. 
  * ``LastUpdateTime:`` Last time at which drop probability is changed.
  * ``PMark:`` Value of drop probability.

## Running the tests

BLUE Was implemented intially in ns-3.25 
  * Programs related to BLUE AQM has been provided by in
```
      src/traffic-control/model/blue-queue-disc.cc
```
```
      src/traffic-control/model/blue-queue-disc.h
```
* To test the BLUE AQM we compare it with 
```
      src/traffic-control/examples/pfifo-vs-blue.cc
```
```
      src/traffic-control/examples/red-vs-blue.cc
```

* To run the comparisons we should execute following
```
      ./waf configure --enable-examples --enable-tests
      ./waf build
      ./waf --run "pfifo-vs-blue --queueDiscType=BLUE"
      ./waf --run "red-vs-blue   --queueDiscType=BLUE"
```
* Validation of BLUE AQM<br>
  The BLUE model is tested using :cpp:class:BlueQueueDiscTestSuite class defined in 
  src/traffic-control/test/blue-queue-disc-test-suite.cc 
  The suite includes 4 test cases:
```
        * Test 1: enqueue/dequeue with no drops and makes sure that BLUE attributes can be set correctly.
        * Test 2: default values for BLUE parameters
        * Test 3: higher increment value for Pmark
        * Test 4: lesser time interval for updating Pmark
        
        The test suite can be run using the following commands:
          ./waf configure --enable-examples --enable-tests
          ./waf build
          ./test.py -suit blue-queue-disc
```

### References

[1] Feng, W. C., Kandlur, D., Saha, D., & Shin, K. (1999). BLUE: A new class of active queue management algorithms. Ann Arbor, 1001, 48105.

[2] Floyd, S., & Jacobson, V. (1993). Random early detection gateways for congestion avoidance. IEEE/ACM Transactions on networking, 1(4), 397-413.

[3] http://www.isi.edu/nsnam/ns/

[4] http://www.nsnam.org/
