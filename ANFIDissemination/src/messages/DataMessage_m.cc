//
// Generated file, do not edit! Created by nedtool 4.6 from messages/DataMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DataMessage_m.h"

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

Register_Class(DataMessage);

DataMessage::DataMessage(const char *name, int kind) : ::cPacket(name,kind)
{
    this->messageROI_var = 0;
    this->messageOriginTime_var = 0;
    this->messageTTL_var = 0;
    this->hops_var = 0;
}

DataMessage::DataMessage(const DataMessage& other) : ::cPacket(other)
{
    copy(other);
}

DataMessage::~DataMessage()
{
}

DataMessage& DataMessage::operator=(const DataMessage& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void DataMessage::copy(const DataMessage& other)
{
    this->messageOriginPosition_var = other.messageOriginPosition_var;
    this->messageROI_var = other.messageROI_var;
    this->messageOriginTime_var = other.messageOriginTime_var;
    this->messageTTL_var = other.messageTTL_var;
    this->hops_var = other.hops_var;
}

void DataMessage::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->messageOriginPosition_var);
    doPacking(b,this->messageROI_var);
    doPacking(b,this->messageOriginTime_var);
    doPacking(b,this->messageTTL_var);
    doPacking(b,this->hops_var);
}

void DataMessage::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->messageOriginPosition_var);
    doUnpacking(b,this->messageROI_var);
    doUnpacking(b,this->messageOriginTime_var);
    doUnpacking(b,this->messageTTL_var);
    doUnpacking(b,this->hops_var);
}

Coord& DataMessage::getMessageOriginPosition()
{
    return messageOriginPosition_var;
}

void DataMessage::setMessageOriginPosition(const Coord& messageOriginPosition)
{
    this->messageOriginPosition_var = messageOriginPosition;
}

double DataMessage::getMessageROI() const
{
    return messageROI_var;
}

void DataMessage::setMessageROI(double messageROI)
{
    this->messageROI_var = messageROI;
}

simtime_t DataMessage::getMessageOriginTime() const
{
    return messageOriginTime_var;
}

void DataMessage::setMessageOriginTime(simtime_t messageOriginTime)
{
    this->messageOriginTime_var = messageOriginTime;
}

simtime_t DataMessage::getMessageTTL() const
{
    return messageTTL_var;
}

void DataMessage::setMessageTTL(simtime_t messageTTL)
{
    this->messageTTL_var = messageTTL;
}

int DataMessage::getHops() const
{
    return hops_var;
}

void DataMessage::setHops(int hops)
{
    this->hops_var = hops;
}

class DataMessageDescriptor : public cClassDescriptor
{
  public:
    DataMessageDescriptor();
    virtual ~DataMessageDescriptor();

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

Register_ClassDescriptor(DataMessageDescriptor);

DataMessageDescriptor::DataMessageDescriptor() : cClassDescriptor("DataMessage", "cPacket")
{
}

DataMessageDescriptor::~DataMessageDescriptor()
{
}

bool DataMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DataMessage *>(obj)!=NULL;
}

const char *DataMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DataMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int DataMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *DataMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "messageOriginPosition",
        "messageROI",
        "messageOriginTime",
        "messageTTL",
        "hops",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int DataMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageOriginPosition")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageROI")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageOriginTime")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageTTL")==0) return base+3;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DataMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "Coord",
        "double",
        "simtime_t",
        "simtime_t",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *DataMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DataMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DataMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getMessageOriginPosition(); return out.str();}
        case 1: return double2string(pp->getMessageROI());
        case 2: return double2string(pp->getMessageOriginTime());
        case 3: return double2string(pp->getMessageTTL());
        case 4: return long2string(pp->getHops());
        default: return "";
    }
}

bool DataMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setMessageROI(string2double(value)); return true;
        case 2: pp->setMessageOriginTime(string2double(value)); return true;
        case 3: pp->setMessageTTL(string2double(value)); return true;
        case 4: pp->setHops(string2long(value)); return true;
        default: return false;
    }
}

const char *DataMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(Coord));
        default: return NULL;
    };
}

void *DataMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getMessageOriginPosition()); break;
        default: return NULL;
    }
}


