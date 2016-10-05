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
#define DECISION_ALGO_FUNC "detect_turn_car"
#define DECISION_ALGO_ADDENTRYLANE "add_entry_lane"
#define DECISION_ALGO_ADDEXITLANE "add_exit_lane"

class DecisionAlgorithm {
public:
    DecisionAlgorithm();
    virtual ~DecisionAlgorithm();
    bool checkTurn(double velocity, double pos_x, double pos_y, std::string car_id, std::string lane_id);
    void addEntryLane(std::string lane_id);
    void addExitLane(std::string lane_id);
protected:
    PyObject *pName, *pFunc, *pModule, *pArgs, *pAddEntry, *pAddExit;
};

#endif /* DECISIONALGORITHM_H_ */
