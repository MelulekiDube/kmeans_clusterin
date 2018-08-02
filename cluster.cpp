/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cluster.cpp
 * Author: dube_
 * 
 * Created on 27 July 2018, 7:56 PM
 */
#include <iostream>
#include "point.h"
using namespace DBXMEL004;
using namespace std;

cluster::cluster() : cluster_number(0) {
}

cluster::cluster(const cluster& orig) {
}

cluster::~cluster() {
}

cluster::cluster(int cn, DBXMEL004::point& c) : cluster_number(cn), centroid(c), points(0) {
}

std::vector<DBXMEL004::point>& cluster::get_points() {
    return this->points;
}

int cluster::get_clusternumber() {
    return cluster_number;
}

void cluster::add_point(const point& rhs) {
    points.push_back(rhs);
}

void cluster::remove_point(const point& rhs) {
    vector<point>::iterator it = points.begin();
    for(int i =0; i < points.size(); ++i){
        if (points[i] == rhs) {
            points.erase(it+i);
            return;
        }
        ++it;
    }
}

bool cluster::constant_centroid() {
    return (previous_centroid == centroid);
}

void cluster::recompute_centroid() {
    double x_temp =0, y_temp=0;
    int counter = 0;
    for(point p: points){
        x_temp += p.get_xlocation();
        y_temp += p.get_ylocation();
        ++counter;
    }
    point temp((x_temp/counter), (y_temp/counter));
    previous_centroid = move(centroid);
    centroid =temp;
}

point& cluster::get_centroid() {
    return this->centroid;
}