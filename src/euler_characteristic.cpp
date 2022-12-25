#include "euler_characteristic.h"
#include "edges.h"
#include <unordered_set>

int GetVertexCount(const Eigen::MatrixXi& F)
{
    std::unordered_set<int> vertexIndexSet;

    for (int faceIndex = 0; faceIndex < F.rows(); ++ faceIndex) {
        for (int i = 0; i < 3; ++ i) {
            int vertexIndex = F(faceIndex, i);
            vertexIndexSet.insert(vertexIndex);
        }
    }
    return vertexIndexSet.size();
}


int euler_characteristic(const Eigen::MatrixXi &F)
{
    int vertexCount = GetVertexCount(F);
    auto E = edges(F);
    int edgeCount = E.rows();

    int chi = vertexCount - edgeCount + F.rows();
    return chi;
}


