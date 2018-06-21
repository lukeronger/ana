/*
  This is where auxiliary functions for 
  analysis go. Any custom TSelector class
  functions that have been prototyped in 
  the class.cxx file should be implemented
  here.
 
*/

// Some examples

// method

void mySELECTOR::Calc_kine_P()
{
  
    TVector3 VelectronIn,VelectronOut,VprotonOut,VphotonOut,Vlepto,Vhadro,VhadroPP,Vvirtualphoton;
    TVector3 VX;



    VelectronIn    = ElectronBeam.Vect();
    VelectronOut   = El_Vec.Vect();
    VprotonOut     = Pr_Vec.Vect();
    VphotonOut     = Ph_Vec.Vect();
    Vvirtualphoton = (ElectronBeam-El_Vec).Vect();

    Vlepto         = VelectronIn.Cross(VelectronOut);
    Vhadro         = VprotonOut.Cross(Vvirtualphoton);
    VhadroPP       = VprotonOut.Cross(VphotonOut);

    Phi_Pr = 180./TMath::Pi()*Vlepto.Angle(Vhadro);
    Phi_Ph = 180./TMath::Pi()*Vlepto.Angle(VhadroPP);

    if(Vlepto.Dot(VprotonOut)>0.)  Phi_Pr = 360.-Phi_Pr;
    if(Vlepto.Dot(VphotonOut)<0.)  Phi_Ph = 360.-Phi_Ph;

    // VX = (ElectronBeam + Target_Vec - Pr_Vec - El_Vec).Vect();
    // Angl_X_g  = 180./TMath::Pi()*VphotonOut.Angle(VX);
    // Angl_hg_hp= 180./TMath::Pi()*Vhadro.Angle(VhadroPP);
    // if(VhadroPP.Dot(VprotonOut)<0)Angl_hg_hp = -Angl_hg_hp;


    t_Pr  = (Pr_Vec-PTarget_Vec).M2();
    t_Ph  = (ElectronBeam-El_Vec-Ph_Vec).M2();
    t_N=-100.;
    TLorentzVector BalV = ElectronBeam+Target_Vec-Ph_Vec-El_Vec-Pr_Vec;
    mm2_epg = (ElectronBeam+Target_Vec-Pr_Vec-El_Vec-Ph_Vec).M2();
    Xbal  = BalV.X();
    Ybal  = BalV.Y();
    Zbal  = BalV.Z();
    Ebal  = BalV.E();
}
void mySELECTOR::Calc_kine_N()
{
  
    TVector3 VelectronIn,VelectronOut,VneutronOut,VphotonOut,Vlepto,Vhadro,VhadroPP,Vvirtualphoton;
    TVector3 VX;

    Phi_N          = -900.;          // initialization - impossible value
    Phi_Ph          = -900.;          // initialization - impossible value
    Phi_Pr         = -900.;
    mm2_epg = -100.;

    VelectronIn    = ElectronBeam.Vect();
    VelectronOut   = El_Vec.Vect();
    VneutronOut     = N_Vec.Vect();
    VphotonOut     = Ph_Vec.Vect();
    Vvirtualphoton = (ElectronBeam-El_Vec).Vect();

    Vlepto         = VelectronIn.Cross(VelectronOut);
    Vhadro         = VneutronOut.Cross(Vvirtualphoton);
    VhadroPP       = VneutronOut.Cross(VphotonOut);

    Phi_N = 180./TMath::Pi()*Vlepto.Angle(Vhadro);
    Phi_Ph = 180./TMath::Pi()*Vlepto.Angle(VhadroPP);

    if(Vlepto.Dot(VneutronOut)>0.)  Phi_N = 360.-Phi_N;
    if(Vlepto.Dot(VphotonOut)<0.)  Phi_Ph = 360.-Phi_Ph;

    // VX = (ElectronBeam + Target_Vec - Pr_Vec - El_Vec).Vect();
    // Angl_X_g  = 180./TMath::Pi()*VphotonOut.Angle(VX);
    // Angl_hg_hp= 180./TMath::Pi()*Vhadro.Angle(VhadroPP);
    // if(VhadroPP.Dot(VneutronOut)<0)Angl_hg_hp = -Angl_hg_hp;

    //    Float_t nu = Ebeam-El_P;
    //    W = TMath::Sqrt(Nmass*Nmass + 2*Nmass*nu - Q2);
    t_N  = (N_Vec-NTarget_Vec).M2();
    t_Ph  = (ElectronBeam-El_Vec-Ph_Vec).M2();
    t_Pr = -100.;
    TLorentzVector BalV = ElectronBeam+Target_Vec-Ph_Vec-El_Vec-N_Vec;

    mm2_eng = (ElectronBeam+Target_Vec-N_Vec-El_Vec-Ph_Vec).M2();
    Xbal  = BalV.X();
    Ybal  = BalV.Y();
    Zbal  = BalV.Z();
    Ebal  = BalV.E();
}

