// Implementation of the module.
// Adapted from the tictoc tutorial


#include "CSAppMsg_m.h"
#include "BitTrackerApp.h"

#include "IPvXAddressResolver.h"

// the module class is now registered with omnet++ and tells it to look for
// a corresponding NED file for a simple module definition of the same name.
// ** Never put this inside a header file **
Define_Module (BitTrackerApp);

// ******* Peer SimpleModule *******

// constructor
BitTrackerApp::BitTrackerApp (void)
  : cSimpleModule ()
{
}

// destructor
BitTrackerApp::~BitTrackerApp (void)
{
}

// overridden methods
void BitTrackerApp::initialize (void)
{

    this->localAddress_ = this->par ("localAddress").stringValue ();
    this->localPort_ = this->par ("localPort");
    this->connectPort_ = this->par ("connectPort");


  // retrieve our name parameter.
    //this->name_ = this->par ("name").stringValue();
  // if I am a client I initiate the transfer

    this->socket_ = new TCPSocket ();


    this->socket_->bind (this->localAddress_.length () ?
            IPvXAddressResolver ().resolve (this->localAddress_.c_str ()) : IPvXAddress (),
            this->localPort_);

    // register ourselves as the callback object
    bool *passive = new bool (true);
    this->socket_->setCallbackObject (this, passive);  // send the flag

    // do not forget to set the outgoing gate
    this->socket_->setOutputGate (gate ("tcpOut"));

    // now listen for incoming connections.  This version is the forking version where
    // upon every new incoming connection, a new socket is created.
    this->socket_->listen ();

    EV << "+++ Peer: " << this->localAddress_ << " created a listening socket with "
       << "connection ID = " << this->socket_->getConnectionId () << " +++" << endl;

    // now save this socket in our map
    this->socketMap_.addSocket (this->socket_);

    cerr << "end BitTracker init" << endl;
}

void BitTrackerApp::socketEstablished(int connId, void *yourPtr) {
    EV << "=== Peer: " << this->localAddress_
       << " received socketEstablished message on connID " << connId << " ===" << endl;
}

void BitTrackerApp::socketDataArrived(int connId, void *, cPacket *msg, bool urgent) {
    EV << "=== Peer: " << this->localAddress_
       << " received socketDataArrived message. ===" << endl;

    //This is going to be a request for the peers, so we will simply return the list of peers.
    cerr << "before cast" << endl;
        CS_Req *req = dynamic_cast<CS_Req *> (msg);
        if (!req) {
            EV << "Arriving packet is not of type CS_Req" << endl;
        } else {
            EV << "Arriving packet: Requestor ID = " << req->getId ()
               << ", Requested filename = " << req->getFile ()  << endl;

            streampos size;
            char * memblock;
            //TODO:  here this will send the list of peers, so that the client can ask for the pieces
            memblock = peers_.getBytes();
            // now send a response
            this->sendResponse (connId, this->localAddress_.c_str (), memblock, size);
            delete[] memblock;
        }
    //}

    delete msg;
}

void BitTrackerApp::sendResponse (int connId, const char *id, char* data, unsigned long size) {
    EV << "=== Peer: " << this->localAddress_ << " sendResponse. "
       << "Sending ID: " << id << ", size: " << size << " ===" << endl;

    cMessage *temp_msg = new cMessage ("temp");
    TCPCommand *temp_cmd = new TCPCommand ();
    temp_cmd->setConnId (connId);
    temp_msg->setControlInfo (temp_cmd);

    TCPSocket *socket = this->socketMap_.findSocketFor (temp_msg);

    if (!socket) {
        EV << ">>> Cannot find socket to send request <<< " << endl;
    } else {
        CS_Resp *resp = new CS_Resp ();
        resp->setType ((int)CS_RESPONSE);
        resp->setId (id);
        resp->setSize (size);
        // need to set the byte length else nothing gets sent as I found the hard way
        resp->setByteLength (128);  // I think we can set any length we want :-)
        resp->setDataArraySize(size);
        for(int i = 0; i < size; ++i)
            resp->setData(i, data[i]);
        socket->send (resp);
    }

    // cleanup
    delete temp_msg;
}

void BitTrackerApp::handleMessage(cMessage *msg) {
    TCPSocket *socket = this->socketMap_.findSocketFor(msg);

    if(!socket) {
        EV << "=== Peer: " << this->localAddress_ << " **No socket yet ** ===" << endl;

        //int connId = cmd->getConnId();
        // debugging
        EV << "+++ Peer: " << this->localAddress_ << " creating a new socket with "
           << "connection ID = " << " ===" << endl;

        // notice that we must use the other constructor of TCPSocket so that it
        // will use the underlying connID that was created after an incoming
        // connection establishment message
        TCPSocket *new_socket = new TCPSocket (msg);

        // register ourselves as the callback object
        bool *passive = new bool (true);
        new_socket->setCallbackObject (this, passive);

        // do not forget to set the outgoing gate
        new_socket->setOutputGate (gate ("tcpOut"));

        // another thing I learned the hard way is that we must set up the data trasnfer
        // mode for this new socket
        new_socket->setDataTransferMode (this->socket_->getDataTransferMode ());

        // now save this socket in our map
        this->socketMap_.addSocket (new_socket);

        cerr << "handlemessage end" << endl;
        // process the message
        new_socket->processMessage (msg);

    }
}

void BitTrackerApp::socketPeerClosed(int connId, void *) {
    cMessage *temp_msg = new cMessage ("temp");
    TCPCommand *temp_cmd = new TCPCommand ();
    temp_cmd->setConnId (connId);
    temp_msg->setControlInfo (temp_cmd);

    TCPSocket *socket = this->socketMap_.findSocketFor (temp_msg);
    this->socketMap_.removeSocket(socket);
}

// there was no need for us to have provided this method, however, if
// you want to gather statistics of your simulation, this is the
// method you need to add
void BitTrackerApp::finish (void)
{
    EV << "=== finish called" << endl;
    // finalize any statistics collection
}

// ******* RDT_1_0 SimpleModule *******
