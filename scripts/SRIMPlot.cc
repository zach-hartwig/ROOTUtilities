void SRIMPlot(string fname)
{
  const Double_t keV2MeV = 1e-3;
  const Double_t um2mm = 1e-3;
  
  vector<Double_t> energyVec, rangeVec, stoppingVec;
  
  bool beginDataRead = false;
  
  ifstream input(fname.c_str());

  string line;

  /////////////////////////////////////////////
  // Skip the SRIM output file header (5 lines)
  for(int i=0; i<5; i++)
    getline(input, line);


  ////////////////////////////////////////////////////////
  // Extract the plot title from the SRIM output file name
  getline(input, line);

  size_t start = line.find("\\");
  size_t end = line.find_last_of(".");
  cout << end << endl;

  
  ////////////////////////////////////////////////////////////
  // Extract the stopping/range data from the SRIM output file

  if(start != string::npos && end != string::npos){
    string Title = line.substr(start+1, (end-start-1));
  }
  else{
    cout << "\nError! Could not extract the file name from the SRIM output file title!\n"
	 <<   "       Will set to 'SRIM energy vs. depth'!\n"
	 << endl;
    Title = "SRIM energy vs. depth";
  }
  
  if(!input.is_open()){
    cout << "\nError! Could not find the file '" << FName << "'!\n"
	 << endl;
  }
  else{
    while(input.good()){

      getline(input, line);
      
      if(line.find("-----------  ---------- ---------- ----------  ----------  ----------")!=string::npos)
	beginDataRead = true;
      else if(beginDataRead){
	stringstream ss(line);
	
	if(line.find("-----------------------------------------------------------")!=string::npos)
	  break;
	
	double energy, dEdx_elec, dEdx_nucl, range, straggle_long, straggle_lat;
	string energy_unit, range_unit, straggle_long_unit, straggle_lat_unit;
	
	ss >> energy >> energy_unit 
	   >> dEdx_elec >> dEdx_nucl 
	   >> range >> range_unit 
	   >> straggle_long >> straggle_long_unit 
	   >> straggle_lat >> straggle_lat_unit;
	
	if(energy_unit=="keV")
	  energy*=keV2MeV;
	
	if(range_unit=="A")
	  range*=um2A;
	
	if(range_unit=="um")
	  range*=um2mm;

	energyVec.push_back(energy);
	rangeVec.push_back(range);
	stoppingVec.push_back(dEdx_elec + dEdx_nucl);
      }
    }

    vector<Double_t> distVec;
    vector<Double_t>::iterator it = rangeVec.begin();
    for(; it!=rangeVec.end(); it++)
      distVec.push_back(rangeVec.at(rangeVec.size()-1) - (*it));
    
    G = new TGraph(distVec.size(), &distVec[0], &energyVec[0]);
    G->SetLineColor(kBlue);
    G->SetLineWidth(2);
    G->Draw("AL");

    G->SetTitle(Title.c_str());
    G->GetXaxis()->SetTitle("Depth into material [mm]");
    G->GetXaxis()->SetTitleSize(0.055);
    G->GetXaxis()->SetNdivisions(510);

    G->GetYaxis()->SetTitle("Particle energy [MeV]");
    G->GetYaxis()->SetTitleSize(0.055);
    G->GetYaxis()->SetNdivisions(510);

    gPad->SetGrid(true, true);
  }
}
