#ifndef DD_TIBLayerAlgo_h
#define DD_TIBLayerAlgo_h

#include <map>
#include <string>
#include <vector>
#include "DetectorDescription/Base/interface/DDTypes.h"
#include "DetectorDescription/Algorithm/interface/DDAlgorithm.h"

class DDTIBLayerAlgo : public DDAlgorithm {
 public:
  //Constructor and Destructor
  DDTIBLayerAlgo(); 
  virtual ~DDTIBLayerAlgo();
  
  void initialize(const DDNumericArguments & nArgs,
		  const DDVectorArguments & vArgs,
		  const DDMapArguments & mArgs,
		  const DDStringArguments & sArgs,
		  const DDStringVectorArguments & vsArgs);

  void execute();

private:

  std::string              idNameSpace;    //Namespace of this and ALL parts
  std::string              genMat;         //General material name
  double                   detectorTilt;   //Detector Tilt
  double                   layerL;         //Length of the layer
  double                   detectorTol;    //Tolerance 
  double                   detectorW;      //Width     of detector layer
  double                   detectorT;      //Thickness       .........
  double                   coolTubeW;      //Width     of layer with cable+cool
  double                   coolTubeT;      //Thickness       .........

  double                   radiusLo;       //Radius for detector at lower level
  double                   phioffLo;       //Phi offset             ......
  int                      stringsLo;      //Number of strings      ......
  std::string              detectorLo;     //Detector string name   ......
  double                   roffDetLo;      //Radial offset          ......
  std::string              coolCableLo;    //Cable+Cool name        ......
  double                   roffCableLo;    //Radial offset          ......

  double                   radiusUp;       //Radius for detector at upper level
  double                   phioffUp;       //Phi offset             ......
  int                      stringsUp;      //Number of strings      ......
  std::string              detectorUp;     //Detector string name   ......
  double                   roffDetUp;      //Radial offset          ......
  std::string              coolCableUp;    //Cable+Cool name        ......
  double                   roffCableUp;    //Radial offset          ......

  double                   cylinderT;      //Cylinder thickness
  double                   cylinderInR;    //Cylinder inner radius
  std::string              cylinderMat;    //Cylinder material
  double                   MFRingInR;      //Inner Manifold Ring Inner Radius 
  double                   MFRingOutR;     //Outer Manifold Ring Outer Radius 
  double                   MFRingT;        //Manifold Ring Thickness
  double                   MFRingDz;       //Manifold Ring Half Lenght
  std::string              MFIntRingMat;      //Manifold Ring Material
  std::string              MFExtRingMat;      //Manifold Ring Material

  double                   supportT;       //Cylinder barrel CF skin thickness

  std::string              centMat;        //Central rings  material
  std::vector<double>      centRing1par;   //Central rings parameters
  std::vector<double>      centRing2par;   //Central rings parameters

  std::string              ribMat;         //Rib material
  std::vector<double>      ribW;           //Rib width
  std::vector<double>      ribPhi;         //Rib Phi position

  int                      dohmN;              //Number of phi sectors for DOHMs
  std::vector<double>      dohmList;           //List of DOHMs
  double                   dohmCarrierW;       //DOHM Carrier Width
  double                   dohmCarrierT;       //DOHM Carrier Thickness
  double                   dohmCarrierR;       //DOHM Carrier Radial Height
  std::string              dohmCarrierMaterial;//DOHM Carrier Material
  std::string              dohmCableMaterial;  //DOHM Cable Material
  double                   dohmPrimW;          //DOHM PRIMary Width
  double                   dohmPrimL;          //DOHM PRIMary Length
  double                   dohmPrimT;          //DOHM PRIMary Thickness
  std::string              dohmPrimMaterial;   //DOHM PRIMary Material
  double                   dohmAuxW;           //DOHM AUXiliary Width
  double                   dohmAuxL;           //DOHM AUXiliary Length
  double                   dohmAuxT;           //DOHM AUXiliary Thickness
  std::string              dohmAuxMaterial;    //DOHM AUXiliary Material
  std::string              dohmRotPlus;        //DOHM Rotation matrix for TIB+
  std::string              dohmRotMinus;       //DOHM Rotation matrix for TIB-

};

#endif
