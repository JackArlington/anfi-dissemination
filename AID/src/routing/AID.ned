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

package aid.routing;

import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;

//
// TODO auto-generated module
//
simple AID extends BaseWaveApplLayer
{
    @statistic[duplicatedMessages](record=sum);
    @statistic[messagesTransmitted](record=sum);
    @statistic[messagesReceived](record=sum);
    
    // logging parameters
    int log_traffic;
    int log_replication;
    
    double randomDelayTimeMax @unit(s) = default(60ms);
    double maxGPSError @unit(m) = default(0m);
    
    double datarate @unit(bps) = default(2Mbps);       
            	
	@class(AID);
}
