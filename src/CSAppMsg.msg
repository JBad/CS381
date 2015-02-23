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

enum BT_MSG_TYPE {
    Tracker_REQUEST = 0;
    Tracker_RESPONSE = 1;
    Peer_INFO_REQUEST = 2;
    Peer_INFO_RESPONSE = 3;
    Peer_CHUNK_REQUEST = 4;
    Peer_CHUNK_RESPONSE = 5;
};

packet BT_Packet
{
   int     type @enum(BT_MSG_TYPE);  // our message type
};

packet Tracker_Req extends BT_Packet
{
    string	id;		        // announce the requestor's ID
};

packet Tracker_Resp extends BT_Packet
{
    string  id;			// ID of the responder
    string peers[];
    int numPeers;
};

packet Peer_Packet
{
    int     type @enum(BT_MSG_TYPE);
};

packet Peer_InfoReq extends BT_Packet
{
};

packet Peer_InfoResp extends BT_Packet
{
	int chunks[];
	int size;   
};

packet Peer_ChunkReq extends BT_Packet
{
	int chunk;   
};

packet Peer_ChunkResp extends BT_Packet
{
    char data[];
    int size;   
};

    
