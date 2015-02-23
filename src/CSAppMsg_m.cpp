//
// Generated file, do not edit! Created by nedtool 4.6 from CSAppMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CSAppMsg_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("BT_MSG_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("BT_MSG_TYPE"));
    e->insert(Tracker_REQUEST, "Tracker_REQUEST");
    e->insert(Tracker_RESPONSE, "Tracker_RESPONSE");
    e->insert(Peer_INFO_REQUEST, "Peer_INFO_REQUEST");
    e->insert(Peer_INFO_RESPONSE, "Peer_INFO_RESPONSE");
    e->insert(Peer_CHUNK_REQUEST, "Peer_CHUNK_REQUEST");
    e->insert(Peer_CHUNK_RESPONSE, "Peer_CHUNK_RESPONSE");
);

Register_Class(BT_Packet);

BT_Packet::BT_Packet(const char *name, int kind) : ::cPacket(name,kind)
{
    this->type_var = 0;
}

BT_Packet::BT_Packet(const BT_Packet& other) : ::cPacket(other)
{
    copy(other);
}

BT_Packet::~BT_Packet()
{
}

BT_Packet& BT_Packet::operator=(const BT_Packet& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void BT_Packet::copy(const BT_Packet& other)
{
    this->type_var = other.type_var;
}

void BT_Packet::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->type_var);
}

void BT_Packet::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
}

int BT_Packet::getType() const
{
    return type_var;
}

void BT_Packet::setType(int type)
{
    this->type_var = type;
}

class BT_PacketDescriptor : public cClassDescriptor
{
  public:
    BT_PacketDescriptor();
    virtual ~BT_PacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(BT_PacketDescriptor);

BT_PacketDescriptor::BT_PacketDescriptor() : cClassDescriptor("BT_Packet", "cPacket")
{
}

BT_PacketDescriptor::~BT_PacketDescriptor()
{
}

bool BT_PacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BT_Packet *>(obj)!=NULL;
}

const char *BT_PacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BT_PacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int BT_PacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BT_PacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int BT_PacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BT_PacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *BT_PacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "BT_MSG_TYPE";
            return NULL;
        default: return NULL;
    }
}

int BT_PacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BT_Packet *pp = (BT_Packet *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BT_PacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BT_Packet *pp = (BT_Packet *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        default: return "";
    }
}

bool BT_PacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BT_Packet *pp = (BT_Packet *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *BT_PacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *BT_PacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BT_Packet *pp = (BT_Packet *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Tracker_Req);

Tracker_Req::Tracker_Req(const char *name, int kind) : ::BT_Packet(name,kind)
{
    this->id_var = 0;
}

Tracker_Req::Tracker_Req(const Tracker_Req& other) : ::BT_Packet(other)
{
    copy(other);
}

Tracker_Req::~Tracker_Req()
{
}

Tracker_Req& Tracker_Req::operator=(const Tracker_Req& other)
{
    if (this==&other) return *this;
    ::BT_Packet::operator=(other);
    copy(other);
    return *this;
}

void Tracker_Req::copy(const Tracker_Req& other)
{
    this->id_var = other.id_var;
}

void Tracker_Req::parsimPack(cCommBuffer *b)
{
    ::BT_Packet::parsimPack(b);
    doPacking(b,this->id_var);
}

void Tracker_Req::parsimUnpack(cCommBuffer *b)
{
    ::BT_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
}

const char * Tracker_Req::getId() const
{
    return id_var.c_str();
}

void Tracker_Req::setId(const char * id)
{
    this->id_var = id;
}

class Tracker_ReqDescriptor : public cClassDescriptor
{
  public:
    Tracker_ReqDescriptor();
    virtual ~Tracker_ReqDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Tracker_ReqDescriptor);

Tracker_ReqDescriptor::Tracker_ReqDescriptor() : cClassDescriptor("Tracker_Req", "BT_Packet")
{
}

Tracker_ReqDescriptor::~Tracker_ReqDescriptor()
{
}

bool Tracker_ReqDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Tracker_Req *>(obj)!=NULL;
}

