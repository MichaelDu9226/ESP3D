/*
 ESP170.cpp - ESP3D command class

 Copyright (c) 2014 Luc Lebosse. All rights reserved.

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with This code; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "../../include/esp3d_config.h"
#if defined (CAMERA_DEVICE)
#include "../commands.h"
#include "../esp3doutput.h"
#include "../settings_esp3d.h"
#include "../../modules/authentication/authentication_service.h"
#include "../../modules/network/netservices.h"
#include "../../modules/camera/camera.h"
//Set camera server state which can be ON, OFF
//[ESP170]<state>pwd=<admin password>
bool Commands::ESP170(const char* cmd_params, level_authenticate_type auth_type, ESP3DOutput * output)
{
    bool response = true;
    String parameter;
#ifdef AUTHENTICATION_FEATURE
    if (auth_type == LEVEL_GUEST) {
        output->printERROR("Wrong authentication!", 401);
        return false;
    }
#else
    (void)auth_type;
#endif //AUTHENTICATION_FEATURE
    parameter = get_param (cmd_params, "");
    //get
    if (parameter.length() == 0) {
        output->printMSG(!esp3d_camera.started()?"Camera OFF":"Camera ON");
    } else { //set
#ifdef AUTHENTICATION_FEATURE
        if (auth_type != LEVEL_ADMIN) {
            output->printERROR("Wrong authentication!", 401);
            return false;
        }
#endif //AUTHENTICATION_FEATURE
        parameter.toUpperCase();
        if (!((parameter == "ON") || (parameter == "OFF"))) {
            output->printERROR("Only ON or OFF mode supported!");
            return false;
        } else {
            if (parameter == "ON") {
                esp3d_camera.begin();
            } else {
                esp3d_camera.stopHardware();
            }
            output->printMSG ("ok");
        }
    }
    return response;
}

#endif //HTTP_FEATURE && CAMERA_DEVICE
