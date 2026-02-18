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
gravity = [0 0 -9.819]'; %Inertial frame

Cd0 = 0.61; % coefficient of drag 
A = 0.0045; % frontal area m^2
rho = 1.225; % air density kg/m^3

% fin angles manually set
a1 = deg2rad(0);
a2 = deg2rad(0);
a3 = deg2rad(0);
a4 = deg2rad(0);

fin_angles = [a1 a2 a3 a4]';

Cl = 0.191; %average fin lift coefficient at 5 deg AoA
Af = 0.003689; % fin area
%Fl = 1/2*Cl*A*Vb^2
lr = 34.15; % center of lift from root of fin
fr = (75/2 + lr)/1000; % Fin moment arm (m)

Cg = 0.5;
Cp = 0.4;
dfins = 0.7;
%Cl = 0.0334462*a
fin_positions = [dfins-Cg 0 fr; dfins-Cg -fr 0; dfins-Cg 0 -fr; dfins-Cg fr 0]; 
r_cp = [Cg-Cp 0 0]';

N = [0 1 0; 0 0 1; 0 -1 0; 0 0 -1];
si = [0 0 1; 0 -1 0; 0 0 -1; 0 1 0];
ci = [cos(a1) sin(a1) 0; cos(a2) 0 sin(a2); cos(a3) sin(a3) 0; cos(a4) 0 sin(a4)];
ni = cross(si, ci);    

CNa = 12; % Normal force coefficient slope
Cmq = -20; % Pitch moment coefficient slope
Cnr = -20; %yaw moment slope
L = 1; % Length of the roxket

out = sim("openmodel.slx");
