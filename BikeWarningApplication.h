//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __VEINS_BIKEWARNINGAPPLICATION_H_
#define __VEINS_BIKEWARNINGAPPLICATION_H_

#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

class BikeWarningApplication : public BaseWaveApplLayer
{
    protected:
        Veins::TraCIMobility* mobility;
        Veins::TraCICommandInterface *traci;
        Veins::TraCICommandInterface::Vehicle *traciVehicle;
        std::string myID;
        virtual void initialize(int stage);
        virtual void finish();
        virtual void handleSelfMsg(cMessage *msg);
        virtual void onData(WaveShortMessage *wsm);
        virtual void onBeacon(WaveShortMessage *wsm);
};

#endif
