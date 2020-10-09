#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
using namespace std;

LineManager::LineManager(const string filename, vector <Task*> &tasks, vector <CustomerOrder> &custOrders) {
	/*read the records from file and setup all the m_pNextTask references in the Task objects, Linking each Task object together to form the assembly line*/
	ifstream file(filename);
	Utilities tu; //tempUtility;
	bool tb; //tempBool
	string str,str1,str2; //temp string
	size_t pos = 0, i = 0;
	vector<Task*> tempArray; 
	
	if (file) {
		while (!file.eof()) {
			pos = 0;
			tb = false;
			getline(file, str);
			str1 = tu.extractToken(str, pos, tb);
			str2 = "";
			if (tb) {
			pos = (str1.length() + 1);
			str2 = tu.extractToken(str, pos, tb);
			} 

			for (Task * x : tasks) {
				if (x->getName() == str1) {
					for (Task* c : tasks) {
						if (c->getName() == str2) {
							x->setNextTask(*c);
							tempArray.push_back(c);
							break;
						}
					}
				}
			}
		}
		file.close();
	} else cout << "Unable to open file"<<endl;
	
	
	/*for (int i = 0; i < tasks.size();i++) {
		if (tempArray[i] != tasks[i]) firstTask = tempArray[i];
	}*/
	//Move all the CustomerOrder objects onto the front of the ToBeFilled queue
	for (unsigned i = 0; i < custOrders.size(); i++) {
		ToBeFilled.push_front(move(custOrders[i]));
	}
	m_cntCustomerOrder = custOrders.size();
	//Copy all the Task objects into the AssemblyLine container
	AssemblyLine = tasks;
	vector <Task*> tempTempArray = tasks;
	i = 0;
	while( tempTempArray.size()>1) {
		//cout << tempTempArray[i]->getName();
		for (unsigned j = 0; j < tempTempArray.size(); j++) {
			if (tempArray[i]->getName() == tempTempArray[j]->getName()) {
				tempTempArray.erase(tempTempArray.begin()+j);
			}

		}
		i++;
	}


	
	firstTask = tempTempArray[0];

	//tempTempArray = tasks;
	//while (tempTempArray.size() > 1) {
	//	//cout << tempTempArray[i]->getName();
	//	for (int j = 0; j < tempTempArray.size(); j++) {
	//		if (tempArray[i]->getName() == tempTempArray[j]->getName()) {
	//			tempTempArray.erase(tempTempArray.begin() + j);
	//		}

	//	}
	//	i++;
	//}

	//cout<< tempArray.back()->getName();
	lastTask = tempArray.back();
	/*vector <Task*> anotherarray;
	anotherarray.push_back(firstTask);
	for (int i = 0; i < tempArray.size(); i++){
		anotherarray.push_back(tempArray[i]);
		cout << anotherarray[i]->getName();
	}*/
}

bool LineManager::run(std::ostream& os) {
	CustomerOrder tmp;
	
	
	if (!(ToBeFilled.empty())) {
	//	for (int i = 0; i < AssemblyLine.size(); i++) if (AssemblyLine[i]->getName() == firstTask->getName()) start = i;
		
		*firstTask += std::move(ToBeFilled.back());
        ToBeFilled.pop_back();
	}
	for (auto task : AssemblyLine) task->runProcess(os);
	

	for (auto task : AssemblyLine)  task->moveTask();
	
	
	if (lastTask->getCompleted(tmp)) Completed.push_back(std::move(tmp));
	

	return Completed.size() == m_cntCustomerOrder;

}

void LineManager::displayCompleted(std::ostream& os) const {
	for (size_t i = 0; i < Completed.size(); i++) Completed[i].display(os);
}

void LineManager::validateTasks() const {
	for (size_t i = 0; i < AssemblyLine.size(); i++)  AssemblyLine[i]->validate(std::cout);
}