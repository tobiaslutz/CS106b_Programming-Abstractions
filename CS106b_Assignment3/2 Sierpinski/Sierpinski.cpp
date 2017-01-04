/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
using namespace std;
const double SIN_60_DEG = 0.8660;
void drawSierpinski(GWindow gw, int ord, int finOrd, double len, double hei, double cx, double cy);

int main() {
    GWindow gw;
    int edgeL = getInteger("Edge Lenght ? ");
    int finalOrder = getInteger("Order ? ");
    
    double xC = gw.getWidth() / 2;
    double yC = gw.getHeight() / 2;
    double h = edgeL * SIN_60_DEG;
    
    gw.drawPolarLine(xC - (edgeL / 2), yC + (h / 2), edgeL, 60);
    gw.drawPolarLine(xC - (edgeL / 2), yC + (h / 2), edgeL, 0);
    gw.drawPolarLine(xC + (edgeL / 2), yC + (h / 2), edgeL, 120);
    
    if(finalOrder > 0)
        drawSierpinski(gw, 1, finalOrder, edgeL / 2, h / 2, xC, yC);
    return 0;
}

void drawSierpinski(GWindow gw, int ord, int finOrd, double len, double hei, double cx, double cy)    {
    gw.drawPolarLine(cx, cy + hei, len, 120);
    gw.drawPolarLine(cx, cy + hei, len, 60);
    gw.drawPolarLine(cx - (len / 2), cy, len, 0);
    
    double cx1 = cx;
    double cy1 = cy - (hei / 2);
    
    double cx2 = cx + (len / 2);
    double cy2 = cy + (hei / 2);
    
    double cx3 = cx - (len / 2);
    double cy3 = cy + (hei / 2);
    
    if(ord < finOrd)   {
        drawSierpinski(gw, ord + 1, finOrd, len / 2, hei / 2, cx3, cy3);
        drawSierpinski(gw, ord + 1, finOrd, len / 2, hei / 2, cx1, cy1);
        drawSierpinski(gw, ord + 1, finOrd, len / 2, hei / 2, cx2, cy2);
    }
    
}
