/*
 * DecisionAlgorithm.h
 *
 *  Created on: Sep 28, 2016
 *      Author: arachnid92
 */

#include <python3.5m/Python.h>
#include <string>
#include <iostream>

#ifndef DECISIONALGORITHM_H_
#define DECISIONALGORITHM_H_

#define DECISION_ALGO_SCRIPT "algorithm"
#define DECISION_ALGO_FUNC "detect_turn"

class DecisionAlgorithm {
public:
    DecisionAlgorithm();
    virtual ~DecisionAlgorithm();
    bool probableTurn(double pvel, double pposx, double pposy, double cvel, double cposx, double cposy, std::string car_id);
protected:
    PyObject *pName, *pFunc, *pModule, *pArgs;
};

#endif /* DECISIONALGORITHM_H_ */
