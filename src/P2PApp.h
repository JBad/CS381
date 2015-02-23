/*
 * RDT_1_0.h
 *
 *  Created on: Jan 13, 2015
 *      Author: gokhale
 */

#ifndef P2PApp_H
#define P2PApp_H

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#include "INETDefs.h"       // this contains imp definitions from the INET
#include "TCPSocket.h"      // this is needed for sockets
#include "TCPSocketMap.h"

#include <omnetpp.h>

#define MSG_LEN 1024

// any simple module must provide an implementation.  Typically this involves
// deriving from the cSimpleModule class.
class P2PApp : public cSimpleModule, public TCPSocket::CallbackInterface
{
public:
    P2PApp (void);

  virtual ~P2PApp ();

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

  static char* ss_to_charp(std::stringstream& accum);

  static std::vector<std::string> split(const std::string &s, char delim);

  std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);

protected:

  virtual void    socketDataArrived (int connId, void *yourPtr, cPacket *msg, bool urgent);

  virtual void    socketEstablished (int connId, void *yourPtr);

  virtual void    socketPeerClosed (int connId, void *yourPtr);

  virtual void    socketClosed (int connId, void *yourPtr);

  virtual void    socketFailure (int connId, void *yourPtr, int code);

  /** Redefine to handle incoming TCPStatusInfo. */
  virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {delete status;}

  /**
   * internal methods for BitTorrent
   */

  /**
   * two messages could come in here, either a request for a list of all the chunks we have,
   * or a request for a specific chunk, will handle which case and provide the char * to send back
   * for -1 -> list of the chunks it currently has in this case return_value[0] = 'i'
   * for not -1 it returns that chunk in this case
   */
  virtual char * makePeerResponse(char * bytes);

  /**
   * just returns a char * with -1 in it.
   */
  virtual char * makeRequestForPeerAllChunks();

  /**
   * File Complete? returns if we have all of the chunks;
   */
  virtual bool fileComplete();

  /**
   * handleResponseFromTracker, this is just placing the new peers into the set of current peers
   */
  virtual void handleResponseFromTracker(char * list);

  /**
   * Given the peer and a list of the chunks that that peer has, we store it, so now we know who
   * to ask for what piece
   */
  virtual void handleResponsefromPeerChunkList(char * list, char * peer);

  /**
   * Looks for peer in the list of peer and see what chunk this peer has, that we do not have
   * and sends a request for that chunk, if there is nothing new it returns null, CHECK this!
   */
  virtual char * makeRequestFor(char * peer);


private:
  string name_; // some name assigned to us

  TCPSocket    *socket_;   // our main listening socket

  string localAddress_;    // our local address
  int localPort_;          // our local port we will listen on

  string connectAddress_;  // address of our peers
  int connectPort_;        // ports of the peer we connect to

  set<string>peers_;
  map<string, set<int>>peerChunks_;
  map<string, int> pendingRequest_;
  vector<bool>chunks_;
  vector<char*> data;
};

struct msg{
    char* peer;
    char* bytes;
};

#endif /* P2P_H */
