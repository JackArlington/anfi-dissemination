//
// Generated file, do not edit! Created by nedtool 4.6 from messages/AIDMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "AIDMessage_m.h"

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

Register_Class(AIDMessage);

AIDMessage::AIDMessage(const char *name, int kind) : ::WaveShortMessage(name,kind)
{
    this->srcAddr_var = 0;
    this->destAddr_var = 0;
    this->msgId_var = 0;
    this->ttl_var = 0;
    this->messageROI_var = 0;
    this->messageOriginTime_var = 0;
    this->messageTTL_var = 0;
    this->hops_var = 0;
    this->sent_var = 0;
}

AIDMessage::AIDMessage(const AIDMessage& other) : ::WaveShortMessage(other)
{
    copy(other);
}

AIDMessage::~AIDMessage()
{
}

AIDMessage& AIDMessage::operator=(const AIDMessage& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void AIDMessage::copy(const AIDMessage& other)
{
    this->srcAddr_var = other.srcAddr_var;
    this->destAddr_var = other.destAddr_var;
    this->msgId_var = other.msgId_var;
    this->ttl_var = other.ttl_var;
    this->messageROI_var = other.messageROI_var;
    this->messageOriginTime_var = other.messageOriginTime_var;
    this->messageTTL_var = other.messageTTL_var;
    this->hops_var = other.hops_var;
    this->sent_var = other.sent_var;
}

void AIDMessage::parsimPack(cCommBuffer *b)
{
    ::WaveShortMessage::parsimPack(b);
    doPacking(b,this->srcAddr_var);
    doPacking(b,this->destAddr_var);
    doPacking(b,this->msgId_var);
    doPacking(b,this->ttl_var);
    doPacking(b,this->messageROI_var);
    doPacking(b,this->messageOriginTime_var);
    doPacking(b,this->messageTTL_var);
    doPacking(b,this->hops_var);
    doPacking(b,this->sent_var);
}

void AIDMessage::parsimUnpack(cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    doUnpacking(b,this->srcAddr_var);
    doUnpacking(b,this->destAddr_var);
    doUnpacking(b,this->msgId_var);
    doUnpacking(b,this->ttl_var);
    doUnpacking(b,this->messageROI_var);
    doUnpacking(b,this->messageOriginTime_var);
    doUnpacking(b,this->messageTTL_var);
    doUnpacking(b,this->hops_var);
    doUnpacking(b,this->sent_var);
}

unsigned int AIDMessage::getSrcAddr() const
{
    return srcAddr_var;
}

void AIDMessage::setSrcAddr(unsigned int srcAddr)
{
    this->srcAddr_var = srcAddr;
}

unsigned int AIDMessage::getDestAddr() const
{
    return destAddr_var;
}

void AIDMessage::setDestAddr(unsigned int destAddr)
{
    this->destAddr_var = destAddr;
}

unsigned int AIDMessage::getMsgId() const
{
    return msgId_var;
}

void AIDMessage::setMsgId(unsigned int msgId)
{
    this->msgId_var = msgId;
}

int AIDMessage::getTtl() const
{
    return ttl_var;
}

void AIDMessage::setTtl(int ttl)
{
    this->ttl_var = ttl;
}

double AIDMessage::getMessageROI() const
{
    return messageROI_var;
}

void AIDMessage::setMessageROI(double messageROI)
{
    this->messageROI_var = messageROI;
}

simtime_t AIDMessage::getMessageOriginTime() const
{
    return messageOriginTime_var;
}

void AIDMessage::setMessageOriginTime(simtime_t messageOriginTime)
{
    this->messageOriginTime_var = messageOriginTime;
}

simtime_t AIDMessage::getMessageTTL() const
{
    return messageTTL_var;
}

void AIDMessage::setMessageTTL(simtime_t messageTTL)
{
    this->messageTTL_var = messageTTL;
}

int AIDMessage::getHops() const
{
    return hops_var;
}

void AIDMessage::setHops(int hops)
{
    this->hops_var = hops;
}

simtime_t AIDMessage::getSent() const
{
    return sent_var;
}

void AIDMessage::setSent(simtime_t sent)
{
    this->sent_var = sent;
}

class AIDMessageDescriptor : public cClassDescriptor
{
  public:
    AIDMessageDescriptor();
    virtual ~AIDMessageDescriptor();

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

Register_ClassDescriptor(AIDMessageDescriptor);

AIDMessageDescriptor::AIDMessageDescriptor() : cClassDescriptor("AIDMessage", "WaveShortMessage")
{
}

AIDMessageDescriptor::~AIDMessageDescriptor()
{
}

bool AIDMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AIDMessage *>(obj)!=NULL;
}

const char *AIDMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AIDMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount(object) : 9;
}

unsigned int AIDMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *AIDMessageDescriptor::getFieldName(void *object, int field) const
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
        "messageROI",
        "messageOriginTime",
        "messageTTL",
        "hops",
        "sent",
    };
    return (field>=0 && field<9) ? fieldNames[field] : NULL;
}

int AIDMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgId")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "ttl")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageROI")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageOriginTime")==0) return base+5;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageTTL")==0) return base+6;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+7;
    if (fieldName[0]=='s' && strcmp(fieldName, "sent")==0) return base+8;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AIDMessageDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "double",
        "simtime_t",
        "simtime_t",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : NULL;
}

const char *AIDMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int AIDMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AIDMessage *pp = (AIDMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AIDMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AIDMessage *pp = (AIDMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSrcAddr());
        case 1: return ulong2string(pp->getDestAddr());
        case 2: return ulong2string(pp->getMsgId());
        case 3: return long2string(pp->getTtl());
        case 4: return double2string(pp->getMessageROI());
        case 5: return double2string(pp->getMessageOriginTime());
        case 6: return double2string(pp->getMessageTTL());
        case 7: return long2string(pp->getHops());
        case 8: return double2string(pp->getSent());
        default: return "";
    }
}

bool AIDMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AIDMessage *pp = (AIDMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcAddr(string2ulong(value)); return true;
        case 1: pp->setDestAddr(string2ulong(value)); return true;
        case 2: pp->setMsgId(string2ulong(value)); return true;
        case 3: pp->setTtl(string2long(value)); return true;
        case 4: pp->setMessageROI(string2double(value)); return true;
        case 5: pp->setMessageOriginTime(string2double(value)); return true;
        case 6: pp->setMessageTTL(string2double(value)); return true;
        case 7: pp->setHops(string2long(value)); return true;
        case 8: pp->setSent(string2double(value)); return true;
        default: return false;
    }
}

const char *AIDMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *AIDMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AIDMessage *pp = (AIDMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


