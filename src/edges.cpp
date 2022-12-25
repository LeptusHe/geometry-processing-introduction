#include "edges.h"
#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <iostream>

#define ENABLE_DEBUG 0

using edge = std::pair<int, int>;

std::uint64_t EncodeEdge(int v0, int v1)
{
    std::uint64_t lhs = std::min(v0, v1);
    std::uint64_t rhs = std::max(v0, v1);
    std::uint64_t encode = (lhs << 32) + rhs;

    return encode;
}

Eigen::MatrixXi edges(const Eigen::MatrixXi &F)
{
    std::unordered_map<uint64_t, edge> set;

    std::vector<std::pair<int, int>> edges;
    for (int faceIndex = 0; faceIndex < F.rows(); ++ faceIndex) {
        for (int i = 0; i < 3; ++ i) {
            int lhs = F(faceIndex, (i + 0) % 3);
            int rhs = F(faceIndex, (i + 1) % 3);

            if ((std::min(lhs, rhs) == 1060) &&
                (std::max(lhs, rhs) == 1077)) {
                int a = 1;
            }

            uint64_t edge = EncodeEdge(lhs, rhs);
            if (set.find(edge) == std::end(set)) {
                edges.push_back(std::make_pair(lhs, rhs));
                set[edge] = std::make_pair(lhs, rhs);
            } else {
#if ENABLE_DEBUG
                const auto& val = set[edge];
                EncodeEdge(val.first, val.second);
                std::cout << "duplicate edge: "
                    << "old: " << val.first << ", " << val.second
                    << ", new: " << lhs << ", " << rhs << std::endl;
#endif
            }
        }
    }

    int edgeCnt = edges.size();
    Eigen::MatrixXi E(edgeCnt, 2);
    for (int i = 0; i < edgeCnt; ++ i) {
        const auto& edge = edges[i];

        int v0 = edge.first;
        int v1 = edge.second;

        E(i, 0) = v0;
        E(i, 1) = v1;
    }

    return E;
}
