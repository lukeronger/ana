mySELECTOR::additions(){
  TTree *DVCS_tree; 
  TTree *MC_tree; 
  TFile *outfile; 
  Bool_t   firstCall; 
  void    AddBranches();
  void    AddMCBranches();
  void    Calc_kine_P();
  void    Calc_kine_MC();
  void    Calc_kine_N();
  void find_closest(Int_t begin, vector<double> theta, vector<double> phi, vector<double> beta);
  
  // Fixed size dimensions of array or collections stored in the TTree if any.
  Int_t nelec,nprot,nneut,nphotFT,nphotEC,nphot;  
  Int_t i_el,i_pr,i_n,i_phEC,i_phFT,i_ph;
  Int_t isortEC[40],isortIC[40];
  Int_t GoodECPhotIndex,GoodICPhotIndex;
  Int_t RunNumber,FileNumber;
  Int_t pol_sign,helicity;
  Int_t Ph_det;
  Float_t TarPol;
  Float_t Ebeam, Pmass, Nmass, Dmass,LightSpeed;
  Float_t Q2, Xbj, W,t_Pr,t_Ph,t_N,El_P,Phi_Pr,Phi_Ph, Phi_N,Angl_X_g,Angl_hg_hp,Xbal,Ybal,Zbal,Ebal,El_Theta, El_Phi,Pr_P,Pr_Theta,Pr_Phi,N_P,N_Theta,N_Phi,Ph_EC_P[40],Ph_EC_Theta[40],Ph_EC_Phi[40],Ph_FT_P[40],Ph_FT_Theta[40],Ph_FT_Phi[40],Ph_P,Ph_Theta,Ph_Phi;
  Float_t mm2_epg,mm2_eng,mm2_ep,mm2_eg;
  Float_t El_P_MC,El_Theta_MC,El_Phi_MC;
  Float_t Pr_P_MC,Pr_Theta_MC,Pr_Phi_MC;
  Float_t N_P_MC,N_Theta_MC,N_Phi_MC;
  Float_t Ph_P_MC,Ph_Theta_MC,Ph_Phi_MC; 
  Float_t Q2_MC, Xbj_MC, W_MC,t_Pr_MC,t_Ph_MC,t_N_MC,Phi_MC;
  Int_t n_spec,p_spec;

  Int_t clustering_finish_flag;
  Int_t cluster_subA, cluster_subB;
  Float_t clustering_closest_distance;

  //right now I don't know what these TF1 are (actually, I imagine that they are histograms showing the kinematic dependence of CND resolutions...) nor how to get them, so I simplify find_closest, just to proceed with the code - Rong please fix this//

  /* TF1 sigmaTheta("sigmaTheta","2.5"); */
  /* TF1 sigmaPhi("sigmaPhi","2.8"); */
  /* TF1 sigmaBeta("sigmaBeta","0.065*x"); */
  TLorentzVector ElectronBeam, Target_Vec,PTarget_Vec,NTarget_Vec;
  TLorentzVector El_Vec,Pr_Vec,N_Vec,Ph_IC_Vec[40],Ph_EC_Vec[40],Ph_Vec;
  TLorentzVector El_Vec_MC,Pr_Vec_MC,N_Vec_MC,Ph_Vec_MC;

  TVector3 pp;
  TVector3 PP[4];
  
  vector<double> cnd_trk_theta;
  vector<double> cnd_trk_phi;
  
  vector<double> cnd_hits_layer1_theta;
  vector<double> cnd_hits_layer1_phi;
  vector<double> cnd_hits_layer1_beta;
  vector<double> cnd_hits_layer2_theta;
  vector<double> cnd_hits_layer2_phi;
  vector<double> cnd_hits_layer2_beta;
  vector<double> cnd_hits_layer3_theta;
  vector<double> cnd_hits_layer3_phi;
  vector<double> cnd_hits_layer3_beta;
  
  vector<double> cnd_hits_theta;
  vector<double> cnd_hits_phi;
  vector<double> cnd_hits_beta;
  vector<double> cnd_neutron_px;
  vector<double> cnd_neutron_py;
  vector<double> cnd_neutron_pz;
  
  vector<double> trk_at_cnd_x;
  vector<double> trk_at_cnd_y;
  vector<double> trk_at_cnd_z;
  
  double thetan, phin, betan;
  double thetap, phip, betap;
  int pid[4];
  int veto_flag;
}
