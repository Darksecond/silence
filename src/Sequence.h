#pragma once
#include <vector>

class Sequence {
	struct Trigger {
		double start;
		float duration;

		inline bool operator<(const Trigger& other) const {
			return start < other.start;
		}
	};

	std::vector<Trigger> _triggers;
public:
	void createTrigger(double start, float duration);

	/**
	 * The amount of triggers that have happend, will be 0 if none have triggered yet.
	 */
	int getPosition() const;

	/**
	 * Get the current value of the sequence.
	 * If two pulses trigger around the same time their 
	 * individual values are added together, with a maximum of 1.0.
	 * In graph form the value would look something like this, over time.
	 * 
	 *        \           \
	 *       | \         | \
	 *       |  \        |  \
	 *       |   \       |   \
	 * ------|    \------|    \------
	 */
	float getValue() const;
};
