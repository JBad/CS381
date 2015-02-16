/*
 * RDT_1_0.h
 *
 *  Created on: Jan 13, 2015
 *      Author: gokhale
 */

#ifndef Server_H
#define Server_H

#include <string>
using namespace std;

#include <omnetpp.h>

#define MSG_LEN 1024

// any simple module must provide an implementation.  Typically this involves
// deriving from the cSimpleModule class.
class Server : public cSimpleModule
{
public:
  Server (void);

  ~Server ();

  // need to override these virtual functions
  virtual void initialize (void);

  virtual void handleMessage (cMessage *msg);

  virtual void finish (void);

private:
  string name_; // some name assigned to us
};

// any simple module must provide an implementation.  Typically this involves
// deriving from the cSimpleModule class.
class RDT_1_0 : public cSimpleModule
{
public:
  RDT_1_0 (void);

  ~RDT_1_0 ();

  // alternately the signature should look like this
  // Peer (const char *name, cModule *parentModule, unsigned stacksize)
  // passing these to the base class


  // need to override these virtual functions
  virtual void initialize (void);

  virtual void handleMessage (cMessage *msg);

  virtual void finish (void);

private:
  string name_; // some name assigned to us
};


#endif /* Server_H */
