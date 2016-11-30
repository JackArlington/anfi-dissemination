//
// Generated file, do not edit! Created by nedtool 4.6 from messages/FloodingMessage.msg.
//

#ifndef _FLOODINGMESSAGE_M_H_
#define _FLOODINGMESSAGE_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
    #include <list>
	#include "WaveShortMessage_m.h"
// }}

/**
 * Class generated from <tt>messages/FloodingMessage.msg:10</tt> by nedtool.
 * <pre>
 * message FloodingMessage extends WaveShortMessage
 * {
 *     unsigned int srcAddr;
 *     unsigned int destAddr;
 *     unsigned int msgId;
 *     int ttl;
 *     int hopCount = 0;
 *     simtime_t sent;
 * }
 * </pre>
 */
class FloodingMessage : public ::WaveShortMessage
{
  protected:
    unsigned int srcAddr_var;
    unsigned int destAddr_var;
    unsigned int msgId_var;
    int ttl_var;
    int hopCount_var;
    simtime_t sent_var;

  private:
    void copy(const FloodingMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const FloodingMessage&);

  public:
    FloodingMessage(const char *name=NULL, int kind=0);
    FloodingMessage(const FloodingMessage& other);
    virtual ~FloodingMessage();
    FloodingMessage& operator=(const FloodingMessage& other);
    virtual FloodingMessage *dup() const {return new FloodingMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned int getSrcAddr() const;
    virtual void setSrcAddr(unsigned int srcAddr);
    virtual unsigned int getDestAddr() const;
    virtual void setDestAddr(unsigned int destAddr);
    virtual unsigned int getMsgId() const;
    virtual void setMsgId(unsigned int msgId);
    virtual int getTtl() const;
    virtual void setTtl(int ttl);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual simtime_t getSent() const;
    virtual void setSent(simtime_t sent);
};

inline void doPacking(cCommBuffer *b, FloodingMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, FloodingMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef _FLOODINGMESSAGE_M_H_

