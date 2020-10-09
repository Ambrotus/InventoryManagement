#include "Task.h"
using namespace std;

Task::Task(const string input) : Task::Item(input), m_pNextTask(nullptr) {}

void Task::runProcess(ostream& os) {
	/*runs a single cycle of the assembly line for the current task.
		If there are CustomerOrders in the queue, it will verify the fill status of the last CustomerOrder
		and fill it if the order contains the Item specified by the current Task.*/

	// it's a queue, where the last one on the pile, is the first one out. Like a pez dispenser
	//http://www.cplusplus.com/reference/deque/deque/back/
	if (!m_orders.empty() && !m_orders.back().getOrderFillState()) 
		m_orders.back().fillItem(*this, os);
}

bool Task::moveTask() {
	/*moves the last CustomerOrder in the queue to the next task on the assembly line 
	if the orders fill state for the current Item is true.
	Otherwise, the CustomerOrder should remain in the queue for the next processing cycle.
	If the queue is empty, return false.*/
	bool itemsReady = false;
	if (!m_orders.empty() && m_orders.back().getItemFillState(getName()) && m_pNextTask != nullptr) {
		
		//might change this to setNextTask() if it does the same?
		*m_pNextTask += move(m_orders.back()); //move casts it to a xval to be accepted by our += who wants a rval defined below
		
		m_orders.pop_back();
		itemsReady = true;
		
	}
	return itemsReady;
}

void Task::setNextTask(Task& obj) {
	//stores the provided Task object's reference into the m_pNextTask pointer
	m_pNextTask = &obj;
}

bool Task::getCompleted(CustomerOrder& obj) {
	/*Removes the last CustomerOrder from the queue, 
	places it in the parameter and returns true.
	If the CustomerOrder queue is empty, return false.*/
	bool temp = false;
	if (!m_orders.empty() && m_orders.back().getOrderFillState()) {
		obj = move(m_orders.back());
		m_orders.pop_back();
		temp = true;
	}
	return temp;
}

void Task::validate(std::ostream& os) {
	/*writes the name of the Item this Task is responsible for into the parameter : 
	ITEM_NAME-- > NEXT_ITEM_NAME
	if m_pNextTask does not exist it writes : ITEM_NAME-- > END OF LINE.
	the messages are terminated with an endline*/
	if (m_pNextTask != nullptr) os << getName() << " --> " << m_pNextTask->getName();
	else os << getName() << " --> " << "END OF LINE";
	os << endl;
}

Task& Task::operator+=(CustomerOrder&& obj) {
	//Moves the parameter onto the front of the CustomerOrder queue.
	m_orders.push_front(move(obj));
	return *this;
}

