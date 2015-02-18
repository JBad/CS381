//
// Generated file, do not edit! Created by nedtool 4.6 from CSAppMsg.msg.
//

#ifndef _CSAPPMSG_M_H_
#define _CSAPPMSG_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>CSAppMsg.msg:16</tt> by nedtool.
 * <pre>
 * enum CS_MSG_TYPE
 * {
 * 
 *     CS_REQUEST = 0;
 *     CS_RESPONSE = 1;
 * }
 * </pre>
 */
enum CS_MSG_TYPE {
    CS_REQUEST = 0,
    CS_RESPONSE = 1
};

/**
 * Class generated from <tt>CSAppMsg.msg:22</tt> by nedtool.
 * <pre>
 * packet CS_Packet
 * {
 *     int type @enum(CS_MSG_TYPE);  // our message type
 * }
 * </pre>
 */
class CS_Packet : public ::cPacket
{
  protected:
    int type_var;

  private:
    void copy(const CS_Packet& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CS_Packet&);

  public:
    CS_Packet(const char *name=NULL, int kind=0);
    CS_Packet(const CS_Packet& other);
    virtual ~CS_Packet();
    CS_Packet& operator=(const CS_Packet& other);
    virtual CS_Packet *dup() const {return new CS_Packet(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type);
};

inline void doPacking(cCommBuffer *b, CS_Packet& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, CS_Packet& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>CSAppMsg.msg:27</tt> by nedtool.
 * <pre>
 * packet CS_Req extends CS_Packet
 * {
 *     string id;		        // announce the requestor's ID
 *     string file;        // request for a file
 * }
 * </pre>
 */
class CS_Req : public ::CS_Packet
{
  protected:
    opp_string id_var;
    opp_string file_var;

  private:
    void copy(const CS_Req& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CS_Req&);

  public:
    CS_Req(const char *name=NULL, int kind=0);
    CS_Req(const CS_Req& other);
    virtual ~CS_Req();
    CS_Req& operator=(const CS_Req& other);
    virtual CS_Req *dup() const {return new CS_Req(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * getId() const;
    virtual void setId(const char * id);
    virtual const char * getFile() const;
    virtual void setFile(const char * file);
};

inline void doPacking(cCommBuffer *b, CS_Req& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, CS_Req& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>CSAppMsg.msg:33</tt> by nedtool.
 * <pre>
 * packet CS_Resp extends CS_Packet
 * {
 *     string id;			// ID of the responder
 *     unsigned long size;	// size of the data	
 *     char data[];    // contents of the file
 * }
 * </pre>
 */
class CS_Resp : public ::CS_Packet
{
  protected:
    opp_string id_var;
    unsigned long size_var;
    char *data_var; // array ptr
    unsigned int data_arraysize;

  private:
    void copy(const CS_Resp& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CS_Resp&);

  public:
    CS_Resp(const char *name=NULL, int kind=0);
    CS_Resp(const CS_Resp& other);
    virtual ~CS_Resp();
    CS_Resp& operator=(const CS_Resp& other);
    virtual CS_Resp *dup() const {return new CS_Resp(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * getId() const;
    virtual void setId(const char * id);
    virtual unsigned long getSize() const;
    virtual void setSize(unsigned long size);
    virtual void setDataArraySize(unsigned int size);
    virtual unsigned int getDataArraySize() const;
    virtual char getData(unsigned int k) const;
    virtual void setData(unsigned int k, char data);
};

inline void doPacking(cCommBuffer *b, CS_Resp& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, CS_Resp& obj) {obj.parsimUnpack(b);}


#endif // ifndef _CSAPPMSG_M_H_

