#ifndef task_H
#define task_H
#include <deque>
#include "CustomerOrder.h"

using namespace std;

class Task :public Item{
	//m_orders – is a double ended queue with new CustomerOrders coming in one side and exiting out the other once filled.
	deque<CustomerOrder> m_orders;
	//m_pNextTask – a pointer to the next task on the assembly line
	Task* m_pNextTask;

public:
	//string contains a single record (one line) that has been retrieved from the input file specified by the user to be used for Item instantiation. 
	Task(const string input);
	
	//a Task object cannot be copied or moved. You must make sure this capability has been deleted from your Task definition.
	Task& operator= (const Task& obj) = delete; //instantly default to delete when called 
	Task(const Task&) = delete; //copy constructor
	Task(const Task&&) = delete;// move constructor
	Task& operator= (const Task&&) = delete;

	//runs a single cycle of the assembly line for the current task. 
	void runProcess(ostream&);
	
	//moves the last CustomerOrder in the queue to the next task on the assembly line if the orders fill state for the current Item is true
	//Otherwise, the CustomerOrder should remain in the queue for the next processing cycle. If the queue is empty, return false
	bool moveTask();

	//stores the provided Task object's reference into the m_pNextTask pointer.
	void setNextTask(Task&);

	//Removes the last CustomerOrder from the queue, places it in the parameter and returns true. If the CustomerOrder queue is empty, return false.
	bool getCompleted(CustomerOrder&);

	//writes the name of the Item this Task is responsible for into the parameter: ITEM_NAME --> NEXT_ITEM_NAME
	void validate(std::ostream&);

	//Moves the parameter onto the front of the CustomerOrder queue
	Task& operator+=(CustomerOrder&&);


};


#endif // !task_H