const char *Tracker_ReqDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Tracker_ReqDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int Tracker_ReqDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *Tracker_ReqDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int Tracker_ReqDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Tracker_ReqDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *Tracker_ReqDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Tracker_ReqDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Tracker_Req *pp = (Tracker_Req *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Tracker_ReqDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Tracker_Req *pp = (Tracker_Req *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        default: return "";
    }
}

bool Tracker_ReqDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Tracker_Req *pp = (Tracker_Req *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        default: return false;
    }
}

const char *Tracker_ReqDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *Tracker_ReqDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Tracker_Req *pp = (Tracker_Req *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Tracker_Resp);

Tracker_Resp::Tracker_Resp(const char *name, int kind) : ::BT_Packet(name,kind)
{
    this->id_var = 0;
    peers_arraysize = 0;
    this->peers_var = 0;
    this->numPeers_var = 0;
}

Tracker_Resp::Tracker_Resp(const Tracker_Resp& other) : ::BT_Packet(other)
{
    peers_arraysize = 0;
    this->peers_var = 0;
    copy(other);
}

Tracker_Resp::~Tracker_Resp()
{
    delete [] peers_var;
}

Tracker_Resp& Tracker_Resp::operator=(const Tracker_Resp& other)
{
    if (this==&other) return *this;
    ::BT_Packet::operator=(other);
    copy(other);
    return *this;
}

void Tracker_Resp::copy(const Tracker_Resp& other)
{
    this->id_var = other.id_var;
    delete [] this->peers_var;
    this->peers_var = (other.peers_arraysize==0) ? NULL : new opp_string[other.peers_arraysize];
    peers_arraysize = other.peers_arraysize;
    for (unsigned int i=0; i<peers_arraysize; i++)
        this->peers_var[i] = other.peers_var[i];
    this->numPeers_var = other.numPeers_var;
}

void Tracker_Resp::parsimPack(cCommBuffer *b)
{
    ::BT_Packet::parsimPack(b);
    doPacking(b,this->id_var);
    b->pack(peers_arraysize);
    doPacking(b,this->peers_var,peers_arraysize);
    doPacking(b,this->numPeers_var);
}

void Tracker_Resp::parsimUnpack(cCommBuffer *b)
{
    ::BT_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
    delete [] this->peers_var;
    b->unpack(peers_arraysize);
    if (peers_arraysize==0) {
        this->peers_var = 0;
    } else {
        this->peers_var = new opp_string[peers_arraysize];
        doUnpacking(b,this->peers_var,peers_arraysize);
    }
    doUnpacking(b,this->numPeers_var);
}

const char * Tracker_Resp::getId() const
{
    return id_var.c_str();
}

void Tracker_Resp::setId(const char * id)
{
    this->id_var = id;
}

void Tracker_Resp::setPeersArraySize(unsigned int size)
{
    opp_string *peers_var2 = (size==0) ? NULL : new opp_string[size];
    unsigned int sz = peers_arraysize < size ? peers_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        peers_var2[i] = this->peers_var[i];
    for (unsigned int i=sz; i<size; i++)
        peers_var2[i] = 0;
    peers_arraysize = size;
    delete [] this->peers_var;
    this->peers_var = peers_var2;
}

unsigned int Tracker_Resp::getPeersArraySize() const
{
    return peers_arraysize;
}

const char * Tracker_Resp::getPeers(unsigned int k) const
{
    if (k>=peers_arraysize) throw cRuntimeError("Array of size %d indexed by %d", peers_arraysize, k);
    return peers_var[k].c_str();
}

void Tracker_Resp::setPeers(unsigned int k, const char * peers)
{
    if (k>=peers_arraysize) throw cRuntimeError("Array of size %d indexed by %d", peers_arraysize, k);
    this->peers_var[k] = peers;
}

int Tracker_Resp::getNumPeers() const
{
    return numPeers_var;
}

void Tracker_Resp::setNumPeers(int numPeers)
{
    this->numPeers_var = numPeers;
}

class Tracker_RespDescriptor : public cClassDescriptor
{
  public:
    Tracker_RespDescriptor();
    virtual ~Tracker_RespDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Tracker_RespDescriptor);

Tracker_RespDescriptor::Tracker_RespDescriptor() : cClassDescriptor("Tracker_Resp", "BT_Packet")
{
}

Tracker_RespDescriptor::~Tracker_RespDescriptor()
{
}

bool Tracker_RespDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Tracker_Resp *>(obj)!=NULL;
}

