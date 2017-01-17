// PlanetOrbit.cc
// Takes inputted initial conditions and uses Euler's simulator and Leapfrog to generate an output file, which can be plotted in gnuplot. 
// Usage: ./PlanetOrbit
// To plot data use >gnuplot "PlotLeap.gnu" with output GIF or output JPEG for animation or image.

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define D 3 // dimensionality
#define G 6.67408e-11 // G
static double M=0; // mass of "sun" at (0,0) in kg
static double dt=0; // time step dt
static double Tt=2000; // total simulation time, is 2000s by default

struct Planet {
	double x[D]; // (x,y) coordinates
	double v[D]; // velocity
	double F[D]; // force
	double m; // mass of planet
	double sqrd; // square distance (length of position vector)
	double KE; // kinetic energy
	double PE; // potential energy from field
	double E; // total energy
	double AM; // angular momentum about origin
} ;

struct SolarSystem {
	Planet planet1;
	Planet planet2;
	Planet Sun;
} ;

void showState(Planet &p, double T, char const c[]);//Function which outputs the planet's state to a specified file at a time T
double compSqDist(Planet &p1, Planet &p2);//Function which computes the distance between two planets.
void gravForce(SolarSystem &s);//Function which computes the force on all bodies for all other bodies.
void PositionStep(Planet &p);//Function which computes position step over dt.
void VelocityStep(Planet &p);//Function which computes velocity step over dt.
void ComputeEnergy(Planet &p);//Function which computes all energies of the body.
void ComputeAM(Planet &p);//Function which computes angular momentum of the body.
void Leapfrog(SolarSystem &s, char const c[], char const d[]);//Function which implements the Leapfrog method.
void LeapPositionStep(Planet &p);//Function which computes position step over 0.5*dt.
void fileWipe(char const c[]);//Function which clears a file of previous data (wipe).

int main()
{
	SolarSystem s;//Declare all bodies.
	cout << "Program to calculate trajectories and data about trajectories from sets of inital data." << endl << endl;
	//Specifying planet orbital parameters.
	s.planet1.x[0]=0e+11; s.planet1.x[1]=1e+11;
	s.planet1.v[0]=3.5e+4; s.planet1.v[1]=0; //s.planet1.v[2]=0; <- Used to produce 3d binary system.
	s.planet2.x[0]=0e+11; s.planet2.x[1]=1e+11+0.05*3.85e+8, // s.planet2.x[2]=3.85e+8; <- Used to produce 3d binary system.
	s.planet2.v[0]=3.5e+4; s.planet2.v[1]=0; //s.planet2.v[2]=1.022e+3; <- Used to produce 3d binary system.
	s.Sun.x[0]=0e+11; s.Sun.x[1]=0e+11;
	s.Sun.v[0]=0; s.Sun.v[1]=0;

	s.Sun.m=1.989e+30; // Define solar mass in struct s.Sun just incase
	
	dt=0.25*86400; // In days
	Tt=5*3.154e+7; // In years
	M=1.989e+30; // Solar mass
	s.planet1.m=5.972e+24; // Terran mass
	s.planet2.m=0*7.342e+22+1*5.972e+24; // Lunar mass or Terran mass
	cout << endl << "Generating data tables..." << endl;
	fileWipe("LeapData.txt");// Wipe files ready for new input.
	fileWipe("LeapData2.txt");
	Leapfrog(s,"LeapData.txt","LeapData2.txt");// Perform Leapfrog method.
}

void fileWipe(char const c[])
{
	ofstream fout;
	fout.open(c, ios::trunc);
	fout.close(); // Wipes data file for new data entry.
}

void showState(Planet &p, double T, char const c[])
{
	ofstream fout;
	fout.open(c, ios::app); // Opens file in append mode.
	if (fout.good()){
	for (int n=0; n < D; n++) {
		fout << p.x[n] << "\t"; }
	for (int m=0; m < D; m++) {
		fout << p.v[m] << "\t"; }
	for (int j=0; j < D; j++) {
		fout << p.F[j] << "\t"; }
	fout << T << "\t";
	fout << p.AM << "\t" << p.KE << "\t" << p.PE << "\t" << p.E << "\t";
	fout << endl;
	fout.close();} else {cout << "Error, file could not be read." << endl;} // Prints all states of the body.
}	

