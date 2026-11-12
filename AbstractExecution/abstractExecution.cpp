
#include "abstractExecution.hpp"

#include <vector>
	
void abstract_execution_engine::run(Instruction* entry) {
	// Use a worklist method to run the analysis.
	std::vector<Instruction*> worklist;

	worklist.push_back(entry);

	if (!current_state) {
		current_state = initializeAbstractState();
	}

	while (!worklist.empty()) {
		// Get the first item in the worklist.
		Instruction* next = worklist[0];
		worklist.erase(worklist.begin()); // dequeue.

		ExecuteStatement(next, *current_state);

		// TODO address conditionals, loops, merge points in code.
		while (Instruction* work = GetNextExecutionUnit()) {
			worklist.push_back(work);
		}
	}
}
