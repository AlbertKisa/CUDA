
#include <TxBessel.h>

#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;
using namespace Bess;


static const double  bess_xj00=5.783185962946785;
static const double  bess_xj10=3.047126234366209e1;
static const double  bess_xj01=1.468197064212389e1;
static const double  bess_xj11=4.921845632169460e1;
static const double  bess_twoopi=0.6366197723675813;
static const double  bess_pio4=0.7853981633974483;
static const double  bess_j0r[]={1.682397144220462e-4,2.058861258868952e-5,
				 5.288947320067750e-7,5.557173907680151e-9,2.865540042042604e-11,
				 7.398972674152181e-14,7.925088479679688e-17};
static const double  bess_j0s[]={1.0,1.019685405805929e-2,5.130296867064666e-5,
				 1.659702063950243e-7,3.728997574317067e-10,
				 5.709292619977798e-13,4.932979170744996e-16};
static const double  bess_j0pn[]={9.999999999999999e-1,1.039698629715637,
				  2.576910172633398e-1,1.504152485749669e-2,1.052598413585270e-4};
static const double  bess_j0pd[]={1.0,1.040797262528109,2.588070904043728e-1,
				  1.529954477721284e-2,1.168931211650012e-4};
static const double  bess_j0qn[]={-1.562499999999992e-2,-1.920039317065641e-2,
				  -5.827951791963418e-3,-4.372674978482726e-4,-3.895839560412374e-6};
static const double  bess_j0qd[]={1.0,1.237980436358390,3.838793938147116e-1,
				  3.100323481550864e-2,4.165515825072393e-4};
static const double  bess_j1r[]={7.309637831891357e-5,3.551248884746503e-6,
				 5.820673901730427e-8,4.500650342170622e-10,1.831596352149641e-12,
				 3.891583573305035e-15,3.524978592527982e-18};
static const double  bess_j1s[]={1.0,9.398354768446072e-3,4.328946737100230e-5,
				 1.271526296341915e-7,2.566305357932989e-10,
				 3.477378203574266e-13,2.593535427519985e-16};
static const double  bess_j1pn[]={1.0,1.014039111045313,2.426762348629863e-1,
				  1.350308200342000e-2,9.516522033988099e-5};
static const double  bess_j1pd[]={1.0,1.012208056357845,2.408580305488938e-1,
				  1.309511056184273e-2,7.746422941504713e-5};
static const double  bess_j1qn[]={4.687499999999991e-2,5.652407388406023e-2,
				  1.676531273460512e-2,1.231216817715814e-3,1.178364381441801e-5};
static const double  bess_j1qd[]={1.0,1.210119370463693,3.626494789275638e-1,
				  2.761695824829316e-2,3.240517192670181e-4};
static const double  bess_y0r[]={-7.653778457189104e-3,-5.854760129990403e-2,
				 3.720671300654721e-4,3.313722284628089e-5,4.247761237036536e-8,
				 -4.134562661019613e-9,-3.382190331837473e-11,
				 -1.017764126587862e-13,-1.107646382675456e-16};
static const double  bess_y0s[]={1.0,1.125494540257841e-2,6.427210537081400e-5,
				 2.462520624294959e-7,7.029372432344291e-10,1.560784108184928e-12,
				 2.702374957564761e-15,3.468496737915257e-18,2.716600180811817e-21};
static const double  bess_y0pn[]={9.999999999999999e-1,1.039698629715637,
				  2.576910172633398e-1,1.504152485749669e-2,1.052598413585270e-4};
static const double  bess_y0pd[]={1.0,1.040797262528109,2.588070904043728e-1,
				  1.529954477721284e-2,1.168931211650012e-4};
static const double  bess_y0qn[]={-1.562499999999992e-2,-1.920039317065641e-2,
				  -5.827951791963418e-3,-4.372674978482726e-4,-3.895839560412374e-6};
