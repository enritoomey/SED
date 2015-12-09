%% 3.9
psi = 10*pi/180;
theta = -15*pi/180;
phi = 20*pi/180;

d_psi = 2*pi/180;
d_theta = 1*pi/180;
d_phi = 0;

M = [-sin(theta) 0 1;
    sin(phi)*cos(theta) cos(phi) 0;
    cos(phi)*cos(theta) -sin(phi) 0];

omega_b = M*[d_psi d_theta d_phi]'

BN = cosine_matrix([psi theta phi],[3 2 1]);

%verificacion
BN*BN'

omega_n = BN'*omega_b

%% 3.10
order = [3 1 3];
angles = [-30 40 20].*pi/180;
C = cosine_matrix(angles,order);

PHI = acos(0.5*(trace(C)-1));
e_vec = 1/2/sin(PHI)*[C(2,3)-C(3,2);C(3,1)-C(1,3);C(1,2)-C(2,1)];

fprintf('El angulo de rotacion PHI es %.2g\n El eje de rotacion es:\n  %0.3g\n  %0.3g\n  %0.3g',...
    PHI*180/pi,e_vec(1),e_vec(2),e_vec(3))

%% 3.11
PHI = 45*pi/180;
e_vec = 1/sqrt(3)*[1 1 1]';
e_mat = [0 -e_vec(3) e_vec(2);
         e_vec(3) 0 -e_vec(1);
         -e_vec(2) e_vec(1) 0];
C = expm(-PHI.*e_mat)

psi = atan(C(1,2)/C(1,1))*180/pi
theta = -asin(C(1,3))*180/pi
phi = atan(C(2,3)/C(3,3))*180/pi

%% 3.12 
% Verificamos que con la expresion 3.81 obtenemos la misma matriz C
C = eye(3)*cos(PHI)-sin(PHI)*e_mat+(1-cos(PHI))*e_vec*e_vec'

psi = atan(C(1,2)/C(1,1))*180/pi
theta = -asin(C(1,3))*180/pi
phi = atan(C(2,3)/C(3,3))*180/pi



