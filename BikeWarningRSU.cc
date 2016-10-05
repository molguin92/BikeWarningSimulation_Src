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

#include "veins/modules/application/early_warning/BikeWarningRSU.h"
#include "veins/modules/application/early_warning/json.hpp"

Define_Module(BikeWarningRSU);
using json = nlohmann::json;

void BikeWarningRSU::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    if (stage == 0) {
        mobi = dynamic_cast<BaseMobility*>(getParentModule()->getSubmodule(
                "mobility"));
        RSU_RANGE = par("RSURange").doubleValue();
        std::string in_e = par("IN_EDGES").stringValue();
        std::string out_e = par("OUT_EDGES").stringValue();

        cStringTokenizer entry_lanes(in_e.c_str());
        cStringTokenizer exit_lanes(out_e.c_str());

        while(entry_lanes.hasMoreTokens())
            algo.addEntryLane(entry_lanes.nextToken());

        while(exit_lanes.hasMoreTokens())
            algo.addExitLane(exit_lanes.nextToken());

    }
    else
    {
        rsu_pos = mobi->getCurrentPosition();
    }
}

void BikeWarningRSU::onBeacon(WaveShortMessage* wsm) {


    json data_j = json::parse(std::string(wsm->getWsmData()));

    std::string id = data_j["id"];
    double vel = data_j["vel"];
    double pos_x = data_j["pos_x"];
    double pos_y = data_j["pos_y"];
    std::string lane_id = data_j["lane_id"];

    Coord* car_pos = new Coord(pos_x, pos_y, rsu_pos.z);
    double dist = rsu_pos.distance(*car_pos);

    // check if car is in range
    if (dist <= RSU_RANGE) {
        if(algo.checkTurn(vel, pos_x, pos_y, id, lane_id) == 1)
        {
            std::cout << "TURN WARNING FOR " << id << std::endl;
            // TODO: actually send message here
        }
    }

}

void BikeWarningRSU::onData(WaveShortMessage* wsm) {
}

void BikeWarningRSU::finish() {

    BaseWaveApplLayer::finish();
}
