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

package cs381_rdt_1_0;

// import all the inet defns as needed for our experiment
import ned.DatarateChannel;

// define a typedef for a simple module. Here we define a user-level
// process, which could be a sender or receiver
simple Client
{
    parameters:
    	string name;
    	
    gates: // define the ports to the outside world
        input fromXport;
        output toXport;
}

simple Server
{
    parameters:
    	string name;
    	
    gates: // define the ports to the outside world
        input fromXport;
        output toXport;
}


// define a typedef for a simple module. Here we define a protocol
// layer implementation of a transport protocol
simple RDT_1_0
{
   parameters:
    	string name;
    	
    gates: // define the ports to the outside world and layer above
        input fromAppln;
        output toAppln;

        input fromNet;
        output toNet;
}


// now we define a module comprising instances of the simple
// module type defined above.  Again there are no parameters for the
// top level compound module. 
module RelXport_Network_1_0
{
    types:
        // now we define an error free channel connecting the two nodes. Say
        // it is a WAN connection
        channel ErrorFreeWAN extends DatarateChannel
        {
            delay = 100ms;       // delay is 100 msec
            datarate = 1e+6bps;     // 1 Mbps
        }

    submodules: // child modules
        // process instances
        client: Client {
           parameters:
			    name = "client1";
		   @display("p=115,50");
        }
        server: Server {
			parameters:
			    name = "server1";
            @display("p=318,50");
        }
        // protocol layer instances
        sender: RDT_1_0 {
           parameters:
			    name = "sender";
            @display("p=115,181");
        }
        receiver: RDT_1_0 {
           parameters:
			    name = "receiver";
            @display("p=318,181");
        }
    connections: // connections between child modules

        // layer wise communication (no channel)
        client.toXport --> sender.fromAppln;
        sender.toAppln --> client.fromXport;

        server.toXport --> receiver.fromAppln;
        receiver.toAppln --> server.fromXport;

        // network connection
        sender.toNet --> ErrorFreeWAN --> receiver.fromNet;
        sender.fromNet <-- ErrorFreeWAN <-- receiver.toNet;
}

// now define a network
network rdt_1_0_nw
{
    submodules:
        myNW : RelXport_Network_1_0;
}
