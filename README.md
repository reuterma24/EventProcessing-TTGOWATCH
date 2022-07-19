# EventProcessing-TTGOWATCH

by Chris, Martin and Pascal in SoSe 2022.


# General Idea
![watchSetup](https://user-images.githubusercontent.com/84461357/179754101-7df50dd0-cc32-444d-8d6f-cb290eda0b86.JPG)

The general idea is that each watch recieves/sends events from/to both other watches. The watches communicate via WLAN, therefore the illustration above is technically not correct as there is a router in center. We assigned each watch a static IP in the network (12, 13, 14) so that they are able to communicate with each other.  
Events are represented as letters ranging from A to F in our implementation. Each watch is constantly processing the incoming events in a queue to detect the complex pattern assigned to it. The operators _AND_ and _SEQ_ are supported.  
We wrote a _library-like_ EventProcessing Class called CEP. Therefore it should be easy to assign an arbitrary complex pattern to an individual watch.


# What Went Well
The whole setup and deploying code to the watch from the arduino IDE was well documented in a manual and went suprisingly smooth. Only minor difficulties.


# Obstacles
Establishing wireless communication between (just) two watches took us way longer than expected. 


# Setup
First, follow the instructions in the manual to use the arduino IDE together with the watch.  
Open the whole project in the IDE and have a quick look at the _EventProcessing_TTGOWATCH.ino_ file and move to [this](https://github.com/reuterma24/EventProcessing-TTGOWATCH/blob/59c1df0fea0641a8e6914c44a1d574a6165ffd08/EventProcessing_TTGOWATCH.ino#L14-L19") section.  
Here it is mandatory to comment out two IPAddresses so that each watch gets a unique address in the network. You may also need to change the first 3 places of the IPAddress, the gateway and the subnet mask depending on your router.
  
To assign each watch a different pattern you have to navigate over [here](https://github.com/reuterma24/EventProcessing-TTGOWATCH/blob/59c1df0fea0641a8e6914c44a1d574a6165ffd08/CEP.ino#L173-L180) in the _CEP.ino_ file. 
You can either choose one of the predefined patterns by commenting out/in the respective ones or create a pattern of your desire.
