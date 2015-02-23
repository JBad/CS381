// Implementation of the module.
// Adapted from the tictoc tutorial

#include "CSAppMsg_m.h"
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

    this->connect();

    //cMessage *timer_msg = new cMessage("timer");
    //this->scheduleAt(simTime() + exponential(0.001), timer_msg);

    cout << "end P2P init" << endl;
}

/** handle the timeout method */
void P2PApp::handleTimer(cMessage *msg) {

    EV << "=== Peer: " << this->localAddress_
              << " received handleTimer message. " << endl;

    // cleanup the incoming message
    delete msg;

    this->connect();
}

// determines how to handle a message (note that an message is
// essentially any event)
void P2PApp::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        this->handleTimer(msg);
    } else {
        this->socket_->processMessage(msg);
    }

    return;
}

// connect to peer i
void P2PApp::connect() {
    cout << "startConnect" << endl;
    EV << "=== Peer: " << this->localAddress_ << " received connect message"
              << endl;
    EV << "issuing connect command\n";
    setStatusString("connecting");

    // we allocate a socket to be used for actively connecting to the peer and
    // transferring data over it.
    socket_ = new TCPSocket();
    socket_->setOutputGate(gate("tcpOut"));

    socket_->setDataTransferMode(this->socket_->getDataTransferMode());

    // issue a connect request
    socket_->connect(
            IPvXAddressResolver().resolve(this->connectAddress_.c_str()),
            this->connectPort_);

    socket_->setCallbackObject(this, NULL);

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

    setStatusString("closing");

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

        //this->handleResponseFromTracker()
        //TODO
    }
    case Peer_INFO_REQUEST:
    {
        Peer_InfoReq *resp = dynamic_cast<Peer_InfoReq *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Peer_InfoReq" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }

        //this->makePeerResponse()
        //TODO: always do -1 case
    }
    case Peer_INFO_RESPONSE:
    {
        Peer_InfoResp *resp = dynamic_cast<Peer_InfoResp *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Peer_InfoResp" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }

        //this->handleResponseFromPeerChunkList()
        //TODO: change
    }
    case Peer_CHUNK_REQUEST:
    {
        Peer_ChunkReq *resp = dynamic_cast<Peer_ChunkReq *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Peer_ChunkReq" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }

        //this->makePeerResponse()
        //TODO: not -1 case
    }
    case Peer_CHUNK_RESPONSE:
    {
        Peer_ChunkResp *resp = dynamic_cast<Peer_ChunkResp *>(msg);

        if (!resp) {
            EV << "Arriving packet is not of type Peer_ChunkResp" << endl;
        } else {
            EV << "Arriving packet: Responder ID = " << resp->getId() << endl;
        }

        //this->handleResponsePeerSingleChunk()
        //TODO
    }
    default:
    {
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
    req->setType(int(Tracker_REQUEST));
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

char * P2PApp::makePeerResponse(char * bytes) {
    int value = atoi(bytes);
    if (value == -1) {
        stringstream chunks;
        chunks << "i";
        for (int i = 0; i < 20; ++i) {
            if (chunks_[i] == true) {
                chunks << i;
                chunks << ";";
            }
        }

        return P2PApp::ss_to_charp(chunks);
    } else {
        return data_[value];
    }
}

char * P2PApp::makeRequestForPeerAllChunks() {
    int value = -1;
    stringstream chunks;
    chunks << value;
    return P2PApp::ss_to_charp(chunks); //remember to delete the mem
}

bool P2PApp::fileComplete() {
    for (int i = 0; i < 20; ++i) {
        if (!chunks_[i]) {
            return false;
        }
    }
    return true;
}

void P2PApp::handleResponseFromTracker(char * list) {
    std::string str(list);
    vector<string> newPeers = P2PApp::split(str, ';');
    for (int i = 0; i < newPeers.size(); ++i) {
        peers_.insert(newPeers[i]);
        pendingRequests_.insert(std::pair<string, int>(newPeers[i], -1));
    }
}

void P2PApp::handleResponsefromPeerChunkList(char * list, char * peer) {
    string peerName(peer);
    std::string str(list);
    vector<string> chunks = P2PApp::split(str, ';');
    for (int i = 0; i < chunks.size(); ++i) {
        int value = atoi(chunks[i].c_str());
        peerChunks_[peerName].insert(value);
    }
}

void P2PApp::handleResponsefromPeerSingleChunk(char * data, char * peer) {
    string peerName(peer);
    for (int it = 0; it < chunks_.size(); ++it) {
        int value = pendingRequests_[peerName];
        pendingRequests_[peerName] = -1;
        data_[value] = data;
        chunks_[value] = true;
    }
}

char * P2PApp::makeRequestFor(char * peer) {
    string peerName(peer);
    set<int> peerChunk = peerChunks_[peerName];
    for (set<int>::iterator i = peerChunk.begin(); i != peerChunk.end(); ++i) {
        if (!chunks_[*i]) {
            stringstream chunks;
            chunks << *i;
            pendingRequests_[peerName] = *i;
            return P2PApp::ss_to_charp(chunks); //remember to delete the mem
        }
    }
    return NULL;
}

std::vector<std::string>& P2PApp::split(const std::string &s, char delim,
        std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

char* P2PApp::ss_to_charp(std::stringstream& accum) {
    char * writable;
    writable = new char[accum.str().size() + 1];
    std::string str = accum.str();
    std::copy(str.begin(), str.end(), writable);
    writable[str.length()] = '\0'; // don't forget the terminating 0

    return writable;
}

std::vector<std::string> P2PApp::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
