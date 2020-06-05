#include "Updating.h"
#include <vector>

namespace Updating {

	std::unordered_set<Updator*> updators;

	void Update()
	{
		std::vector<Updator*> finishedUpdators;
		for (auto updator : updators) {
			updator->Call();
			if (updator->is_done) {
				finishedUpdators.push_back(updator);
			}
		}
		for (auto updator : finishedUpdators) {
			updators.erase(updator);
		}
	}
}