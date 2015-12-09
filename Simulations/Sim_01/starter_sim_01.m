% Simples Orbit simulator ever

%input
Mfix = 5.972e+24; %[kg]
pos1_0 = [(6.371e+6+500) 0  0]; %[m] posicion de m respecto a Mfix
vel1_0 = [0 7.9e+3 4.5e+3]; %[m/s]
delta_pos1 = [1500, 0, 0]; % [m/s]
pos2_0 = pos1_0+delta_pos1; %[m] posicion de m respecto a Mfix
vel2_0 = vel1_0; %[m/s]

%constantes
G = 6.674e-11;%[Nm²/kg²]
mu = G*Mfix;%[m^3/s^2]

% Orbita Chief
h = cross(pos1_0,vel1_0); %[m²/s]
h_norm = norm(h);
c = cross(v_ini,h) - mu*r_ini/norm(r_ini);
exc = norm(c)/mu;
T = 2*pi*norm(h)^3/(mu^2*sqrt((1-exc^2)^3));

% simulation
StopTime = 10*T;
step = 1;
sim('sim_01');