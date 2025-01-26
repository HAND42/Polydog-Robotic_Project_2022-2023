function demo_pursuit_guidance_custom_positions()

    %% Simulation Parameters
    dt = 0.1;            % time step (s)
    T  = 20;             % total simulation time (s)
    timeVec = 0:dt:T;    % time array

    % Drone speeds in each scenario (m/s)
    droneSpeedCross  = 25; 
    droneSpeedHeadOn = 20;
    droneSpeedTail   = 24;
    
    % Target speeds in each scenario (m/s)
    targetSpeedCross  = 19;
    targetSpeedHeadOn = 12;
    targetSpeedTail   = 18;

    %% 1) CROSSING SCENARIO
    p0_drone_cross  = [25; -100];     % Drone starts at (25, -100)
    p0_target_cross = [100; 50];      % Target starts at (100, 50)
    v_target_cross  = [-targetSpeedCross; 0];  % Moves horizontally to the left

    [droneCross, targetCross, interceptCross, timeCross] = simulatePursuitGuidance( ...
        p0_drone_cross, p0_target_cross, droneSpeedCross, v_target_cross, dt, timeVec);

    %% 2) HEAD-ON SCENARIO
    p0_drone_headOn  = [25; -100];     % Drone at (25, -100)
    p0_target_headOn = [25; 100];      % Target at (25, 100)
    v_target_headOn  = [-2; -targetSpeedHeadOn];  % Mostly vertical velocity

    [droneHeadOn, targetHeadOn, interceptHeadOn, timeHeadOn] = simulatePursuitGuidance( ...
        p0_drone_headOn, p0_target_headOn, droneSpeedHeadOn, v_target_headOn, dt, timeVec);

    %% 3) TAIL-CHASE SCENARIO
    p0_drone_tail  = [25; -100];      % Drone at (25, -100)
    p0_target_tail = [-25; -50];      % Target at (-25, -50)
    v_target_tail  = [2; targetSpeedTail];  % Slight horizontal drift, mostly upward

    [droneTail, targetTail, interceptTail, timeTail] = simulatePursuitGuidance( ...
        p0_drone_tail, p0_target_tail, droneSpeedTail, v_target_tail, dt, timeVec);

    %% Display Interception Times
    fprintf('Interception Times:\n');
    fprintf('Crossing Scenario: %.2f seconds\n', timeCross);
    fprintf('Head-On Scenario: %.2f seconds\n', timeHeadOn);
    fprintf('Tail-Chase Scenario: %.2f seconds\n', timeTail);

    %% Plot Results: side by side comparison of the 3 scenarios
    figure('Name','Pursuit Guidance with Explosion','NumberTitle','off','Color','w');

    % CROSSING
    subplot(1,3,1); hold on; grid on; axis equal;
    plot(targetCross(1,:), targetCross(2,:), 'r-', 'LineWidth', 2, 'DisplayName','Target');
    plot(droneCross(1,:),  droneCross(2,:),  'b-', 'LineWidth', 2, 'DisplayName','Drone');
    if ~isempty(interceptCross)
        plot(interceptCross(1), interceptCross(2), 'yo', 'MarkerSize', 12, 'MarkerFaceColor', 'y', 'DisplayName', 'Intercept point');
    end
    legend('Location','best');
    title('Crossing');
    xlabel('X [m]'); ylabel('Y [m]');
    xlim([-100, 100]);

    % HEAD-ON
    subplot(1,3,2); hold on; grid on; axis equal;
    plot(targetHeadOn(1,:), targetHeadOn(2,:), 'r-', 'LineWidth', 2, 'DisplayName','Target');
    plot(droneHeadOn(1,:),  droneHeadOn(2,:),  'b-', 'LineWidth', 2, 'DisplayName','Drone');
    if ~isempty(interceptHeadOn)
        plot(interceptHeadOn(1), interceptHeadOn(2), 'yo', 'MarkerSize', 12, 'MarkerFaceColor', 'y', 'DisplayName', 'Intercept point');
    end
    legend('Location','best');
    title('Head-On');
    xlabel('X [m]'); ylabel('Y [m]');
    xlim([-100, 100]);  % Set x-axis range
    ylim([-100, 100]);  % Set y-axis range

    % TAIL-CHASE
    subplot(1,3,3); hold on; grid on; axis equal;
    plot(targetTail(1,:), targetTail(2,:), 'r-', 'LineWidth', 2, 'DisplayName','Target');
    plot(droneTail(1,:),  droneTail(2,:),  'b-', 'LineWidth', 2, 'DisplayName','Drone');
    if ~isempty(interceptTail)
        plot(interceptTail(1), interceptTail(2), 'yo', 'MarkerSize', 12, 'MarkerFaceColor', 'y', 'DisplayName', 'Intercept point');
    end
    legend('Location','best');
    title('Tail-Chase');
    xlabel('X [m]'); ylabel('Y [m]');
    xlim([-100, 100]);  % Set x-axis range
    ylim([-100, 150]);  % Set y-axis range
end

%% ===================================================================== %%
function [dronePath, targetPath, interceptPoint, interceptTime] = simulatePursuitGuidance( ...
    p0_drone, p0_target, droneSpeed, v_target, dt, timeVec)


    N = length(timeVec);
    interceptionThreshold = 5;  % Threshold distance for interception (m)
    interceptPoint = [];  % Initialize interception point as empty
    interceptTime = NaN;  % Initialize interception time as NaN

    % Allocate memory for position storage
    dronePath  = nan(2, N);  % Use NaN for unfilled entries after interception
    targetPath = nan(2, N);

    % Initialize positions
    dronePos  = p0_drone;
    targetPos = p0_target;

    % Store initial positions
    dronePath(:,1)  = dronePos;
    targetPath(:,1) = targetPos;

    for k = 2:N
        % Update target position
        targetPos = targetPos + v_target * dt;

        % Calculate relative position from drone to target
        relPos = targetPos - dronePos;
        dist   = norm(relPos);  % Distance between drone and target

        % Check if the drone has intercepted the target
        if dist <= interceptionThreshold
            % Record interception point and time
            interceptPoint = targetPos;
            interceptTime = timeVec(k);
            % Store the final positions for plotting
            dronePath(:,k)  = dronePos;
            targetPath(:,k) = targetPos;
            % End simulation early
            break;
        end

        % Calculate the unit direction toward the target
        if dist > 1e-6
            unitDir = relPos / dist;  % Unit vector pointing to the target
        else
            unitDir = [0; 0];  % Drone has reached the target
        end

        % Update drone position
        dronePos = dronePos + droneSpeed * unitDir * dt;

        % Store positions for plotting
        dronePath(:,k)  = dronePos;
        targetPath(:,k) = targetPos;
    end

    % Trim unused path entries
    dronePath = dronePath(:, ~isnan(dronePath(1,:)));
    targetPath = targetPath(:, ~isnan(targetPath(1,:)));
end
