//
//  DBSCAN.hpp
//  StandardCyborgSDK
//
//  Created by Jacob Roscoe on 9/22/23.
//  Copyright © 2023 Standard Cyborg. All rights reserved.
//

#ifndef DBSCAN_hpp
#define DBSCAN_hpp

#include <vector>
#include <cmath>

#define UNCLASSIFIED -1
#define NOISE -2
#define SUCCESS 0
#define FAILURE -3

using namespace std;

struct Point3D
{
    float x, y, z;  // X, Y, Z position
    int clusterID;  // clustered ID
};

class DBSCAN {
public:
    DBSCAN(unsigned int minPts, float eps, vector<Point3D> points){
        m_minPoints = minPts;
        m_epsilon = eps;
        m_points = points;
        m_pointSize = points.size();
    }
    ~DBSCAN(){}

    int run();
    vector<int> calculateCluster(Point3D point);
    int expandCluster(Point3D point, int clusterID);
    inline double calculateDistance(const Point3D& pointCore, const Point3D& pointTarget);

    size_t getTotalPointSize() {return m_pointSize;}
    int getMinimumClusterSize() {return m_minPoints;}
    int getEpsilonSize() {return m_epsilon;}
    vector<int> getCorePointIndexes();

public:
    vector<Point3D> m_points;

private:
    size_t m_pointSize;
    unsigned int m_minPoints;
    float m_epsilon;
};

#endif /* DBSCAN_hpp */
