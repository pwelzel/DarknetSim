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

package darknetsim;

simple DarknetBaseNode like inet.applications.udpapp.UDPApp {
    parameters:
        @statistic[sigSendDM](record=count,vector?);
        @statistic[sigUnhandledMSG](record=count,vector?);
        @statistic[sigDropTtlExeeded](record=count,vector?);
        @statistic[sigRequestRemainingTTL](record=stats,vector?);
        @statistic[sigResponseRemainingTTL](record=stats,vector?);
        int localPort;
        string nodeID;
        string destinations;
        int defaultTTL = default(32);
    gates:
	    input udpIn;
	    output udpOut;
    
}