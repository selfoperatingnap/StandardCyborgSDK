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
    math::Vec3 centerPoint;
};

bool compareBySize(const Cluster& a, const Cluster& b) {
    return a.indexes.size() > b.indexes.size();
}

bool compareByDistance(const Cluster& a, const Cluster& b) {
    return pow(a.centerPoint.x, 2) + pow(a.centerPoint.y, 2) + pow(a.centerPoint.z, 2) < pow(b.centerPoint.x, 2) + pow(b.centerPoint.y, 2) + pow(b.centerPoint.z, 2);
}

#endif /* Cluster_hpp */
