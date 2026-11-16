
#include "abstractExecution.hpp"

#include <vector>
	
void abstract_execution_engine::run(Instruction* entry) {
	// Use a worklist method to run the analysis.
	std::vector<std::pair<Instruction*, abstract_state*>> worklist;

	if (!current_state) {
		current_state = initializeAbstractState();
	}
	worklist.push_back(std::make_pair(entry, current_state));

	while (!worklist.empty()) {
		// Get the first item in the worklist.
		auto next = worklist[0];
		auto* inst = next.first;
		auto* state = next.second;
		worklist.erase(worklist.begin()); // dequeue.

		ExecuteStatement(inst, *state);

		// TODO address merge points in code.
		while (true) {
			auto work = GetNextExecutionUnit();
			if (work.first == nullptr) {break;}
			worklist.push_back(work);
		}
	}
}
