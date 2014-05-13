/*
 * TSU.cc
 *
 *  Created on: Apr 7, 2014
 *      Author: rpslive
 */

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

#include "TSUmsg_m.h"

class TSU : public cSimpleModule
{
private:
    bool status;
  protected:
    virtual TSUmsg *generateCheckStatusMessage();
    virtual TSUmsg *generateReplyStatusMessage();
    virtual void forwardCheckStatusMessage(TSUmsg *msg);
    virtual void forwardReplyStatusMessage(TSUmsg *msg);
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(TSU);

void TSU::initialize()
{
    if(strcmp("TSU3",getName())==0)
        status=false;
    else
        status=true;
    // TSU1 sends the first message
    if (strcmp("TSU1", getName()) == 0)
    {
        EV<< "Sending initial checkStatus packet from "<<getName()<<"\n";
        TSUmsg *msg = generateCheckStatusMessage();
        send(msg, "out1");
    }
}

TSUmsg *TSU::generateCheckStatusMessage()
{
    // Produce source and destination addresses.
    int src = 1;   // our module index
    int dest = 4;
    int messageType=0;
    int checkCount=3;
    char msgname[20];
    sprintf(msgname, "CheckStatus-%d-to-%d", src, dest);
    // Create message object and set source and destination field.
    TSUmsg *msg = new TSUmsg(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    msg->setMessageType(messageType);
    msg->setCheck(checkCount);
    EV<<"message details "<<msg->getSource()<<" "<<msg->getDestination()<<" "<<msg->getMessageType()<<" "<<msg->getCheck()<<"\n";
    EV<<"status of "<<getName()<<" is "<<status<<"\n";
    return msg;
}

void TSU::handleMessage(cMessage *msg)
{

    TSUmsg *tmsg = check_and_cast<TSUmsg *>(msg);
    if(tmsg->getMessageType()==0&&tmsg->getCheck()>1&&status){//checkStatus
        forwardCheckStatusMessage(tmsg);
    }
    else if(tmsg->getMessageType()==1&&(strcmp("TSU1",getName())!=0)){
        forwardReplyStatusMessage(tmsg);
    }
    else if(strcmp("TSU1",getName())!=0){
        TSUmsg *msg = generateReplyStatusMessage();
        send(msg, "out0");
    }
    else{
        delete(msg);
    }
}

TSUmsg *TSU::generateReplyStatusMessage()
{
    // Produce source and destination addresses.
    const char *str=getName();

    int src = str[3]-'0';   // our module index
    int dest = 1;
    int messageType=1;
    int checkCount=1;
    char msgname[20];
    status*=checkCount;
    sprintf(msgname, "ReplyStatus-%d-to-%d", src, dest);
    // Create message object and set source and destination field.
    EV<< "Sending initial ReplyStatus packet from "<<getName()<<"\n";
    TSUmsg *msg = new TSUmsg(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    msg->setMessageType(messageType);
    msg->setCheck(status);
    EV<<"message details "<<msg->getSource()<<" "<<msg->getDestination()<<" "<<msg->getMessageType()<<" "<<msg->getCheck()<<"\n";
    EV<<"status of "<<getName()<<" is "<<status<<"\n";
    return msg;
}

void TSU::forwardCheckStatusMessage(TSUmsg *msg)
{
    int src=msg->getSource();
    int dest=src+1;
    int checkCount=msg->getCheck();
    int messageType=msg->getMessageType();
    char msgname[20];
    sprintf(msgname, "CheckStatus-%d-to-%d", src+1, dest+1);
    // Create message object and set source and destination field.
    EV<< "Forwarding checkStatus packet from "<<getName()<<"with checkCounter "<<checkCount-1<<"\n";
    TSUmsg *msg1 = new TSUmsg(msgname);
    msg1->setSource(src+1);
    msg1->setDestination(dest+1);
    msg1->setMessageType(messageType);
    msg1->setCheck(--checkCount);
    EV<<"message details "<<msg1->getSource()<<" "<<msg1->getDestination()<<" "<<msg1->getMessageType()<<" "<<msg1->getCheck()<<"\n";
    EV<<"status of "<<getName()<<" is "<<status<<"\n";
    send(msg1,"out1");
}

void TSU::forwardReplyStatusMessage(TSUmsg *msg)
{
    int src=msg->getSource();
    int dest=src-1;
    int checkCount=msg->getCheck();
    int messageType=msg->getMessageType();
    char msgname[20];
    status*=checkCount;
    sprintf(msgname, "ReplyStatus-%d-to-%d", src-1, dest-1);
    // Create message object and set source and destination field.
    EV<< "Forwarding ReplyStatus packet from "<<getName()<<"\n";
    TSUmsg *msg1 = new TSUmsg(msgname);
    msg1->setSource(src-1);
    msg1->setDestination(dest-1);
    msg1->setMessageType(messageType);
    msg1->setCheck(status);
    EV<<"message details "<<msg1->getSource()<<" "<<msg1->getDestination()<<" "<<msg1->getMessageType()<<" "<<msg1->getCheck()<<"\n";
    EV<<"status of "<<getName()<<" is "<<status<<"\n";
    send(msg1,"out0");
}



