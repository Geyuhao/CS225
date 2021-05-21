#include <iostream>
#include <fstream>
#include "8_dbscan.h"


void readBenchmarkData(vector<DISTANCE>& points)
{
    // load point cloud
    FILE *stream;
    stream = fopen ("data.dat","ra");

    unsigned int minpts, num_points, cluster, i = 0;
    double epsilon;
    fscanf(stream, "%u\n", &num_points);

    DISTANCE *p = (DISTANCE *)calloc(num_points, sizeof(DISTANCE));

    while (i < num_points)
    {
          fscanf(stream, "%d,%f,%f,%d,%d\n", &(p[i].id),&(p[i].x), &(p[i].y), &(p[i].treatment_type), &cluster);
          p[i].id = i;
          p[i].z = 0;
          p[i].clusterID = UNCLASSIFIED;
          points.push_back(p[i]);
          ++i;
    }

    free(p);
    fclose(stream);
}

void printResults(vector<DISTANCE>& points, int num_points, Cluster** clusters)
{
    int i = 0;
    while (i < num_points)
    {
        People* temp = new People();
        temp->id_number = points[i].id;
        temp->address.first = points[i].x;
        temp->address.second = points[i].y;
        temp->Treatment_Type = points[i].treatment_type;
        Person_BP* P = new Person_BP(temp);
        clusters[temp->Treatment_Type]->insert_people(P);
        ++i;
    }
}