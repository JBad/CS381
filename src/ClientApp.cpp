// Implementation of the module.
// Adapted from the tictoc tutorial

#include "CSAppMsg_m.h"
#include "ClientApp.h"

#include "IPvXAddressResolver.h"

// the module class is now registered with omnet++ and tells it to look for
// a corresponding NED file for a simple module definition of the same name.
// ** Never put this inside a header file **
Define_Module(ClientApp);

// ******* Peer SimpleModule *******

// constructor
ClientApp::ClientApp(void) {
    cout << "end client const" << endl;
}

// destructor
ClientApp::~ClientApp(void) {
}

// overridden methods
void ClientApp::initialize(void) {
    cSimpleModule::initialize();



    this->localAddress_ = this->par("localAddress").stringValue();
    this->localPort_ = this->par("localPort");
    this->connectPort_ = this->par("connectPort");

    this->connectAddress_ = this->par("connectAddress").stringValue();

    cout << "start client init" << endl;

    this->connect();

    //cMessage *timer_msg = new cMessage("timer");
    //this->scheduleAt(simTime() + exponential(0.001), timer_msg);

    cout << "end client init" << endl;
}

/** handle the timeout method */
void ClientApp::handleTimer(cMessage *msg) {

    EV << "=== Peer: " << this->localAddress_
              << " received handleTimer message. " << endl;

    // cleanup the incoming message
    delete msg;

    this->connect();
}

// determines how to handle a message (note that an message is
// essentially any event)
void ClientApp::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        this->handleTimer(msg);
    } else {
        this->socket_->processMessage(msg);
    }

    return;
}

// connect to peer i
void ClientApp::connect() {
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
void ClientApp::close() {
    EV << "=== Peer: " << this->localAddress_ << " received close () message"
              << endl;
    EV << "issuing CLOSE command\n";

    setStatusString("closing");

    this->socket_->close();
}

void ClientApp::socketDataArrived(int connId, void *, cPacket *msg,
        bool urgent) {
    EV << "=== Peer: " << this->localAddress_
       << " received socketDataArrived message. ===" << endl;

    CS_Packet *packet = dynamic_cast<CS_Packet *>(msg);

    if(!packet) {
        return;
    }

    if(((CS_MSG_TYPE)packet->getType()) == CS_RESPONSE) {
        CS_Resp *resp = dynamic_cast<CS_Resp *>(msg);

        if(!resp) {
            EV << "Arriving packet is not of type P2P_Req" << endl;
        } else {
            setStatusString("Response");
            EV << "Arriving packet: Responder ID = " << resp->getId ()
               << ", size = " << resp->getSize () << endl;

        }
    }

    delete msg;
}

void ClientApp::handleResponse (CS_Resp *res, int connId) {
    if(res->getDataArraySize() > 0) {
        /*
        vector<char> curChunk;
        for(int i = 0; i < res->getDataArraySize(); ++i) {
            curChunk.push_back(res->getData(i));
        }
        file_.push_back(curChunk);

        //modify for bittorrent to just ask for new chunk
        this->sendRequest(connId);*/
        ofstream myfile;
        myfile.open("dummy-client.txt");
        for(int i = 0; i < res->getDataArraySize(); ++i) {
            myfile << res->getData(i);
        }
        myfile.close();
    }
}

void ClientApp::sendRequest (int connId, const char* id, string fname) {
    CS_Req *req = new CS_Req();
    req->setType(int(CS_REQUEST));
    req->setId(this->localAddress_.c_str());
    req->setFile(fname.c_str());

    req->setByteLength(128);

    socket_->send(req);
}


void ClientApp::socketEstablished(int connId, void *role) {
    EV << "=== Peer: " << this->localAddress_
       << " received socketEstablished message on connID " << connId << " ===" << endl;

    setStatusString("ConnectionEstablished");

    bool *passive = static_cast<bool *> (role);
    if (*passive) {
        EV << "=== We are in passive role and hence just wait for an incoming req ===" << endl;
    } else {
        EV << "=== We are in active role and hence initiate a req ===" << endl;

        this->sendRequest (connId, this->localAddress_.c_str (), "dummy.txt");
    }
}

void ClientApp::socketPeerClosed(int connId, void *yourPtr) {

}

void ClientApp::socketClosed(int connId, void *) {
    delete socket_;
}

void ClientApp::socketFailure(int connId, void *yourPtr, int code) {

}

// there was no need for us to have provided this method, however, if
// you want to gather statistics of your simulation, this is the
// method you need to add
void ClientApp::finish(void) {
    EV << "=== finish called" << endl;

    delete socket_;
    // finalize any statistics collection
}

void ClientApp::setStatusString(const char *s) {
    if (ev.isGUI()) {
        getDisplayString().setTagArg("t", 0, s);
        bubble(s);
    }
}

