#pragma once

#include <cstddef>
#include <cstdint>

template <size_t I, size_t G>
struct GenericHandle {
	uint32_t index : I;
	uint32_t generation : G;
};
