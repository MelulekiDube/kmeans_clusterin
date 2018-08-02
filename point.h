/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   point.h
 * Author: dube_
 *
 * Created on 26 July 2018, 11:05 PM
 */

#ifndef POINT_H
#define POINT_H

#include <vector>

namespace DBXMEL004 {
    class cluster;

    class point {
    public:

        point();

        point(int pn);
         
        point(double x, double y);
        point(int pn, double x, double y);
        point(const point& orig);
        point(point&& orig);
        point& operator= (const point& rhs);
        point& operator= (point&& rhs);
        double get_xlocation();
        double get_ylocation();
        int get_pointnumber();
        double distance_to(const DBXMEL004::point& rhs);
        void recompute_clusters(std::vector<DBXMEL004::cluster*> cluster_centroids);
        void print_cordinates();
        bool operator==(const point& rhs) const;
        ~point();
    private:
        int point_number;
        double x_location, y_location;        
        DBXMEL004::cluster* belongs_to;
    };

    class cluster {
    public:
        cluster();
        
        cluster(int cn, DBXMEL004::point& c);
        cluster(const cluster& orig);
        void add_point(const DBXMEL004::point& rhs);
        void remove_point(const DBXMEL004::point& rhs);
        void recompute_centroid();
        bool constant_centroid();
        int get_clusternumber();
        DBXMEL004::point& get_centroid();
        std::vector<DBXMEL004::point>& get_points();
        ~cluster();
        std::vector<DBXMEL004::point> points;
    private:
        int cluster_number;
        DBXMEL004::point centroid;
        DBXMEL004::point previous_centroid;
    };
};
#endif /* POINT_H */

