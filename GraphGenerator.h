#pragma once
#include <vector>
#include <random>

class GraphGenerator
{
public:

	using Graph = std::vector<std::vector<std::pair<long long, long long>>>;

	static Graph randomGraph_V(long long num_of_nodes);
	static Graph randomGraph_V15(long long num_of_nodes);
	static Graph randomGraph_V2(long long num_of_nodes);
	static Graph levitWorstCase(long long num_of_nodes);
	static Graph randomGraph_cityBlockDistance(long long num_of_nodes);

private:

	struct ValueGenerator
	{
		long long num_of_nodes;
		std::uniform_int_distribution<> edge_value;
		std::uniform_int_distribution<> node_id;
		std::random_device rd;
		std::mt19937 generator;

		ValueGenerator(long long num_of_nodes);

		long long getNodeId();
		long long getNodeId(long long max_id);
		long long getEdgeValue();
		long long getNumOfEdges(long long min_num_of_edges, long long max_num_of_edges);
	};

	static Graph randomTree_(long long num_of_nodes);
	static Graph randomGraph_(long long num_of_nodes, long long num_of_edges);
};
