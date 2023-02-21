#include "Levit.h"

std::vector<int> Levit::count(const std::vector<std::vector<std::pair<int, int>>>& graph, int start_node)
{
    int n = graph.size();
    std::vector<int> lengths(n);
    std::unordered_set<int> M0, M2;
    std::queue<int> M1, M1e;

    lengths[start_node] = 0;
    M1e.push(start_node);
    for (int i = 0; i < n; ++i)
    {
        if (i == start_node)
        {
            continue;
        }
        lengths[i] = INT_MAX;
        M2.insert(i);
    }

    while (!M1.empty() || !M1e.empty())
    {
        int node;
        if (!M1e.empty())
        {
            node = M1e.front();
            M1e.pop();
        }
        else
        {
            node = M1.front();
            M1.pop();
        }
        for (auto& i : graph[node])
        {
            if (M2.find(i.first) != M2.end())
            {
                M2.erase(i.first);
                M1.push(i.first);
                lengths[i.first] = lengths[node] + i.second;
            }
            else if (M0.find(i.first) != M0.end())
            {
                if (lengths[i.first] > lengths[node] + i.second)
                {
                    lengths[i.first] = lengths[node] + i.second;
                    M0.erase(i.first);
                    M1e.push(i.first);
                }
            }
            else
            {
                lengths[i.first] = std::min(lengths[i.first], lengths[node] + i.second);
            }
        }
        M0.insert(node);
    }
    
    return lengths;
}
