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

#ifndef BIKEWARNINGRSU_H_
#define BIKEWARNINGRSU_H_

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"

#define ENTERING 1
#define EXITING 0

typedef struct CAR_STATUS
{
    double dist;
    int status;
} CAR_STATUS;

class BikeWarningRSU: public BaseWaveApplLayer {
    public:
        virtual void initialize(int stage);
        virtual void finish();
    protected:
        BaseMobility* mobi;
        double RSU_RANGE;
        std::map<std::string, CAR_STATUS> cars_in_junct;
    protected:
        virtual void onBeacon(WaveShortMessage* wsm);
        virtual void onData(WaveShortMessage* wsm);
};

#endif /* BIKEWARNINGRSU_H_ */
