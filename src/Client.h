/*
 * RDT_1_0.h
 *
 *  Created on: Jan 13, 2015
 *      Author: gokhale
 */

#ifndef Client_H
#define Client_H

#include <string>
using namespace std;

#include <omnetpp.h>

#define MSG_LEN 1024

// any simple module must provide an implementation.  Typically this involves
// deriving from the cSimpleModule class.
class Client : public cSimpleModule
{
public:
    Client (void);

  ~Client ();

  // need to override these virtual functions
  virtual void initialize (void);

  virtual void handleMessage (cMessage *msg);

  virtual void finish (void);

private:
  string name_; // some name assigned to us
};




#endif /* Client_H */
