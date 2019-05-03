#pragma once
#include<iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
using namespace std;
class Component;//declare Component class
class Entity;// declare Entity class
//sets up ComponentID as an unsigned int
using ComponentID = size_t;
//inline acts a bit like header file, puts the code exactly where we use the function. here it will grab the components Id
inline ComponentID getComponentTypeID() 
{
	static ComponentID lastID = 0;//ID starts at zero
	return lastID++;//increments everytime we get a new ID
}
//inline template w/o exception using typename T and running getComponentID(), returns typeID
template<typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();//generates new lastID and puts it in our typeID
	return typeID;//returns the typeID for the component
}

constexpr size_t maxComponents = 32;//max number of components an entity is able to hold
/*if we need to find out if an entity has got a selection of components, we will be able to compare whether it has it or not.
 via generating a bitset, passing it in, and if it matches the signature of the entity, we know we have all the components we need
*/
using ComponentBitSet = bitset<maxComponents>;
//an array of component pointers the length of our max components
using ComponentArray = array<Component*, maxComponents>;

class Component
{
public:
	//pointer  to its owner
	Entity* entity;
	//using virtual so we can override the functions
	//init can get access to other components
	virtual void init(){}

	virtual void update(){}
	virtual void draw(){}
	virtual ~Component(){}

};

class Entity
{
private:
	//is the entity active "true", if not we can remove it from the game
	bool active = true;
	/*vector to keep a list of all the components the entity is holding. 
	vector is like an array but we dont have the size
	the vector/array will be called components, using a unique_ptr of type Component
	So we ultimately end up with a list of Components called components which we dont need to know..
	the size of thanks to vector...this and previous line are the main point to understand
	*/
	vector<unique_ptr<Component>> components;
	//giving the Entity its array of components called componentArray, holds the entities components
	ComponentArray componentArray;
	/*giving the entity its own ComponentBitSet caleed component BitSet, allows us to check if the entity has a 
	selection of components or not*/
	ComponentBitSet componentBitSet;
public:
	/* We will have the entity loop through all its components and have the entity call its' update and draw
	methods for each of the components*/
	void update()
	{
		//loops through entities components to call update for each component, uses reference named c to reference components
		for (auto& c : components) c->update();	
	}
	//loops through entities components to call draw for each component, uses reference named c to reference components
	void draw() 
	{
		for (auto& c : components) c->draw();
	}
	/* function to see if its active, using const because it won't change*/
	bool isActive() const { return active; }
	/*arms any given component, because our component has a reference to the owner, we can call the entities
	destroy function from there*/
	void destroy() { active = false; }

	/*template using bitset tells us if the entity has the component via true false*/
	template <typename T> bool hasComponent() const
	{
		/*we will generate a bitset and see if it matches the bitset of the entity with the passed componentID*/
		return componentBitSet[getComponentTypeID<T>];
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(forward<TArgs>(mArgs)...));
		c->entity = this;
		unique_ptr<Component> uPtr{ c };
		components.emplace_back(move(uPtr));
		/*so whats happening here, our component array, this is our index,
		we are going to get our type array  = c.. when we add a position component, it will always be put in the same positionn in the array*/
		componentArray[getComponentTypeID<T>()] = c;
		/*set bitset to show it*/
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		//set ptr to the position in our component array
		auto ptr(componentArray[getComponentTypeID<T>()]);

		return *static_cast<T*>(ptr);
	}
	
};

class Manager
{
private:
	/*making a vector array to hold the entities we will be managing*/
	vector<unique_ptr<Entity>> entities;
public:
	//basically for entity e in vector array entities.. update it
	void update()
	{
		for (auto& e : entities) e->update();
	}
	//basically for entity e in vector array entities.. draw it
	void draw()
	{
		for (auto& e : entities) e->draw();
	}
	//every frame move through our entities and remove the ones that aren't there(no longer active)
	void refresh()
	{
		entities.erase(remove_if(begin(entities), end(entities),
			[](const unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			end(entities));
	}
	//add entity to the world through manager class
	Entity& addEntity()
	{
		//Entity type pointer to a new Entity object
		Entity* e = new Entity();
		//create unique pointer of type entity and initialize it to the Entity pointer e
		unique_ptr<Entity> uPtr{ e };
		//appends the value of uPtr to the end of the container or in this case the vector array entities
		entities.emplace_back(move(uPtr));
		//return e ptr to finish adding the entity
		return *e;
	}
};




