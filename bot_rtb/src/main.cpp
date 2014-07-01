#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#include <math.h>
#include <realtimebattle/Messagetypes.h>

#include "TemplateBot.h"
#include "Pathfinding.h"
#include "StateMachine.h"

using namespace std;

#define abs(x) ((x>0) ? (x) : -(x))

volatile sig_atomic_t exit_robot = false;

TemplateBot tb;

message_to_robot_type
getMessage(char* msg_name)
{
    for(int i=0; message_to_robot[i].msg[0] != '\0'; i++)
    {
        if( strcmp(message_to_robot[i].msg, msg_name) == 0 )
            return (message_to_robot_type)i;
    }
    return UNKNOWN_MESSAGE_TO_ROBOT;
}


void handleSignal(int n)
{
    char msg_name[81];
    char text[81];
    string botName;
    message_to_robot_type msg_t;

    cin.clear();

    while(!cin.eof())
    {
        cin >> msg_name;
        msg_t = getMessage(msg_name);

        switch(msg_t)
        {
            case INITIALIZE:
                int first; cin >> first;
                tb.getListener().onInit(first);
                break;
                
            case YOUR_NAME:
                cin >> botName;
                tb.getListener().onYourName(botName);
                break;
                
            case YOUR_COLOUR:
                int color; cin >> color;
                tb.getListener().onYourColor(color);
                break;
                
            case GAME_OPTION:
                int    option;
                double value;
                
                cin >> option >> value;
                
                tb.getListener().onGameOptions(option, value);
                break;
            
            case GAME_STARTS:
                tb.getListener().onGameStart();
                break;
                
            case GAME_FINISHES:
                tb.getListener().onGameFinish();
                break;
            
            case RADAR:
                int object;
                double distance, robotAngle;
                
                cin >> distance >> object >> robotAngle;
                tb.getListener().onRadar(object, distance, robotAngle);
                break;
             
            case INFO:
                double time, speed, cannonAngle;
                cin >> time >> speed >> cannonAngle;
                tb.getListener().onInfo(time, speed, cannonAngle);
                break;

            case COORDINATES:
                double x, y, angle;
                cin >> x >> y >> angle;
                tb.getListener().onCoordinates(x, y, angle);
                break;
                
            case ROBOT_INFO:
                int teammate;
                double energy;
                cin >> energy >> teammate;
                tb.getListener().onRobotInfo(energy, teammate);
                break;
                
            case ROTATION_REACHED:
                int whatReached; cin >> whatReached;
                tb.getListener().onRotationReached(whatReached);
                break;
                
            case ENERGY:
                double myEnergy;
                cin >> myEnergy;
                tb.getListener().onEnergy(myEnergy);
                break;
                
            case ROBOTS_LEFT:
                int robotsLeft;
                cin >> robotsLeft;
                tb.getListener().onRobotsLeft(robotsLeft);
                break;
                
            case COLLISION:
                int objectType;
                double collisionAngle;
                cin >> objectType >> collisionAngle;
                tb.getListener().onCollision(objectType, collisionAngle);
                break;
                
            case DEAD:
                tb.getListener().onDead();
                break;
                
            case EXIT_ROBOT:
                tb.getListener().onExit();
                break;

            default: break;
        }
    }
    signal(n, handleSignal);
}

int main(int argc, char **argv)
{
    signal(SIGUSR1, handleSignal);

    cout << "RobotOption " << SEND_SIGNAL << " " << true << endl;

    for(;; sleep(1))
        if(exit_robot)
            return(EXIT_SUCCESS);
    
    return(EXIT_SUCCESS);
}
