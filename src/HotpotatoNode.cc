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

//#include <IPAddressResolver.h>
#include "HotpotatoNode.h"

Define_Module(HotpotatoNode);

std::vector<DarknetPeer*> HotpotatoNode::findNextHop(DarknetMessage* msg) {
    if(!connections.size()) { // peer list empty -> raise exception? (TODO)
        EV << "ERROR: empty peer list!";
        return std::vector<DarknetPeer*>(0);
    }
    if(peers.find(msg->getDestNodeID()) != peers.end() and connections.find(msg->getDestNodeID()) != connections.end()) {
        return std::vector<DarknetPeer*>(1,peers[msg->getDestNodeID()]);
    }else {
        std::map<std::string, DarknetConnection*>::iterator iter = connections.begin();
        std::advance(iter, dblrand() * connections.size());
        return std::vector<DarknetPeer*>(1,peers[iter->first]);
    }
}