/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   point.cpp
 * Author: dube_
 * 
 * Created on 27 July 2018, 2:39 PM
 */

#include <cmath>
#include <ctgmath>
#include <limits>
#include <iostream>

#include "point.h"
using namespace DBXMEL004;
using namespace std;

point::point(double x, double y) : x_location(x), y_location(y), belongs_to(nullptr) {
}

point::point(int pn, double x, double y) : point_number(pn), x_location(x), y_location(y), belongs_to(nullptr) {
}

point::point(const point& orig) : point_number(orig.point_number), x_location(orig.x_location), y_location(orig.y_location), belongs_to(orig.belongs_to) {
}

point::point(point&& orig)
: point_number(move(orig.point_number)), x_location(move(orig.x_location)), y_location(move(orig.y_location)), belongs_to((move(orig.belongs_to))) {

}

point& point::operator=(const point& rhs) {
    this->x_location = rhs.x_location;
    this->y_location = rhs.y_location;
    this->point_number = rhs.point_number;
    this->belongs_to = rhs.belongs_to;
    return *this;
}

point& point::operator= (point&& rhs){
    this->x_location = move(rhs.x_location);
    this->y_location = move(rhs.y_location);
    this->point_number = move(rhs.point_number);
    this->belongs_to = move(rhs.belongs_to);
    return *this;
}

point::point(int pn) : point_number(pn), x_location(0), y_location(0), belongs_to(nullptr) {
}

point::point() : belongs_to(nullptr) {
}

point::~point() {
}

int point::get_pointnumber() {
    return point_number;
}

double point::get_xlocation() {
    return x_location;
}

double point::get_ylocation() {
    return y_location;
}

/**
 * Method to calculate the distance between two points
 * @param rhs
 * @return 
 */
double point::distance_to(const point& rhs) {
    double x_diff = rhs.x_location - x_location;
    double y_diff = rhs.y_location - y_location;
    return sqrt(double(pow(x_diff, 2)) + double(pow(y_diff, 2)));
}

/**
 * Method to calculate which cluster a certain point belongs to
 * 
 * @param cluster_centroids
 */
void point::recompute_clusters(vector<cluster*> cluster_centroids) {
    double min_distance = std::numeric_limits<double>::max();
    for (cluster *c : cluster_centroids) {
        double temp = distance_to(c->get_centroid());
        if (temp < min_distance) {
            //remove the point from the initial cluster
            if (this->belongs_to != 0) {
                this->belongs_to->remove_point(*(this));
            }
            // change the cluster that the point belongs to
            this->belongs_to = c;
            this->belongs_to->add_point(*this); // and this point to the new cluster that is belongs to.   
            min_distance = temp; // change the the current distance to be the mean distance
        }
    }
}

bool point::operator==(const point& rhs) const {
    return ((rhs.point_number == this->point_number)&&(rhs.belongs_to == this->belongs_to)
            &&(rhs.x_location == this->x_location)&& (rhs.y_location == this->y_location));
}

void point::print_cordinates() {
    std::cout << "x: " << x_location;
    std::cout << " y: " << y_location << endl;

}
