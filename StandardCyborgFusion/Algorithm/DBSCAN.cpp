//
//  DBSCAN.cpp
//  StandardCyborgSDK
//
//  Created by Jacob Roscoe on 9/22/23.
//  Copyright © 2023 Standard Cyborg. All rights reserved.
//

#include "DBSCAN.hpp"
#include <map>
#include <string>

int DBSCAN::run()
{
    int clusterID = 1;
    vector<Point3D>::iterator iter;
    for(iter = m_points.begin(); iter != m_points.end(); ++iter)
        {
        if ( iter->clusterID == UNCLASSIFIED )
            {
            if ( expandCluster(*iter, clusterID) != FAILURE )
                {
                clusterID += 1;
                }
            }
        }
    return 0;
}

int DBSCAN::expandCluster(Point3D point, int clusterID)
{
    vector<int> clusterSeeds = calculateCluster(point);

    if ( clusterSeeds.size() < m_minPoints )
        {
        point.clusterID = NOISE;
        return FAILURE;
        }
    else
        {
        int index = 0, indexCorePoint = 0;
        vector<int>::iterator iterSeeds;
        for( iterSeeds = clusterSeeds.begin(); iterSeeds != clusterSeeds.end(); ++iterSeeds)
            {
            m_points.at(*iterSeeds).clusterID = clusterID;
            if (m_points.at(*iterSeeds).x == point.x && m_points.at(*iterSeeds).y == point.y && m_points.at(*iterSeeds).z == point.z )
                {
                indexCorePoint = index;
                }
            ++index;
            }
        clusterSeeds.erase(clusterSeeds.begin()+indexCorePoint);

        for( vector<int>::size_type i = 0, n = clusterSeeds.size(); i < n; ++i )
            {
            vector<int> clusterNeighors = calculateCluster(m_points.at(clusterSeeds[i]));

            if ( clusterNeighors.size() >= m_minPoints )
                {
                vector<int>::iterator iterNeighors;
                for ( iterNeighors = clusterNeighors.begin(); iterNeighors != clusterNeighors.end(); ++iterNeighors )
                    {
                    if ( m_points.at(*iterNeighors).clusterID == UNCLASSIFIED || m_points.at(*iterNeighors).clusterID == NOISE )
                        {
                        if ( m_points.at(*iterNeighors).clusterID == UNCLASSIFIED )
                            {
                            clusterSeeds.push_back(*iterNeighors);
                            n = clusterSeeds.size();
                            }
                        m_points.at(*iterNeighors).clusterID = clusterID;
                        }
                    }
                }
            }

        return SUCCESS;
        }
}

vector<int> DBSCAN::calculateCluster(Point3D point)
{
    int index = 0;
    vector<Point3D>::iterator iter;
    vector<int> clusterIndex;
    for( iter = m_points.begin(); iter != m_points.end(); ++iter)
        {
        if ( calculateDistance(point, *iter) <= m_epsilon )
            {
            clusterIndex.push_back(index);
            }
        index++;
        }
    return clusterIndex;
}

vector<int> DBSCAN::getCorePointIndexes()
{
    // Create a map to group objects by the 'clusterID' property
    std::map<std::string, vector<int>> groupedPointIndexes;

    // Iterate through the array and group objects by 'clusterID'
    for (int i = 0; i < m_pointSize; ++i) {
        Point3D point = m_points[i];
        if (point.clusterID != UNCLASSIFIED && point.clusterID != NOISE) {
            groupedPointIndexes[std::to_string(point.clusterID)].push_back(i);
        }
    }

    if (groupedPointIndexes.size() != 0) {
        string key;
        size_t size = 0;
        // Iterate through the map and get the group with largest size
        for (const auto& pair : groupedPointIndexes) {
            if (pair.second.size() > size) {
                key = pair.first;
                size = pair.second.size();
            }
        }
        return groupedPointIndexes[key];
    } else {
        return vector<int>();
    }
}

inline double DBSCAN::calculateDistance(const Point3D& pointCore, const Point3D& pointTarget )
{
    return sqrt(pow(pointCore.x - pointTarget.x,2)+pow(pointCore.y - pointTarget.y,2)+pow(pointCore.z - pointTarget.z,2));
}

