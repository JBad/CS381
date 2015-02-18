/*
 * RDT_1_0.h
 *
 *  Created on: Jan 13, 2015
 *      Author: gokhale
 */

#ifndef ServerApp_H
#define ServerApp_H

#include <string>
#include <vector>

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
class ServerApp : public cSimpleModule, public TCPSocket::CallbackInterface
{
public:
  ServerApp (void);

  ~ServerApp ();

  // need to override these virtual functions
  virtual void initialize (void);

  virtual void finish (void);

  //@{
  /** Does nothing but update statistics/status. Redefine to perform or schedule first sending. */
  virtual void socketEstablished(int connId, void *yourPtr);

  virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);

  /** Since remote TCP closed, invokes close(). Redefine if you want to do something else. */
  virtual void socketPeerClosed(int connId, void *yourPtr);

  virtual void sendResponse (int connId, const char *id, char* data, unsigned long size);

  virtual void handleMessage(cMessage *msg);

private:
  string name_; // some name assigned to us

  TCPSocket    *socket_;   // our main listening socket
  TCPSocketMap socketMap_; // maps of sockets we maintain

  string localAddress_;    // our local address
  int localPort_;          // our local port we will listen on

  string connectAddress_;  // address of our peers
  int connectPort_;        // ports of the peer we connect to
};


#endif /* ServerApp_H */
