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

Define_Module(BikeWarningApplication);
using json = nlohmann::json;

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
    //std::cout << "x " << traci->junction("cluster_15159499_18038479_21113262_347787163_8851291").getPosition().x << std::endl;
    //std::cout << "y " << traci->junction("cluster_15159499_18038479_21113262_347787163_8851291").getPosition().y << std::endl;
    switch (msg->getKind()) {
        case SEND_BEACON_EVT: {
            //std::cout << "Sending beacon: ";
            WaveShortMessage* wsm = prepareWSM("beacon", beaconLengthBits, type_CCH, beaconPriority, -1, -1);

            Coord pos = mobility->getCurrentPosition();
            std::string id = mobility->getExternalId();

            json data_j = {
                    {"id", id},
                    {"pos_x", pos.x},
                    {"pos_y", pos.y}
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
    std::cout << std::string(wsm->getWsmData()) << std::endl;
}

void BikeWarningApplication::onBeacon(WaveShortMessage *wsm)
{
}

