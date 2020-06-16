#include <neural-network/auxiliar.hpp>

void generate(std::vector<Player *> &oldBirds) {
    for (int i = 0; i < oldBirds.size(); i++) {
        oldBirds[i]->regenerate(poolSelection(oldBirds));
    }
}

void normalizeFitness(std::vector<Player *> birds) {
    int sum = 0;

    for (auto &bird : birds) {
        sum += bird->getScore();
    }

    for (auto &bird : birds) {
        bird->setFitness(double(bird->getScore()) / sum);
    }
}

// NeuralNetwork poolSelection(std::vector<Player *> birds) {
//     int index = 0;
//     int bs = 0;
//     for (int i = 0; i < birds.size(); i++) {
//         if (birds[i]->getScore() > bs) {
//             bs = birds[i]->getScore();
//             index = i;
//         }
//     }

//     return birds[index]->getBrain();
// }

NeuralNetwork poolSelection(std::vector<Player *> birds) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    int index = 0;

    double r = dist(rng);

    // Keep subtracting probabilities until you get less than zero
    // Higher probabilities will be more likely to be fixed since they will
    // subtract a larger number towards zero
    while (r > 0) {
        r -= birds[index]->getFitness();
        // And move on to the next
        index++;
        if (index >= 1000) break;
    }

    // Go back one
    index--;

    return birds[index]->getBrain();
}
