#ifndef MESSAGELISTENER_HPP
#define	MESSAGELISTENER_HPP

#include <iostream>

class TemplateBot;

class MessageListener
{
    private:
        TemplateBot *owner;
        
    public:
        MessageListener();
        MessageListener(const MessageListener& orig);
        virtual ~MessageListener();
        
        void setOwner(TemplateBot *owner);
        
        void onInit(int first);
        void onGameStart();
        void onGameFinish();
        void onGameOptions(int option, double value);
        void onYourName(const std::string &name);
        void onYourColor(int color);
        void onRadar(int object, double distance, double angle);
        void onInfo(double time, double speed, double cannonAngle);
        void onCoordinates(double x, double y, double angle);
        void onRobotInfo(double energy, int teammate);
        void onRotationReached(int object);
        void onEnergy(double energy);
        void onRobotsLeft(int robotsLeft);
        void onCollision(int object, double angle);
        void onDead();
        void onExit();
};

#endif