void mySELECTOR::Calc_kine_MC()
{
  
  TVector3 VelectronIn,VelectronOut,VprotonOut,VneutronOut,VphotonOut,Vlepto,Vhadro,VhadroPP,Vvirtualphoton;
    TVector3 VX;

    p_spec=0;
    n_spec=0;
    Phi_MC          = -900.;          // initialization - impossible value
    t_Pr_MC = -900.;
    t_N_MC = -900.;
    VelectronIn.SetXYZ(0.,0.,Ebeam);
    VneutronOut.SetXYZ(-500.,-500.,-500.);
    VprotonOut.SetXYZ(-500.,-500.,-500.);
    Pr_Vec_MC.SetPxPyPzE(-500.,-500.,-500.,-500.);
    N_Vec_MC.SetPxPyPzE(-500.,-500.,-500.,-500.);

    if (MC_Particle_px->empty() || MC_Particle_py->empty() || MC_Particle_pz->empty() || MC_Particle_pid->empty())
    {
      cout<<"Skipped because of an event with empty: "
	  << (MC_Particle_px->empty() ? "MC_Particle_px " : " ")
	  << (MC_Particle_py->empty() ? "MC_Particle_py " : " ")
	  << (MC_Particle_pz->empty() ? "MC_Particle_pz " : " ")
	  << (MC_Particle_pid->empty() ? "MC_Particle_pid " : " ")
	  << std::endl;
      return;
    }
    
    VelectronOut.SetXYZ((*MC_Particle_px)[0],(*MC_Particle_py)[0],(*MC_Particle_pz)[0]);

    if((*MC_Particle_pid)[1]==2212.)
      {
	p_spec=1;
	VneutronOut.SetXYZ((*MC_Particle_px)[2],(*MC_Particle_py)[2],(*MC_Particle_pz)[2]);
	VprotonOut.SetXYZ((*MC_Particle_px)[1],(*MC_Particle_py)[1],(*MC_Particle_pz)[1]);
      }
    if((*MC_Particle_pid)[1]==2112.)
      {
	n_spec=1;
	VprotonOut.SetXYZ((*MC_Particle_px)[2],(*MC_Particle_py)[2],(*MC_Particle_pz)[2]);
	VneutronOut.SetXYZ((*MC_Particle_px)[1],(*MC_Particle_py)[1],(*MC_Particle_pz)[1]);
      }
    VphotonOut.SetXYZ((*MC_Particle_px)[3],(*MC_Particle_py)[3],(*MC_Particle_pz)[3]);
    Vvirtualphoton = (ElectronBeam-El_Vec).Vect();

    Vlepto         = VelectronIn.Cross(VelectronOut);
    if((*MC_Particle_pid)[1]==2112){
      Vhadro         = VprotonOut.Cross(Vvirtualphoton);
      VhadroPP       = VprotonOut.Cross(VphotonOut);
    }

    if((*MC_Particle_pid)[1]==2212){
      Vhadro         = VneutronOut.Cross(Vvirtualphoton);
      VhadroPP       = VneutronOut.Cross(VphotonOut);
    }
    Phi_MC = 180./TMath::Pi()*Vlepto.Angle(Vhadro);

    if((*MC_Particle_pid)[1]==2112 && Vlepto.Dot(VprotonOut)>0.)  Phi_MC = 360.-Phi_MC;
    if((*MC_Particle_pid)[1]==2212 && Vlepto.Dot(VneutronOut)>0.)  Phi_MC = 360.-Phi_MC;
    VX = (ElectronBeam + Target_Vec - Pr_Vec - El_Vec).Vect();

    Float_t pmom[4];
    for(Int_t i=0;i<4;i++)
      {
	pmom[i]=TMath::Sqrt((*MC_Particle_px)[i]*(*MC_Particle_px)[i]+(*MC_Particle_py)[i]*(*MC_Particle_py)[i]+(*MC_Particle_pz)[i]*(*MC_Particle_pz)[i]);
      }

    El_Vec_MC.SetPxPyPzE((*MC_Particle_px)[0],(*MC_Particle_py)[0],(*MC_Particle_pz)[0],pmom[0]);
    El_P_MC=El_Vec_MC.P();
    El_Theta_MC=180./TMath::Pi()*El_Vec_MC.Theta();
    El_Phi_MC=180./TMath::Pi()*El_Vec_MC.Phi();

    if((*MC_Particle_pid)[1]==2112.){
      Pr_Vec_MC.SetPxPyPzE((*MC_Particle_px)[2],(*MC_Particle_py)[2],(*MC_Particle_pz)[2],TMath::Sqrt(pmom[2]*pmom[2]+Pmass*Pmass));
      Pr_P_MC=Pr_Vec_MC.P();
      Pr_Theta_MC=180./TMath::Pi()*Pr_Vec_MC.Theta();
      Pr_Phi_MC=180./TMath::Pi()*Pr_Vec_MC.Phi();
      N_Vec_MC.SetPxPyPzE((*MC_Particle_px)[1],(*MC_Particle_py)[1],(*MC_Particle_pz)[1],TMath::Sqrt(pmom[1]*pmom[1]+Nmass*Nmass));
      N_P_MC=N_Vec_MC.P();
      N_Theta_MC=180./TMath::Pi()*N_Vec_MC.Theta();
      N_Phi_MC=180./TMath::Pi()*N_Vec_MC.Phi();
    }

    if((*MC_Particle_pid)[1]==2212.){
      N_Vec_MC.SetPxPyPzE((*MC_Particle_px)[2],(*MC_Particle_py)[2],(*MC_Particle_pz)[2],TMath::Sqrt(pmom[2]*pmom[2]+Nmass*Nmass));
      N_P_MC=N_Vec_MC.P();
      N_Theta_MC=180./TMath::Pi()*N_Vec_MC.Theta();
      N_Phi_MC=180./TMath::Pi()*N_Vec_MC.Phi();
      Pr_Vec_MC.SetPxPyPzE((*MC_Particle_px)[1],(*MC_Particle_py)[1],(*MC_Particle_pz)[1],TMath::Sqrt(pmom[1]*pmom[1]+Pmass*Pmass));
      Pr_P_MC=Pr_Vec_MC.P();
      Pr_Theta_MC=180./TMath::Pi()*Pr_Vec_MC.Theta();
      Pr_Phi_MC=180./TMath::Pi()*Pr_Vec_MC.Phi();
    }

    Ph_Vec_MC.SetPxPyPzE((*MC_Particle_px)[3],(*MC_Particle_py)[3],(*MC_Particle_pz)[3],pmom[3]);
    Ph_P_MC=Ph_Vec_MC.P();
    Ph_Theta_MC=180./TMath::Pi()*Ph_Vec_MC.Theta();
    Ph_Phi_MC=180./TMath::Pi()*Ph_Vec_MC.Phi();

    Float_t nu = Ebeam-El_P_MC;
    Q2_MC = 4*Ebeam*El_Vec_MC.P()*TMath::Power(TMath::Sin(El_Vec_MC.Theta()/2),2.);
    Xbj_MC = Q2_MC/(2*Pmass*(Ebeam-El_P_MC));
    if((*MC_Particle_pid)[1]==2112.)W_MC = TMath::Sqrt(Pmass*Pmass + 2*Pmass*nu - Q2_MC);
    if((*MC_Particle_pid)[1]==2212.)W_MC = TMath::Sqrt(Nmass*Nmass + 2*Nmass*nu - Q2_MC);
    if((*MC_Particle_pid)[1]==2112.)t_Pr_MC  = (Pr_Vec_MC-Target_Vec).M2();
    if((*MC_Particle_pid)[1]==2212.)t_N_MC = (N_Vec_MC-Target_Vec).M2();
    t_Ph_MC  = (ElectronBeam-El_Vec_MC-Ph_Vec_MC).M2();
}
void mySELECTOR::AddBranches()
{
   DVCS_tree = (TTree*) new TTree("DVCS","DVCS");
   DVCS_tree->Branch("RunNumber",&RunNumber,"RunNumber/I");
   DVCS_tree->Branch("pol_sign",&pol_sign,"pol_sign/I");
   //   DVCS_tree->Branch("bpola",&bpola,"bpola/F");
   DVCS_tree->Branch("helicity",&helicity,"helicity/I");
   DVCS_tree->Branch("TarPol",&TarPol,"TarPol/F");
   DVCS_tree->Branch("Q2",&Q2,"Q2/F");
   DVCS_tree->Branch("Xbj", &Xbj, "Xbj/F");
   DVCS_tree->Branch("W", &W, "W/F");
   DVCS_tree->Branch("t_Pr",&t_Pr,"t_Pr/F");
   DVCS_tree->Branch("t_Ph",&t_Ph,"t_Ph/F");
   DVCS_tree->Branch("t_N",&t_N,"t_N/F");
   DVCS_tree->Branch("Phi_Pr",&Phi_Pr,"Phi_Pr/F");
   DVCS_tree->Branch("Phi_Ph",&Phi_Ph,"Phi_Ph/F");
   DVCS_tree->Branch("Phi_N",&Phi_N,"Phi_N/F");
   // DVCS_tree->Branch("Angl_X_g",&Angl_X_g,"Angl_X_g/F");
   // DVCS_tree->Branch("Angl_hg_hp",&Angl_hg_hp,"Angl_hg_hp/F");
   DVCS_tree->Branch("Xbal",&Xbal,"Xbal/F");
   DVCS_tree->Branch("Ybal",&Ybal,"Ybal/F");
   DVCS_tree->Branch("Zbal",&Zbal,"Zbal/F");
   DVCS_tree->Branch("Ebal",&Ebal,"Ebal/F");
   DVCS_tree->Branch("nelec",&nelec,"nelec/I");
   DVCS_tree->Branch("El_P",&El_P,"El_P/F");
   DVCS_tree->Branch("El_Theta",&El_Theta,"El_Theta/F");
   DVCS_tree->Branch("El_Phi",&El_Phi,"El_Phi/F");
   DVCS_tree->Branch("nprot",&nprot,"nprot/I");
   DVCS_tree->Branch("Pr_P",&Pr_P,"Pr_P/F");
   DVCS_tree->Branch("Pr_Theta",&Pr_Theta,"Pr_Theta/F");
   DVCS_tree->Branch("Pr_Phi",&Pr_Phi,"Pr_Phi/F");
   DVCS_tree->Branch("N_P",&Pr_P,"N_P/F");
   DVCS_tree->Branch("N_Theta",&Pr_Theta,"N_Theta/F");
   DVCS_tree->Branch("N_Phi",&Pr_Phi,"N_Phi/F");
   DVCS_tree->Branch("nphotEC",&nphotEC,"nphotEC/I");
   DVCS_tree->Branch("Ph_EC_P",Ph_EC_P,"Ph_EC_P[nphotEC]/F");
   DVCS_tree->Branch("Ph_EC_Theta",Ph_EC_Theta,"Ph_EC_Theta[nphotEC]/F");
   DVCS_tree->Branch("Ph_EC_Phi",Ph_EC_Phi,"Ph_EC_Phi[nphotEC]/F");
   DVCS_tree->Branch("nphotFT",&nphotFT,"nphotFT/I");
   DVCS_tree->Branch("Ph_FT_P",Ph_FT_P,"Ph_FT_P[nphotFT]/F");
   DVCS_tree->Branch("Ph_FT_Theta",Ph_FT_Theta,"Ph_FT_Theta[nphotFT]/F");
   DVCS_tree->Branch("Ph_FT_Phi",Ph_FT_Phi,"Ph_FT_Phi[nphotFT]/F");
   DVCS_tree->Branch("Ph_det",&Ph_det,"Ph_det/I");
   DVCS_tree->Branch("nphot",&nphot,"nphot/I");
   DVCS_tree->Branch("Ph_P",&Ph_P,"Ph_P/F");
   DVCS_tree->Branch("Ph_Theta",&Ph_Theta,"Ph_Theta/F");
   DVCS_tree->Branch("Ph_Phi",&Ph_Phi,"Ph_Phi/F");
   DVCS_tree->Branch("mm2_epg",&mm2_epg,"mm2_epg/F");
   DVCS_tree->Branch("mm2_eng",&mm2_eng,"mm2_eng/F");
   DVCS_tree->Branch("El_P_MC",&El_P_MC,"El_P_MC/F");
   DVCS_tree->Branch("El_Theta_MC",&El_Theta_MC,"El_Theta_MC/F");
   DVCS_tree->Branch("El_Phi_MC",&El_Phi_MC,"El_Phi_MC/F");
   DVCS_tree->Branch("Pr_P_MC",&Pr_P_MC,"Pr_P_MC/F");
   DVCS_tree->Branch("Pr_Theta_MC",&Pr_Theta_MC,"Pr_Theta_MC/F");
   DVCS_tree->Branch("Pr_Phi_MC",&Pr_Phi_MC,"Pr_Phi_MC/F");
   DVCS_tree->Branch("N_P_MC",&N_P_MC,"N_P_MC/F");
   DVCS_tree->Branch("N_Theta_MC",&N_Theta_MC,"N_Theta_MC/F");
   DVCS_tree->Branch("N_Phi_MC",&N_Phi_MC,"N_Phi_MC/F");
   DVCS_tree->Branch("Ph_P_MC",&Ph_P_MC,"Ph_P_MC/F");
   DVCS_tree->Branch("Ph_Theta_MC",&Ph_Theta_MC,"Ph_Theta_MC/F");
   DVCS_tree->Branch("Ph_Phi_MC",&Ph_Phi_MC,"Ph_Phi_MC/F");
   DVCS_tree->Branch("Q2_MC",&Q2_MC,"Q2_MC/F");
   DVCS_tree->Branch("Xbj_MC", &Xbj_MC, "Xbj_MC/F");
   DVCS_tree->Branch("W_MC", &W_MC, "W_MC/F");
   DVCS_tree->Branch("t_Pr_MC",&t_Pr_MC,"t_Pr_MC/F");
   DVCS_tree->Branch("t_N_MC",&t_N_MC,"t_N_MC/F");
   DVCS_tree->Branch("t_Ph_MC",&t_Ph_MC,"t_Ph_MC/F");
   DVCS_tree->Branch("Phi_MC",&Phi_MC,"Phi_MC/F");
   DVCS_tree->Branch("n_spec",&n_spec,"n_spec/I");
   DVCS_tree->Branch("p_spec",&p_spec,"p_spec/I");
}
void mySELECTOR::AddMCBranches()
{
   MC_tree = (TTree*) new TTree("MC","MC");
   MC_tree->Branch("El_P_MC",&El_P_MC,"El_P_MC/F");
   MC_tree->Branch("El_Theta_MC",&El_Theta_MC,"El_Theta_MC/F");
   MC_tree->Branch("El_Phi_MC",&El_Phi_MC,"El_Phi_MC/F");
   MC_tree->Branch("Pr_P_MC",&Pr_P_MC,"Pr_P_MC/F");
   MC_tree->Branch("Pr_Theta_MC",&Pr_Theta_MC,"Pr_Theta_MC/F");
   MC_tree->Branch("Pr_Phi_MC",&Pr_Phi_MC,"Pr_Phi_MC/F");
   MC_tree->Branch("N_P_MC",&N_P_MC,"N_P_MC/F");
   MC_tree->Branch("N_Theta_MC",&N_Theta_MC,"N_Theta_MC/F");
   MC_tree->Branch("N_Phi_MC",&N_Phi_MC,"N_Phi_MC/F");
   MC_tree->Branch("Ph_P_MC",&Ph_P_MC,"Ph_P_MC/F");
   MC_tree->Branch("Ph_Theta_MC",&Ph_Theta_MC,"Ph_Theta_MC/F");
   MC_tree->Branch("Ph_Phi_MC",&Ph_Phi_MC,"Ph_Phi_MC/F");
   MC_tree->Branch("Q2_MC",&Q2_MC,"Q2_MC/F");
   MC_tree->Branch("Xbj_MC", &Xbj_MC, "Xbj_MC/F");
   MC_tree->Branch("W_MC", &W_MC, "W_MC/F");
   MC_tree->Branch("t_Pr_MC",&t_Pr_MC,"t_Pr_MC/F");
   MC_tree->Branch("t_N_MC",&t_N_MC,"t_N_MC/F");
   MC_tree->Branch("t_Ph_MC",&t_Ph_MC,"t_Ph_MC/F");
   MC_tree->Branch("Phi_MC",&Phi_MC,"Phi_MC/F");
   MC_tree->Branch("n_spec",&n_spec,"n_spec/I");
   MC_tree->Branch("p_spec",&p_spec,"p_spec/I");
}
void mySELECTOR::find_closest(Int_t begin, vector<double> theta, vector<double> phi, vector<double> beta){
  if((begin+1)>=static_cast<int>(theta.size()))return;
  for(int i=begin+1;i<static_cast<int>(theta.size());i++){
      // double distance = sqrt((theta.at(begin)-theta.at(i))*(theta.at(begin)-theta.at(i))/sigmaTheta(theta.at(begin))/sigmaTheta(theta.at(i))
      //                +(phi.at(begin)-phi.at(i))*(phi.at(begin)-phi.at(i))/sigmaPhi(phi.at(begin))/sigmaPhi(phi.at(i))
      //                +(beta.at(begin)-beta.at(i))*(beta.at(begin)-beta.at(i))/sigmaBeta(beta.at(begin))/sigmaBeta(beta.at(i))); 
    double distance = sqrt((theta.at(begin)-theta.at(i))*(theta.at(begin)-theta.at(i))+(phi.at(begin)-phi.at(i))*(phi.at(begin)-phi.at(i))/+(beta.at(begin)-beta.at(i))*(beta.at(begin)-beta.at(i))); 
    
      if(distance>5)continue;
      else{
         if(distance<clustering_closest_distance){
            cluster_subA = begin;
            cluster_subB = i;
         }
      }
   }
   find_closest(begin+1, theta, phi, beta);
}