const char *Tracker_RespDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Tracker_RespDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int Tracker_RespDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *Tracker_RespDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
        "peers",
        "numPeers",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int Tracker_RespDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "peers")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "numPeers")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Tracker_RespDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *Tracker_RespDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Tracker_RespDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Tracker_Resp *pp = (Tracker_Resp *)object; (void)pp;
    switch (field) {
        case 1: return pp->getPeersArraySize();
        default: return 0;
    }
}

std::string Tracker_RespDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Tracker_Resp *pp = (Tracker_Resp *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        case 1: return oppstring2string(pp->getPeers(i));
        case 2: return long2string(pp->getNumPeers());
        default: return "";
    }
}

bool Tracker_RespDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Tracker_Resp *pp = (Tracker_Resp *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        case 1: pp->setPeers(i,(value)); return true;
        case 2: pp->setNumPeers(string2long(value)); return true;
        default: return false;
    }
}

const char *Tracker_RespDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *Tracker_RespDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Tracker_Resp *pp = (Tracker_Resp *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Peer_Packet);

Peer_Packet::Peer_Packet(const char *name, int kind) : ::cPacket(name,kind)
{
    this->type_var = 0;
}

Peer_Packet::Peer_Packet(const Peer_Packet& other) : ::cPacket(other)
{
    copy(other);
}

Peer_Packet::~Peer_Packet()
{
}

Peer_Packet& Peer_Packet::operator=(const Peer_Packet& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Peer_Packet::copy(const Peer_Packet& other)
{
    this->type_var = other.type_var;
}

void Peer_Packet::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->type_var);
}

void Peer_Packet::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
}

int Peer_Packet::getType() const
{
    return type_var;
}

void Peer_Packet::setType(int type)
{
    this->type_var = type;
}

class Peer_PacketDescriptor : public cClassDescriptor
{
  public:
    Peer_PacketDescriptor();
    virtual ~Peer_PacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Peer_PacketDescriptor);

Peer_PacketDescriptor::Peer_PacketDescriptor() : cClassDescriptor("Peer_Packet", "cPacket")
{
}

Peer_PacketDescriptor::~Peer_PacketDescriptor()
{
}

bool Peer_PacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Peer_Packet *>(obj)!=NULL;
}

const char *Peer_PacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Peer_PacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int Peer_PacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *Peer_PacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int Peer_PacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Peer_PacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *Peer_PacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "BT_MSG_TYPE";
            return NULL;
        default: return NULL;
    }
}

int Peer_PacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Peer_Packet *pp = (Peer_Packet *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Peer_PacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_Packet *pp = (Peer_Packet *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        default: return "";
    }
}

bool Peer_PacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Peer_Packet *pp = (Peer_Packet *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *Peer_PacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *Peer_PacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_Packet *pp = (Peer_Packet *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Peer_InfoReq);

Peer_InfoReq::Peer_InfoReq(const char *name, int kind) : ::BT_Packet(name,kind)
{
}

Peer_InfoReq::Peer_InfoReq(const Peer_InfoReq& other) : ::BT_Packet(other)
{
    copy(other);
}

Peer_InfoReq::~Peer_InfoReq()
{
}

Peer_InfoReq& Peer_InfoReq::operator=(const Peer_InfoReq& other)
{
    if (this==&other) return *this;
    ::BT_Packet::operator=(other);
    copy(other);
    return *this;
}

void Peer_InfoReq::copy(const Peer_InfoReq& other)
{
}

void Peer_InfoReq::parsimPack(cCommBuffer *b)
{
    ::BT_Packet::parsimPack(b);
}

void Peer_InfoReq::parsimUnpack(cCommBuffer *b)
{
    ::BT_Packet::parsimUnpack(b);
}

class Peer_InfoReqDescriptor : public cClassDescriptor
{
  public:
    Peer_InfoReqDescriptor();
    virtual ~Peer_InfoReqDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Peer_InfoReqDescriptor);

Peer_InfoReqDescriptor::Peer_InfoReqDescriptor() : cClassDescriptor("Peer_InfoReq", "BT_Packet")
{
}

Peer_InfoReqDescriptor::~Peer_InfoReqDescriptor()
{
}

bool Peer_InfoReqDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Peer_InfoReq *>(obj)!=NULL;
}

