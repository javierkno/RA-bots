#ifndef BOTSTATES_H
#define BOTSTATES_H

#include "State.h"
#include <realtimebattle/Messagetypes.h>
//#include "TemplateBot.h"

class TemplateBot;

class PickCookie : public State<TemplateBot>
{
private:
	PickCookie(){}
	PickCookie(const PickCookie&);
	PickCookie& operator=(const PickCookie&);
public:
	static PickCookie* Instance();
	virtual void Enter(TemplateBot* bot);
	virtual void Execute(TemplateBot* bot);
	virtual void Exit(TemplateBot* bot);
};

class Patrol : public State<TemplateBot>
{
private:
	Patrol(){}
	Patrol(const Patrol&);
	Patrol& operator=(const Patrol&);
public:
	static Patrol* Instance();
	virtual void Enter(TemplateBot* bot);
	virtual void Execute(TemplateBot* bot);
	virtual void Exit(TemplateBot* bot);
};

class Empty : public State<TemplateBot>
{
private:
	Empty(){}
	Empty(const Empty&);
	Empty& operator=(const Empty&);
public:
	static Empty* Instance();
	virtual void Enter(TemplateBot* bot);
	virtual void Execute(TemplateBot* bot);
	virtual void Exit(TemplateBot* bot);
};

class Scout : public State<TemplateBot>
{
private:
	Scout(){}
	Scout(const Scout&);
	Scout& operator=(const Scout&);
public:
	static Scout* Instance();
	virtual void Enter(TemplateBot* bot);
	virtual void Execute(TemplateBot* bot);
	virtual void Exit(TemplateBot* bot);
};

class Attack : public State<TemplateBot>
{
private:
	Attack(){}
	Attack(const Attack&);
	Attack& operator=(const Attack&);
public:
	static Attack* Instance();
	virtual void Enter(TemplateBot* bot);
	virtual void Execute(TemplateBot* bot);
	virtual void Exit(TemplateBot* bot);
};

class Shoot : public State<TemplateBot>
{
private:
	Shoot(){}
	Shoot(const Shoot&);
	Shoot& operator=(const Shoot&);
public:
	static Shoot* Instance();
	virtual void Enter(TemplateBot* bot);
	virtual void Execute(TemplateBot* bot);
	virtual void Exit(TemplateBot* bot);
};

#endif