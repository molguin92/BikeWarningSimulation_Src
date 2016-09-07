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
        mobi = dynamic_cast<BaseMobility*> (getParentModule()->getSubmodule("mobility"));
        RSU_RANGE = 30.0; //par("RSURange").doubleValue();
    }
}

void BikeWarningRSU::onBeacon(WaveShortMessage* wsm)
{
    json data_j = json::parse(std::string(wsm->getWsmData()));
    //std::cout << data_j.dump(4) << std::endl;
    std::string id = data_j["id"];
    float pos_x = data_j["pos_x"];
    float pos_y = data_j["pos_y"];

    Coord rsu_pos = mobi->getCurrentPosition();
    Coord* car_pos = new Coord(pos_x, pos_y, rsu_pos.z);
    double dist = rsu_pos.distance(*car_pos);

    if(dist <= RSU_RANGE)
    {
        t_channel channel = dataOnSch ? type_SCH : type_CCH;
        WaveShortMessage* msg = prepareWSM("data", dataLengthBits, channel, dataPriority, wsm->getSenderAddress(), 2);
        msg->setWsmData("RSU_ACK");
        sendWSM(msg);
    }


}

void BikeWarningRSU::onData(WaveShortMessage* wsm) {
}

void BikeWarningRSU::finish() {
    BaseWaveApplLayer::finish();
}
