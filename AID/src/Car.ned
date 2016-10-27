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

package aid;

import org.car2x.veins.base.modules.*;
import org.car2x.veins.modules.mobility.traci.TraCIMobility;
import org.car2x.veins.modules.nic.Nic80211p;

//
// TODO auto-generated type
//
module Car
{
    parameters:
        @display("i=device/laptop_l;bgb=304,230");
        string applicationModule;
    gates:
        input radioIn; // gate for sendDirect

    submodules:

        appl: <applicationModule> like org.car2x.veins.base.modules.IBaseApplLayer {
            @display("p=90,35;b=100,20,rect");
        }

        nic: Nic80211p {
            @display("p=90,150;b=100,20,rect");
        }

        mobility: TraCIMobility {
            @display("p=257,172;i=block/cogwheel");
        }

    connections:
        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> appl.lowerControlIn;
        nic.upperControlIn <-- appl.lowerControlOut;

        radioIn --> nic.radioIn;

}
