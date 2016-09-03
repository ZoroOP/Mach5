/******************************************************************************/
/*!
\file   M5Object.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/20

//! Component based Game object used in the Mach 5 Engine
*/
/******************************************************************************/
#include "M5Object.h"
#include "M5Debug.h"
#include "M5Component.h"
#include <algorithm>

namespace
{
const int START_SIZE = 8;
}

int M5Object::s_objectIDCounter = 0;

/******************************************************************************/
/*!
M5Object constructor.  Sets intial data for the game object including the
ArcheType, however this doesn't allocate any components.  Use the 
ObjectManager to create objects with components.

\param type
The type that this object will be.
*/
/******************************************************************************/
M5Object::M5Object(M5ArcheTypes type) :
	m_components(),
	m_type(type),
	pos(0, 0),
	scale(1, 1),
	vel(0, 0),
	rotation(0),
	rotationVel(0),
	isDead(false),
	m_id(++s_objectIDCounter)
{
	m_components.reserve(START_SIZE);
}
/******************************************************************************/
/*!
Removes and deletes all component pointers.
*/
/******************************************************************************/
M5Object::~M5Object(void)
{
	RemoveAllComponents();
}
/******************************************************************************/
/*!
Removes all components from this game object and deletes the component 
pointers

*/
/******************************************************************************/
void M5Object::RemoveAllComponents(void)
{
	VecItor itor = m_components.begin();
	VecItor end = m_components.end();
	while (itor != end)
	{
		delete (*itor);
		++itor;
	}
}
/******************************************************************************/
/*!
Updates all components in the game object

*/
/******************************************************************************/
void M5Object::Update(float dt)
{
	size_t size = m_components.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_components[i]->Update(dt);
	}

	//Update object data
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;
	rotation += rotationVel * dt;
}
/******************************************************************************/
/*!
Gets the unique id of this game object

*/
/******************************************************************************/
int M5Object::GetID(void) const
{
	return m_id;
}
/******************************************************************************/
/*!
Creates a copy of this game object including all components

*/
/******************************************************************************/
M5Object* M5Object::Clone(void)
{
	//create new object
	M5Object* pClone = new M5Object(m_type);
	//copy this internal data
	pClone->pos   = pos;
	pClone->vel   = vel;
	pClone->scale = scale;
	pClone->m_id  = ++s_objectIDCounter;

	//clone all components
	size_t size = m_components.size();
	for (size_t i = 0; i < size; ++i)
	{
		M5Component* pComp = m_components[i]->Clone();
		pClone->AddComponent(pComp);
	}

	return pClone;
}
/******************************************************************************/
/*!
Adds a component to this object

\param pComponent
The component to add

*/
/******************************************************************************/
void M5Object::AddComponent(M5Component* pComponent)
{
	//Make sure this component doesn't already exist
	VecItor itor = std::find(m_components.begin(), m_components.end(), pComponent);
	M5DEBUG_ASSERT(itor == m_components.end(), "Trying to add a component that already exists");
	
	//Set this object as the parent
	pComponent->SetParent(this);
	m_components.push_back(pComponent);
}
/******************************************************************************/
/*!
Removes the instance of a specific component

\param pComponent
The component instance to remove
*/
/******************************************************************************/
void M5Object::RemoveComponent(M5Component* pComponent)
{
	VecItor end = m_components.end();
	//Make the sure the instance exists in this object
	VecItor itor = std::find(m_components.begin(), end, pComponent);
	M5DEBUG_ASSERT(itor != end, "Trying to remove a component that doesn't exist");
	//swap with last component
	std::iter_swap(itor, --end);
	m_components.pop_back();

	//Clear parent before deleting
	pComponent->SetParent(0);
	delete pComponent;

}
/******************************************************************************/
/*!
Removes all components of this specific type

\param type
The type of component to remove
*/
/******************************************************************************/
void M5Object::RemoveAllComponents(M5ComponentTypes type)
{
	size_t size = m_components.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (m_components[i]->GetType() == type)
		{
			delete m_components[i];
			m_components[i] = m_components[size - 1];
			m_components.pop_back();
		}
	}
}
/******************************************************************************/
/*!
Returns the type of Component.
*/
/******************************************************************************/
M5ArcheTypes M5Object::GetType(void) const
{
	return m_type;
}