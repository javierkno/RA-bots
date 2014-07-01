#include <iostream>
#include <realtimebattle/Messagetypes.h>
#include "TemplateBot.h"
#include "BotStates.h"

using namespace std;

TemplateBot::TemplateBot()
{

	coordinates[0]= Node(0,0);
	coordinates[1]= Node(-9,-9);
	coordinates[2]= Node(9,9);
	coordinates[3]= Node(-9,9);
	coordinates[4]= Node(9,-9);
	x=100;
	speed=-1;
	lodistance=0;
	odistance=0;
    listener.setOwner(this);
    stmachine = new StateMachine<TemplateBot>(this);
}

TemplateBot::TemplateBot(const TemplateBot& orig) { }
TemplateBot::~TemplateBot() { }

void TemplateBot::setOption(int option, int value)
{
    cout << "RobotOption " << option << " " << value << endl;
}

void TemplateBot::setName(const char* name)
{
    cout << "Name " << name << endl;
}

void TemplateBot::setColor(int homeColor, int awayColor)
{
    cout << "Colour " << homeColor << " " << awayColor << endl;
}

void TemplateBot::rotate(int object, double angularVelocity)
{
    cout << "Rotate " << object << " " << angularVelocity << endl;
}

void TemplateBot::rotateTo(int object, double angularVelocity, double angle)
{
    cout << "RotateTo " << object << " " << angularVelocity << " " << angle << endl;
}

void TemplateBot::rotateAmount(int object, double angularVelocity, double angle)
{
    cout << "RotateAmount " << object << " " << angularVelocity << " " << angle << endl;
}

void TemplateBot::sweep(int object, double angularVelocity, double rightAngle, double leftAngle)
{
    cout << "Sweep " << object << " " << angularVelocity << " " << rightAngle << " " << leftAngle << endl;
}

void TemplateBot::accelerate(double value)
{
    cout << "Accelerate " << value << endl;
}
void TemplateBot::brake(double value)
{
    cout << "Brake " << value << endl;
}

void TemplateBot::shoot(double energy)
{
    cout << "Shoot " << energy << endl;
}

Node* TemplateBot::getSiguiente()
{
	Node *n;
	if(camino.size()!=0) {
		n = camino.back();
		camino.pop_back();
	}
	sig = n;
	return n;
}

void TemplateBot::getPath(int x1, int y1)
{
	camino = pf.Astar(round(x),round(y),x1,y1);

	int n = camino.size();
	for(int i=n-1;i>=0;i--)
	{
		Node *n = camino[i];
		cout<<"Debug coord ("<<n->x<<", "<<n->y<<")"<<endl;
	}
}

double TemplateBot::angleTo(int x1, int y1)
{
	return AngleTo(x,y,angle,x1,y1);
}

Node* TemplateBot::getActual()
{
	return sig;
}

void TemplateBot::clearPath()
{
	camino = vector<Node*>();
	sig = NULL;
}