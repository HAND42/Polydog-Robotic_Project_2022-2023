function proportional_navigation_control()
    % Proportional Navigation with AirSim via TCP
    
    % AirSim TCP parameters
    airsimIP = '127.0.0.1';
    airsimPort = 41451;
    tcpClient = tcpclient(airsimIP, airsimPort);

    % Simulation parameters
    N = 4;  % Navigation constant (commonly 3-5)
    dt = 0.1;  % Time step (s)
    throttleForce = 0.6;  % Constant throttle force

    % Connect to AirSim
    fprintf('Connecting to AirSim at %s:%d...\n', airsimIP, airsimPort);
    
    % Infinite loop to send commands and read telemetry
    while true
        % Fetch telemetry data from AirSim
        telemetry = fetchTelemetry(tcpClient);
        if isempty(telemetry)
            fprintf('No telemetry received. Retrying...\n');
            pause(0.1);
            continue;
        end
        
        % Parse telemetry data
        dronePos = telemetry.dronePos;  % Drone position [x, y, z]
        targetPos = telemetry.targetPos;  % Target position [x, y, z]
        droneVel = telemetry.droneVel;  % Drone velocity [vx, vy, vz]
        
        % Calculate relative position and velocity
        relPos = targetPos - dronePos;
        relVel = telemetry.targetVel - droneVel;

        % Compute LOS angle and LOS rate
        LOS = atan2(relPos(2), relPos(1));  % Line-of-Sight angle
        dist = norm(relPos);
        LOS_rate = (relPos(1) * relVel(2) - relPos(2) * relVel(1)) / dist^2;  % Angular LOS rate

        % Compute Proportional Navigation turn rate
        turnRate = N * LOS_rate;
        
        % Generate yaw and pitch commands
        yaw = atan2(relPos(2), relPos(1));  % Yaw angle toward the target
        pitch = atan2(relPos(3), dist);    % Pitch to correct altitude

        % Roll is not used in PN (set to zero)
        roll = 0;

        % Send control commands to AirSim
        sendControlCommand(tcpClient, yaw, pitch, roll, throttleForce);
        
        % Display telemetry and control info
        fprintf('Drone Pos: [%.2f, %.2f, %.2f] | Target Pos: [%.2f, %.2f, %.2f] | Yaw: %.2f | Pitch: %.2f\n', ...
            dronePos, targetPos, yaw, pitch);

        pause(dt);  % Wait for the next step
    end
end

%% Fetch telemetry data from AirSim
function telemetry = fetchTelemetry(tcpClient)
    try
        % Request telemetry data
        write(tcpClient, uint8('telemetry'));
        data = read(tcpClient);
        telemetry = jsondecode(char(data));
    catch
        telemetry = [];
    end
end

%% Send control commands to AirSim
function sendControlCommand(tcpClient, yaw, pitch, roll, throttle)
    try
        command = struct('yaw', yaw, 'pitch', pitch, 'roll', roll, 'throttle', throttle);
        write(tcpClient, uint8(jsonencode(command)));
    catch
        warning('Failed to send control command to AirSim.');
    end
end
