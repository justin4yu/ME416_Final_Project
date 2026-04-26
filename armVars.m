% Build robot
robot = buildRobot();

% Joint configurations
q_v1 = [deg2rad(30), 100, deg2rad(-60)];

% Compute forward kinematics
T = robot.fkine(q_v1);

% SE3 version for ikine in command window
xyz_SE3 = T;

% Package as timeseries for From Workspace block in Simulink
xyz.time = [0; 10];
xyz.signals.values = cat(3, T.T, T.T);
xyz.signals.dimensions = [4 4];

% Initial guess for IK
q0 = q_v1;

% Mask
mask = [1 1 1 0 0 0];