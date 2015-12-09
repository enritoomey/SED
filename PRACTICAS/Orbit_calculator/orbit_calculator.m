close all; clear all; clc
%% Orbitas
Mfix = 5.972e+24; %[kg]
m = 40; %[kg]
r_ini = [(6.371e+6+500) 0  0]; %[m] posicion de m respecto a Mfix
v_ini = [0 7.9e+3 4.5e+3]; %[m/s]


%constantes
G = 6.674e-11;%[Nm²/kg²]
mu = G*(Mfix+m);

% tiempo de simulacion
n = 1; % en periodos;

% momento angular
h = cross(r_ini,v_ini); %[m²/s]
h_norm = norm(h);

% constantes de la orbita
c = cross(v_ini,h) - mu*r_ini/norm(r_ini);
exc = norm(c)/mu;
p = norm(h)^2/mu;
f_ini = cos((p/norm(r_ini)-1)/exc);
C = [r_ini/norm(r_ini);cross(h,r_ini)/norm(cross(h,r_ini));h/h_norm];
i_ang = acos(h(3)/h_norm);
if C(2,3) == 0;
    w = 0;
else 
    w = atan(C(1,3)/C(2,3))-f_ini;
end
if C(3,2) == 0;
    Omega = 0;
else
    Omega = atan(-C(1,3)/C(2,3));
end

% Periodo
P = 2*pi*norm(h)^3/(mu^2*sqrt((1-exc^2)^3));


% Integracion:
dt = 0.1;%[s]
time = 0:dt:P*n;
f = zeros(length(time),1);
f(1) = f_ini;
for i =2:length(f)
    k1 = orbit(f(i-1),mu,p,exc);
    k2 = orbit(f(i-1)+dt/2*k1,mu,p,exc);
    k3 = orbit(f(i-1)+dt/2*k2,mu,p,exc);
    k4 = orbit(f(i-1)+dt*k3,mu,p,exc);
    f(i) = f(i-1)+dt/6*(k1+2*k2+2*k3+k4);
end
r = p./(1+exc.*cos(f));

x = r.*(cos(Omega)*cos(w+f)-sin(Omega)*sin(w+f)*cos(i_ang));
y = r.*(sin(Omega)*cos(w+f)+cos(Omega)*sin(w+f)*cos(i_ang));
z = r.*(sin(w+f)*sin(i_ang));
v_x = -mu/h_norm*(cos(Omega)*(sin(w+f)+exc*sin(w))+sin(Omega)*cos(i_ang)*(cos(w+f)+exc*cos(w)));
v_y = -mu/h_norm*(sin(Omega)*(sin(w+f)+exc*sin(w))-cos(Omega)*cos(i_ang)*(cos(w+f)+exc*cos(w)));
v_z = -mu/h_norm*(-sin(i_ang)*(cos(w+f)+exc*cos(w)));

figure()
plot3(x,y,z,'Color','red','LineWidth',2,'LineStyle','--')
axis equal; hold on;
[xe,ye,ze] = sphere(20);
surface(xe*6.371e+6,ye*6.371e+6,ze*6.371e+6)

% cantidad de esferas por orbita
n_esferas = 10;
len = 1e3;
for j=0:n_esferas;
    i = floor((j/n_esferas)*P/dt)+1;
    [xe,ye,ze] = sphere(10);
    surface(xe*5e5+x(i),ye*5e5+y(i),ze*5e5+z(i))
    arrow3d([x(i),x(i)+len*v_x(i)],[y(i),y(i)+len*v_y(i)],[z(i),z(i)+len*v_z(i)],0.95,5e+4,7e+4,[0,0,0]);
    text(x(i),y(i),z(i),num2str(j));
end