function demo_proportional_navigation_custom_positions()

    %% Simulation Parameters
    dt = 0.1;            % Time step (s)
    T = 300;             % Total simulation time (s)
    timeVec = 0:dt:T;    % Time array

    % Navigation constant
    N = 4;  % Proportional Navigation constant (typically between 3-5)

    % Drone speeds (m/s)
    droneSpeedCross = 25;
    droneSpeedHeadOn = 20;
    droneSpeedTail = 24;

    % Target speeds (m/s)
    targetSpeedCross = 19;
    targetSpeedHeadOn = 12;
    targetSpeedTail = 18;

    %% 1) Crossing Scenario
    p0_drone_cross = [25; -100];
    p0_target_cross = [100; 50];
    v_target_cross = [-targetSpeedCross; 0];  % Target moves horizontally left

    [droneCross, targetCross, interceptCross, timeCross] = simulateProportionalNavigation( ...
        p0_drone_cross, p0_target_cross, droneSpeedCross, v_target_cross, dt, timeVec, N);

    %% 2) Head-On Scenario
    p0_drone_headOn = [25; -100];
    p0_target_headOn = [25; 100];
    v_target_headOn = [-2; -targetSpeedHeadOn];  % Target moves vertically down

    [droneHeadOn, targetHeadOn, interceptHeadOn, timeHeadOn] = simulateProportionalNavigation( ...
        p0_drone_headOn, p0_target_headOn, droneSpeedHeadOn, v_target_headOn, dt, timeVec, N);

    %% 3) Tail-Chase Scenario
    p0_drone_tail = [25; -100];
    p0_target_tail = [-50; -25];
    v_target_tail = [2; targetSpeedTail];  % Target moves upward with slight horizontal drift

    [droneTail, targetTail, interceptTail, timeTail] = simulateProportionalNavigation( ...
        p0_drone_tail, p0_target_tail, droneSpeedTail, v_target_tail, dt, timeVec, N);

    %% Display Interception Times
    fprintf('Interception Times:\n');
    fprintf('Crossing Scenario: %.2f seconds\n', timeCross);
    fprintf('Head-On Scenario: %.2f seconds\n', timeHeadOn);
    fprintf('Tail-Chase Scenario: %.2f seconds\n', timeTail);

    %% Plot Results
    figure('Name', 'Proportional Navigation Scenarios', 'NumberTitle', 'off', 'Color', 'w');

    % Crossing Scenario
    subplot(1, 3, 1); hold on; grid on; axis equal;
    plot(targetCross(1,:), targetCross(2,:), 'r-', 'LineWidth', 2, 'DisplayName', 'Target');
    plot(droneCross(1,:), droneCross(2,:), 'b-', 'LineWidth', 2, 'DisplayName', 'Drone');
    if ~isempty(interceptCross)
        plot(interceptCross(1), interceptCross(2), 'yo', 'MarkerSize', 12, 'MarkerFaceColor', 'y', 'DisplayName', 'Intercept');
    end
    legend('Location', 'best');
    title('Crossing');
    xlabel('X [m]'); ylabel('Y [m]');
    xlim([-100, 100]);

    % Head-On Scenario
    subplot(1, 3, 2); hold on; grid on; axis equal;
    plot(targetHeadOn(1,:), targetHeadOn(2,:), 'r-', 'LineWidth', 2, 'DisplayName', 'Target');
    plot(droneHeadOn(1,:), droneHeadOn(2,:), 'b-', 'LineWidth', 2, 'DisplayName', 'Drone');
    if ~isempty(interceptHeadOn)
        plot(interceptHeadOn(1), interceptHeadOn(2), 'yo', 'MarkerSize', 12, 'MarkerFaceColor', 'y', 'DisplayName', 'Intercept');
    end
    legend('Location', 'best');
    title('Head-On');
    xlabel('X [m]'); ylabel('Y [m]');
    xlim([-100, 100]); ylim([-100, 100]);

    % Tail-Chase Scenario
    subplot(1, 3, 3); hold on; grid on; axis equal;
    plot(targetTail(1,:), targetTail(2,:), 'r-', 'LineWidth', 2, 'DisplayName', 'Target');
    plot(droneTail(1,:), droneTail(2,:), 'b-', 'LineWidth', 2, 'DisplayName', 'Drone');
    if ~isempty(interceptTail)
        plot(interceptTail(1), interceptTail(2), 'yo', 'MarkerSize', 12, 'MarkerFaceColor', 'y', 'DisplayName', 'Intercept');
    end
    legend('Location', 'best');
    title('Tail-Chase');
    xlabel('X [m]'); ylabel('Y [m]');
    xlim([-100, 100]); ylim([-100, 250]);
end

%% ===================================================================== %%
function [dronePath, targetPath, interceptPoint, interceptTime] = simulateProportionalNavigation( ...
    p0_drone, p0_target, droneSpeed, v_target, dt, timeVec, N)


    N_steps = length(timeVec);
    interceptionThreshold = 5;  % Interception distance (m)
    interceptPoint = [];
    interceptTime = NaN;  % Default to NaN if no interception

    % Preallocate paths
    dronePath = nan(2, N_steps);
    targetPath = nan(2, N_steps);

    % Initialize positions and velocities
    dronePos = p0_drone;
    targetPos = p0_target;
    droneVel = [0; droneSpeed];  % Initial velocity pointing upwards

    % Store initial positions
    dronePath(:,1) = dronePos;
    targetPath(:,1) = targetPos;

    for k = 2:N_steps
        % Update target position
        targetPos = targetPos + v_target * dt;

        % Relative position and distance
        relPos = targetPos - dronePos;
        dist = norm(relPos);

        % Check for interception
        if dist <= interceptionThreshold
            interceptPoint = targetPos;
            interceptTime = timeVec(k);  % Record interception time
            break;
        end

        % Calculate LOS angle and LOS rate
        LOS = atan2(relPos(2), relPos(1));  % Line-of-Sight angle
        relVel = v_target - droneVel;       % Relative velocity
        LOS_rate = (relPos(1)*relVel(2) - relPos(2)*relVel(1)) / dist^2;  % LOS rate

        % Proportional Navigation Turn Rate
        turnRate = N * LOS_rate;

        % Update drone velocity direction
        droneHeading = atan2(droneVel(2), droneVel(1)) + turnRate * dt;
        droneVel = droneSpeed * [cos(droneHeading); sin(droneHeading)];

        % Update drone position
        dronePos = dronePos + droneVel * dt;

        % Store positions
        dronePath(:,k) = dronePos;
        targetPath(:,k) = targetPos;
    end

    % Trim unused path entries
    dronePath = dronePath(:, ~isnan(dronePath(1,:)));
    targetPath = targetPath(:, ~isnan(targetPath(1,:)));
end
