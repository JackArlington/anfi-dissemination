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

package flooding;

import flooding.rsu.RSU;
import org.car2x.veins.base.modules.BaseWorldUtility;
import org.car2x.veins.base.connectionManager.ConnectionManager;
import org.car2x.veins.modules.mobility.traci.TraCIScenarioManagerLaunchd;
import org.car2x.veins.modules.obstacle.ObstacleControl;
import org.car2x.veins.modules.world.annotations.AnnotationManager;

//
// TODO auto-generated type
//
network VANET
{
    parameters:
    	@display("i=background/green");   
    	int numberRSU = default(0); 	
    
    submodules:
        rsu[numberRSU]: RSU;
        
        baseWorldUtility: BaseWorldUtility {
            @display("p=70,20");
        }
        connectionManager: ConnectionManager {
            @display("p=70,91");
        }
        manager: TraCIScenarioManagerLaunchd {
            @display("p=512,128");
        }
        obstacles: ObstacleControl {
            @display("p=240,50");
        }
        annotations: AnnotationManager {
            @display("p=260,50");
        }
	
	connections allowunconnected:      
    
}
