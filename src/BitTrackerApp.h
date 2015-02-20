/*
 * RDT_1_0.h
 *
 *  Created on: Jan 13, 2015
 *      Author: gokhale
 */

#ifndef BitTrackerApp_H
#define BitTrackerApp_H

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
class BitTrackerApp : public cSimpleModule, public TCPSocket::CallbackInterface
{
public:
  BitTrackerApp (void);

  ~BitTrackerApp ();

  // need to override these virtual functions
  virtual void initialize (void);

  virtual void handleMessage(cMessage *msg);

  virtual void socketEstablished(int connId, void *yourPtr);

  virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);

  virtual void socketPeerClosed(int connId, void *yourPtr);

  virtual void socketFailure();

  virtual void sendResponse (int connId, const char *id, char* data, unsigned long size);

  virtual void finish (void);



private:
  string name_; // some name assigned to us

  TCPSocket    *socket_;   // our main listening socket
  TCPSocketMap socketMap_; // maps of sockets we maintain

  string localAddress_;    // our local address
  int localPort_;          // our local port we will listen on

  string connectAddress_;  // address of our peers
  int connectPort_;        // ports of the peer we connect to


  map<string, vector<int> > PeerChunkDB;
  set<string> peers_; // set of all peers
};


#endif /* BitTrackerApp_H */