static const double  bess_y0qd[]={1.0,1.237980436358390,3.838793938147116e-1,
				  3.100323481550864e-2,4.165515825072393e-4};
static const double  bess_y1r[]={-1.041835425863234e-1,-1.135093963908952e-5,
				 2.212118520638132e-4,1.270981874287763e-6,
				 -3.982892100836748e-8,-4.820712110115943e-10,
				 -1.929392690596969e-12,-2.725259514545605e-15};
static const double  bess_y1s[]={1.0,1.186694184425838e-2,7.121205411175519e-5,
				 2.847142454085055e-7,8.364240962784899e-10,1.858128283833724e-12,
				 3.018846060781846e-15,3.015798735815980e-18};
static const double  bess_y1pn[]={1.0,1.014039111045313,2.426762348629863e-1,
				  1.350308200342000e-2,9.516522033988099e-5};
static const double  bess_y1pd[]={1.0,1.012208056357845,2.408580305488938e-1,
				  1.309511056184273e-2,7.746422941504713e-5};
static const double  bess_y1qn[]={4.687499999999991e-2,5.652407388406023e-2,
				  1.676531273460512e-2,1.231216817715814e-3,1.178364381441801e-5};
static const double  bess_y1qd[]={1.0,1.210119370463693,3.626494789275638e-1,
				  2.761695824829316e-2,3.240517192670181e-4};

static const double  bess_i0p[]={9.999999999999997e-1,2.466405579426905e-1,
				 1.478980363444585e-2,3.826993559940360e-4,5.395676869878828e-6,
				 4.700912200921704e-8,2.733894920915608e-10,1.115830108455192e-12,
				 3.301093025084127e-15,7.209167098020555e-18,1.166898488777214e-20,
				 1.378948246502109e-23,1.124884061857506e-26,5.498556929587117e-30};
static const double  bess_i0q[]={4.463598170691436e-1,1.702205745042606e-3,
				 2.792125684538934e-6,2.369902034785866e-9,8.965900179621208e-13};
static const double  bess_i0pp[]={1.192273748120670e-1,1.947452015979746e-1,
				  7.629241821600588e-2,8.474903580801549e-3,2.023821945835647e-4};
static const double  bess_i0qq[]={2.962898424533095e-1,4.866115913196384e-1,
				  1.938352806477617e-1,2.261671093400046e-2,6.450448095075585e-4,
				  1.529835782400450e-6};
static const double  bess_i1p[]={5.000000000000000e-1,6.090824836578078e-2,
				 2.407288574545340e-3,4.622311145544158e-5,5.161743818147913e-7,
				 3.712362374847555e-9,1.833983433811517e-11,6.493125133990706e-14,
				 1.693074927497696e-16,3.299609473102338e-19,4.813071975603122e-22,
				 5.164275442089090e-25,3.846870021788629e-28,1.712948291408736e-31};
static const double  bess_i1q[]={4.665973211630446e-1,1.677754477613006e-3,
				 2.583049634689725e-6,2.045930934253556e-9,7.166133240195285e-13};
static const double  bess_i1pp[]={1.286515211317124e-1,1.930915272916783e-1,
				  6.965689298161343e-2,7.345978783504595e-3,1.963602129240502e-4};
static const double  bess_i1qq[]={3.309385098860755e-1,4.878218424097628e-1,
				  1.663088501568696e-1,1.473541892809522e-2,1.964131438571051e-4,
				  -1.034524660214173e-6};
static const double  bess_k0pi[]={1.0,2.346487949187396e-1,1.187082088663404e-2,
				  2.150707366040937e-4,1.425433617130587e-6};
static const double  bess_k0qi[]={9.847324170755358e-1,1.518396076767770e-2,
				  8.362215678646257e-5};
static const double  bess_k0p[]={1.159315156584126e-1,2.770731240515333e-1,
				 2.066458134619875e-2,4.574734709978264e-4,3.454715527986737e-6};
