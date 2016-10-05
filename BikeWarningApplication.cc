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

#include "BikeWarningApplication.h"
#include "veins/modules/application/early_warning/json.hpp"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

Define_Module(BikeWarningApplication);
using json = nlohmann::json;
using Junction = Veins::TraCICommandInterface::Junction;

void BikeWarningApplication::initialize(int stage)
{
    //std::cout << "initializing...\n";
    BaseWaveApplLayer::initialize(stage);

    switch (stage)
    {
    case 0:
        // init everything

        mobility = Veins::TraCIMobilityAccess().get(getParentModule());
        traci = mobility->getCommandInterface();
        traciVehicle = mobility->getVehicleCommandInterface();
        break;
    case 1:
        myID = mobility->getExternalId();

        break;
    default:
        break;
    }
}

void BikeWarningApplication::finish()
{
    BaseWaveApplLayer::finish();
}

void BikeWarningApplication::handleSelfMsg(cMessage *msg)
{
   switch (msg->getKind()) {
        case SEND_BEACON_EVT: {
            //std::cout << "Sending beacon: ";
            WaveShortMessage* wsm = prepareWSM("beacon", beaconLengthBits, type_CCH, beaconPriority, -1, -1);

            Coord pos = mobility->getCurrentPosition();
            double speed = mobility->getSpeed();
            std::string id = mobility->getExternalId();
            std::string lane_id = traciVehicle->getLaneId();

            json data_j = {
                    {"id", id},
                    {"vel", speed},
                    {"pos_x", pos.x},
                    {"pos_y", pos.y},
                    {"lane_id", lane_id}
            };

            std::string jdata = data_j.dump();
            //std::cout << jdata << std::endl;

            wsm->setWsmData(jdata.c_str());
            sendWSM(wsm);
            scheduleAt(simTime() + par("beaconInterval").doubleValue(), sendBeaconEvt);
            break;
        }
        default: {
            if (msg)
                DBG << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

void BikeWarningApplication::onData(WaveShortMessage *wsm)
{
    if(wsm->getRecipientAddress() == myId)
        // only "receive" the message if it's for me
        std::cout << "CAR " << myID << ": " << std::string(wsm->getWsmData()) << std::endl;
}

void BikeWarningApplication::onBeacon(WaveShortMessage *wsm)
{
}