const char *Peer_InfoReqDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Peer_InfoReqDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int Peer_InfoReqDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *Peer_InfoReqDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int Peer_InfoReqDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Peer_InfoReqDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *Peer_InfoReqDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Peer_InfoReqDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Peer_InfoReq *pp = (Peer_InfoReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Peer_InfoReqDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_InfoReq *pp = (Peer_InfoReq *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool Peer_InfoReqDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Peer_InfoReq *pp = (Peer_InfoReq *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *Peer_InfoReqDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *Peer_InfoReqDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_InfoReq *pp = (Peer_InfoReq *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Peer_InfoResp);

Peer_InfoResp::Peer_InfoResp(const char *name, int kind) : ::BT_Packet(name,kind)
{
    chunks_arraysize = 0;
    this->chunks_var = 0;
    this->size_var = 0;
}

Peer_InfoResp::Peer_InfoResp(const Peer_InfoResp& other) : ::BT_Packet(other)
{
    chunks_arraysize = 0;
    this->chunks_var = 0;
    copy(other);
}

Peer_InfoResp::~Peer_InfoResp()
{
    delete [] chunks_var;
}

Peer_InfoResp& Peer_InfoResp::operator=(const Peer_InfoResp& other)
{
    if (this==&other) return *this;
    ::BT_Packet::operator=(other);
    copy(other);
    return *this;
}

void Peer_InfoResp::copy(const Peer_InfoResp& other)
{
    delete [] this->chunks_var;
    this->chunks_var = (other.chunks_arraysize==0) ? NULL : new int[other.chunks_arraysize];
    chunks_arraysize = other.chunks_arraysize;
    for (unsigned int i=0; i<chunks_arraysize; i++)
        this->chunks_var[i] = other.chunks_var[i];
    this->size_var = other.size_var;
}

void Peer_InfoResp::parsimPack(cCommBuffer *b)
{
    ::BT_Packet::parsimPack(b);
    b->pack(chunks_arraysize);
    doPacking(b,this->chunks_var,chunks_arraysize);
    doPacking(b,this->size_var);
}

void Peer_InfoResp::parsimUnpack(cCommBuffer *b)
{
    ::BT_Packet::parsimUnpack(b);
    delete [] this->chunks_var;
    b->unpack(chunks_arraysize);
    if (chunks_arraysize==0) {
        this->chunks_var = 0;
    } else {
        this->chunks_var = new int[chunks_arraysize];
        doUnpacking(b,this->chunks_var,chunks_arraysize);
    }
    doUnpacking(b,this->size_var);
}

void Peer_InfoResp::setChunksArraySize(unsigned int size)
{
    int *chunks_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = chunks_arraysize < size ? chunks_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        chunks_var2[i] = this->chunks_var[i];
    for (unsigned int i=sz; i<size; i++)
        chunks_var2[i] = 0;
    chunks_arraysize = size;
    delete [] this->chunks_var;
    this->chunks_var = chunks_var2;
}

unsigned int Peer_InfoResp::getChunksArraySize() const
{
    return chunks_arraysize;
}

int Peer_InfoResp::getChunks(unsigned int k) const
{
    if (k>=chunks_arraysize) throw cRuntimeError("Array of size %d indexed by %d", chunks_arraysize, k);
    return chunks_var[k];
}

void Peer_InfoResp::setChunks(unsigned int k, int chunks)
{
    if (k>=chunks_arraysize) throw cRuntimeError("Array of size %d indexed by %d", chunks_arraysize, k);
    this->chunks_var[k] = chunks;
}

int Peer_InfoResp::getSize() const
{
    return size_var;
}

void Peer_InfoResp::setSize(int size)
{
    this->size_var = size;
}

class Peer_InfoRespDescriptor : public cClassDescriptor
{
  public:
    Peer_InfoRespDescriptor();
    virtual ~Peer_InfoRespDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Peer_InfoRespDescriptor);

Peer_InfoRespDescriptor::Peer_InfoRespDescriptor() : cClassDescriptor("Peer_InfoResp", "BT_Packet")
{
}

Peer_InfoRespDescriptor::~Peer_InfoRespDescriptor()
{
}

bool Peer_InfoRespDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Peer_InfoResp *>(obj)!=NULL;
}

const char *Peer_InfoRespDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Peer_InfoRespDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int Peer_InfoRespDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *Peer_InfoRespDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "chunks",
        "size",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int Peer_InfoRespDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "chunks")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Peer_InfoRespDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *Peer_InfoRespDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Peer_InfoRespDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Peer_InfoResp *pp = (Peer_InfoResp *)object; (void)pp;
    switch (field) {
        case 0: return pp->getChunksArraySize();
        default: return 0;
    }
}