static const double  bess_k0q[]={9.836249671709183e-1,1.627693622304549e-2,
				 9.809660603621949e-5};
static const double  bess_k0pp[]={1.253314137315499,1.475731032429900e1,
				  6.123767403223466e1,1.121012633939949e2,9.285288485892228e1,
				  3.198289277679660e1,3.595376024148513,6.160228690102976e-2};
static const double  bess_k0qq[]={1.0,1.189963006673403e1,5.027773590829784e1,
				  9.496513373427093e1,8.318077493230258e1,3.181399777449301e1,
				  4.443672926432041,1.408295601966600e-1};
static const double  bess_k1pi[]={0.5,5.598072040178741e-2,1.818666382168295e-3,
				  2.397509908859959e-5,1.239567816344855e-7};
static const double  bess_k1qi[]={9.870202601341150e-1,1.292092053534579e-2,
				  5.881933053917096e-5};
static const double  bess_k1p[]={-3.079657578292062e-1,-8.109417631822442e-2,
				 -3.477550948593604e-3,-5.385594871975406e-5,-3.110372465429008e-7};
static const double  bess_k1q[]={9.861813171751389e-1,1.375094061153160e-2,
				 6.774221332947002e-5};
static const double  bess_k1pp[]={1.253314137315502,1.457171340220454e1,
				  6.063161173098803e1,1.147386690867892e2,1.040442011439181e2,
				  4.356596656837691e1,7.265230396353690,3.144418558991021e-1};
static const double  bess_k1qq[]={1.0,1.125154514806458e1,4.427488496597630e1,
				  7.616113213117645e1,5.863377227890893e1,1.850303673841586e1,
				  1.857244676566022,2.538540887654872e-2};



double Bess::bess_j0(const double x) 
{
  double nump,denp,numq,denq,y,z,ax,xx;
  ax=abs(x);

  if (ax < 8.0) {
    bess_rat(x,bess_j0r,bess_j0s,6,
	     y,z,nump,denp);
    return nump*(y-bess_xj00)*(y-bess_xj10)/denp;
  } else {
    bess_asp(bess_j0pn,bess_j0pd,bess_j0qn,bess_j0qd,1.,
	     ax,
	     y,z,xx,nump,denp,numq,denq);
    return sqrt(bess_twoopi/ax)*(cos(xx)*nump/denp-z*sin(xx)*numq/denq);
  }
}


double Bess::bess_j1(const double x) 
{
  double nump,denp,numq,denq,y,z,ax,xx;
  ax=abs(x);

  if (ax < 8.0) {
    bess_rat(x,bess_j1r,bess_j1s,6,
	     y,z,nump,denp);
    return x*nump*(y-bess_xj01)*(y-bess_xj11)/denp;
  } else {
    bess_asp(bess_j1pn,bess_j1pd,bess_j1qn,bess_j1qd,3.,
	     ax,
	     y,z,xx,nump,denp,numq,denq);
    double ans=sqrt(bess_twoopi/ax)*(cos(xx)*nump/denp-z*sin(xx)*numq/denq);
    return x > 0.0 ? ans : -ans;
  }
}


double Bess::bess_y0(const double x) 
{
  double nump,denp,numq,denq,y,z,ax,xx;

  if (x < 8.0) {
    double j0x = j0(x);
    bess_rat(x,bess_y0r,bess_y0s,8,
	     y,z,nump,denp);
    return nump/denp+bess_twoopi*j0x*log(x);
  } else {
    ax=x;
    bess_asp(bess_y0pn,bess_y0pd,bess_y0qn,bess_y0qd,1.,
	     ax,
	     y,z,xx,nump,denp,numq,denq);
    return sqrt(bess_twoopi/x)*(sin(xx)*nump/denp+z*cos(xx)*numq/denq);
  }
}


