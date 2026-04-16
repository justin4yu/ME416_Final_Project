%% Drive Control Parameters

% Encoder
N = 4400;        % counts per revolution
Ts = 0.01;       % sample time (s)

% Robot geometry
r = 0.03;        % wheel radius (m)
L = 0.15;        % wheelbase (m)

% Low Pass Filter
tau = 0.05;      % cutoff frequency, 50 ms smoothing
beta = Ts / (Ts + tau);

alpha_w = 0.7;

% Motor Dynamics
% Power / sampling
Vbatt  = 12;
Ts     = 0.01;       % Sample Time

% Geometry
r_w    = 0.03;      % Wheel radius
Ltrack = 0.15;       % Wheel Spacing from Center

% Motor model (initial guesses)
Lm = 1;           % Armature Inductance  
Rm = 8;              % Armature Resistance
Jm = 2e-5;           % Rotor / Equivalent Inertia
bm = 2e-4;           % Viscous Damping Coefficient
Ke = 0.03;           % Back-EMF C   onstant
Kt = 0.03;           % Torque Constant

% GUI Control Params
v_ref_cmd  = 0.05;
w_ref_cmd  = 0;
enable_cmd = 1;
estop_cmd  = 0;

% --- Single-wheel speed model for LQR ---
a_w = -(bm + Kt*Ke/Rm)/Jm;
b_w = (Kt*Vbatt)/(Rm*Jm);

Ad_w = exp(a_w*Ts);
Bd_w = ((Ad_w - 1)/a_w) * b_w;   % exact ZOH discretization

% LQR weights (starting values)
Qw = 1;
Rw = 1;

% Discrete LQR gain
K_lqr_w = dlqr(Ad_w, Bd_w, Qw, Rw);

% Reference precompensator so constant omega_ref can be tracked
Nbar_lqr_w = (1 - Ad_w)/Bd_w + K_lqr_w;

open('ME416_Autonomy_Model.slx');