std::string Peer_InfoRespDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_InfoResp *pp = (Peer_InfoResp *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getChunks(i));
        case 1: return long2string(pp->getSize());
        default: return "";
    }
}

bool Peer_InfoRespDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Peer_InfoResp *pp = (Peer_InfoResp *)object; (void)pp;
    switch (field) {
        case 0: pp->setChunks(i,string2long(value)); return true;
        case 1: pp->setSize(string2long(value)); return true;
        default: return false;
    }
}

const char *Peer_InfoRespDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *Peer_InfoRespDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_InfoResp *pp = (Peer_InfoResp *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Peer_ChunkReq);

Peer_ChunkReq::Peer_ChunkReq(const char *name, int kind) : ::BT_Packet(name,kind)
{
    this->chunk_var = 0;
}

Peer_ChunkReq::Peer_ChunkReq(const Peer_ChunkReq& other) : ::BT_Packet(other)
{
    copy(other);
}

Peer_ChunkReq::~Peer_ChunkReq()
{
}

Peer_ChunkReq& Peer_ChunkReq::operator=(const Peer_ChunkReq& other)
{
    if (this==&other) return *this;
    ::BT_Packet::operator=(other);
    copy(other);
    return *this;
}

void Peer_ChunkReq::copy(const Peer_ChunkReq& other)
{
    this->chunk_var = other.chunk_var;
}

void Peer_ChunkReq::parsimPack(cCommBuffer *b)
{
    ::BT_Packet::parsimPack(b);
    doPacking(b,this->chunk_var);
}

void Peer_ChunkReq::parsimUnpack(cCommBuffer *b)
{
    ::BT_Packet::parsimUnpack(b);
    doUnpacking(b,this->chunk_var);
}

int Peer_ChunkReq::getChunk() const
{
    return chunk_var;
}

void Peer_ChunkReq::setChunk(int chunk)
{
    this->chunk_var = chunk;
}

class Peer_ChunkReqDescriptor : public cClassDescriptor
{
  public:
    Peer_ChunkReqDescriptor();
    virtual ~Peer_ChunkReqDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Peer_ChunkReqDescriptor);

Peer_ChunkReqDescriptor::Peer_ChunkReqDescriptor() : cClassDescriptor("Peer_ChunkReq", "BT_Packet")
{
}

Peer_ChunkReqDescriptor::~Peer_ChunkReqDescriptor()
{
}

bool Peer_ChunkReqDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Peer_ChunkReq *>(obj)!=NULL;
}

const char *Peer_ChunkReqDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Peer_ChunkReqDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int Peer_ChunkReqDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *Peer_ChunkReqDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "chunk",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int Peer_ChunkReqDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "chunk")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Peer_ChunkReqDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *Peer_ChunkReqDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Peer_ChunkReqDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Peer_ChunkReq *pp = (Peer_ChunkReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Peer_ChunkReqDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_ChunkReq *pp = (Peer_ChunkReq *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getChunk());
        default: return "";
    }
}

bool Peer_ChunkReqDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Peer_ChunkReq *pp = (Peer_ChunkReq *)object; (void)pp;
    switch (field) {
        case 0: pp->setChunk(string2long(value)); return true;
        default: return false;
    }
}

const char *Peer_ChunkReqDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *Peer_ChunkReqDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_ChunkReq *pp = (Peer_ChunkReq *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Peer_ChunkResp);

Peer_ChunkResp::Peer_ChunkResp(const char *name, int kind) : ::BT_Packet(name,kind)
{
    data_arraysize = 0;
    this->data_var = 0;
    this->size_var = 0;
}

Peer_ChunkResp::Peer_ChunkResp(const Peer_ChunkResp& other) : ::BT_Packet(other)
{
    data_arraysize = 0;
    this->data_var = 0;
    copy(other);
}

