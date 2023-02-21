#pragma once
#include <vector>
#include <random>

class GraphGenerator
{
public:

	using Graph = std::vector<std::vector<std::pair<int, int>>>;

	static Graph randomGraph_V(int num_of_nodes);
	static Graph randomGraph_V15(int num_of_nodes);
	static Graph randomGraph_V2(int num_of_nodes);
	static Graph levitWorstCase(int num_of_nodes);
	static Graph randomGraph_cityBlockDistance(int num_of_nodes);

private:

	struct ValueGenerator
	{
		int num_of_nodes;
		std::uniform_int_distribution<> edge_value;
		std::uniform_int_distribution<> node_id;
		std::random_device rd;
		std::mt19937 generator;

		ValueGenerator(int num_of_nodes);

		int getNodeId();
		int getNodeId(int max_id);
		int getEdgeValue();
		int getNumOfEdges(int min_num_of_edges, int max_num_of_edges);
	};

	static Graph randomTree_(int num_of_nodes);
	static Graph randomGraph_(int num_of_nodes, int num_of_edges);
};
