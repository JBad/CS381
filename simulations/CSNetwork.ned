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

package cs381.simulations;

import cs381.ClientApp;
import cs381.ServerApp;


import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;

network CSNetwork
{
	submodules:
	    configurator: IPv4NetworkConfigurator {
            parameters:
                config=xml("<config><interface hosts='*' address='192.168.x.x' netmask='255.255.x.x'/></config>");
        }
    	
    	client1: ClientApp {
    	}
    	
    	server1: ServerApp {
    	}
    	
   	connections:
   	    client1.tcpOut --> server1.tcpIn;
   	    server1.tcpOut --> client1.tcpIn;
   	    
}
