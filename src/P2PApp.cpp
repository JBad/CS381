// Implementation of the module.
// Adapted from the tictoc tutorial

#include "P2PApp.h"

#include "IPvXAddressResolver.h"

// the module class is now registered with omnet++ and tells it to look for
// a corresponding NED file for a simple module definition of the same name.
// ** Never put this inside a header file **
Define_Module(P2PApp);

// ******* Peer SimpleModule *******

// constructor
P2PApp::P2PApp(void) {
    cout << "end P2P const" << endl;
}

// destructor
P2PApp::~P2PApp(void) {
}

// overridden methods
void P2PApp::initialize(void) {
    cSimpleModule::initialize();

    this->localAddress_ = this->par("localAddress").stringValue();
    this->localPort_ = this->par("localPort");
    this->connectPort_ = this->par("connectPort");

    this->connectAddress_ = this->par("connectAddress").stringValue();

    cout << "start P2P init" << endl;

    string dataTransferMode = this->par ("dataTransferMode").stringValue ();

    // create a new socket for the listening role
    this->socket_ = new TCPSocket ();

    // decide the data transfer mode
    if (!dataTransferMode.compare ("bytecount"))
        this->socket_->setDataTransferMode (TCP_TRANSFER_BYTECOUNT);
    else if (!dataTransferMode.compare ("object"))
        this->socket_->setDataTransferMode (TCP_TRANSFER_OBJECT);
    else if (!dataTransferMode.compare ("bytestream"))
        this->socket_->setDataTransferMode (TCP_TRANSFER_BYTESTREAM);
    else { // error
        EV << "=== Bad data transfer mode value. Assuming object" << endl;
        this->socket_->setDataTransferMode (TCP_TRANSFER_OBJECT);
    }

    this->socket_->bind (this->localAddress_.length () ?
            IPvXAddressResolver ().resolve (this->localAddress_.c_str ()) : IPvXAddress (),
            this->localPort_);

    bool *passive = new bool (true);
    this->socket_->setCallbackObject (this, passive);  // send the flag

    // do not forget to set the outgoing gate
    this->socket_->setOutputGate (gate ("tcpOut"));

    this->socket_->listen ();

    // debugging
    EV << "+++ Peer: " << this->localAddress_ << " created a listening socket with "
       << "connection ID = " << this->socket_->getConnectionId () << " +++" << endl;

    // now save this socket in our map
    this->socketMap_.addSocket (this->socket_);

    // now we start a timer so that when it kicks in, we make a connection to another peer
    cMessage *timer_msg = new cMessage ("timer");
    this->scheduleAt (simTime () + exponential (0.001), timer_msg);

}

/** handle the timeout method */
void P2PApp::handleTimer(cMessage *msg) {

    EV << "=== Peer: " << this->localAddress_
              << " received handleTimer message. " << endl;

    // cleanup the incoming message
    delete msg;


    //connect to tracker
    this->connect(this->connectAddress_);


}

// determines how to handle a message (note that an message is
// essentially any event)
void P2PApp::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        this->handleTimer(msg);
    } else {
        TCPSocket *socket = this->socketMap_.findSocketFor (msg);
        if(!socket) {
            TCPCommand *cmd = dynamic_cast<TCPCommand *>(msg->getControlInfo());

            if(!cmd) {
                throw cRuntimeError("P2PApp::handleMessage: no TCPCommand control info in message (not from TCP?)");
            } else {
                int connId = cmd->getConnId();

                EV << "+++ Peer: " << this->localAddress_ << " creating a new socket with "
                   << "connection ID = " << connId << " ===" << endl;

                TCPSocket *new_socket = new TCPSocket(msg);

                bool *passive = new bool(true);
                new_socket->setCallbackObject(this, passive);

                new_socket->setOutputGate(gate("tcpOut"));

                //new_socket->setDataTransferMode(this->socket_->getDataTransferMode());

                // now save this socket in our map
                this->socketMap_.addSocket (new_socket);

                // process the message
                new_socket->processMessage (msg);
            }
        } else {
            socket->processMessage (msg);
        }
    }
}

