/*
 * DecisionAlgorithm.cpp
 *
 *  Created on: Sep 28, 2016
 *      Author: arachnid92
 */

#include "DecisionAlgorithm.h"

DecisionAlgorithm::DecisionAlgorithm() {
    Py_Initialize();
    PyRun_SimpleString( "import os, sys, random, traceback\n"
                        "sys.path.append(os.getcwd())\n");
    pName = PyUnicode_DecodeFSDefault(DECISION_ALGO_SCRIPT);
    pModule = PyImport_Import(pName);
    if(pModule == NULL)
    {
        std::cout << "Null pModule" << std::endl;
        throw -1;
    }
    pFunc = PyObject_GetAttrString(pModule, DECISION_ALGO_FUNC);
    pAddEntry = PyObject_GetAttrString(pModule, DECISION_ALGO_ADDENTRYLANE);
    pAddExit = PyObject_GetAttrString(pModule, DECISION_ALGO_ADDEXITLANE);

    if(!(pFunc && PyCallable_Check(pFunc)))
    {
        std::cout << "Null Decision Function" << std::endl;
        throw -1;
    }
    else if(!(pAddEntry && PyCallable_Check(pAddEntry)))
    {
        std::cout << "Null Entry Lane Function" << std::endl;
        throw -1;
    }
    else if(!(pAddExit && PyCallable_Check(pAddExit)))
    {
        std::cout << "Null Exit Lane Function" << std::endl;
        throw -1;
    }

}

void DecisionAlgorithm::addEntryLane(std::string lane_id)
{
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyByteArray_FromStringAndSize(lane_id.c_str(), lane_id.length()));
    PyObject_CallObject(pAddEntry, pArgs);
    Py_DECREF(pArgs);
}

void DecisionAlgorithm::addExitLane(std::string lane_id)
{
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyByteArray_FromStringAndSize(lane_id.c_str(), lane_id.length()));
    PyObject_CallObject(pAddExit, pArgs);
    Py_DECREF(pArgs);
}

bool DecisionAlgorithm::checkTurn(double velocity, double pos_x, double pos_y, std::string car_id, std::string lane_id)
{

    pArgs = PyTuple_New(5);
    PyTuple_SetItem(pArgs, 0, PyFloat_FromDouble(velocity));
    PyTuple_SetItem(pArgs, 1, PyFloat_FromDouble(pos_x));
    PyTuple_SetItem(pArgs, 2, PyFloat_FromDouble(pos_y));
    PyTuple_SetItem(pArgs, 3, PyByteArray_FromStringAndSize(car_id.c_str(), car_id.length()));
    PyTuple_SetItem(pArgs, 4, PyByteArray_FromStringAndSize(lane_id.c_str(), lane_id.length()));


    PyObject* result = PyObject_CallObject(pFunc, pArgs);
    if(result == NULL)
    {
        std::cerr << "null return, something went wrong" << std::endl;
        throw -1;
    }

    long final = PyLong_AsLong(result);
    Py_DECREF(pArgs);

    return final;// == final;
}

DecisionAlgorithm::~DecisionAlgorithm() {

    Py_DECREF(pName);
    Py_XDECREF(pFunc);
    Py_XDECREF(pAddEntry);
    Py_XDECREF(pAddExit);
    Py_DECREF(pModule);
    Py_Finalize();

}

