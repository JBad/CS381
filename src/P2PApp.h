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
#include <set>
#include <algorithm>

using namespace std;

#include "INETDefs.h"       // this contains imp definitions from the INET
#include "TCPSocket.h"      // this is needed for sockets
#include "TCPSocketMap.h"
#include "CSAppMsg_m.h"

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

  //virtual void handleResponse (Tracker_Resp *res, int connId);

  virtual void connect(void);

  virtual void close(void);

  virtual void setStatusString(const char *s);

  virtual void sendRequest (int connId, const char* id, string fname);

  virtual void finish (void);

  static char* ss_to_charp(std::stringstream& accum);

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
  virtual Peer_InfoResp* makePeerListResponse(void);

  virtual Peer_ChunkResp* makePeerChunkResponse(Peer_ChunkReq* req);

  virtual Peer_InfoReq* makePeerListRequest(string peer);

  virtual Peer_ChunkReq* makePeerChunkRequest(string peer, int chunk);

  /**
   * File Complete? returns if we have all of the chunks;
   */
  virtual bool fileComplete();

  /**
   * handleResponseFromTracker, this is just placing the new peers into the set of current peers
   */
  virtual void handleResponseFromTracker(Tracker_Resp* resp);

  /**
   * Given the peer and a list of the chunks that that peer has, we store it, so now we know who
   * to ask for what piece
   */
  virtual void handleResponsefromPeerChunkList(Peer_InfoResp* resp);

  /**
   * Looks for peer in the list of peer and see what chunk this peer has, that we do not have
   * and sends a request for that chunk, if there is nothing new it returns null, CHECK this!
   */
  virtual cMessage * makeRequestFor(string peer);


  virtual void handleResponsefromPeerSingleChunk(Peer_ChunkResp* resp);

  virtual void sendThisPacket(cMessage *incoming, cMessage *outgoing);

private:
  string name_; // some name assigned to us

  TCPSocket    *socket_;   // our main listening socket

  string localAddress_;    // our local address
  int localPort_;          // our local port we will listen on

  string connectAddress_;  // address of our peers
  int connectPort_;        // ports of the peer we connect to

  set<string> peers_;
  map<string, set<int>> peerChunks_;
  map<string, int> pendingRequests_;
  vector<bool> chunks_;
  vector<bool> activeChunks_;
  vector<char*> data_;
  vector<int> dataSize_;
  TCPSocketMap socketMap_; // maps of sockets we maintain
};

struct msg{
    char* peer;
    char* bytes;
};

#endif /* P2P_H */
