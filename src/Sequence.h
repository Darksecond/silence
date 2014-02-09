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
	int getPosition() const;
	float getValue() const;
};
