clear all

% Body fixed frame, x: roll axis, y: pitch axis, z: yaw axis
% Inertial frame, NED (x: North, y: East, z: Down)
mf = 1.535; % full mass kg
me = 1.420; % empty mass kg
bt = 2.5; % motor burnout time s
dmdt = -(mf - me)/bt; % rate of mass change (linear)
Ie = [0.0028 0 0; 0 0.43 0; 0 0 0.43];% Empty inertia matrix
If = [0.0028 0 0; 0 0.48 0; 0 0 0.48]; %Full inertia matrix

%Forces
Thrust = [75 0 0]'; %Body fixed frame
gravity = [0 0 -9.819/4]'; %Inertial frame

Cd0 = 0.61; % coefficient of drag 
A = 0.0045; % frontal area m^2
rho = 1.225; % air density kg/m^3

% fin angles manually set
% a1 = deg2rad(0);
% a2 = deg2rad(1);
% a3 = deg2rad(0);
% a4 = deg2rad(1);
% 
% fin_angles = [a1 a2 a3 a4]';

%Cl = 0.191; %average fin lift coefficient at 5 deg AoA
Af = 0.003689; % fin area
%Fl = 1/2*Cl*A*Vb^2
lr = 34.15; % center of lift from root of fin
fr = (75/2 + lr)/1000; % Fin moment arm (m)

%Cg = 0.5;
Cp = -0.3;
dfins = 0.2;
%Cl = 0.0334462*a
fin_positions = [dfins 0 fr; dfins -fr 0; dfins 0 -fr; dfins fr 0]; 
r_cp = [-Cp 0 0]';

N = [0 -1 0; 0 0 -1; 0 1 0; 0 0 1]; % Canard Lift directions
si = [0 0 1; 0 -1 0; 0 0 -1; 0 1 0]; % Canard span directions 

Cla = 4; %1.975;
CNa = 12; % Normal force coefficient slope
Cmq = -20; % Pitch moment coefficient slope
Cnr = -20; %yaw moment slope
Clp = -0.5; % roll moment slope
L = 1; % Length of the rocket
b = 0.14;

% PID target values
ref_w = pi; %Target rolling rate (rad/s)
refx = 60;
refy = 60;
ref_phi = pi/2;

% Pitch and Yaw PID gains
Pgainx = deg2rad(20)/(refx-50);
Pgainy = deg2rad(20)/(refy-50);
Dgain = 0.1;
Igain = 0.01;

% Roll orientation PID gains
Pgainphi = deg2rad(10)/ref_phi;
Dgainphi = 0.02;
Igainphi = 0;

tau = 0.05; % actuatuor time constant for fin servos
alim = deg2rad(800); % servo rate limiter

Vsafe = 0.1; %

out = sim("closedmodel.slx");
