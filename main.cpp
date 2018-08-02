/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dube_
 *
 * Created on 27 July 2018, 6:45 PM
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <ios>
#include <istream>
#include <iostream>
#include <fstream>


#include "point.h"
using namespace std;
using namespace DBXMEL004;
/*
 * 
 */
string point_filename;
string cluster_filename;
string output_filename;
vector<point> points;
vector<cluster*> clusters;
cluster c1, c2, c3;
void initialize_points();
void initilize_cluster();
void assign_clusters();
void compute_centroid();
void print_items(ofstream& out);
void execute();
bool should_stop();
void get_points_filename();
void get_cluster_filename();
bool process_input(string identifier, string filename);
string format("\t: \"kmeans -p <point filename> -o <outputfile>\"");

int main(int argc, char** argv) {
    int i;
    if (argc == 5) {
        if (process_input(argv[1], argv[2]) && process_input(argv[3], argv[4])) {
            execute();
            i = 0;
        } else {
            cout << "something is wrong with one of the inputs" << endl;
            i = 1;
        }
    } else {
        cout << "Wrong input format please start the application again as follows:" << endl;
        cout << format << endl;
        i = 1;
    }
    return i;
}

bool process_input(string identifier, string filename) {
    if (identifier == "-p") {
        point_filename = filename;
    } else if (identifier == "-o") {
        output_filename = filename;
    } else {
        return false;
    }
    return true;
}

void initialize_points() {
    ifstream input(point_filename);
    int i = 1;
    int x_temp, y_temp;
    while (input >> x_temp >> y_temp) {
        point temp(i++, x_temp, y_temp);
        points.push_back(temp);
    }
    input.close();
}

bool should_stop() {
    for (cluster *c : clusters) {
        if (!c->constant_centroid()) {
            return false;
        }
    }
    return true;
}

void initilize_cluster() {
    cluster temp1(1, points[1 - 1]);
    cluster temp2(2, points[4 - 1]);
    cluster temp3(3, points[7 - 1]);
    ::c1 = temp1;
    ::c2 = temp2;
    ::c3 = temp3;
    clusters.push_back(&c1);
    clusters.push_back(&c2);
    clusters.push_back(&c3);
}

void assign_clusters() {
    for (int i = 0; i < points.size(); ++i) {
        points[i].recompute_clusters(clusters);
    }
}

void print_items(ofstream& out) {
    for (int i = 0; i < clusters.size(); ++i) {
        clusters[i]->recompute_centroid();
        out << "Cluster " << clusters[i]->get_clusternumber() << ": ";
        for (int j = 0; j < ((*clusters[i]).get_points()).size(); ++j) {
            if (j != 0) {
                out << ", ";
            }
            out << ((*clusters[i]).get_points())[j].get_pointnumber();
        }
        out << endl;
        out << "Centroid: (" << clusters[i]->get_centroid().get_xlocation() << ", " << clusters[i]->get_centroid().get_ylocation() << ")" << endl;
    }
}

void execute() {
    int i = 1;
    initialize_points();
    initilize_cluster();
    ofstream output_fle(output_filename);
    while (!should_stop()) {
        output_fle << "Iteration " << i++ << "\n";
        assign_clusters();
        print_items(output_fle);
        output_fle << "\n";
    }
    output_fle.close();
}