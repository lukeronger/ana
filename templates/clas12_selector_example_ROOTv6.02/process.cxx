mySELECTOR::process(){
  /*
    This is where the process function
    for the generated TSelector would 
    go. Check ROOT documentation for
    more information.
  */
  fChain>GetTree()->GetEntry(entry);
  // CODE HERE
  nelec=0;
  i_el = -1;
  nprot=0;
  i_pr = -1;
  nneut=0;
  i_n=0;
  nphotEC=0;
  i_phEC = -1;
  nphotFT=0;
  i_phFT = -1;
  nphot=0;
  i_ph=-1;

  trk_at_cnd_x.clear();
  trk_at_cnd_y.clear();
  trk_at_cnd_z.clear();
  
  cnd_hits_layer1_theta.clear();
  cnd_hits_layer1_phi.clear();
  cnd_hits_layer1_beta.clear();
  cnd_hits_layer2_theta.clear();
  cnd_hits_layer2_phi.clear();
  cnd_hits_layer2_beta.clear();
  cnd_hits_layer3_theta.clear();
  cnd_hits_layer3_phi.clear();
  cnd_hits_layer3_beta.clear();
  
  cnd_hits_theta.clear();
  cnd_hits_phi.clear();
  cnd_hits_beta.clear();
  
  cnd_neutron_px.clear();
  cnd_neutron_py.clear();
  cnd_neutron_pz.clear();

  Calc_kine_MC(); 
  MC_tree->Fill();
  int size = static_cast<int>(REC_Particle_pid->size());

  for(int j=0;j<size;j++)
    {
      Float_t pmom[size];
      pmom[j]=TMath::Sqrt((*REC_Particle_px)[j]*(*REC_Particle_px)[j]+(*REC_Particle_py)[j]*(*REC_Particle_py)[j]+(*REC_Particle_pz)[j]*(*REC_Particle_pz)[j]);

      //electron ID
      if((*REC_Particle_charge)[j]<0 && (*REC_Particle_pid)[j]==11)
	{
	  nelec++;
	  i_el=j;
	  El_Vec.SetPxPyPzE((*REC_Particle_px)[j],(*REC_Particle_py)[j],(*REC_Particle_pz)[j],pmom[j]);
	  Q2 = 4*Ebeam*El_Vec.P()*TMath::Power(TMath::Sin(El_Vec.Theta()/2),2.);;
	  Float_t nu = Ebeam-El_P;
	  W = TMath::Sqrt(Pmass*Pmass + 2*Pmass*nu - Q2);
	  El_P = pmom[j];
	  Xbj = Q2/(2*Pmass*(Ebeam-El_P));
	  El_Theta = El_Vec.Theta()*180./TMath::Pi();
	  El_Phi = El_Vec.Phi()*180./TMath::Pi();
	}
      if(nelec>=1)
	{
	  //photon ID 
	  if(j!=i_el && (*REC_Particle_charge)[j]==0 && (*REC_Particle_pid)[j]==22)
	    {
	      nphot++;
	      i_ph=j;
	      Ph_Vec.SetPxPyPzE((*REC_Particle_px)[j],(*REC_Particle_py)[j],(*REC_Particle_pz)[j],pmom[j]);
	      Ph_P = Ph_Vec.E();
	      Ph_Theta = Ph_Vec.Theta()*180./TMath::Pi();
	      Ph_Phi = Ph_Vec.Phi()*180./TMath::Pi();  
	    }
	  //	  if(j!=i_el && j!=i_ph && (*REC_Particle_charge)[j]>0 && (*REC_Particle_pid)[j]==2112)
	  if(j!=i_el && j!=i_ph && (*REC_Track_q)[j]>0)
	    {
	      //proton ID
	      nprot++;
	      i_pr=j;
	      Pr_Vec.SetPxPyPzE((*REC_Particle_px)[j],(*REC_Particle_py)[j],(*REC_Particle_pz)[j],TMath::Sqrt(pmom[j]*pmom[j]+Pmass*Pmass));
	      Pr_P = pmom[j];
	      Pr_Theta = Pr_Vec.Theta()*180./TMath::Pi();
	      Pr_Phi = Pr_Vec.Phi()*180./TMath::Pi(); 
	    }
	  if(j!=i_el && j!=i_ph && j!=i_pr && TMath::Abs((*REC_Track_q)[j])!=1)
	    //here goes the neutron-ID cuts for CND (and EC should be here too) - Rong, please check and correct where I removed the "sigmas" parts
	    {
	      
	      for(int j=0;j<static_cast<int>(CND_hits_tx->size());j++){
		if(((*CND_hits_tx)[j]*(*CND_hits_tx)[j]+(*CND_hits_ty)[j]*(*CND_hits_ty)[j])>400){
		  trk_at_cnd_x.push_back((*CND_hits_tx)[j]);
		  trk_at_cnd_y.push_back((*CND_hits_ty)[j]);
		  trk_at_cnd_z.push_back((*CND_hits_tz)[j]);
		}
	      }
	      veto_flag = 0;
	      
	      for(int j=0;j<static_cast<int>(CND_hits_energy->size());j++){
		if((*CND_hits_energy)[j]>3){
		  for(int k=0;k<trk_at_cnd_x.size();k++)
			if(   fabs((*CND_hits_x)[j]-trk_at_cnd_x.at(k))<3.45
			      && fabs((*CND_hits_y)[j]-trk_at_cnd_y.at(k))<3.45
			      && fabs((*CND_hits_z)[j]-trk_at_cnd_z.at(k))<5.52 )veto_flag = 1;
		      if(veto_flag)continue;
		      if(((*CND_hits_time)[j]-124.25)>8)continue;
		      pp.SetXYZ((*CND_hits_x)[j], (*CND_hits_y)[j], (*CND_hits_z)[j]);
		      if((*CND_hits_layer)[j]==1){
			cnd_hits_layer1_theta.push_back(pp.Theta()*180/3.14159);
			cnd_hits_layer1_phi.push_back(pp.Phi()*180/3.14159);
			cnd_hits_layer1_beta.push_back(pp.Mag()/((*CND_hits_time)[j]-124.25)/30.0);
		      }
		      else if((*CND_hits_layer)[j]==2){
			cnd_hits_layer2_theta.push_back(pp.Theta()*180/3.14159);
			cnd_hits_layer2_phi.push_back(pp.Phi()*180/3.14159);
			cnd_hits_layer2_beta.push_back(pp.Mag()/((*CND_hits_time)[j]-124.25)/30.0);
		      }
		      else if((*CND_hits_layer)[j]==3){
			cnd_hits_layer3_theta.push_back(pp.Theta()*180/3.14159);
			cnd_hits_layer3_phi.push_back(pp.Phi()*180/3.14159);
			cnd_hits_layer3_beta.push_back(pp.Mag()/((*CND_hits_time)[j]-124.25)/30.0);
		      }
			}
		}
		
		///// clustering algoithm for neutral particles
		for(int j=0;j<cnd_hits_layer1_theta.size();j++){
		    if(cnd_hits_layer1_beta.at(j)>0.8 )continue;
		    cnd_hits_theta.push_back(cnd_hits_layer1_theta.at(j));
		    cnd_hits_phi.push_back(cnd_hits_layer1_phi.at(j));
		    cnd_hits_beta.push_back(cnd_hits_layer1_beta.at(j));
		  }
	      for(int j=0;j<cnd_hits_layer2_theta.size();j++){
		if(cnd_hits_layer2_beta.at(j)>0.8 )continue;
		cnd_hits_theta.push_back(cnd_hits_layer2_theta.at(j));
		cnd_hits_phi.push_back(cnd_hits_layer2_phi.at(j));
		cnd_hits_beta.push_back(cnd_hits_layer2_beta.at(j));
	      }
	      for(int j=0;j<cnd_hits_layer3_theta.size();j++){
		if(cnd_hits_layer3_beta.at(j)>0.8 )continue;
		cnd_hits_theta.push_back(cnd_hits_layer3_theta.at(j));
		cnd_hits_phi.push_back(cnd_hits_layer3_phi.at(j));
		cnd_hits_beta.push_back(cnd_hits_layer3_beta.at(j));
	      }
	      if(cnd_hits_theta.size()<1)continue;
	      else if(cnd_hits_theta.size()==1){
		double Pn = cnd_hits_beta.at(0)*0.939/sqrt(1-cnd_hits_beta.at(0)*cnd_hits_beta.at(0));
		cnd_neutron_px.push_back(Pn*sin(cnd_hits_theta.at(0)*3.14159/180.0)*cos(cnd_hits_phi.at(0)*3.14159/180.0)); 
		cnd_neutron_py.push_back(Pn*sin(cnd_hits_theta.at(0)*3.14159/180.0)*sin(cnd_hits_phi.at(0)*3.14159/180.0)); 
		cnd_neutron_pz.push_back(Pn*cos(cnd_hits_theta.at(0)*3.14159/180.0)); 
	      }
	      else if(cnd_hits_theta.size()==2){
		double distance = sqrt((cnd_hits_theta.at(0)-cnd_hits_theta.at(1))*(cnd_hits_theta.at(0)-cnd_hits_theta.at(1))
				       +(cnd_hits_phi.at(0)-cnd_hits_phi.at(1))*(cnd_hits_phi.at(0)-cnd_hits_phi.at(1))
				       +(cnd_hits_beta.at(0)-cnd_hits_beta.at(1))*(cnd_hits_beta.at(0)-cnd_hits_beta.at(1)));
		if(distance<5){
		  double beta_ave = (cnd_hits_beta.at(0)+cnd_hits_beta.at(1))/2.0;
		  double theta_ave = (cnd_hits_theta.at(0)+cnd_hits_theta.at(1))/2.0*3.14159/180.0;
		  double phi_ave = (cnd_hits_phi.at(0)+cnd_hits_phi.at(1))/2.0*3.14159/180.0;
		  double Pn = beta_ave*0.939/sqrt(1-beta_ave*beta_ave);
		  cnd_neutron_px.push_back(Pn*sin(theta_ave)*cos(phi_ave));
		  cnd_neutron_py.push_back(Pn*sin(theta_ave)*sin(phi_ave));
		  cnd_neutron_pz.push_back(Pn*cos(theta_ave));
		}
		else {
		  for(int j=0;j<cnd_hits_beta.size();j++){
		    double Pn = cnd_hits_beta.at(j)*0.939/sqrt(1-cnd_hits_beta.at(j)*cnd_hits_beta.at(j));
		    cnd_neutron_px.push_back(Pn*sin(cnd_hits_theta.at(j)*3.14159/180.0)*cos(cnd_hits_phi.at(j)*3.14159/180.0));
		    cnd_neutron_py.push_back(Pn*sin(cnd_hits_theta.at(j)*3.14159/180.0)*sin(cnd_hits_phi.at(j)*3.14159/180.0));
		    cnd_neutron_pz.push_back(Pn*cos(cnd_hits_theta.at(j)*3.14159/180.0));
		  }
		}
	      }
	      //// hierarchiral clustering
	      else if(cnd_hits_theta.size()>2){
		int cnd_hits_number_good = cnd_hits_theta.size();
		while(1){
		  clustering_closest_distance = 1e15;
		  cluster_subA = -1;
		  cluster_subB = -1;
		  find_closest(0, cnd_hits_theta, cnd_hits_phi, cnd_hits_beta);
		  if(cluster_subA==-1||cluster_subB==-1)break;
		  else{
		    int cnd_hits_number_good_now = cnd_hits_theta.size();
		    cnd_hits_theta.at(cluster_subA)=(cnd_hits_theta.at(cluster_subA)*(1+cnd_hits_number_good-cnd_hits_number_good_now)+cnd_hits_theta.at(cluster_subB))
		      /(2.0+cnd_hits_number_good-cnd_hits_number_good_now);
		    cnd_hits_phi.at(cluster_subA)=(cnd_hits_phi.at(cluster_subA)*(1+cnd_hits_number_good-cnd_hits_number_good_now)+cnd_hits_phi.at(cluster_subB))
		      /(2.0+cnd_hits_number_good-cnd_hits_number_good_now);
		    cnd_hits_beta.at(cluster_subA)=(cnd_hits_beta.at(cluster_subA)*(1+cnd_hits_number_good-cnd_hits_number_good_now)+cnd_hits_beta.at(cluster_subB))
		      /(2.0+cnd_hits_number_good-cnd_hits_number_good_now);
		    cnd_hits_theta.erase(cnd_hits_theta.begin()+cluster_subB); 
		    cnd_hits_phi.erase(cnd_hits_phi.begin()+cluster_subB); 
		    cnd_hits_beta.erase(cnd_hits_beta.begin()+cluster_subB); 
		  }            
		}
		for(int j=0;j<cnd_hits_beta.size();j++){
		  double Pn = cnd_hits_beta.at(j)*0.939/sqrt(1-cnd_hits_beta.at(j)*cnd_hits_beta.at(j));
		  cnd_neutron_px.push_back(Pn*sin(cnd_hits_theta.at(j)*3.14159/180.0)*cos(cnd_hits_phi.at(j)*3.14159/180.0));
		  cnd_neutron_py.push_back(Pn*sin(cnd_hits_theta.at(j)*3.14159/180.0)*sin(cnd_hits_phi.at(j)*3.14159/180.0));
		  cnd_neutron_pz.push_back(Pn*cos(cnd_hits_theta.at(j)*3.14159/180.0));
		}
	     }
	      for(int ii=0;ii<cnd_neutron_px.size();ii++){
		N_Vec.SetPxPyPzE(cnd_neutron_px.at(ii),cnd_neutron_py.at(ii),cnd_neutron_pz.at(ii),TMath::Sqrt(cnd_neutron_px.at(ii)*cnd_neutron_px.at(ii)+cnd_neutron_py.at(ii)*cnd_neutron_py.at(ii)+cnd_neutron_pz.at(ii)*cnd_neutron_pz.at(ii)+Nmass*Nmass));
		nneut++;
	      }		
	    }	  
	}
      Phi_Pr          = -900.;          // initialization - impossible value
      Phi_Ph          = -900.;          // initialization - impossible value
      Phi_N           = -900.;
      mm2_eng = -900;
      t_Pr = -900.;
      t_N = -900.;
      t_Ph= -900;

      if(nelec>=1 && nphot>=1 && nprot>=1)
	{
	  Calc_kine_P();
	  //	  DVCS_tree->Fill();
	}
      if(nelec>=1 && nphot>=1 && nneut>=1)
	{
	  Calc_kine_N();
	  //	  DVCS_tree->Fill();
	}      
      if(nelec>=1)DVCS_tree->Fill();
    }  
   
  return kTRUE;  
}
