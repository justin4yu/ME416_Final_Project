%% Drive Control Parameters

% Encoder
N = 1024;        % counts per revolution
Ts = 0.01;       % sample time (s)

% Robot geometry
r = 0.03;        % wheel radius (m)
L = 0.15;        % wheelbase (m)

open('ME416_Autonomy_Model.slx');