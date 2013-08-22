//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "FloodingNode.h"
#include <algorithm>

Define_Module(FloodingNode);



std::vector<DarknetPeer*> FloodingNode::findNextHop(DarknetMessage* msg) {
    //TODO: could be improved
    std::vector<DarknetPeer*> list;
    for(std::set<std::string>::iterator it = connected.begin(); it != connected.end(); it++) {
        list.push_back(peers[*it]);
    }
    EV <<  nodeID << ": findNextHop size: " << list.size();
    return list;
}

/*
 * check whether we we have seen msg earlier respectively a duplicate of it
 */
void FloodingNode::handleDarknetMessage(DarknetMessage* msg) {
    long test = msg->getTreeId();
    if(std::find(seenMessages.begin(),seenMessages.end(),test) == seenMessages.end()) { //already seen?
        seenMessages.push_back(msg->getTreeId());
        DarknetSimpleNode::handleDarknetMessage(msg);
    }else {
        // TODO: tell about dropped message
        delete msg;
    }
}

/*
 * add TreeID of msg to list of seen messages to prevent dealing again with them if receiving nodes send them back
 */
bool FloodingNode::sendMessage(DarknetMessage* msg) {
    if(std::find(seenMessages.begin(),seenMessages.end(),msg->getTreeId()) != seenMessages.end()) { //already seen?
        seenMessages.push_back(msg->getTreeId()); // prevent dealing with messages we self sent
    }
    return DarknetSimpleNode::sendMessage(msg);
}