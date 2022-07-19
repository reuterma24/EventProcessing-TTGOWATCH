# EventProcessing-TTGOWATCH

by Chris, Martin and Pascal in SoSe 2022.


# General Idea
![watchSetup](https://user-images.githubusercontent.com/84461357/179754101-7df50dd0-cc32-444d-8d6f-cb290eda0b86.JPG)

The general idea is that each watch recieves/sends events from/to both other watches. The watches communicate via WLAN, therefore the illustration above is technically not correct as there is a router in center. We assigned each watch a static IP in the network (12, 13, 14) so that they are able to communicate with each other.
Each watch is constantly processing the incoming events in a queue to detect the complex pattern assigned to it (pattern in visualization).  
We wrote a _library like_ EventProcessing Class called CEP. Therefore it should be easy to assign an arbitrary complex pattern to an individual watch.
Events are represented as letters ranging from A to F in our implementation.

# What went well ?
The whole setup and deploying code to the watch from the arduino IDE was well documented in a manual and went suprisingly smooth. Only minor difficulties.


# Obstacles
Establishing wireless communication between (just) two watches took us way longer than expected. 