double Bess::bess_y1(const double x) 
{
  double nump,denp,numq,denq,y,z,ax,xx;

  if (x < 8.0) {
    double j1x = j1(x);
    bess_rat(x,bess_y1r,bess_y1s,7,
	     y,z,nump,denp);
    return x*nump/denp+bess_twoopi*(j1x*log(x)-1.0/x);
  } else {
    ax=x;
    bess_asp(bess_y1pn,bess_y1pd,bess_y1qn,bess_y1qd,3.,
	     ax,
	     y,z,xx,nump,denp,numq,denq);
    return sqrt(bess_twoopi/x)*(sin(xx)*nump/denp+z*cos(xx)*numq/denq);
  }
}


void Bess::bess_rat(const double x, const double *r, const double *s, const int n,
		    double& y, double& z, double& nump, double& denp) 
{
  y=x*x;
  z=64.0-y;
  nump=r[n];
  denp=s[n];
  for(int i=n-1;i>=0;i--) {
    nump=nump*z+r[i];
    denp=denp*y+s[i];
  }
}


void Bess::bess_asp(const double *pn, const double *pd, const double *qn, const double *qd, const double fac,
		    const double ax,
		    double& y, double& z, double& xx,  double& nump, double& denp, double& numq, double& denq) 
{
  z=8.0/ax;
  y=z*z;
  xx=ax-fac*bess_pio4;
  nump=pn[4];
  denp=pd[4];
  numq=qn[4];
  denq=qd[4];
  for (int i=3;i>=0;i--) {
    nump=nump*y+pn[i];
    denp=denp*y+pd[i];
    numq=numq*y+qn[i];
    denq=denq*y+qd[i];
  }	
}

double Bess::bess_i0(const double x) 
{
  double y,z,ax;

  if ((ax=abs(x)) < 15.0) {
    y = x*x;
    return bess_poly(bess_i0p,13,y)/bess_poly(bess_i0q,4,225.-y);
  } else {
    z=1.0-15.0/ax;
    return exp(ax)*bess_poly(bess_i0pp,4,z)/(bess_poly(bess_i0qq,5,z)*sqrt(ax));
  }
}


double Bess::bess_i1(const double x) 
{
  double y,z,ax;

  if ((ax=abs(x)) < 15.0) {
    y=x*x;
    return x*bess_poly(bess_i1p,13,y)/bess_poly(bess_i1q,4,225.-y);
  } else {
    z=1.0-15.0/ax;
    double ans=exp(ax)*bess_poly(bess_i1pp,4,z)/(bess_poly(bess_i1qq,5,z)*sqrt(ax));
    return x > 0.0 ? ans : -ans;
  }
}


double Bess::bess_k0(const double x) 
{
  double y,z,term;

  if (x <= 1.0) {
    z=x*x;
    term = bess_poly(bess_k0pi,4,z)*log(x)/bess_poly(bess_k0qi,2,1.-z);
    return bess_poly(bess_k0p,4,z)/bess_poly(bess_k0q,2,1.-z)-term;
  } else {
    z=1.0/x;
    return exp(-x)*bess_poly(bess_k0pp,7,z)/(bess_poly(bess_k0qq,7,z)*sqrt(x));
  }
}


double Bess::bess_k1(const double x) 
{
  double y,z,term;

  if (x <= 1.0) {
    z=x*x;
    term = bess_poly(bess_k1pi,4,z)*log(x)/bess_poly(bess_k1qi,2,1.-z);
    return x*(bess_poly(bess_k1p,4,z)/bess_poly(bess_k1q,2,1.-z)+term)+1./x;
  } else {
    z=1.0/x;
    return exp(-x)*bess_poly(bess_k1pp,7,z)/(bess_poly(bess_k1qq,7,z)*sqrt(x));
  }
}

double Bess::bess_poly(const double *cof, const int n, const double x) 
{
  double ans = cof[n];
  for (int i=n-1;i>=0;i--) ans = ans*x+cof[i];
  return ans;
}
