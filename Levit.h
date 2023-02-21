#pragma once
#include <vector>
#include <unordered_set>
#include <queue>

class Levit
{
public:
	static std::vector<long long> count(const std::vector<std::vector<std::pair<long long, long long>>>& graph, long long start_node = 0);
};

