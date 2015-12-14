from numpy import *
time = 15*24*3600 #[s]
print(time)

# Earth data
Re = 6.371e6 #[km]
J2 = 1082.63e-6
mu = 3.986004418e14

# Orbit characteristics
a = Re + 500e3 #[km]
gamma = J2/2*(Re/a)**2
n = sqrt(mu/a**3)
T = 2*pi/n
print(T)
i = 55*pi/180

# Pregunta 4.1.c)
dphi = 3/2*gamma*(5*cos(i)**2-1)
Du = 2*pi*time/T
print(Du)
Dphi = Du*dphi
print("The relative excentricity vector rotates "+str(Dphi*180/pi)+" deg in 15 days at LEO.")

# Pregunta 4.1.e)
di = 5*pi/180 #[rad]
Dtheta = 3*gamma*sin(i*di)**2*Du
print("The relative inclination vector rotates "+str(Dtheta*180/pi)+" deg in 15 days at LEO.")

#pregunta 4.1.f)
da = 1.5e3/a #1.5km
dlambda_J2 = -21/1*gamma*sin(2*i)*di
dlambda_kepler = -3/2*da
print("The relative mean longuitude translates"+str(dlambda_J2*Du*180/pi)+" deg due to Je effects and "+str(dlambda_kepler*Du*180/pi)+" deg por da (kepler)")

da_bounded = dlambda_J2*2/3
print("da = "+str(da_bounded)+" for bounded orbits, with "+str(da_bounded*a/1000)+" km of difference in semi-mayor axis.") 
