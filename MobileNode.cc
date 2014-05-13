/*
 * MobileNode.cc
 *
 *  Created on: Apr 22, 2014
 *      Author: rpslive
 */


/**
 * A mobile node.
 */

#include <omnetpp.h>
#include "ChannelController.h"

class MobileNode : public cSimpleModule, public IMobileNode
{
  protected:
    // configuration
    double timeStep;
    double txRange;
    double speed;
    // node position and heading (speed is constant in this model)
    double heading; // in degrees
    double x, y; // in meters, relative to playground origin
    double playgroundHeight,playgroundWidth;  // in meters
    bool showTxRange;

  public:
     MobileNode();
     virtual ~MobileNode();
     double getX() { return x; }
     double getY() { return y; }
     double getTxRange() { return txRange; }

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
   // virtual std::string getKmlFragment();
};

Define_Module(MobileNode);

MobileNode::MobileNode()
{
}

MobileNode::~MobileNode()
{
}

void MobileNode::initialize()
{
    x = 50;
    y = 98;
    heading = 90;
    timeStep = par("timeStep");
    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);
    playgroundHeight = simulation.getSystemModule()->par("playgroundHeight");
    playgroundWidth = simulation.getSystemModule()->par("playgroundWidth");
    showTxRange = par("showTxRange");
    speed = par("speed");
    txRange = par("txRange");

    ChannelController::getInstance()->addMobileNode(this);

    // schedule first move
    cMessage *timer = new cMessage("move");
    scheduleAt(simTime(), timer);
}

void MobileNode::handleMessage(cMessage *msg)
{
    // update position
    double vx = sin(heading*M_PI/180) * speed;
    double vy = -cos(heading*M_PI/180) * speed;
    x += vx*timeStep;
    y += vy*timeStep;

    // keep the node inside the playground
    if (x < 0) {x=0; heading = 360 - heading; }
    if (x > playgroundWidth) {x=playgroundWidth; heading = 360-heading;}
    if (y < 0) {y=0; heading = 180 - heading;}
    if (y > playgroundHeight) {y=playgroundHeight; heading = 180 - heading;}

    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);

    // schedule next move
    scheduleAt(simTime()+timeStep, msg);
}



