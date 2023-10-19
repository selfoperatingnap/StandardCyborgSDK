//
//  Cluster.hpp
//  StandardCyborgFusion
//
//  Created by Jacob Roscoe on 9/28/23.
//  Copyright © 2023 Standard Cyborg. All rights reserved.
//

#ifndef Cluster_hpp
#define Cluster_hpp

#include <vector>
#include <standard_cyborg/math/Vec3.hpp>

using namespace std;
using namespace standard_cyborg;

struct Cluster {
    vector<int> indexes;
    vector<math::Vec3> pointsAroundCenter;
};

bool compareBySize(const Cluster& a, const Cluster& b) {
    return a.indexes.size() > b.indexes.size();
}

bool compareBySizeOfPointsAroundCenter(const Cluster& a, const Cluster& b) {
    return a.pointsAroundCenter.size() > b.pointsAroundCenter.size();
}

bool compareByDepth(const Cluster& a, const Cluster& b) {
    if (a.pointsAroundCenter.empty()) {
        return false;
    }
    if (b.pointsAroundCenter.empty()) {
        return true;
    }

    // Compare the average depth of up to 10 points closest to the center.
    float averageDepthOfCenterPointsA = 0;
    float averageDepthOfCenterPointsB = 0;

    int countA = 0;
    for (int i = 0; i < a.pointsAroundCenter.size() && i < 10; i++) {
        countA++;
        averageDepthOfCenterPointsA += a.pointsAroundCenter.at(i).z;
    }
    averageDepthOfCenterPointsA /= countA;

    int countB = 0;
    for (int i = 0; i < b.pointsAroundCenter.size() && i < 10; i++) {
        countB++;
        averageDepthOfCenterPointsB += b.pointsAroundCenter.at(i).z;
    }
    averageDepthOfCenterPointsB /= countB;

    return averageDepthOfCenterPointsA < averageDepthOfCenterPointsB;
}

#endif /* Cluster_hpp */
