#include <cmath>
#include <ctime>
#include <game/Player.hpp>
#include <limits>
#include <vector>

#pragma once

/** 
 *  Update the neuralnetwork for each individue in the population
 * 
 *  @param oldBirds the previus generation
 */
void generate(std::vector<Player *> &oldBirds);

/** 
 *  Normalize the fitness of each individual
 * 
 *  @param bird the entire population
 */
void normalizeFitness(std::vector<Player *> birds);

/** 
 *  Random Select with same chaces a arbitary individual
 * 
 *  @param bird the entire population
 * 
 * @returns The neural network of the selected individual
 */
NeuralNetwork poolSelection(std::vector<Player *> birds);