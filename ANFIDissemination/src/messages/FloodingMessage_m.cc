//
// Generated file, do not edit! Created by nedtool 4.6 from messages/FloodingMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "FloodingMessage_m.h"

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

Register_Class(FloodingMessage);

FloodingMessage::FloodingMessage(const char *name, int kind) : ::WaveShortMessage(name,kind)
{
    this->srcAddr_var = 0;
    this->destAddr_var = 0;
    this->msgId_var = 0;
    this->ttl_var = 0;
}

FloodingMessage::FloodingMessage(const FloodingMessage& other) : ::WaveShortMessage(other)
{
    copy(other);
}

FloodingMessage::~FloodingMessage()
{
}

FloodingMessage& FloodingMessage::operator=(const FloodingMessage& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void FloodingMessage::copy(const FloodingMessage& other)
{
    this->srcAddr_var = other.srcAddr_var;
    this->destAddr_var = other.destAddr_var;
    this->msgId_var = other.msgId_var;
    this->ttl_var = other.ttl_var;
}

void FloodingMessage::parsimPack(cCommBuffer *b)
{
    ::WaveShortMessage::parsimPack(b);
    doPacking(b,this->srcAddr_var);
    doPacking(b,this->destAddr_var);
    doPacking(b,this->msgId_var);
    doPacking(b,this->ttl_var);
}

void FloodingMessage::parsimUnpack(cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    doUnpacking(b,this->srcAddr_var);
    doUnpacking(b,this->destAddr_var);
    doUnpacking(b,this->msgId_var);
    doUnpacking(b,this->ttl_var);
}

unsigned int FloodingMessage::getSrcAddr() const
{
    return srcAddr_var;
}

void FloodingMessage::setSrcAddr(unsigned int srcAddr)
{
    this->srcAddr_var = srcAddr;
}

unsigned int FloodingMessage::getDestAddr() const
{
    return destAddr_var;
}

void FloodingMessage::setDestAddr(unsigned int destAddr)
{
    this->destAddr_var = destAddr;
}

unsigned int FloodingMessage::getMsgId() const
{
    return msgId_var;
}

void FloodingMessage::setMsgId(unsigned int msgId)
{
    this->msgId_var = msgId;
}

unsigned int FloodingMessage::getTtl() const
{
    return ttl_var;
}

void FloodingMessage::setTtl(unsigned int ttl)
{
    this->ttl_var = ttl;
}

class FloodingMessageDescriptor : public cClassDescriptor
{
  public:
    FloodingMessageDescriptor();
    virtual ~FloodingMessageDescriptor();

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

Register_ClassDescriptor(FloodingMessageDescriptor);

FloodingMessageDescriptor::FloodingMessageDescriptor() : cClassDescriptor("FloodingMessage", "WaveShortMessage")
{
}

FloodingMessageDescriptor::~FloodingMessageDescriptor()
{
}

bool FloodingMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FloodingMessage *>(obj)!=NULL;
}

const char *FloodingMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FloodingMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int FloodingMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *FloodingMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "msgId",
        "ttl",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int FloodingMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgId")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "ttl")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FloodingMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *FloodingMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int FloodingMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FloodingMessage *pp = (FloodingMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FloodingMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FloodingMessage *pp = (FloodingMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSrcAddr());
        case 1: return ulong2string(pp->getDestAddr());
        case 2: return ulong2string(pp->getMsgId());
        case 3: return ulong2string(pp->getTtl());
        default: return "";
    }
}

bool FloodingMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FloodingMessage *pp = (FloodingMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcAddr(string2ulong(value)); return true;
        case 1: pp->setDestAddr(string2ulong(value)); return true;
        case 2: pp->setMsgId(string2ulong(value)); return true;
        case 3: pp->setTtl(string2ulong(value)); return true;
        default: return false;
    }
}

const char *FloodingMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *FloodingMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FloodingMessage *pp = (FloodingMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


