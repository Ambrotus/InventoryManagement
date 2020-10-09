#ifndef linemanager_H
#define linemanager_H
#include <vector>
#include "Task.h"

using namespace std;
class LineManager {

	vector<Task*> AssemblyLine;			//– A container containing all the references of the Task objects on the assembly line
	deque<CustomerOrder> ToBeFilled;	//– A queue of customer orders to be filled
	deque<CustomerOrder> Completed;		//– A queue of customer orders completed
	unsigned m_cntCustomerOrder;		//– The number of CustomerOrder objects the assembly line started with.
	Task* firstTask;
	Task* lastTask;
public:
	/*reads the records from file and setup all the m_pNextTask references in the Task objects, Linking each Task object together to form the assembly line
	Move all the CustomerOrder objects onto the front of the ToBeFilled queue
	Copy all the Task objects into the AssemblyLine container*/
	LineManager(const string filename, vector <Task*> &tasks, vector <CustomerOrder> &custOrders);
	//LineManager(const string fileName, std::vector<Task*>& tasks, std::vector<CustomerOrder>& ToFill);
	//this function performs one cycle of operations on the assembly line
	bool run(ostream& os);
	//displays all the orders that were completed
	void displayCompleted(ostream&) const;
	//validates each task on the assembly line
	void validateTasks() const;
};

#endif // !linemanager_H
