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

package org.car2x.veins.modules.application.early_warning;
import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;

simple BikeWarningRSU extends BaseWaveApplLayer
{
    parameters:
        double RSURange;
        string IN_EDGES;
        string OUT_EDGES;
        string JUNCTION;
    
    @class(BikeWarningRSU);
    @display("i=block/app2");
}