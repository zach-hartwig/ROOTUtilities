int scopePlot(string FName, int Channels=1){

  const int Ch = Channels;

  const double s2ns = 1;//1e9;

  TGraph *G = new TGraph;

  C = new TCanvas("C","Tektronix Scope Plot",0,0,700,433);

  ///////////////////////////////////////
  // Read in the Tektronix format file //
  ///////////////////////////////////////

  ifstream Input(FName.c_str());

  int Point = 0;
  int LineNum = 0;
  string Line;


  for(int i=0; i<18; i++)
    getline(Input,Line);

  if(!Input.good()){
    cout << "\nError! File '" << FName << "'was not successfully opened!\n"
	 << endl;
    exit(-42);
  }
  else
    while(Input.good()){

      getline(Input, Line);

      if(Input.eof())
	break;

      istringstream SS(Line);
      string Token[2];

      getline(SS, Token[0], ',');
      getline(SS, Token[1], ',');
      
      size_t pos = Token[1].find("inf");
      if(pos != string::npos)
	continue;
      
      double X = atof(Token[0].c_str()) * s2ns;
      double Y = atof(Token[1].c_str()) + 0.12;

      if(LineNum % 500 == 0){
	G->SetPoint(Point, X, Y);		 
	Point++;
      }

      LineNum++;
    }

  G->RemovePoint(Point);
  G->RemovePoint(Point-1);

  G->Draw("ALP");
  G->SetTitle("Tektronix Scope Trace");
  G->SetLineColor(kBlue);
  G->SetLineWidth(2);
  G->GetXaxis()->SetTitle("Time [ns]");
  G->GetYaxis()->SetTitle("Voltage [V]");

  F = new TFile("~/test.root","recreate");
  G->Write("Trace");
  F->Write();
  F->Close();

  C->Update();

  return 0;
}