double compSqDist(Planet &p1, Planet &p2)
{
	double sum=0, answer=0;
	for (int i=0; i < D; i++) {
		sum = sum + pow((p1.x[i]-p2.x[i]),2); }
	return sqrt(sum);
}

void gravForce(SolarSystem &s)
{
	double dsolar1, dplan12, dsolar2;
	dsolar1=compSqDist(s.planet1,s.Sun);
	dplan12=compSqDist(s.planet1,s.planet2);
	dsolar2=compSqDist(s.planet2,s.Sun); // Update distances.
	double A= static_cast<double>(-1*G); // A gives the form of the law i.e. scale factor from vector x->F
	// Has this form for gravitation, from Hooke's A=k, for electromag = Qq/(4*pi*E0*pow(p.sqrd,3)) etc
	for (int i=0; i < D; i++) {
		s.planet1.F[i]=(A*M*s.planet1.m*s.planet1.x[i]/pow(dsolar1,3))+(A*s.planet2.m*s.planet1.m*((s.planet2.x[i]-s.planet1.x[i])/pow(dplan12,3)));
		s.planet2.F[i]=(A*M*s.planet2.m*s.planet2.x[i]/pow(dsolar2,3))+(A*s.planet1.m*s.planet2.m*((s.planet1.x[i]-s.planet2.x[i])/pow(dplan12,3)));}
} //Forces updated.

void PositionStep(Planet &p)
{
	for (int i=0; i < D; i++) {
		p.x[i]=p.x[i]+p.v[i]*dt;} //Increment by dt*v
}

void LeapPositionStep(Planet &p)
{
	for (int i=0; i < D; i++) {
		p.x[i]=p.x[i]+p.v[i]*0.5*dt;} // Increment by 0.5dt*v
}

void VelocityStep(Planet &p)
{
	for (int i=0; i < D; i++) {
		p.v[i]=p.v[i]+(p.F[i]/p.m)*dt;} // Increment by (f/m)dt
}

void ComputeEnergy(Planet &p) //Only works in the 1 body 1 sun case.
{
	double velmag=0; 
	for (int i=0; i < D; i++) {
		velmag = velmag + pow(p.v[i],2);}
	velmag = sqrt(velmag);
	p.KE=0.5*p.m*pow(velmag,2);
	p.PE=static_cast<double>(G*M)*p.m/p.sqrd;
	p.E=p.KE+p.PE;
}

void ComputeAM(Planet &p) //Only works in the 1 body 1 sun case.
{
	double velmag=0;
	for (int i=0; i < D; i++) {
		velmag = velmag + pow(p.v[i],2);}
	velmag = sqrt(velmag);
	double dot=0;
	for (int i=0; i < D; i++) {
		dot = dot + p.x[i]*p.v[i];}
	double vsin=velmag*sin(acos(dot/(p.sqrd*velmag)));
	p.AM=p.sqrd*p.m*vsin;
}

void Leapfrog(SolarSystem &s, char const c[], char const d[])
{
	double T=0; //Running time counter.
	while (T<=Tt) {
		LeapPositionStep(s.planet1);//Interspersed calculation.
		LeapPositionStep(s.planet2);
		T=T+0.5*dt;
		gravForce(s);
		VelocityStep(s.planet1);
		VelocityStep(s.planet2);
		LeapPositionStep(s.planet1);
		LeapPositionStep(s.planet2);
		T=T+0.5*dt;
		ComputeEnergy(s.planet1);
		ComputeEnergy(s.planet2);
		ComputeAM(s.planet1);
		ComputeAM(s.planet2);
		showState(s.planet1,T,c);
		showState(s.planet2,T,d);
	}
}
