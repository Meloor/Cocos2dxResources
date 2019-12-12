#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact * contact)
{
	log("BeginContact");
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	auto spa = (Sprite*)bodyA->GetUserData();
	auto spb = (Sprite*)bodyB->GetUserData();
	if (spa != nullptr&&spb != nullptr) {
		spa->setTag(spa->getTag() + 1);
		spb->setTag(spb->getTag() + 1);
		if (spa->getTag() > 0)spa->setColor(Color3B::YELLOW);
		if (spb->getTag() > 0)spb->setColor(Color3B::YELLOW);
	}
}

void ContactListener::EndContact(b2Contact * contact)
{
	log("EndContact");
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	auto spa = (Sprite*)bodyA->GetUserData();
	auto spb = (Sprite*)bodyB->GetUserData();
	if (spa != nullptr&&spb != nullptr) {
		spa->setTag(spa->getTag() - 1);
		spb->setTag(spb->getTag() - 1);
		if (spa->getTag()<=0)spa->setColor(Color3B::WHITE);
		if (spb->getTag()<=0)spb->setColor(Color3B::WHITE);
	}
}

void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManiFold)
{
	log("PreSolve");
}

void ContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	log("PostSolve");
}