Peer_ChunkResp::~Peer_ChunkResp()
{
    delete [] data_var;
}

Peer_ChunkResp& Peer_ChunkResp::operator=(const Peer_ChunkResp& other)
{
    if (this==&other) return *this;
    ::BT_Packet::operator=(other);
    copy(other);
    return *this;
}

void Peer_ChunkResp::copy(const Peer_ChunkResp& other)
{
    delete [] this->data_var;
    this->data_var = (other.data_arraysize==0) ? NULL : new char[other.data_arraysize];
    data_arraysize = other.data_arraysize;
    for (unsigned int i=0; i<data_arraysize; i++)
        this->data_var[i] = other.data_var[i];
    this->size_var = other.size_var;
}

void Peer_ChunkResp::parsimPack(cCommBuffer *b)
{
    ::BT_Packet::parsimPack(b);
    b->pack(data_arraysize);
    doPacking(b,this->data_var,data_arraysize);
    doPacking(b,this->size_var);
}

void Peer_ChunkResp::parsimUnpack(cCommBuffer *b)
{
    ::BT_Packet::parsimUnpack(b);
    delete [] this->data_var;
    b->unpack(data_arraysize);
    if (data_arraysize==0) {
        this->data_var = 0;
    } else {
        this->data_var = new char[data_arraysize];
        doUnpacking(b,this->data_var,data_arraysize);
    }
    doUnpacking(b,this->size_var);
}

void Peer_ChunkResp::setDataArraySize(unsigned int size)
{
    char *data_var2 = (size==0) ? NULL : new char[size];
    unsigned int sz = data_arraysize < size ? data_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        data_var2[i] = this->data_var[i];
    for (unsigned int i=sz; i<size; i++)
        data_var2[i] = 0;
    data_arraysize = size;
    delete [] this->data_var;
    this->data_var = data_var2;
}

unsigned int Peer_ChunkResp::getDataArraySize() const
{
    return data_arraysize;
}

char Peer_ChunkResp::getData(unsigned int k) const
{
    if (k>=data_arraysize) throw cRuntimeError("Array of size %d indexed by %d", data_arraysize, k);
    return data_var[k];
}

void Peer_ChunkResp::setData(unsigned int k, char data)
{
    if (k>=data_arraysize) throw cRuntimeError("Array of size %d indexed by %d", data_arraysize, k);
    this->data_var[k] = data;
}

int Peer_ChunkResp::getSize() const
{
    return size_var;
}

void Peer_ChunkResp::setSize(int size)
{
    this->size_var = size;
}

class Peer_ChunkRespDescriptor : public cClassDescriptor
{
  public:
    Peer_ChunkRespDescriptor();
    virtual ~Peer_ChunkRespDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Peer_ChunkRespDescriptor);

Peer_ChunkRespDescriptor::Peer_ChunkRespDescriptor() : cClassDescriptor("Peer_ChunkResp", "BT_Packet")
{
}

Peer_ChunkRespDescriptor::~Peer_ChunkRespDescriptor()
{
}

bool Peer_ChunkRespDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Peer_ChunkResp *>(obj)!=NULL;
}

const char *Peer_ChunkRespDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Peer_ChunkRespDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int Peer_ChunkRespDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *Peer_ChunkRespDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "data",
        "size",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int Peer_ChunkRespDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Peer_ChunkRespDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "char",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *Peer_ChunkRespDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Peer_ChunkRespDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Peer_ChunkResp *pp = (Peer_ChunkResp *)object; (void)pp;
    switch (field) {
        case 0: return pp->getDataArraySize();
        default: return 0;
    }
}

std::string Peer_ChunkRespDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_ChunkResp *pp = (Peer_ChunkResp *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getData(i));
        case 1: return long2string(pp->getSize());
        default: return "";
    }
}

bool Peer_ChunkRespDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Peer_ChunkResp *pp = (Peer_ChunkResp *)object; (void)pp;
    switch (field) {
        case 0: pp->setData(i,string2long(value)); return true;
        case 1: pp->setSize(string2long(value)); return true;
        default: return false;
    }
}

const char *Peer_ChunkRespDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *Peer_ChunkRespDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Peer_ChunkResp *pp = (Peer_ChunkResp *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


