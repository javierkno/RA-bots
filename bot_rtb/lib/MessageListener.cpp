#include <iostream>
#include <realtimebattle/Messagetypes.h>
#include "MessageListener.h"
#include "TemplateBot.h"
#include "FuzzyControl.h"
#include "BotStates.h"

using namespace std;

MessageListener::MessageListener() { }
MessageListener::MessageListener(const MessageListener& orig) { }
MessageListener::~MessageListener() { }

void MessageListener::setOwner(TemplateBot* owner)
{
    this->owner = owner;
}

void MessageListener::onInit(int first)
{
    if(first != 1)
        return;
    
    owner->setName("Botarate");
    owner->setColor(0x69F, 0x080);
    owner->setOption(SEND_ROTATION_REACHED, 1);
}

void MessageListener::onGameOptions(int option, double value)
{
    switch(option)
    {
        case ROBOT_MAX_ROTATE           : owner->setMaxRotate(value);                break;
        case ROBOT_CANNON_MAX_ROTATE    : owner->setCannonMaxRotate(value);          break;
        case ROBOT_RADAR_MAX_ROTATE     : owner->setRadarMaxRotate(value);           break;
        case ROBOT_MAX_ACCELERATION     : owner->setMaxAcceleration(value);          break;
        case ROBOT_MIN_ACCELERATION     : owner->setMinAcceleration(value);          break;
        case ROBOT_START_ENERGY         : owner->setStartEnergy(value);              break;
        case ROBOT_MAX_ENERGY           : owner->setMaxEnergy(value);                break;
        case ROBOT_ENERGY_LEVELS        : owner->setEnergyLevels(value);             break;
        case SHOT_SPEED                 : owner->setShootSpeed(value);               break;
        case SHOT_MIN_ENERGY            : owner->setShootMinEnergy(value);           break;
        case SHOT_MAX_ENERGY            : owner->setShootMaxEnergy(value);           break;
        case SHOT_ENERGY_INCREASE_SPEED : owner->setShootEnergyIncreaseSpeed(value); break;
        
        default :  break;
    }
}

void MessageListener::onGameStart()
{
	owner->getStateMachine()->SetCurrentState(Empty::Instance());
    owner->getStateMachine()->SetGlobalState(Shoot::Instance());
}

void MessageListener::onGameFinish()
{

}

void MessageListener::onYourName(const string &name)
{

}

void MessageListener::onYourColor(int color)
{

}

void MessageListener::onRadar(int object, double distance, double angle)
{
    //cout << "Print Obj: " << object << " ";
    
    //cout<<"Debug OBJECT= "<<object<<endl;

    /*switch(object)
    {
        case ROBOT  : cout << "Debug Robot"; break;
        case SHOT   : cout << "Debug Shot"; break;
        case WALL   : cout << "Debug Wall"; break;
        case COOKIE : cout << "Debug Cookie"; break;
        case MINE   : cout << "Debug Mine"; break;
        case LAST_OBJECT_TYPE : cout << "Debug LastObjType"; break;
        
        default     : cout << "Debug Not recognized"; break;
    }*/
    
    owner->setObject(object);
    owner->setObjectDistance(distance);
    owner->setObjectAngle(angle);

    owner->getStateMachine()->Update();
    //cout << " Dist " << distance << " Angle " << angle << endl;*/
}

void MessageListener::onInfo(double time, double speed, double cannonAngle)
{
    owner->setSpeed(speed);
    owner->setCannonAngle(cannonAngle);
}

void MessageListener::onCoordinates(double x, double y, double angle)
{
    owner->setX(x);
    owner->setY(y);
    owner->setAngle(angle);
    //TODO
}

void MessageListener::onRobotInfo(double energy, int teammate)
{
    owner->setEnemyEnergy(energy);
    owner->setTeammate(teammate);
}

void MessageListener::onRotationReached(int object)
{

}

void MessageListener::onEnergy(double energy)
{
    owner->setEnergy(energy);
}

void MessageListener::onRobotsLeft(int robotsLeft)
{
    cout<<"Debug ROBOTS LEFT="<<robotsLeft<<endl;
    owner->setRobotsLeft(robotsLeft);
}

void MessageListener::onCollision(int object, double angle)
{
    owner->setCollisionObject(object);
}

void MessageListener::onDead()
{
    
}

void MessageListener::onExit()
{
    
}
