/*
 * RDT_1_0.h
 *
 *  Created on: Jan 13, 2015
 *      Author: gokhale
 */

#ifndef ClientApp_H
#define ClientApp_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "INETDefs.h"       // this contains imp definitions from the INET
#include "TCPSocket.h"      // this is needed for sockets
#include "TCPSocketMap.h"

#include <omnetpp.h>

#define MSG_LEN 1024

// any simple module must provide an implementation.  Typically this involves
// deriving from the cSimpleModule class.
class ClientApp : public cSimpleModule, public TCPSocket::CallbackInterface
{
public:
    ClientApp (void);

  virtual ~ClientApp ();

  // need to override these virtual functions
  virtual void initialize (void);

  virtual void handleMessage (cMessage *msg);

  virtual void handleTimer (cMessage *msg);

  virtual void handleResponse (CS_Resp *res, int connId);

  virtual void connect(void);

  virtual void close(void);

  virtual void setStatusString(const char *s);

  virtual void sendRequest (int connId, const char* id, string fname);

  virtual void finish (void);

protected:

  virtual void    socketDataArrived (int connId, void *yourPtr, cPacket *msg, bool urgent);

  virtual void    socketEstablished (int connId, void *yourPtr);

  virtual void    socketPeerClosed (int connId, void *yourPtr);

  virtual void    socketClosed (int connId, void *yourPtr);

  virtual void    socketFailure (int connId, void *yourPtr, int code);

  /** Redefine to handle incoming TCPStatusInfo. */
  virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {delete status;}

private:
  string name_; // some name assigned to us

  TCPSocket    *socket_;   // our main listening socket

  string localAddress_;    // our local address
  int localPort_;          // our local port we will listen on

  string connectAddress_;  // address of our peers
  int connectPort_;        // ports of the peer we connect to
};




#endif /* Client_H */
