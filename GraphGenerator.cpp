#include "GraphGenerator.h"

std::vector<std::vector<std::pair<long long, long long>>> GraphGenerator::randomGraph_V(long long num_of_nodes)
{
    ValueGenerator generator(num_of_nodes);

    return randomGraph_(num_of_nodes, generator.getNumOfEdges(num_of_nodes - 1, std::min(num_of_nodes * (num_of_nodes - 1), num_of_nodes * 3)));
}

std::vector<std::vector<std::pair<long long, long long>>> GraphGenerator::randomGraph_V15(long long num_of_nodes)
{
    ValueGenerator generator(num_of_nodes);

    long long num_of_edges = (long double)(num_of_nodes * num_of_nodes * num_of_nodes) / (num_of_nodes * num_of_nodes);

    return randomGraph_(num_of_nodes, generator.getNumOfEdges(std::max(num_of_nodes - 1, num_of_edges / 3), std::min(num_of_nodes * (num_of_nodes - 1), num_of_edges * 3)));
}

std::vector<std::vector<std::pair<long long, long long>>> GraphGenerator::randomGraph_V2(long long num_of_nodes)
{
    ValueGenerator generator(num_of_nodes);
    
    long long num_of_edges = num_of_nodes * num_of_nodes;

    return randomGraph_(num_of_nodes, generator.getNumOfEdges(std::max(num_of_nodes - 1, num_of_edges / 3), num_of_nodes * (num_of_nodes - 1)));
}

std::vector<std::vector<std::pair<long long, long long>>> GraphGenerator::levitWorstCase(long long num_of_nodes)
{
    Graph graph(num_of_nodes);

    graph[0].emplace_back(std::make_pair(num_of_nodes - 1, 0));
    graph[num_of_nodes - 1].emplace_back(std::make_pair(0, 0));

    for (long long i = num_of_nodes - 2; i > 0; --i)
    {
        graph[i].emplace_back(std::make_pair(0, graph[0][graph[0].size() - 1].second + i - 1));
        graph[0].emplace_back(std::make_pair(i, graph[0][graph[0].size() - 1].second + i - 1));
    }

    for (long long i = 1; i < num_of_nodes; ++i)
    {
        for (long long j = i + 1; j < num_of_nodes; ++j)
        {
            graph[i].emplace_back(std::make_pair(j, j - i - 1));
            graph[j].emplace_back(std::make_pair(i, j - i - 1));
        }
    }

    return graph;
}

long long getDistance(std::pair<long long, long long> node_1, std::pair<long long, long long> node_2)
{
    return std::abs(node_1.first - node_2.first) + std::abs(node_1.second - node_2.second);
}

std::vector<std::vector<std::pair<long long, long long>>> GraphGenerator::randomGraph_cityBlockDistance(long long num_of_nodes)
{

    ValueGenerator generator(num_of_nodes);

    std::vector<std::pair<long long, long long>> nodes(num_of_nodes);

    for (auto& node : nodes)
    {
        node = std::make_pair(generator.getEdgeValue(), generator.getEdgeValue());
    }

    Graph graph(num_of_nodes);

    for (long long i = 1; i < num_of_nodes; ++i)
    {
        long long node_id = generator.getNodeId(i - 1);
        graph[node_id].emplace_back(std::make_pair(i, getDistance(nodes[node_id], nodes[i])));
    }

    long long num_of_edges = (long double)(num_of_nodes * num_of_nodes * num_of_nodes) / (num_of_nodes * num_of_nodes);
    num_of_edges = generator.getNumOfEdges(std::max(num_of_nodes - 1, num_of_edges / 3), std::min(num_of_nodes * (num_of_nodes - 1), num_of_edges * 3)) - num_of_nodes + 1;

    while(num_of_edges)
    {
        long long node_1 = generator.getNodeId();
        long long node_2 = generator.getNodeId();
        if (node_1 == node_2)
        {
            continue;
        }
        graph[node_1].emplace_back(std::make_pair(node_2, getDistance(nodes[node_1], nodes[node_2])));
        --num_of_edges;
    }

    return graph;
}

std::vector<std::vector<std::pair<long long, long long>>> GraphGenerator::randomTree_(long long num_of_nodes)
{
    ValueGenerator generator(num_of_nodes);

    Graph graph(num_of_nodes);

    for (long long i = 1; i < num_of_nodes; ++i)
    {
        graph[generator.getNodeId(i - 1)].emplace_back(std::make_pair(i, generator.getEdgeValue()));
    }

    return graph;
}

std::vector<std::vector<std::pair<long long, long long>>> GraphGenerator::randomGraph_(long long num_of_nodes, long long num_of_edges)
{
    ValueGenerator generator(num_of_nodes);
    Graph graph = randomTree_(num_of_nodes);
    num_of_edges -= num_of_nodes - 1;
    
    while (num_of_edges)
    {
        long long node_1 = generator.getNodeId();
        long long node_2 = generator.getNodeId();
        if (node_1 == node_2)
        {
            continue;
        }
        graph[node_1].emplace_back(std::make_pair(node_2, generator.getEdgeValue()));
        --num_of_edges;
    }

    return graph;
}

GraphGenerator::ValueGenerator::ValueGenerator(long long num_of_nodes): num_of_nodes(num_of_nodes), generator(rd()), edge_value(0, 100000), node_id(0, num_of_nodes - 1)
{
}

long long GraphGenerator::ValueGenerator::getNodeId()
{
    return node_id(generator);
}

long long GraphGenerator::ValueGenerator::getNodeId(long long max_id)
{
    return std::uniform_int_distribution<>{0, (int)max_id}(generator);
}

long long GraphGenerator::ValueGenerator::getEdgeValue()
{
    return edge_value(generator);
}

long long GraphGenerator::ValueGenerator::getNumOfEdges(long long min_num_of_edges, long long max_num_of_edges)
{
    return std::uniform_int_distribution<>{(int)min_num_of_edges, (int)max_num_of_edges}(generator);
}
