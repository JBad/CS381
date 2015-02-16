// Implementation of the module.
// Adapted from the tictoc tutorial



#include "Server.h"
#include <ByteArrayMessage.h>

// the module class is now registered with omnet++ and tells it to look for
// a corresponding NED file for a simple module definition of the same name.
// ** Never put this inside a header file **
Define_Module (Server);

Define_Module (RDT_1_0);

// ******* Peer SimpleModule *******

// constructor
Server::Server (void)
  : cSimpleModule ()
{
}

// destructor
Server::~Server (void)
{
}

// overridden methods
void Server::initialize (void)
{
  // this method is called by the simulation engine to initialize the simulation
  //

  // retrieve our name parameter.
    this->name_ = this->par ("name").stringValue();
  // if I am a client I initiate the transfer

}

// determines how to handle a message (note that an message is
// essentially any event)
void Server::handleMessage (cMessage *msg)
{
   if(opp_strcmp(msg->getName(), "Hello")==0){
          this->send (msg, "toXport");
      //    char[][] fileBytes = getBytes("file.txt");
          for(int i = 0; i < 10; ++i) {
              ByteArrayMessage msg();
              //msg.setData(fileBytes[i]);
              //this->send(msg, "toXport");
          }

          cMessage *newMsg = new cMessage ("File");

   }


  EV << this->name_.c_str () << ": Message received of size = "
                << msg->info () << endl;
    return;
}

// there was no need for us to have provided this method, however, if
// you want to gather statistics of your simulation, this is the
// method you need to add
void Server::finish (void)
{
    EV << "=== finish called" << endl;
    // finalize any statistics collection
}

// ******* RDT_1_0 SimpleModule *******

// constructor
RDT_1_0::RDT_1_0 (void)
  : cSimpleModule ()
{
}

// destructor
RDT_1_0::~RDT_1_0 (void)
{
}

// overridden methods
void RDT_1_0::initialize (void)
{
  // retrieve our name parameter.
  this->name_ = this->par ("name").stringValue();

  // nothing else to do since we get messages from the client (if I am sender)
  // else from a sender (if I am a receiver).

}

// determines how to handle a message
void RDT_1_0::handleMessage (cMessage *msg)
{
  // if I am sender I send it to the receiver. If I am a receiver,
  // I send it to the server
    string gate(msg->getSenderGate()->getFullName());
    EV << gate << endl;
    if(opp_strcmp(msg->getSenderGate()->getFullName(), "toXport")==0){
        this->send (msg, "toNet");
    }
    else if(opp_strcmp(msg->getSenderGate()->getFullName(), "toNet")==0){
        this->send(msg, "toAppln");
    }
  return;
}

void RDT_1_0::finish (void)
{
    EV << "=== finish called" << endl;
    // finalize any statistics collection
}
