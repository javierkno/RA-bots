#include "BotStates.h"
#include "TemplateBot.h"

using namespace std;


Empty* 
Empty::Instance()
{
	static Empty instance;

	return &instance;
}

void 
Empty::Enter(TemplateBot* bot)
{

}

void 
Empty::Execute(TemplateBot* bot)
{
	srand(time(0));
	bot->getStateMachine()->ChangeState(Scout::Instance());
}

void 
Empty::Exit(TemplateBot* bot)
{

}

//------------------------------------------------------------------------

Patrol* 
Patrol::Instance()
{
	static Patrol instance;

	return &instance;
}

void 
Patrol::Enter(TemplateBot* bot)
{
	bot->setGoal(rand()%5);
	bot->getPath(bot->getGoal().x,bot->getGoal().y);
	bot->getSiguiente();
}

void 
Patrol::Execute(TemplateBot* bot)
{

	if(bot->getSpeed()!=-1 && bot->getX()!=100) 
	{
		Node *n = bot->getActual();

		//si ha llegado a goal, calcula otro camino
		//cout<<"Debug goalx= "<<bot->getGoal().x<<" goaly= "<<bot->getGoal().y<<endl;
		if(sqrt(pow(bot->getX()-bot->getGoal().x,2) + pow(bot->getY()-bot->getGoal().y,2)) < 1)
		{
			//cout<<"Debug bieeeeeeeeen"<<endl;
			bot->setGoal(rand()%5);
			bot->getPath(bot->getGoal().x,bot->getGoal().y);
			bot->getSiguiente();
		}
		else if(sqrt(pow(bot->getX()-n->x,2) + pow(bot->getY()-n->y,2)) < 1.5)
		{
			n = bot->getSiguiente();
		}

		//cout<<"Debug speed= "<<bot->getSpeed()<<endl;
		//cout<<"Debug distancia ="<<sqrt(pow(bot->getX()-n->x,2) + pow(bot->getY()-n->y,2))<<endl;
		cout<<"Debug siguiente= "<<n->x<<" "<<n->y<<endl;

		if(n!=NULL) 
		{
	    	bot->rotate(1,bot->angleTo(n->x,n->y));
	    	//cout<<"Debug angulo "<<bot->angleTo(n->x,n->y)*180/3.14152<<endl;
		}

		if(bot->angleTo(n->x,n->y)*180/M_PI < 10 && bot->angleTo(n->x,n->y)*180/M_PI > -10)
		{
			if(bot->getSpeed() > 0.5) 
			{
				bot->brake(100);
			}
			else
			{
				bot->accelerate(1);
			}
		}
		else
		{
			bot->brake(100);
		}

		if(sqrt(pow(bot->getX()-n->x,2) + pow(bot->getY()-n->y,2)) < 3)
		{
			bot->brake(bot->getSpeed());
		}

		if(sqrt(pow(bot->getX(),2) + pow(bot->getY(),2)) < 3)
		{
			bot->brake(1);
		}


		cout<<"Debug "<< bot->getX() - bot->getLastX()<< "   "<< bot->getY() - bot->getLastY()<< "  obj= "<<bot->getCollisionObject()<<endl;

		if(fabs( bot->getX() - bot->getLastX() ) < 0.001 && fabs( bot->getY() - bot->getLastY() ) < 0.001 && bot->getCollisionObject()==WALL)
		{
			cout<<"Debug looooooool"<<endl;
			bot->getStateMachine()->ChangeState(Scout::Instance());
			bot->accelerate(-0.1);
		}




	}
}

void 
Patrol::Exit(TemplateBot* bot)
{
	bot->clearPath();
}

//--------------------------------------------------------------------

Scout* 
Scout::Instance()
{
	static Scout instance;

	return &instance;
}

void 
Scout::Enter(TemplateBot* bot)
{
	bot->rotate(1,M_PI);
	bot->brake(1);
	bot->accelerate(0);
	//bot->rotate(3,M_PI);
}

void 
Scout::Execute(TemplateBot* bot)
{
	//bot->rotate(1,M_PI);
	int n=0;

	//pared no escaneada
	if(bot->getObject()==WALL && bot->changed())
	{
		n = bot->getPathfinding().CalcProb(bot->getX(),bot->getY(),bot->getObjectDistance(), bot->getObjectAngle());
	}

	if(n>200)
	{
		bot->getStateMachine()->ChangeState(Patrol::Instance());
	}

	bot->cleanObject();
}

void 
Scout::Exit(TemplateBot* bot)
{
	bot->getPathfinding().LoadMap();
}

//--------------------------------------------------------------------

Attack* 
Attack::Instance()
{
	static Attack instance;

	return &instance;
}

void 
Attack::Enter(TemplateBot* bot)
{

}

void 
Attack::Execute(TemplateBot* bot)
{
	if(bot->getObject() == ROBOT)
	{
		if(bot->getRobotsLeft()<0) 
		{
			//bot->rotate(1,bot->getObjectAngle());
			bot->shoot(bot->getShootMaxEnergy());
			bot->shoot(bot->getShootMaxEnergy());
			bot->shoot(bot->getShootMaxEnergy());
			bot->shoot(bot->getShootMaxEnergy());
		}
	}

	cout<<"Debug objeto ="<<bot->getObject()<<endl;

	if(bot->getObject() == MINE)
	{
		cout<<"Debug MINAAAAAA"<<endl;
		bot->shoot(bot->getShootMinEnergy()+1);
	}
}

void 
Attack::Exit(TemplateBot* bot)
{

}

//-----------------------------------------------------------------------

Shoot* 
Shoot::Instance()
{
	static Shoot instance;

	return &instance;
}

void 
Shoot::Enter(TemplateBot* bot)
{

}

void 
Shoot::Execute(TemplateBot* bot)
{
	if(bot->getObject() == ROBOT)
	{
		//bot->rotate(1,bot->getObjectAngle());
		bot->shoot(bot->getShootMaxEnergy());
		bot->shoot(bot->getShootMaxEnergy());
		bot->shoot(bot->getShootMaxEnergy());
		bot->shoot(bot->getShootMaxEnergy());
	}

	if(bot->getObject() == MINE)
	{
		bot->shoot(bot->getShootMinEnergy()+1);
		bot->shoot(bot->getShootMinEnergy()+1);
	}


}

void 
Shoot::Exit(TemplateBot* bot)
{

}

//----------------------------------------------------------------------

PickCookie* 
PickCookie::Instance()
{
	static PickCookie instance;

	return &instance;
}

void 
PickCookie::Enter(TemplateBot* bot)
{

}

void 
PickCookie::Execute(TemplateBot* bot)
{
	if(bot->getObject() == ROBOT)
	{
		//bot->rotate(1,bot->getObjectAngle());
		bot->shoot(bot->getShootMaxEnergy());
		bot->shoot(bot->getShootMaxEnergy());
		bot->shoot(bot->getShootMaxEnergy());
		bot->shoot(bot->getShootMaxEnergy());
	}

	if(bot->getObject() == MINE)
	{
		bot->shoot(bot->getShootMinEnergy()+1);
		bot->shoot(bot->getShootMinEnergy()+1);
	}


}

void 
PickCookie::Exit(TemplateBot* bot)
{

}