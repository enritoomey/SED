% Inicializacion
clear all; close all; clc;
% slCharacterEncoding('Windows-1252')

d2r = pi/180;
r2d = 180/pi;

% step_size = 0.001; % [s]
% max_step_size = 0.0005; % [s]

% Satellite
Mtot = 20.0; % [kg] masa total
Ixx = 210; % [kg-m2] tensor de inercia
Iyy = 200;
Izz = 118;
Ixy = 0;
Iyz = 0;
Izx = 0;

% Ruedas
% u = [0 0 1];% orientaci髇 de la rueda 1
% x=u(:).'/norm(u);
% yz=null(x).';
% xyz=[x;yz];%The rows of this matrix are the axes
% gs1 = [0 sin(0) cos(0)];
% gs2 = [0 0 1];
% gs3 = [0 0 1];
% gs4 = [0 0 1];
% Orientacion de las ruedas y pre-calculos
n = 4; % numero de ruedas
w1 = [-1 -1 -1]/sqrt(3); % orientaci贸n de la rueda 1
w2 = [-1 -1 +1]/sqrt(3); % orientaci贸n de la rueda 2
w3 = [-1 +1 +1]/sqrt(3); % orientaci贸n de la rueda 3
w4 = [-1 +1 -1]/sqrt(3); % orientaci贸n de la rueda 4 
W = [w1' w2' w3' w4'];
N = zeros(n,n,3);
for i=1:n
    for j=1:n
         N(i,j,:) = cross(W(:,i),W(:,j));
    end
end
Hmax = [10 12 11 9];
Iws = [5 5 5 5];

rpm2r = 2*pi/60;
r2rpm = 1/rpm2r;
omega0 = [2000 2000 2000 2000]*rpm2r;% en rpm


theta = [0;0;0];	% [1] actitud inicial

w0 = [0.2 0.15 -0.18]*(pi/180.0); % [deg/s]>[rad/s] velocidad angular inicial

Itot = [Ixx Ixy Izx; Ixy Iyy Iyz; Izx Iyz Izz];% [kg-m2] tensor de inercia
Itot_inv = inv(Itot);

tau = [10;0;0];
K=0.0;


