#ifndef TEMPLATEBOT_H
#define	TEMPLATEBOT_H

#include "MessageListener.h"
#include "StateMachine.h"
#include "Pathfinding.h"

class TemplateBot
{
    private:
        MessageListener listener;
        //------------------
        StateMachine<TemplateBot>* stmachine;
        Pathfinding pf;

        Node *sig;

        vector<Node*> camino;

        //+++++++++++++++++

        int object;
        double odistance;
        double oangle;
        double lodistance;

        int goal;
        Node coordinates[5];

        double last_x;
        double last_y;

        //--------------------

        /* ROBOT VARIABLES */
        double x;
        double y;
        
        double angle;
        double radarAngle;
        double cannonAngle;
        
        double speed;
        double energy;
        
        double collisionObject;
        double collisionAngle;
        
        double enemyEnergy;
        bool teammate;
        
        int robotsLeft;
        
        /* GAME OPTIONS */
        double maxRotate;
        double cannonMaxRotate;
        double radarMaxRotate;
        double maxAcceleration;
        double minAcceleration;
        double startEnergy;
        double maxEnergy;
        double energyLevels;
        double shootSpeed;
        double shootMinEnergy;
        double shootMaxEnergy;
        double shootEnergyIncreaseSpeed;
        
    public:

        TemplateBot();
        TemplateBot(const TemplateBot& orig);
        virtual ~TemplateBot();
        
        MessageListener& getListener() { return listener; }
        StateMachine<TemplateBot>* getStateMachine() { return stmachine; }
        Pathfinding& getPathfinding() { return pf; }
        
        /* SETTERS */
        void setX(double x)              { last_x = this->x; this->x = x; }
        void setY(double y)              { last_y = this->y; this->y = y; }
        void setAngle(double a)          { this->angle = a; }
        void setRadarAngle(double a)     { this->radarAngle = a; }
        void setCannonAngle(double a)    { this->cannonAngle = a; }
        void setSpeed(double s)          { this->speed = s; }
        void setEnergy(double e)         { this->energy = e; }
        void setEnemyEnergy(double e)    { this->enemyEnergy = e; }
        void setTeammate(bool tm)        { this->teammate = tm; }
        void setCollisionObject(int o)   { this->collisionObject = o; }
        void setCollisionAngle(double a) { this->collisionAngle = a; }
        void setRobotsLeft(int rl)       { this->robotsLeft = rl; }
       
        
        void setMaxRotate(double mr)                  { maxRotate = mr; }
        void setCannonMaxRotate(double cmr)           { cannonMaxRotate = cmr; }
        void setRadarMaxRotate(double rmr)            { radarMaxRotate = rmr; }
        void setMaxAcceleration(double ma)            { maxAcceleration = ma; }
        void setMinAcceleration(double ma)            { minAcceleration = ma; }
        void setStartEnergy(double se)                { startEnergy = se; }
        void setMaxEnergy(double me)                  { maxEnergy = me; }
        void setEnergyLevels(double el)               { energyLevels = el; }
        void setShootSpeed(double ss)                 { shootSpeed = ss; }
        void setShootMinEnergy(double sme)            { shootMinEnergy = sme; }
        void setShootMaxEnergy(double sme)            { shootMaxEnergy = sme; }
        void setShootEnergyIncreaseSpeed(double seis) { shootEnergyIncreaseSpeed = seis; }

        double getMaxRotate()                  { return maxRotate; }
        double getCannonMaxRotate()            { return cannonMaxRotate; }
        double getRadarMaxRotate()             { return radarMaxRotate; }
        double getMaxAcceleration()            { return maxAcceleration; }
        double getMinAcceleration()            { return minAcceleration; }
        double getStartEnergy()                { return startEnergy; }
        double getMaxEnergy()                  { return maxEnergy; }
        double getEnergyLevels()               { return energyLevels; }
        double getShootSpeed()                 { return shootSpeed; }
        double getShootMinEnergy()             { return shootMinEnergy; }
        double getShootMaxEnergy()             { return shootMaxEnergy; }
        double getShootEnergyIncreaseSpeed()   { return shootEnergyIncreaseSpeed; }

        double getX()               { return x; }
        double getY()               { return y;}
        double getAngle()           { return angle; }
        double getRadarAngle()      { return radarAngle; }
        double getCannonAngle()     { return cannonAngle; }
        double getSpeed()           { return speed; }
        double getEnergy()          { return energy; }
        double getEnemyEnergy()     { return enemyEnergy; }
        bool getTeammate()          { return teammate; }
        int getCollisionObject()    { return collisionObject; }
        double getCollisionAngle()  { return collisionAngle; }
        int getRobotsLeft()         { return robotsLeft; }
        
        Node* getSiguiente();
        Node* getActual();
        void getPath(int, int);
        double angleTo(int, int);

        int getObject() { return object; }
        double getObjectDistance() { return odistance; }
        double getObjectAngle() { return oangle; }
        void setObject(int n) { object=n; }
        void setObjectDistance(double d) { lodistance = odistance; odistance = d;}
        void setObjectAngle(double a) { oangle = a; }
        void cleanObject() { object=-1; }
        bool changed() { return !(odistance==lodistance); }
        //Node getCoords(int num) { return coordinates[num]; }

        Node getGoal() { return coordinates[goal]; }
        void setGoal(int g) { goal = g; }

        void clearPath();
        double getLastX() { return last_x; }
        double getLastY() { return last_y; }

        /* MESSAGES TO SERVER */
        void setOption(int option, int value);
        void setName(const char* name);
        void setColor(int homeColor, int awayColor);
        void rotate(int object, double angularVelocity);
        void rotateTo(int object, double angularVelocity, double angle);
        void rotateAmount(int object, double angularVelocity, double angle);
        void sweep(int object, double angularVelocity, double rightAngle, double leftAngle);
        void accelerate(double value);
        void brake(double value);
        void shoot(double energy);
};

#endif