// connect to peer i
void P2PApp::connect(char* connectAddress) {
    cout << "startConnect" << endl;
    EV << "=== Peer: " << this->localAddress_ << " received connect message"
              << endl;
    EV << "issuing connect command\n";
    setStatusString("connecting");

    TCPSocket *new_socket = new TCPSocket();

    new_socket->setOutputGate (gate ("tcpOut"));
    // we allocate a socket to be used for actively connecting to the peer and
    // transferring data over it.

    socket_->setDataTransferMode(this->socket_->getDataTransferMode());

    // issue a connect request
    socket_->connect(
            IPvXAddressResolver().resolve(connectAddress),
            this->connectPort_);

    bool *passive = new bool(false);
    socket_->setCallbackObject(this, passive);

    this->socketMap_.addSocket (new_socket);
    // debugging
    EV << "+++ Peer: " << this->localAddress_ << " created a new socket with "
              << "connection ID = " << socket_->getConnectionId() << " ==="
              << endl;
    cout << "endConnect" << endl;
}

// close the peer side
void P2PApp::close() {
    EV << "=== Peer: " << this->localAddress_ << " received close () message"
              << endl;
    EV << "issuing CLOSE command\n";

    this->socket_->close();
}

void P2PApp::socketDataArrived(int connId, void *, cPacket *msg, bool urgent) {
    EV << "=== Peer: " << this->localAddress_
              << " received socketDataArrived message. ===" << endl;

    BT_Packet *packet = dynamic_cast<BT_Packet *>(msg);

    if (!packet) {
        return;
    }
    (BT_MSG_TYPE) packet->getType();

    switch ((BT_MSG_TYPE) packet->getType()) {
    case Tracker_REQUEST: {
        EV << "This shouldn't be happening since we are not a tracker." << endl;
    }
    case Tracker_RESPONSE: {
        Tracker_Resp *resp = dynamic_cast<Tracker_Resp *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Tracker_Resp" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }

        this->handleResponseFromTracker(resp);
    }
    case Peer_INFO_REQUEST: {
        Peer_InfoReq *resp = dynamic_cast<Peer_InfoReq *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Peer_InfoReq" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }

        Peer_InfoResp* info_resp = this->makePeerListResponse();

        //TODO: SOCKET_MAP
    }
    case Peer_INFO_RESPONSE: {
        Peer_InfoResp *resp = dynamic_cast<Peer_InfoResp *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Peer_InfoResp" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }

        this->handleResponsefromPeerChunkList(resp);

        //TODO: change
    }
    case Peer_CHUNK_REQUEST: {
        Peer_ChunkReq *resp = dynamic_cast<Peer_ChunkReq *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Peer_ChunkReq" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }


        //this->makePeerResponse()
        //TODO: not -1 case
    }
    case Peer_CHUNK_RESPONSE: {
        Peer_ChunkResp *resp = dynamic_cast<Peer_ChunkResp *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Peer_ChunkResp" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }

        //this->handleResponsePeerSingleChunk()
        //TODO
    }
    default: {
        EV << "Arriving packet is not of type that is recognized!!" << endl;
    }
    }

    delete msg;
}
/*
 void P2PApp::handleResponse(CS_Resp *res, int connId) {
 if (res->getDataArraySize() > 0) {

 vector<char> curChunk;
 for(int i = 0; i < res->getDataArraySize(); ++i) {
 curChunk.push_back(res->getData(i));
 }
 file_.push_back(curChunk);

 //modify for bittorrent to just ask for new chunk
 this->sendRequest(connId);
 ofstream myfile;
 myfile.open("dummy-P2P.txt");
 for (int i = 0; i < res->getDataArraySize(); ++i) {
 myfile << res->getData(i);
 }
 myfile.close();
 }
 }*/

void P2PApp::sendRequest(int connId, const char* id, string fname) {
    Tracker_Req *req = new Tracker_Req();
    req->setType((int)Tracker_REQUEST);
    req->setId(this->localAddress_.c_str());
    //req->setFile(fname.c_str());

    req->setByteLength(128);

    socket_->send(req);
}

void P2PApp::socketEstablished(int connId, void *role) {
    EV << "=== Peer: " << this->localAddress_
              << " received socketEstablished message on connID " << connId
              << " ===" << endl;

    setStatusString("ConnectionEstablished");

    bool *passive = static_cast<bool *>(role);
    if (*passive) {
        EV
                  << "=== We are in passive role and hence just wait for an incoming req ==="
                  << endl;
    } else {
        EV << "=== We are in active role and hence initiate a req ===" << endl;

        this->sendRequest(connId, this->localAddress_.c_str(), "dummy.txt");
    }
}

void P2PApp::socketPeerClosed(int connId, void *yourPtr) {

}

void P2PApp::socketClosed(int connId, void *) {
    delete socket_;
}

void P2PApp::socketFailure(int connId, void *yourPtr, int code) {

}

