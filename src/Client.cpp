// Implementation of the module.
// Adapted from the tictoc tutorial



#include "Client.h"

// the module class is now registered with omnet++ and tells it to look for
// a corresponding NED file for a simple module definition of the same name.
// ** Never put this inside a header file **
Define_Module (Client);

// ******* Peer SimpleModule *******

// constructor
Client::Client (void)
  : cSimpleModule ()
{
}

// destructor
Client::~Client (void)
{
}

// overridden methods
void Client::initialize (void)
{
    this->name_ = this->par ("name").stringValue();
    cMessage *msg = new cMessage ("Hello");
    this->scheduleAt (simTime () + exponential (5.0), msg);
}

// determines how to handle a message (note that an message is
// essentially any event)
void Client::handleMessage (cMessage *msg)
{
    this->send (msg, "toXport");
    cMessage *newMsg = new cMessage ("Hello");
     return;
}

/*void Client::handleMessage (ByteArrayMessage *msg)
{
    n
    this->send (msg, "toXport");
    cMessage *newMsg = new cMessage ("Hello");
     return;
}
*/

// there was no need for us to have provided this method, however, if
// you want to gather statistics of your simulation, this is the
// method you need to add
void Client::finish (void)
{
    EV << "=== finish called" << endl;
    // finalize any statistics collection
}

