#include <cmath>
#include <vector>
#include <ctime>

#pragma once

/**
 *  A simple mutation function
 * 
 * @param x the input value
 * 
 * returns x plus a range betwenn 0f and 0.5f
 */ 
double mutate(double x);

/// Generates a random number between (0,1) include 0 and 1
double randomZero_One();

/**
*  Map a value in a range in other range
* 
*  @param value the value to remap
*  @param low1 the lower value of current scale
*  @param high1 the higher value of current scale
*  @param low2 the lower value of mapped scale
*  @param high2 the higher value of mapped scale
* 
*  @returns the remmaped value
*/
double map(double value, double low1, double high1, double low2, double high2);
