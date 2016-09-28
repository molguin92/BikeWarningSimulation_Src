/*
 * DecisionAlgorithm.cpp
 *
 *  Created on: Sep 28, 2016
 *      Author: arachnid92
 */

#include "DecisionAlgorithm.h"

DecisionAlgorithm::DecisionAlgorithm() {
    Py_Initialize();
    PyRun_SimpleString( "import os, sys\n"
                        "sys.path.append(os.getcwd())\n");
    pName = PyUnicode_DecodeFSDefault(DECISION_ALGO_SCRIPT);
    pModule = PyImport_Import(pName);
    if(pModule == NULL)
    {
        std::cout << "Null pModule" << std::endl;
        throw -1;
    }
    pFunc = PyObject_GetAttrString(pModule, DECISION_ALGO_FUNC);

    if(!(pFunc && PyCallable_Check(pFunc)))
    {
        std::cout << "Null pFunc" << std::endl;
        throw -1;
    }

}

bool DecisionAlgorithm::probableTurn(double pvel, double pposx, double pposy, double cvel, double cposx, double cposy, std::string car_id)
{
    pArgs = PyTuple_New(7);
    PyTuple_SetItem(pArgs, 0, PyFloat_FromDouble(pvel));
    PyTuple_SetItem(pArgs, 1, PyFloat_FromDouble(pposx));
    PyTuple_SetItem(pArgs, 2, PyFloat_FromDouble(pposy));
    PyTuple_SetItem(pArgs, 3, PyFloat_FromDouble(cvel));
    PyTuple_SetItem(pArgs, 4, PyFloat_FromDouble(cposx));
    PyTuple_SetItem(pArgs, 5, PyFloat_FromDouble(cposy));
    PyTuple_SetItem(pArgs, 6, PyByteArray_FromStringAndSize(car_id.c_str(), car_id.length()));


    PyObject* result = PyObject_CallObject(pFunc, pArgs);
    long final = PyLong_AsLong(result);
    std::cout << static_cast<int16_t>(final) << std::endl;

    return 1 == final;
}

DecisionAlgorithm::~DecisionAlgorithm() {

    Py_DECREF(pName);
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
    Py_Finalize();

}