// there was no need for us to have provided this method, however, if
// you want to gather statistics of your simulation, this is the
// method you need to add
void P2PApp::finish(void) {
    EV << "=== finish called" << endl;

    delete socket_;
    // finalize any statistics collection
}

void P2PApp::setStatusString(const char *s) {
    if (ev.isGUI()) {
        getDisplayString().setTagArg("t", 0, s);
        bubble(s);
    }
}

Peer_InfoReq* P2PApp::makePeerListRequest(string peer) {
    Peer_InfoReq* req = new Peer_InfoReq();
    req->setId(this->localAddress_.c_str());
    req->setType((int)Peer_INFO_REQUEST);

    return req;
}

Peer_ChunkReq* P2PApp::makePeerChunkRequest(string peer, int chunk) {
    Peer_ChunkReq* req = new Peer_ChunkReq();
    req->setId(this->localAddress_.c_str());
    req->setChunk(chunk);
    req->setType((int)Peer_CHUNK_REQUEST);

    return req;
}

Peer_InfoResp* P2PApp::makePeerListResponse(void) {
    Peer_InfoResp* resp = new Peer_InfoResp();
    resp->setType((int)Peer_INFO_RESPONSE);
    resp->setId(this->localAddress_.c_str());

    int count = 0;
    for (int i = 0; i < 20; ++i) {
        if (chunks_[i] == true)
            ++count;
    }
    resp->setChunksArraySize(count);
    count = 0;
    for (int i = 0; i < 20; ++i) {
        if (chunks_[i] == true) {
            resp->setChunks(count, i);
            ++count;
        }
    }

    return resp;
}

Peer_ChunkResp* P2PApp::makePeerChunkResponse(Peer_ChunkReq* req) {
    Peer_ChunkResp* resp = new Peer_ChunkResp();
    resp->setType((int)Peer_CHUNK_RESPONSE);
    resp->setId(this->localAddress_.c_str());

    resp->setDataArraySize(dataSize_[req->getChunk()]);

    char* d = data_[req->getChunk()];
    for (int i = 0; i < dataSize_[req->getChunk()]; ++i) {
        resp->setData(i, d[i]);
    }

    return resp;
}

bool P2PApp::fileComplete() {
    for (int i = 0; i < 20; ++i) {
        if (!chunks_[i]) {
            return false;
        }
    }
    return true;
}

void P2PApp::handleResponseFromTracker(Tracker_Resp* resp) {
    for (int i = 0; i < resp->getPeersArraySize(); ++i) {
        peers_.insert(resp->getPeers(i));
        pendingRequests_.insert(std::pair<string, int>(resp->getPeers(i), -1));

        Peer_InfoReq* req = this->makePeerListRequest(resp->getPeers(i));

    }
}

void P2PApp::handleResponsefromPeerChunkList(Peer_InfoResp* resp) {
    std::string name(resp->getId());
    set<int> pChunks;
    for (int i = 0; i < resp->getChunksArraySize(); ++i) {
        pChunks.insert(resp->getChunks(i));
    }
    peerChunks_.insert(std::pair<string, set<int>>(name, pChunks));

    this->makeRequestFor(name);
}

void P2PApp::handleResponsefromPeerSingleChunk(Peer_ChunkResp* resp) {
    std::string peerName(resp->getId());
    int value = pendingRequests_[peerName];
    pendingRequests_[peerName] = -1;
    char* incomingData = new char[resp->getDataArraySize()];
    for(int i = 0; i < resp->getDataArraySize(); ++i) {
        incomingData[i] = resp->getData(i);
    }
    chunks_[value] = true;
    data_[value] = incomingData;
}

void P2PApp::makeRequestFor(string peer) {
    string peerName(peer);
    set<int> peerChunk = peerChunks_[peerName];
    for (set<int>::iterator i = peerChunk.begin(); i != peerChunk.end(); ++i) {
        if (!chunks_[*i] && !activeChunks_[*i]) {
            pendingRequests_[peerName] = *i;
            activeChunks_[*i] = true;

            Peer_ChunkReq* req = this->makePeerChunkRequest(peer, *i);

            return;
        }
    }
}

//void P2PApp::sendRequest()

char* P2PApp::ss_to_charp(std::stringstream& accum) {
    char * writable;
    writable = new char[accum.str().size() + 1];
    std::string str = accum.str();
    std::copy(str.begin(), str.end(), writable);
    writable[str.length()] = '\0'; // don't forget the terminating 0

    return writable;
}
