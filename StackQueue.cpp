// StackQueues.cpp : Defines the exported functions for the DLL application.
//

#include "StackQueue.h"

ArrayBasedStack::ArrayBasedStack(void)
{
	
}
ArrayBasedStack::~ArrayBasedStack() 
{
	
}
bool ArrayBasedStack::isEmpty() const
{
	if (m_count == 0){
		return true;
	}else{
		return false;
	}
	
}

bool ArrayBasedStack::push(const int & val)
{
	if (m_count >= 4){
		return false;
	}else{
		stack[arrayval] = val;
		m_count++;
		arrayval++;
		return true;
		
	}
}

bool ArrayBasedStack::pop()
{
	if (m_count == 0){
		return false;
	}else{
		poppedVal = stack[arrayval - 1];
		stack[arrayval] = 0;
		arrayval--;
		m_count--;
		return true;
	}
}


int ArrayBasedStack::peek() const
{
	if (this->isEmpty())
	{
		throw "ADT is emtpy";
	}
	else
	{
		return stack[arrayval - 1];
	}


}
int ArrayBasedStack::get(int index) const{
	return stack[index - 1];
}
int ArrayBasedStack::size(){
	return m_count;
}
std::string ArrayBasedStack::toString() const
{
	//TODO
	return "";
}


ArrayBasedQueue::ArrayBasedQueue(void)
{

}
ArrayBasedQueue::~ArrayBasedQueue()
{

}
bool ArrayBasedQueue::isEmpty() const
{
	if (q_count == 0){
		return true;
	}else{
		return false;
	}
}

bool ArrayBasedQueue::enQueue(const std::string & val)
{
	if (q_count > 99){
		return false;
	}else{
		queue[q_count] = val;
		q_count++;
		return true;
	}
}

bool ArrayBasedQueue::deQueue()
{
	if (q_count == 0){
		return false;
	}else{
		for(int i = 0; i < q_count; i++){
			queue[i] = queue[i+1];
		}
		q_count--;
		return true;
	}
}
std::string ArrayBasedQueue::peek() const
{
	if (this->isEmpty())
	{
		throw "ADT is emtpy";
	}
	else
	{
		return queue[0];
	}


}

std::string ArrayBasedQueue::toString() const
{
	//TODO
	return "hi";

}
